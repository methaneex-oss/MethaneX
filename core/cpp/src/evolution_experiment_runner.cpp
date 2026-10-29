#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>

namespace jarvis::core {
namespace {

std::string fingerprint(const std::string& value) {
    // Stable identity fingerprint, not a cryptographic signature. Trust comes
    // from the locally configured evaluator procedure, not from this digest.
    std::uint64_t hash = 14695981039346656037ULL;
    for (const unsigned char byte : value) {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
    std::ostringstream out;
    out << std::hex << std::setw(16) << std::setfill('0') << hash;
    return out.str();
}

bool safe_field(const std::string& value) {
    return !value.empty() && value.find_first_of("\\r\\n") == std::string::npos;
}

bool parse_measurement(const ProcessIsolationResult& result,
                       const EvolutionExperiment& experiment,
                       const std::string& procedure_id,
                       const std::string& role,
                       double parameter_value,
                       double& fitness) {
    if (!result.started || !result.isolated || !result.completed ||
        result.timed_out || result.output_limited || result.exit_code != 0) return false;

    std::istringstream input(result.output);
    std::string line;
    if (!std::getline(input, line) || line != "JARVIS_EVALUATION_V1") return false;
    std::map<std::string, std::string> fields;
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\\r') line.pop_back();
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
    const auto* artifact = field("artifact_id");
    const auto* measured = field("fitness");
    if (id == nullptr || key == nullptr || value == nullptr || output_role == nullptr ||
        procedure == nullptr || artifact == nullptr || measured == nullptr ||
        *id != experiment.id || *key != experiment.proposal.key ||
        *output_role != role || *procedure != procedure_id ||
        *artifact != fingerprint(experiment.proposal.key + "\\x1f" +
                                 std::to_string(parameter_value) + "\\x1f" + procedure_id))
        return false;
    try {
        std::size_t used = 0;
        const double echoed_value = std::stod(*value, &used);
        if (used != value->size() || !std::isfinite(echoed_value) ||
            echoed_value != parameter_value) return false;
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
                     double& fitness) {
    IsolatedCommand invocation = command;
    const auto artifact = fingerprint(experiment.proposal.key + "\\x1f" +
                                      std::to_string(parameter_value) + "\\x1f" +
                                      command.evaluation_procedure_id);
    invocation.arguments.push_back("--jarvis-evaluation-v1");
    invocation.arguments.push_back("--experiment-id=" + experiment.id);
    invocation.arguments.push_back("--parameter-key=" + experiment.proposal.key);
    invocation.arguments.push_back("--parameter-value=" + std::to_string(parameter_value));
    invocation.arguments.push_back("--role=" + role);
    invocation.arguments.push_back("--procedure-id=" + command.evaluation_procedure_id);
    invocation.arguments.push_back("--artifact-id=" + artifact);
    const auto result = backend.run(invocation);
    return parse_measurement(result, experiment, command.evaluation_procedure_id,
                             role, parameter_value, fitness);
}

} // namespace

ExperimentOutcome EvolutionExperimentRunner::run(EvolutionExperiment& experiment,
                                                  const EvolutionSandbox& sandbox,
                                                  const CandidateExecutor& executor) noexcept {
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
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    if (!safe_field(experiment.id) || !safe_field(experiment.proposal.key) ||
        !safe_field(command.evaluation_procedure_id)) return experiment.outcome;

    // The evaluator must measure both settings through the same named local
    // procedure. A command that merely prints a numeric fitness is not evidence.
    double baseline_fitness = 0.0;
    double candidate_fitness = 0.0;
    if (!run_measurement(experiment, backend, command, "baseline",
                         experiment.proposal.current, baseline_fitness) ||
        !run_measurement(experiment, backend, command, "candidate",
                         experiment.proposal.proposed, candidate_fitness)) {
        return experiment.outcome;
    }

    experiment.baseline_fitness = baseline_fitness;
    experiment.candidate_fitness = candidate_fitness;
    experiment.evaluation_procedure_id = command.evaluation_procedure_id;
    experiment.baseline_artifact_id = fingerprint(
        experiment.proposal.key + "\\x1f" +
        std::to_string(experiment.proposal.current) + "\\x1f" +
        command.evaluation_procedure_id);
    experiment.candidate_artifact_id = fingerprint(
        experiment.proposal.key + "\\x1f" +
        std::to_string(experiment.proposal.proposed) + "\\x1f" +
        command.evaluation_procedure_id);
    experiment.candidate_executed = true;
    experiment.isolated = true;
    experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (experiment.outcome != ExperimentOutcome::Invalid)
        experiment.attest_isolated_result();
    return experiment.outcome;
}

} // namespace jarvis::core
