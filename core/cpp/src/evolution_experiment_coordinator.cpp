#include "jarvis/core/evolution_experiment_coordinator.hpp"

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
    const double evidence_confidence = std::max(config.minimum_confidence, experiment.proposal.confidence);
    if (config.baseline_trials == 0 || config.candidate_trials == 0 ||
        !std::isfinite(config.minimum_improvement) || config.minimum_improvement < 0.0 ||
        !std::isfinite(config.minimum_confidence) || config.minimum_confidence <= 0.0 ||
        config.minimum_confidence >= 1.0 ||
        !std::isfinite(evidence_confidence) || evidence_confidence <= 0.0 ||
        evidence_confidence >= 1.0) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return batch;
    }

    std::vector<double> baseline;
    std::vector<double> candidate;
    baseline.reserve(config.baseline_trials);
    candidate.reserve(config.candidate_trials);

    for (std::size_t i = 0; i < config.baseline_trials; ++i) {
        const auto result = sandbox.run(experiment.proposal, baseline_executor);
        if (!result.completed || result.timed_out || result.output_limited || !std::isfinite(result.fitness)) {
            experiment.outcome = ExperimentOutcome::Invalid;
            return batch;
        }
        baseline.push_back(result.fitness);
    }

    for (std::size_t i = 0; i < config.candidate_trials; ++i) {
        const auto result = sandbox.run(experiment.proposal, candidate_executor);
        if (!result.completed || result.timed_out || result.output_limited || !std::isfinite(result.fitness)) {
            experiment.outcome = ExperimentOutcome::Invalid;
            return batch;
        }
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
    experiment.confidence = evidence_confidence;
    experiment.confidence_interval_low = EvolutionTrials::difference_confidence_interval_low(
        batch.baseline, batch.candidate, evidence_confidence);
    experiment.confidence_interval_high = EvolutionTrials::difference_confidence_interval_high(
        batch.baseline, batch.candidate, evidence_confidence);
    experiment.effect_size = EvolutionTrials::standardized_effect_size(
        batch.baseline, batch.candidate);
    if (!std::isfinite(experiment.confidence_interval_low) ||
        !std::isfinite(experiment.confidence_interval_high) ||
        (std::isnan(experiment.effect_size))) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return batch;
    }
    experiment.candidate_executed = true;
    batch.executed = true;

    if (!EvolutionTrials::supports_adoption(batch.baseline, batch.candidate,
                                            config.minimum_improvement,
                                            evidence_confidence)) {
        const double gain = batch.candidate.mean - batch.baseline.mean;
        experiment.outcome = gain < -config.minimum_improvement
            ? ExperimentOutcome::Degraded
            : ExperimentOutcome::Neutral;
        batch.outcome = experiment.outcome;
        return batch;
    }

    batch.outcome = EvolutionExperimentEngine::evaluate(experiment);
    return batch;
}

} // namespace jarvis::core
