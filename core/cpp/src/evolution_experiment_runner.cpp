#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <map>
#include <mutex>
#include <sstream>
#include <unordered_map>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <string>

namespace jarvis::core {
namespace {

std::string fingerprint(const std::string& value) {
    return EvolutionExperiment::artifact_fingerprint(value);
}

bool safe_field(const std::string& value) {
    return !value.empty() && value.find_first_of("\r\n") == std::string::npos;
}

bool is_interpreter(const std::string& executable) {
    const auto name = std::filesystem::path(executable).filename().string();
    return name == "sh" || name == "bash" || name == "dash" ||
           name == "zsh" || name == "fish" || name == "cmd.exe" ||
           name == "powershell" || name == "pwsh";
}

struct TrustedEvaluator {
    std::string executable;
    std::string fingerprint;
    std::vector<std::string> arguments;
};
std::mutex trusted_evaluators_mutex;
std::unordered_map<std::string, TrustedEvaluator> trusted_evaluators;
std::mutex evidence_key_mutex;
std::string evidence_authentication_key;

std::string evidence_payload(const EvolutionExperiment& e) {
    std::string payload;
    const auto field = [&payload](const std::string& value) {
        payload += std::to_string(value.size());
        payload.push_back(':');
        payload += value;
    };
    field("jarvis-evolution-evidence-v1");
    field(e.id); field(e.proposal.key);
    field(EvolutionExperiment::format_parameter_value(e.proposal.current));
    field(EvolutionExperiment::format_parameter_value(e.proposal.proposed));
    field(EvolutionExperiment::format_parameter_value(e.proposal.expected_gain));
    field(EvolutionExperiment::format_parameter_value(e.proposal.confidence));
    field(EvolutionExperiment::format_parameter_value(e.baseline_fitness));
    field(EvolutionExperiment::format_parameter_value(e.candidate_fitness));
    field(EvolutionExperiment::format_parameter_value(e.minimum_improvement));
    field(EvolutionExperiment::format_parameter_value(e.confidence));
    field(std::to_string(static_cast<int>(e.outcome)));
    field(e.candidate_executed ? "1" : "0"); field(e.isolated ? "1" : "0");
    field(e.evaluation_procedure_id); field(e.evaluator_executable_fingerprint);
    field(e.baseline_artifact_id); field(e.candidate_artifact_id);
    return payload;
}

std::string evidence_mac(const EvolutionExperiment& e, const std::string& key) {
    unsigned char digest[EVP_MAX_MD_SIZE]{};
    unsigned int digest_size = 0;
    const auto payload = evidence_payload(e);
    if (HMAC(EVP_sha256(), key.data(), static_cast<int>(key.size()),
             reinterpret_cast<const unsigned char*>(payload.data()), payload.size(),
             digest, &digest_size) == nullptr || digest_size != 32) return {};
    static constexpr char hex[] = "0123456789abcdef";
    std::string result;
    result.reserve(digest_size * 2);
    for (unsigned int i = 0; i < digest_size; ++i) {
        result.push_back(hex[digest[i] >> 4]);
        result.push_back(hex[digest[i] & 0x0f]);
    }
    return result;
}

bool valid_evidence_mac(const EvolutionExperiment& e, const std::string& key) {
    const auto expected = evidence_mac(e, key);
    if (expected.empty() || e.evidence_authentication.size() != expected.size()) return false;
    return CRYPTO_memcmp(expected.data(), e.evidence_authentication.data(), expected.size()) == 0;
}

bool parse_measurement(const ProcessIsolationResult& result,
                       const EvolutionExperiment& experiment,
                       const std::string& procedure_id,
                       const std::string& role,
                       double parameter_value,
                       std::size_t trial_index,
                       double& fitness) {
    if (!result.started || !result.isolated || !result.completed ||
        result.timed_out || result.output_limited || result.exit_code != 0) return false;

    std::istringstream input(result.output);
    std::string line;
    if (!std::getline(input, line) || line != "JARVIS_EVALUATION_V1") return false;
    std::map<std::string, std::string> fields;
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        const auto separator = line.find('=');
        if (separator == std::string::npos || separator == 0 ||
            !fields.emplace(line.substr(0, separator), line.substr(separator + 1)).second)
            return false;
    }
    const auto field = [&](const char* key) -> const std::string* {
        const auto it = fields.find(key);
        return it == fields.end() ? nullptr : &it->second;
    };
    const auto* id = field("experiment_id");
    const auto* key = field("parameter_key");
    const auto* value = field("parameter_value");
    const auto* output_role = field("role");
    const auto* procedure = field("procedure_id");
    const auto* evaluator_fingerprint = field("evaluator_fingerprint");
    const auto* artifact = field("artifact_id");
    const auto* measured = field("fitness");
    const auto* trial = field("trial_index");
    if (id == nullptr || key == nullptr || value == nullptr || output_role == nullptr ||
        procedure == nullptr || evaluator_fingerprint == nullptr ||
        artifact == nullptr || measured == nullptr || trial == nullptr ||
        *id != experiment.id || *key != experiment.proposal.key ||
        *output_role != role || *procedure != procedure_id ||
        *evaluator_fingerprint != experiment.evaluator_executable_fingerprint ||
        *trial != std::to_string(trial_index) ||
        *artifact != fingerprint(experiment.proposal.key + "\x1f" +
                                 EvolutionExperiment::format_parameter_value(parameter_value) + "\x1f" + procedure_id))
        return false;
    try {
        std::size_t used = 0;
        const double echoed_value = std::stod(*value, &used);
        // The protocol intentionally serializes parameters in the canonical
        // decimal form; compare that representation instead of requiring a
        // lossy decimal round-trip to reproduce the original binary double.
        if (used != value->size() || !std::isfinite(echoed_value) ||
            *value != EvolutionExperiment::format_parameter_value(parameter_value) ||
            echoed_value != std::stod(EvolutionExperiment::format_parameter_value(parameter_value)))
            return false;
        used = 0;
        fitness = std::stod(*measured, &used);
        return used == measured->size() && std::isfinite(fitness);
    } catch (...) {
        return false;
    }
}

bool run_measurement(const EvolutionExperiment& experiment,
                     const ProcessIsolationBackend& backend,
                     const IsolatedCommand& command,
                     const std::string& role,
                     double parameter_value,
                     std::size_t trial_index,
                     double& fitness) {
    // Recheck before each measurement so baseline/candidate cannot silently
    // use different evaluator binaries if the configured executable changes.
    if (EvolutionExperimentRunner::executable_fingerprint(command.executable) !=
        command.expected_executable_fingerprint) return false;
    IsolatedCommand invocation = command;
    const auto artifact = fingerprint(experiment.proposal.key + "\x1f" +
                                      EvolutionExperiment::format_parameter_value(parameter_value) + "\x1f" +
                                      command.evaluation_procedure_id);
    invocation.arguments.push_back("--jarvis-evaluation-v1");
    invocation.arguments.push_back("--experiment-id=" + experiment.id);
    invocation.arguments.push_back("--parameter-key=" + experiment.proposal.key);
    invocation.arguments.push_back("--parameter-value=" + EvolutionExperiment::format_parameter_value(parameter_value));
    invocation.arguments.push_back("--role=" + role);
    invocation.arguments.push_back("--procedure-id=" + command.evaluation_procedure_id);
    invocation.arguments.push_back("--evaluator-fingerprint=" + command.expected_executable_fingerprint);
    invocation.arguments.push_back("--artifact-id=" + artifact);
    invocation.arguments.push_back("--trial-index=" + std::to_string(trial_index));
    const auto result = backend.run(invocation);
    return parse_measurement(result, experiment, command.evaluation_procedure_id,
                             role, parameter_value, trial_index, fitness);
}

} // namespace

