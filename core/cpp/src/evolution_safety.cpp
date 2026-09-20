#include "jarvis/core/evolution_safety.hpp"

#include <cmath>

namespace jarvis::core {

bool EvolutionSafetyGate::approve(const EvolutionExperiment& experiment,
                                  const EvolutionSafetyPolicy& policy) noexcept {
    if (experiment.outcome != ExperimentOutcome::Improved) return false;
    if (!std::isfinite(experiment.baseline_fitness) || !std::isfinite(experiment.candidate_fitness)) return false;
    if (!std::isfinite(experiment.confidence_interval_low) ||
        !std::isfinite(experiment.confidence_interval_high) ||
        experiment.confidence_interval_low > experiment.confidence_interval_high) return false;
    if (std::isnan(experiment.effect_size)) return false;
    if (experiment.confidence < policy.minimum_confidence) return false;
    if (experiment.confidence_interval_low <= experiment.minimum_improvement) return false;
    if ((experiment.baseline_fitness - experiment.candidate_fitness) > policy.maximum_regression) return false;
    return true;
}

} // namespace jarvis::core
