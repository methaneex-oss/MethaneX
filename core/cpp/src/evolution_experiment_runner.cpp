#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_trials.hpp"

#include <bit>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

#ifndef JARVIS_EVOLUTION_EVALUATOR_PATH
#define JARVIS_EVOLUTION_EVALUATOR_PATH ""
#endif

namespace jarvis::core {
namespace {
constexpr const char* kProcedure = "linear-weight-mse-v1";

std::string number(double value) {
    std::ostringstream out;
    out << std::setprecision(17) << value;
    return out.str();
}

bool parse_fitness(const ProcessIsolationResult& result, double& fitness) {
    if (!result.started || !result.isolated || !result.completed ||
        result.timed_out || result.output_limited || result.exit_code != 0 ||
        result.output.empty()) return false;
    try {
        std::size_t parsed = 0;
        fitness = std::stod(result.output, &parsed);
        while (parsed < result.output.size() &&
               (result.output[parsed] == ' ' || result.output[parsed] == '\\n' ||
                result.output[parsed] == '\\r' || result.output[parsed] == '\\t')) ++parsed;
        return parsed == result.output.size() && std::isfinite(fitness) &&
               fitness >= 0.0 && fitness <= 1.0;
    } catch (...) {
        return false;
    }
}

std::string digest_cases(const EvolutionExperiment& experiment,
                         const std::vector<EvolutionFitnessCase>& cases) {
    // Stable identity checksum (not a security signature). Trust comes from
    // using the fixed, repository-built evaluator; this binds its inputs.
    std::uint64_t hash = 14695981039346656037ULL;
    const auto mix = [&hash](const void* bytes, std::size_t size) {
        const auto* data = static_cast<const unsigned char*>(bytes);
        for (std::size_t i = 0; i < size; ++i) {
            hash ^= data[i];
            hash *= 1099511628211ULL;
        }
    };
    const auto mix_string = [&mix](const std::string& value) {
        const std::uint64_t size = value.size();
        mix(&size, sizeof(size));
        mix(value.data(), value.size());
    };
    const auto mix_double = [&mix](double value) {
        const auto bits = std::bit_cast<std::uint64_t>(value);
        mix(&bits, sizeof(bits));
    };
    mix_string(kProcedure);
    mix_string(experiment.id);
    mix_string(experiment.proposal.key);
    mix_double(experiment.proposal.current);
    mix_double(experiment.proposal.proposed);
    mix_double(experiment.proposal.expected_gain);
    mix_double(experiment.proposal.confidence);
    for (const auto& item : cases) {
        mix_double(item.feature);
        mix_double(item.target);
    }
    std::ostringstream out;
    out << std::hex << std::setw(16) << std::setfill('0') << hash;
    return out.str();
}

bool measure_parameter(const ProcessIsolationBackend& backend, double parameter,
                       const std::vector<EvolutionFitnessCase>& cases,
                       std::vector<double>& results) {
    if (std::string(JARVIS_EVOLUTION_EVALUATOR_PATH).empty()) return false;
    results.clear();
    results.reserve(cases.size());
    for (const auto& item : cases) {
        if (!std::isfinite(item.feature) || !std::isfinite(item.target)) return false;
        IsolatedCommand command;
        command.executable = JARVIS_EVOLUTION_EVALUATOR_PATH;
        command.arguments = {kProcedure, number(parameter),
                             number(item.feature), number(item.target)};
        double fitness = 0.0;
        if (!parse_fitness(backend.run(command), fitness)) return false;
        results.push_back(fitness);
    }
    return true;
}

bool close_enough(double left, double right) {
    return std::isfinite(left) && std::isfinite(right) &&
           std::abs(left - right) <= 1e-12;
}
} // namespace

ExperimentOutcome EvolutionExperimentRunner::run(
    EvolutionExperiment& experiment, const EvolutionSandbox& sandbox,
    const CandidateExecutor& executor) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    const auto result = sandbox.run(experiment.proposal, executor);
    if (!result.started || !result.completed || result.timed_out ||
        result.output_limited || !std::isfinite(result.fitness)) return experiment.outcome;
    experiment.candidate_fitness = result.fitness;
    experiment.candidate_executed = true;
    experiment.isolated = false; // simulation is never production evidence
    return EvolutionExperimentEngine::evaluate(experiment);
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_command(
    EvolutionExperiment& experiment, const ProcessIsolationBackend&,
    const IsolatedCommand&) noexcept {
    // Arbitrary executable output cannot establish which candidate was tested
    // or whether baseline and candidate used the same evaluation procedure.
    // Keep this API fail-closed; production evidence uses the repository-owned
    // evaluator below, which binds the proposal to the actual held-out inputs.
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.evaluation_procedure.clear();
    experiment.evaluation_digest.clear();
    experiment.outcome = ExperimentOutcome::Invalid;
    return experiment.outcome;
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_evaluation(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const std::vector<EvolutionFitnessCase>& cases) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.evaluation_procedure.clear();
    experiment.evaluation_digest.clear();
    experiment.outcome = ExperimentOutcome::Invalid;
    if (cases.size() < 2 || experiment.id.empty() ||
        experiment.proposal.key.empty() ||
        !std::isfinite(experiment.proposal.current) ||
        !std::isfinite(experiment.proposal.proposed) ||
        !std::isfinite(experiment.minimum_improvement) ||
        experiment.minimum_improvement < 0.0) return experiment.outcome;

    std::vector<double> baseline_results;
    std::vector<double> candidate_results;
    if (!measure_parameter(backend, experiment.proposal.current, cases, baseline_results) ||
        !measure_parameter(backend, experiment.proposal.proposed, cases, candidate_results))
        return experiment.outcome;

    const auto baseline = EvolutionTrials::summarize(baseline_results);
    const auto candidate = EvolutionTrials::summarize(candidate_results);
    if (baseline.count < 2 || candidate.count < 2) return experiment.outcome;

    experiment.baseline_fitness = baseline.mean;
    experiment.candidate_fitness = candidate.mean;
    experiment.confidence = std::min(baseline.confidence, candidate.confidence);
    experiment.candidate_executed = true;
    experiment.isolated = true;
    experiment.evaluation_cases = cases;
    experiment.evaluation_procedure = kProcedure;
    experiment.evaluation_digest = digest_cases(experiment, cases);
    experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (experiment.outcome != ExperimentOutcome::Invalid)
        experiment.attest_isolated_result();
    else {
        experiment.candidate_executed = false;
        experiment.isolated = false;
    }
    return experiment.outcome;
}

bool EvolutionExperimentRunner::revalidate_isolated_evaluation(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend) noexcept {
    const auto stored_procedure = experiment.evaluation_procedure;
    const auto stored_digest = experiment.evaluation_digest;
    const double stored_baseline = experiment.baseline_fitness;
    const double stored_candidate = experiment.candidate_fitness;
    const double stored_confidence = experiment.confidence;
    const auto stored_outcome = experiment.outcome;
    const auto cases = experiment.evaluation_cases;
    if (stored_procedure != kProcedure || stored_digest.empty() || cases.size() < 2)
        return false;

    EvolutionExperiment recomputed = experiment;
    if (run_isolated_evaluation(recomputed, backend, cases) == ExperimentOutcome::Invalid)
        return false;
    if (recomputed.evaluation_procedure != stored_procedure ||
        recomputed.evaluation_digest != stored_digest ||
        recomputed.outcome != stored_outcome ||
        !close_enough(recomputed.baseline_fitness, stored_baseline) ||
        !close_enough(recomputed.candidate_fitness, stored_candidate) ||
        !close_enough(recomputed.confidence, stored_confidence)) return false;
    experiment = std::move(recomputed);
    return experiment.has_valid_isolation_attestation();
}

} // namespace jarvis::core
