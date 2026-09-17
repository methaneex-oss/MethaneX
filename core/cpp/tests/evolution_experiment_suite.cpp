#include "jarvis/core/evolution_experiment.hpp"

#include <cassert>
#include <cmath>

using namespace jarvis::core;

int main() {
    EvolutionProposal proposal{"strategy.weight", 0.4, 0.5, 0.1, 0.9};

    EvolutionExperiment improved{"exp-improved", proposal, 0.70, 0.84, 0.05, 0.95,
                                 ExperimentOutcome::Pending, true};
    assert(EvolutionExperimentEngine::evaluate(improved) == ExperimentOutcome::Improved);

    EvolutionExperiment neutral{"exp-neutral", proposal, 0.70, 0.73, 0.05, 0.95,
                                ExperimentOutcome::Pending, true};
    assert(EvolutionExperimentEngine::evaluate(neutral) == ExperimentOutcome::Neutral);

    EvolutionExperiment degraded{"exp-degraded", proposal, 0.84, 0.70, 0.05, 0.95,
                                 ExperimentOutcome::Pending, true};
    assert(EvolutionExperimentEngine::evaluate(degraded) == ExperimentOutcome::Degraded);

    EvolutionExperiment low_confidence{"exp-low-confidence", proposal, 0.70, 0.84, 0.05, 0.5,
                                       ExperimentOutcome::Pending, true};
    assert(EvolutionExperimentEngine::evaluate(low_confidence) == ExperimentOutcome::Neutral);

    EvolutionExperiment unexecuted{"exp-unexecuted", proposal, 0.70, 0.84, 0.05, 0.95};
    assert(EvolutionExperimentEngine::evaluate(unexecuted) == ExperimentOutcome::Invalid);

    EvolutionProposal invalid_proposal{"bad", 0.4, 0.5, std::nan(""), 0.9};
    EvolutionExperiment invalid{"exp-invalid", invalid_proposal, 0.0, 1.0, 0.05, 0.9,
                                ExperimentOutcome::Pending, true};
    assert(EvolutionExperimentEngine::evaluate(invalid) == ExperimentOutcome::Invalid);
    assert(std::isfinite(improved.candidate_fitness));
    return 0;
}
