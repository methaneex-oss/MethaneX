#include "jarvis/core/evolution_experiment_coordinator.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double comparison_evidence(const TrialComparison& comparison) noexcept {
    if (!comparison.valid) return 0.0;
    if (comparison.standard_error == 0.0) {
        return comparison.mean_difference == 0.0 ? 0.0 : 1.0;
    }
    const double z = std::abs(comparison.mean_difference / comparison.standard_error);
    if (!std::isfinite(z)) return 0.0;
    return std::clamp(std::erf(z / std::sqrt(2.0)), 0.0, 1.0);
}

} // namespace

EvolutionTrialBatch EvolutionExperimentCoordinator::run(
    EvolutionExperiment& experiment,
    const EvolutionSandbox& sandbox,
    const CandidateExecutor& baseline_executor,
    const CandidateExecutor& candidate_executor,
    EvolutionTrialConfig config) noexcept {
    EvolutionTrialBatch batch;
    if (config.baseline_trials == 0 || config.candidate_trials == 0 ||
        !std::isfinite(config.minimum_improvement) || config.minimum_improvement < 0.0 ||
        !std::isfinite(config.minimum_confidence) || config.minimum_confidence < 0.75 ||
        config.minimum_confidence > 0.99) {
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
    const auto comparison = EvolutionTrials::compare(batch.baseline, batch.candidate,
                                                       config.minimum_confidence);
    experiment.confidence = comparison_evidence(comparison);
    experiment.candidate_executed = true;
    batch.executed = true;

    if (!EvolutionTrials::supports_adoption(batch.baseline, batch.candidate,
                                            config.minimum_improvement,
                                            config.minimum_confidence)) {
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
