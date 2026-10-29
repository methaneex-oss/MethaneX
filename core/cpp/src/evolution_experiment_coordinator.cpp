#include "jarvis/core/evolution_experiment_coordinator.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace jarvis::core {

EvolutionTrialBatch EvolutionExperimentCoordinator::run(
    EvolutionExperiment& experiment,
    const EvolutionSandbox& sandbox,
    const CandidateExecutor& baseline_executor,
    const CandidateExecutor& candidate_executor,
    EvolutionTrialConfig config) noexcept {
    EvolutionTrialBatch batch;
    experiment.clear_isolation_attestation();
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
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


EvolutionTrialBatch EvolutionExperimentCoordinator::run_isolated(
    EvolutionExperiment& experiment,
    const ProcessIsolationBackend& backend,
    const IsolatedCommand& evaluator,
    EvolutionTrialConfig config) noexcept {
    EvolutionTrialBatch batch;
    experiment.clear_isolation_attestation();
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    if (!config.require_isolation || config.baseline_trials < 2 ||
        config.candidate_trials < 2 ||
        config.baseline_trials != config.candidate_trials ||
        evaluator.evaluation_procedure_id.empty() ||
        !std::isfinite(config.minimum_improvement) || config.minimum_improvement < 0.0 ||
        !std::isfinite(config.minimum_confidence) || config.minimum_confidence < 0.0 ||
        config.minimum_confidence > 1.0) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return batch;
    }

    std::vector<double> baseline;
    std::vector<double> candidate;
    baseline.reserve(config.baseline_trials);
    candidate.reserve(config.candidate_trials);
    EvolutionExperiment evidence = experiment;
    // Paired measurements must use the same number of baseline and candidate trials.
    const auto trial_count = config.baseline_trials;
    for (std::size_t i = 0; i < trial_count; ++i) {
        EvolutionExperiment measured = experiment;
        IsolatedCommand trial_evaluator = evaluator;
        trial_evaluator.trial_index = i;
        const auto outcome = EvolutionExperimentRunner::run_isolated_command(
            measured, backend, trial_evaluator);
        if (outcome == ExperimentOutcome::Invalid ||
            !measured.has_valid_isolation_attestation()) {
            experiment.outcome = ExperimentOutcome::Invalid;
            experiment.candidate_executed = false;
            experiment.isolated = false;
            return batch;
        }
        if (i < config.baseline_trials) baseline.push_back(measured.baseline_fitness);
        if (i < config.candidate_trials) candidate.push_back(measured.candidate_fitness);
        evidence = std::move(measured);
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
    experiment.isolated = true;
    experiment.evaluation_procedure_id = evidence.evaluation_procedure_id;
    experiment.evaluator_executable_fingerprint = evidence.evaluator_executable_fingerprint;
    experiment.baseline_artifact_id = evidence.baseline_artifact_id;
    experiment.candidate_artifact_id = evidence.candidate_artifact_id;
    if (EvolutionTrials::supports_adoption(batch.baseline, batch.candidate,
                                           config.minimum_improvement,
                                           config.minimum_confidence)) {
        batch.outcome = EvolutionExperimentEngine::evaluate(experiment);
    } else {
        batch.outcome = batch.candidate.mean - batch.baseline.mean < -config.minimum_improvement
            ? ExperimentOutcome::Degraded : ExperimentOutcome::Neutral;
        experiment.outcome = batch.outcome;
    }
    if (batch.outcome != ExperimentOutcome::Invalid) experiment.attest_isolated_result();
    batch.executed = batch.outcome != ExperimentOutcome::Invalid;
    return batch;
}

} // namespace jarvis::core
