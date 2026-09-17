#include "jarvis/core/evolution_experiment.hpp"

#include <cmath>

namespace jarvis::core {

ExperimentOutcome EvolutionExperimentEngine::evaluate(EvolutionExperiment& experiment) noexcept {
    const auto& proposal = experiment.proposal;
    const bool valid = !experiment.id.empty() && !proposal.key.empty() &&
                       std::isfinite(proposal.current) && std::isfinite(proposal.proposed) &&
                       std::isfinite(proposal.expected_gain) && std::isfinite(proposal.confidence) &&
                       proposal.confidence >= 0.0 && proposal.confidence <= 1.0 &&
                       std::isfinite(experiment.baseline_fitness) &&
                       std::isfinite(experiment.candidate_fitness) &&
                       std::isfinite(experiment.minimum_improvement) &&
                       experiment.minimum_improvement >= 0.0 &&
                       std::isfinite(experiment.confidence) &&
                       experiment.confidence >= 0.0 && experiment.confidence <= 1.0 &&
                       experiment.candidate_executed;
    if (!valid) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    const double improvement = experiment.candidate_fitness - experiment.baseline_fitness;
    if (improvement > experiment.minimum_improvement &&
        experiment.confidence >= proposal.confidence) {
        experiment.outcome = ExperimentOutcome::Improved;
    } else if (improvement < -experiment.minimum_improvement) {
        experiment.outcome = ExperimentOutcome::Degraded;
    } else {
        experiment.outcome = ExperimentOutcome::Neutral;
    }
    return experiment.outcome;
}

} // namespace jarvis::core
