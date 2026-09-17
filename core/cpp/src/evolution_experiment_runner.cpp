#include "jarvis/core/evolution_experiment_runner.hpp"

namespace jarvis::core {

ExperimentOutcome EvolutionExperimentRunner::run(EvolutionExperiment& experiment,
                                                  const EvolutionSandbox& sandbox,
                                                  const CandidateExecutor& executor) noexcept {
    const auto result = sandbox.run(experiment.proposal, executor);
    if (!result.started || !result.completed || result.timed_out || result.output_limited) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    experiment.candidate_fitness = result.fitness;
    return EvolutionExperimentEngine::evaluate(experiment);
}

} // namespace jarvis::core
