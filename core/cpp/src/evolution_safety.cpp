#include "jarvis/core/evolution_safety.hpp"

#include <cmath>

namespace jarvis::core {

bool EvolutionSafetyGate::approve(const EvolutionExperiment& experiment,
                                  const EvolutionSafetyPolicy& policy) noexcept {
    if (experiment.outcome != ExperimentOutcome::Improved) return false;
    if (!std::isfinite(experiment.baseline_fitness) || !std::isfinite(experiment.candidate_fitness) ||
        !std::isfinite(experiment.minimum_improvement) || experiment.minimum_improvement < 0.0 ||
        !std::isfinite(experiment.confidence) || !std::isfinite(policy.minimum_confidence) ||
        !std::isfinite(policy.maximum_regression) || policy.maximum_regression < 0.0) return false;
    if (policy.require_isolation && !experiment.has_valid_isolation_attestation()) return false;
    if (experiment.confidence < policy.minimum_confidence) return false;
    // Recompute the claimed outcome at the safety boundary. A caller cannot
    // label equal or sub-threshold fitness as Improved and bypass evaluation.
    if ((experiment.candidate_fitness - experiment.baseline_fitness) <=
        experiment.minimum_improvement) return false;
    if ((experiment.baseline_fitness - experiment.candidate_fitness) > policy.maximum_regression) return false;
    return true;
}

} // namespace jarvis::core