bool EvolutionExperimentRunner::register_trusted_evaluator(
    const std::string& procedure_id, const std::string& executable,
    const std::vector<std::string>& procedure_arguments) noexcept {
    if (!safe_field(procedure_id) || executable.empty() || is_interpreter(executable)) return false;
    const auto digest = executable_fingerprint(executable);
    if (digest.empty()) return false;
    try {
        std::lock_guard<std::mutex> lock(trusted_evaluators_mutex);
        const auto existing = trusted_evaluators.find(procedure_id);
        if (existing != trusted_evaluators.end())
            return existing->second.executable == executable &&
                   existing->second.fingerprint == digest &&
                   existing->second.arguments == procedure_arguments;
        trusted_evaluators.emplace(procedure_id, TrustedEvaluator{executable, digest, procedure_arguments});
        return true;
    } catch (...) {
        return false;
    }
}

bool EvolutionExperimentRunner::is_trusted_evaluator(
    const std::string& procedure_id, const std::string& executable,
    const std::string& expected_fingerprint) noexcept {
    try {
        std::lock_guard<std::mutex> lock(trusted_evaluators_mutex);
        const auto existing = trusted_evaluators.find(procedure_id);
        if (existing == trusted_evaluators.end() ||
            existing->second.fingerprint != expected_fingerprint ||
            (!executable.empty() && existing->second.executable != executable)) return false;
        return executable_fingerprint(existing->second.executable) == existing->second.fingerprint;
    } catch (...) {
        return false;
    }
}

