#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cmath>
#include <string>

namespace jarvis::core {

ExperimentOutcome EvolutionExperimentRunner::run(EvolutionExperiment& experiment,
                                                  const EvolutionSandbox& sandbox,
                                                  const CandidateExecutor& executor) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    const auto result = sandbox.run(experiment.proposal, executor);
    if (!result.started || !result.completed || result.timed_out || result.output_limited ||
        !std::isfinite(result.fitness)) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    experiment.candidate_fitness = result.fitness;
    experiment.candidate_executed = true;
    experiment.isolated = false; // callback results are not trusted isolation evidence
    return EvolutionExperimentEngine::evaluate(experiment);
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_command(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedCommand& command) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    const auto result = backend.run(command);
    if (!result.started || !result.isolated || !result.completed || result.timed_out ||
        result.output_limited || result.exit_code != 0 || result.output.empty()) {
        return experiment.outcome;
    }
    try {
        std::size_t parsed = 0;
        const double fitness = std::stod(result.output, &parsed);
        while (parsed < result.output.size() &&
               (result.output[parsed] == ' ' || result.output[parsed] == '\n' ||
                result.output[parsed] == '\r' || result.output[parsed] == '\t')) ++parsed;
        if (parsed != result.output.size() || !std::isfinite(fitness)) return experiment.outcome;
        experiment.candidate_fitness = fitness;
        experiment.candidate_executed = true;
        experiment.isolated = true;
        experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
        if (experiment.outcome != ExperimentOutcome::Invalid)
            experiment.attest_isolated_result();
        return experiment.outcome;
    } catch (...) {
        experiment.candidate_executed = false;
        experiment.isolated = false;
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }
}

} // namespace jarvis::core
