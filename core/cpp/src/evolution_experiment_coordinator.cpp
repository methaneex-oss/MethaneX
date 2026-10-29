#include "jarvis/core/evolution_experiment_coordinator.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

EvolutionTrialBatch EvolutionExperimentCoordinator::run(
    EvolutionExperiment& experiment,
    const EvolutionSandbox& sandbox,
    const CandidateExecutor& baseline_executor,
    const CandidateExecutor& candidate_executor,
    EvolutionTrialConfig config) noexcept {
    EvolutionTrialBatch batch;
    if (config.baseline_trials == 0 || config.candidate_trials == 0 ||
        !std::isfinite(config.minimum_improvement) || config.minimum_improvement < 0.0 ||
        !std::isfinite(config.minimum_confidence) || config.minimum_confidence < 0.0 ||
        config.minimum_confidence > 1.0) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return batch;
    }

    std::vector<double> baseline;
    std::vector<double> candidate;
    bool all_trials_isolated = true;
    baseline.reserve(config.baseline_trials);
    candidate.reserve(config.candidate_trials);

    for (std::size_t i = 0; i < config.baseline_trials; ++i) {
        const auto result = sandbox.run(experiment.proposal, baseline_executor);
        if (!result.started || !result.completed || result.timed_out || result.output_limited ||
            (config.require_isolation && !result.isolated) || !std::isfinite(result.fitness)) {
            experiment.outcome = ExperimentOutcome::Invalid;
            return batch;
        }
        all_trials_isolated = all_trials_isolated && result.isolated;
        baseline.push_back(result.fitness);
    }

    for (std::size_t i = 0; i < config.candidate_trials; ++i) {
        const auto result = sandbox.run(experiment.proposal, candidate_executor);
        if (!result.started || !result.completed || result.timed_out || result.output_limited ||
            (config.require_isolation && !result.isolated) || !std::isfinite(result.fitness)) {
            experiment.outcome = ExperimentOutcome::Invalid;
            return batch;
        }
        all_trials_isolated = all_trials_isolated && result.isolated;
        candidate.push_back(result.fitness);
    }

    batch.baseline = EvolutionTrials::summarize(baseline);
    batch.candidate = EvolutionTrials::summarize(candidate);
    if (batch.baseline.count < 2 || batch.candidate.count < 2) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return batch;
    }

    experiment.baseline_fitness = batch.baseline.mean;
    experiment.candidate_fitness = batch.candidate.mean;
    experiment.minimum_improvement = config.minimum_improvement;
    experiment.confidence = std::min(batch.baseline.confidence, batch.candidate.confidence);
    experiment.candidate_executed = true;
    experiment.isolated = all_trials_isolated;
    batch.executed = true;

    if (!EvolutionTrials::supports_adoption(batch.baseline, batch.candidate,
                                            config.minimum_improvement,
                                            config.minimum_confidence)) {
        const double gain = batch.candidate.mean - batch.baseline.mean;
        experiment.outcome = gain < -config.minimum_improvement
            ? ExperimentOutcome::Degraded
            : ExperimentOutcome::Neutral;
        batch.outcome = experiment.outcome;
        if (experiment.isolated) experiment.attest_isolated_result();
        return batch;
    }

    batch.outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (experiment.isolated && batch.outcome != ExperimentOutcome::Invalid)
        experiment.attest_isolated_result();
    return batch;
}


EvolutionTrialBatch EvolutionExperimentCoordinator::run(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedEvaluationProcedure& procedure,
    EvolutionTrialConfig config) noexcept {
    return run_isolated(experiment, backend, procedure, config);
}

EvolutionTrialBatch EvolutionExperimentCoordinator::run_isolated(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedEvaluationProcedure& procedure,
    EvolutionTrialConfig config) noexcept {
    EvolutionTrialBatch batch;
    if (config.baseline_trials < 2 || config.candidate_trials < 2 ||
        !std::isfinite(config.minimum_improvement) || config.minimum_improvement < 0.0 ||
        !std::isfinite(config.minimum_confidence) || config.minimum_confidence < 0.0 ||
        config.minimum_confidence > 1.0) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return batch;
    }

    // Production evaluation measures both parameter states through the same
    // local evaluator and binds evidence to the artifacts and evaluator binary.
    experiment.minimum_improvement = config.minimum_improvement;
    batch.outcome = EvolutionExperimentRunner::run_isolated_evaluation(
        experiment, backend, procedure, config.baseline_trials,
        config.candidate_trials, config.minimum_confidence,
        &batch.baseline, &batch.candidate);
    batch.executed = experiment.candidate_executed &&
                     experiment.has_valid_evaluation_evidence();
    if (!batch.executed) batch.outcome = ExperimentOutcome::Invalid;
    return batch;
}

} // namespace jarvis::core