bool EvolutionExperimentRunner::is_trusted_evaluator(
    const std::string& procedure_id, const std::string& executable,
    const std::string& expected_fingerprint,
    const std::vector<std::string>& procedure_arguments) noexcept {
    try {
        std::lock_guard<std::mutex> lock(trusted_evaluators_mutex);
        const auto existing = trusted_evaluators.find(procedure_id);
        if (existing == trusted_evaluators.end() ||
            existing->second.fingerprint != expected_fingerprint ||
            existing->second.arguments != procedure_arguments ||
            (!executable.empty() && existing->second.executable != executable)) return false;
        return executable_fingerprint(existing->second.executable) == existing->second.fingerprint;
    } catch (...) {
        return false;
    }
}

bool EvolutionExperimentRunner::set_evidence_authentication_key(
    const std::string& key) noexcept {
    if (key.size() < 32) return false;
    try {
        std::lock_guard<std::mutex> lock(evidence_key_mutex);
        if (!evidence_authentication_key.empty())
            return evidence_authentication_key == key;
        evidence_authentication_key = key;
        return true;
    } catch (...) {
        return false;
    }
}

bool EvolutionExperimentRunner::authenticate_persisted_evidence(
    EvolutionExperiment& experiment) noexcept {
    if (!experiment.has_valid_isolation_attestation() ||
        !is_trusted_evaluator(experiment.evaluation_procedure_id, {},
                              experiment.evaluator_executable_fingerprint)) return false;
    try {
        std::lock_guard<std::mutex> lock(evidence_key_mutex);
        if (evidence_authentication_key.size() < 32) return false;
        const auto signature = evidence_mac(experiment, evidence_authentication_key);
        if (signature.empty()) return false;
        experiment.evidence_authentication = signature;
        return true;
    } catch (...) {
        return false;
    }
}

bool EvolutionExperimentRunner::restore_trusted_attestation(
    EvolutionExperiment& experiment) noexcept {
    try {
        std::lock_guard<std::mutex> lock(evidence_key_mutex);
        if (evidence_authentication_key.size() < 32 ||
            !valid_evidence_mac(experiment, evidence_authentication_key) ||
            !is_trusted_evaluator(experiment.evaluation_procedure_id, {},
                                  experiment.evaluator_executable_fingerprint)) return false;
        experiment.attest_isolated_result();
        return experiment.has_valid_isolation_attestation();
    } catch (...) {
        return false;
    }
}

