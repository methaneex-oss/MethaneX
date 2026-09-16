#include "jarvis/core/evolution_experiment.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    EvolutionExperiment experiment;
    experiment.id = "exp-1";
    experiment.proposal = EvolutionProposal{"strategy", 0.2, 0.3, 0.1, 0.8};
    experiment.baseline_fitness = 0.70;
    experiment.candidate_fitness = 0.85;
    experiment.minimum_improvement = 0.05;
    experiment.confidence = 0.90;
    assert(EvolutionExperimentEngine::evaluate(experiment) == ExperimentOutcome::Improved);

    experiment.candidate_fitness = 0.71;
    assert(EvolutionExperimentEngine::evaluate(experiment) == ExperimentOutcome::Neutral);

    experiment.candidate_fitness = 0.50;
    assert(EvolutionExperimentEngine::evaluate(experiment) == ExperimentOutcome::Degraded);

    experiment.id.clear();
    assert(EvolutionExperimentEngine::evaluate(experiment) == ExperimentOutcome::Invalid);
    return 0;
}
