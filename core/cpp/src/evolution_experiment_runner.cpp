#include "jarvis/core/evolution_experiment_runner.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

EvolutionTrialStatistics collect(const EvolutionExperimentRunner::FitnessEvaluator& evaluator,
                                 double parameter, std::size_t trials) noexcept {
    EvolutionTrialStatistics stats;
    if (!evaluator || trials == 0) return stats;

    double mean = 0.0;
    double m2 = 0.0;
    for (std::size_t i = 0; i < trials; ++i) {
        const double value = evaluator(parameter);
        if (!std::isfinite(value)) return {};
        const double delta = value - mean;
        mean += delta / static_cast<double>(i + 1);
        const double delta2 = value - mean;
        m2 += delta * delta2;
    }

    stats.mean = mean;
    stats.variance = trials > 1 ? m2 / static_cast<double>(trials - 1) : 0.0;
    stats.trials = trials;
    return stats;
}

} // namespace

EvolutionExperimentRun EvolutionExperimentRunner::run(
    const EvolutionExperiment& experiment,
    FitnessEvaluator baseline_evaluator,
    FitnessEvaluator candidate_evaluator,
    std::size_t trials) noexcept {
    EvolutionExperimentRun result;
    if (experiment.id.empty() || experiment.proposal.key.empty() || trials == 0 ||
        !std::isfinite(experiment.proposal.current) || !std::isfinite(experiment.proposal.proposed) ||
        !std::isfinite(experiment.proposal.confidence) || experiment.proposal.confidence < 0.0 ||
        experiment.proposal.confidence > 1.0 || !std::isfinite(experiment.minimum_improvement) ||
        experiment.minimum_improvement < 0.0 || !baseline_evaluator || !candidate_evaluator) {
        return result;
    }

    result.baseline = collect(baseline_evaluator, experiment.proposal.current, trials);
    result.candidate = collect(candidate_evaluator, experiment.proposal.proposed, trials);
    if (result.baseline.trials != trials || result.candidate.trials != trials) return result;

    result.improvement = result.candidate.mean - result.baseline.mean;
    const double noise = std::sqrt(result.baseline.variance / static_cast<double>(trials) +
                                   result.candidate.variance / static_cast<double>(trials));
    result.confidence = noise == 0.0
                            ? (result.improvement == 0.0 ? 0.0 : 1.0)
                            : std::clamp(std::abs(result.improvement) /
                                             (std::abs(result.improvement) + noise),
                                         0.0, 1.0);

    if (result.improvement > experiment.minimum_improvement &&
        result.confidence >= experiment.proposal.confidence) {
        result.outcome = ExperimentOutcome::Improved;
    } else if (result.improvement < -experiment.minimum_improvement) {
        result.outcome = ExperimentOutcome::Degraded;
    } else {
        result.outcome = ExperimentOutcome::Neutral;
    }
    return result;
}

} // namespace jarvis::core