std::string EvolutionExperimentRunner::executable_fingerprint(
    const std::string& executable) noexcept {
    try {
        std::ifstream input(executable, std::ios::binary);
        if (!input) return {};
        std::uint64_t hash = 14695981039346656037ULL;
        char buffer[8192];
        while (input) {
            input.read(buffer, sizeof(buffer));
            const auto count = input.gcount();
            for (std::streamsize i = 0; i < count; ++i) {
                hash ^= static_cast<unsigned char>(buffer[i]);
                hash *= 1099511628211ULL;
            }
        }
        if (input.bad()) return {};
        return std::to_string(hash);
    } catch (...) {
        return {};
    }
}

ExperimentOutcome EvolutionExperimentRunner::run(EvolutionExperiment& experiment,
                                                  const EvolutionSandbox& sandbox,
                                                  const CandidateExecutor& executor) noexcept {
    experiment.clear_isolation_attestation();
    experiment.candidate_executed = false;
    experiment.isolated = false;
    const auto result = sandbox.run(experiment.proposal, executor);
    if (!result.started || !result.completed || result.timed_out || result.output_limited ||
        !std::isfinite(result.fitness)) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    experiment.candidate_fitness = result.fitness;
    experiment.candidate_executed = true;
    experiment.isolated = false; // callback results are not trusted isolation evidence
    return EvolutionExperimentEngine::evaluate(experiment);
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_command(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedCommand& command) noexcept {
    experiment.clear_isolation_attestation();
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    if (!backend.limits().require_no_new_privileges ||
        !backend.limits().require_network_syscall_block ||
        !safe_field(experiment.id) || !safe_field(experiment.proposal.key) ||
        !safe_field(command.evaluation_procedure_id) ||
        command.expected_executable_fingerprint.empty() ||
        is_interpreter(command.executable) ||
        !is_trusted_evaluator(command.evaluation_procedure_id, command.executable,
                              command.expected_executable_fingerprint, command.arguments))
        return experiment.outcome;
    // The response parser validates the evaluator identity against the active
    // experiment. Populate the expected identity before either measurement;
    // assigning it only after parsing makes every valid response look untrusted.
    experiment.evaluation_procedure_id = command.evaluation_procedure_id;
    experiment.evaluator_executable_fingerprint = command.expected_executable_fingerprint;

    // The evaluator must measure both settings through the same named local
    // procedure. A command that merely prints a numeric fitness is not evidence.
    double baseline_fitness = 0.0;
    double candidate_fitness = 0.0;
    if (!run_measurement(experiment, backend, command, "baseline",
                         experiment.proposal.current, command.trial_index, baseline_fitness) ||
        !run_measurement(experiment, backend, command, "candidate",
                         experiment.proposal.proposed, command.trial_index, candidate_fitness)) {
        return experiment.outcome;
    }

    experiment.baseline_fitness = baseline_fitness;
    experiment.candidate_fitness = candidate_fitness;
    experiment.evaluation_procedure_id = command.evaluation_procedure_id;
    experiment.evaluator_executable_fingerprint = command.expected_executable_fingerprint;
    experiment.baseline_artifact_id = fingerprint(
        experiment.proposal.key + "\x1f" +
        EvolutionExperiment::format_parameter_value(experiment.proposal.current) + "\x1f" +
        command.evaluation_procedure_id);
    experiment.candidate_artifact_id = fingerprint(
        experiment.proposal.key + "\x1f" +
        EvolutionExperiment::format_parameter_value(experiment.proposal.proposed) + "\x1f" +
        command.evaluation_procedure_id);
    experiment.candidate_executed = true;
    experiment.isolated = true;
    experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (experiment.outcome != ExperimentOutcome::Invalid)
        experiment.attest_isolated_result();
    return experiment.outcome;
}

} // namespace jarvis::core
