#include "jarvis/core/evolution_experiment.hpp"

namespace jarvis::core {

ExperimentOutcome EvolutionExperimentEngine::evaluate(EvolutionExperiment& experiment) noexcept {
    if (experiment.id.empty() || experiment.proposal.key.empty() ||
        experiment.confidence < 0.0 || experiment.confidence > 1.0 ||
        experiment.minimum_improvement < 0.0) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    const double improvement = experiment.candidate_fitness - experiment.baseline_fitness;
    if (improvement > experiment.minimum_improvement && experiment.confidence >= experiment.proposal.confidence) {
        experiment.outcome = ExperimentOutcome::Improved;
    } else if (improvement < -experiment.minimum_improvement) {
        experiment.outcome = ExperimentOutcome::Degraded;
    } else {
        experiment.outcome = ExperimentOutcome::Neutral;
    }
    return experiment.outcome;
}

} // namespace jarvis::core
