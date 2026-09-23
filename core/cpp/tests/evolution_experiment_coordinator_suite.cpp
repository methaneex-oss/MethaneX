#include "jarvis/core/evolution_experiment_coordinator.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    EvolutionExperiment experiment{
        "trial-batch",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.9},
        0.0, 0.0, 0.05, 0.0, 0.0, 0.0, 0.0, ExperimentOutcome::Pending, false};

    EvolutionSandbox sandbox;
    const CandidateExecutor baseline = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 0.70, {}};
    };
    const CandidateExecutor candidate = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 0.80, {}};
    };

    const auto batch = EvolutionExperimentCoordinator::run(
        experiment, sandbox, baseline, candidate, EvolutionTrialConfig{4, 4, 0.05, 0.5});

    assert(batch.executed);
    assert(batch.baseline.count == 4);
    assert(batch.candidate.count == 4);
    assert(experiment.candidate_executed);
    assert(experiment.outcome == ExperimentOutcome::Improved);
    assert(experiment.candidate_fitness > experiment.baseline_fitness);
    return 0;
}
