#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cmath>

namespace jarvis::core {

ExperimentOutcome EvolutionExperimentRunner::run(EvolutionExperiment& experiment,
                                                  const EvolutionSandbox& sandbox,
                                                  const CandidateExecutor& executor) noexcept {
    experiment.candidate_executed = false;
    experiment.isolation_attested_ = false;
    const auto result = sandbox.run(experiment.proposal, executor);
    if (!result.started || !result.completed || result.timed_out || result.output_limited ||
        !result.isolated || !std::isfinite(result.fitness)) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    experiment.candidate_fitness = result.fitness;
    experiment.candidate_executed = true;
    experiment.isolation_attested_ = true;
    const auto outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (outcome != ExperimentOutcome::Improved) experiment.isolation_attested_ = false;
    return outcome;
}

} // namespace jarvis::core
