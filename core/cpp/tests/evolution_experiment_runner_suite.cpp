#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cassert>
#include <cmath>

using namespace jarvis::core;

namespace {
EvolutionExperiment make_experiment() {
    return EvolutionExperiment{
        "runner-test", EvolutionProposal{"strategy.weight", 0.4, 0.5, 0.1, 0.8},
        0.70, 0.0, 0.05, 0.95};
}
}

int main() {
    EvolutionSandbox sandbox;

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) {
                return SandboxResult{true, true, false, false, true, 0.86, {}};
            });
        assert(outcome == ExperimentOutcome::Improved);
        assert(experiment.candidate_executed);
        assert(std::abs(experiment.candidate_fitness - 0.86) < 1e-12);
    }

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) {
                return SandboxResult{true, true, false, false, false, 0.99, "not isolated"};
            });
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
    }

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) {
                return SandboxResult{true, false, true, false, true, 0.99, "timeout"};
            });
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
    }

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) {
                return SandboxResult{true, true, false, true, true, 0.99, "output limit"};
            });
        assert(outcome == ExperimentOutcome::Invalid);
    }

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) {
                return SandboxResult{true, true, false, false, true, std::nan(""), "bad fitness"};
            });
        assert(outcome == ExperimentOutcome::Invalid);
    }

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) -> SandboxResult {
                throw 1;
            });
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
    }

    return 0;
}
