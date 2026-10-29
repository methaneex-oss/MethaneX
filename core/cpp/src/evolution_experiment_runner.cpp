#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

namespace jarvis::core {
namespace {
std::string candidate_identity(const EvolutionProposal& proposal) {
    std::ostringstream out;
    out << proposal.key << "|current=" << std::setprecision(17) << proposal.current
        << "|proposed=" << std::setprecision(17) << proposal.proposed;
    return out.str();
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


ExperimentOutcome EvolutionExperimentRunner::run_isolated_evaluator(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const std::string& procedure_id, const LocalFitnessProcedure& procedure,
    std::size_t baseline_trials, std::size_t candidate_trials,
    double minimum_confidence) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.evaluation_procedure_id.clear();
    experiment.candidate_artifact_id.clear();
    experiment.outcome = ExperimentOutcome::Invalid;
    if (procedure_id.empty() || !procedure || baseline_trials < 2 ||
        candidate_trials < 2 || !std::isfinite(minimum_confidence) ||
        minimum_confidence < 0.0 || minimum_confidence > 1.0) return experiment.outcome;

    std::vector<double> baseline;
    std::vector<double> candidate;
    baseline.reserve(baseline_trials);
    candidate.reserve(candidate_trials);
    for (std::size_t i = 0; i < baseline_trials; ++i) {
        const auto measured = backend.run_evaluator(
            procedure, experiment.proposal, experiment.proposal.current);
        if (!measured.started || !measured.completed || !measured.isolated ||
            !std::isfinite(measured.fitness)) return experiment.outcome;
        baseline.push_back(measured.fitness);
    }
    for (std::size_t i = 0; i < candidate_trials; ++i) {
        const auto measured = backend.run_evaluator(
            procedure, experiment.proposal, experiment.proposal.proposed);
        if (!measured.started || !measured.completed || !measured.isolated ||
            !std::isfinite(measured.fitness)) return experiment.outcome;
        candidate.push_back(measured.fitness);
    }

    const auto baseline_stats = EvolutionTrials::summarize(baseline);
    const auto candidate_stats = EvolutionTrials::summarize(candidate);
    experiment.baseline_fitness = baseline_stats.mean;
    experiment.candidate_fitness = candidate_stats.mean;
    experiment.confidence = std::min(baseline_stats.confidence, candidate_stats.confidence);
    experiment.candidate_executed = true;
    experiment.isolated = true;
    experiment.evaluation_procedure_id = procedure_id;
    experiment.candidate_artifact_id = candidate_identity(experiment.proposal);
    experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (experiment.outcome == ExperimentOutcome::Improved &&
        !EvolutionTrials::supports_adoption(baseline_stats, candidate_stats,
                                            experiment.minimum_improvement,
                                            minimum_confidence)) {
        experiment.outcome = ExperimentOutcome::Neutral;
    }
    if (experiment.outcome != ExperimentOutcome::Invalid)
        experiment.attest_isolated_result();
    return experiment.outcome;
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_command(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedCommand& command) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    const auto result = backend.run(command);
    if (!result.started || !result.isolated || !result.completed || result.timed_out ||
        result.output_limited || result.exit_code != 0 || result.output.empty()) {
        return experiment.outcome;
    }
    try {
        std::size_t parsed = 0;
        const double fitness = std::stod(result.output, &parsed);
        while (parsed < result.output.size() &&
               (result.output[parsed] == ' ' || result.output[parsed] == '\n' ||
                result.output[parsed] == '\r' || result.output[parsed] == '\t')) ++parsed;
        if (parsed != result.output.size() || !std::isfinite(fitness)) return experiment.outcome;
        experiment.candidate_fitness = fitness;
        experiment.candidate_executed = true;
        experiment.isolated = true;
        // Numeric stdout proves only that a process printed a number.
        // It cannot mint trusted evaluation evidence.
        experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
        return experiment.outcome;
    } catch (...) {
        experiment.candidate_executed = false;
        experiment.isolated = false;
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }
}

} // namespace jarvis::core
