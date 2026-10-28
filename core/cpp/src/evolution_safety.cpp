#include "jarvis/core/evolution_safety.hpp"

#include <cmath>

namespace jarvis::core {

bool EvolutionSafetyGate::approve(const EvolutionExperiment& experiment,
                                  const EvolutionSafetyPolicy& policy) noexcept {
    if (experiment.outcome != ExperimentOutcome::Improved || !experiment.candidate_executed)
        return false;
    if (policy.require_isolation && !experiment.isolation_verified()) return false;
    if (!std::isfinite(experiment.baseline_fitness) ||
        !std::isfinite(experiment.candidate_fitness) ||
        !std::isfinite(experiment.minimum_improvement) ||
        experiment.minimum_improvement < 0.0 ||
        !std::isfinite(experiment.confidence) ||
        !std::isfinite(experiment.proposal.confidence) ||
        !std::isfinite(experiment.proposal.current) ||
        !std::isfinite(experiment.proposal.proposed) ||
        !std::isfinite(experiment.proposal.expected_gain)) return false;
    if (experiment.confidence < policy.minimum_confidence ||
        experiment.confidence < experiment.proposal.confidence) return false;
    const double improvement = experiment.candidate_fitness - experiment.baseline_fitness;
    if (!std::isfinite(improvement) || improvement <= experiment.minimum_improvement) return false;
    if ((experiment.baseline_fitness - experiment.candidate_fitness) > policy.maximum_regression)
        return false;
    return true;
}

} // namespace jarvis::core
