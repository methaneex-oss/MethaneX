#include "jarvis/core/evolution_experiment_runner.hpp"
#include "evolution_test_evaluator.hpp"
#include "jarvis/core/evolution_safety.hpp"

#include <cassert>
#include <string>
#include <filesystem>
#include <cmath>

using namespace jarvis::core;

namespace {
std::string evaluator_executable;
void attest_isolated(EvolutionExperiment& experiment) {
    ProcessIsolationBackend backend;
    const IsolatedCommand command{
        evaluator_executable,
        {"--test-evaluator", std::to_string(experiment.baseline_fitness),
         std::to_string(experiment.candidate_fitness)},
        "", "jarvis.test.fixture.v1"};
    EvolutionExperimentRunner::run_isolated_command(experiment, backend, command);
}

EvolutionExperiment make_experiment() {
    return EvolutionExperiment{
        "runner-test", EvolutionProposal{"strategy.weight", 0.4, 0.5, 0.1, 0.8},
        0.70, 0.0, 0.05, 0.95};
}
}

int main(int argc, char** argv) {
    if (test_support::run_evolution_evaluator_fixture(argc, argv)) return 0;
    evaluator_executable = std::filesystem::absolute(argv[0]).string();
    EvolutionSandbox sandbox;

    {
        auto experiment = make_experiment();
        ProcessIsolationBackend backend;
        const IsolatedCommand arbitrary_numeric{
            "/bin/sh", {"-c", "printf 0.86"}, "", "jarvis.test.fixture.v1"};
        const auto rejected = EvolutionExperimentRunner::run_isolated_command(
            experiment, backend, arbitrary_numeric);
        assert(rejected == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
        assert(!experiment.has_valid_isolation_attestation());
    }

    {
        auto experiment = make_experiment();
        experiment.candidate_fitness = 0.86;
        attest_isolated(experiment);
        assert(experiment.outcome == ExperimentOutcome::Improved);
        assert(experiment.candidate_executed);
        assert(experiment.has_valid_isolation_attestation());
        assert(std::abs(experiment.baseline_fitness - 0.70) < 1e-12);
        assert(std::abs(experiment.candidate_fitness - 0.86) < 1e-12);
        experiment.candidate_fitness += 0.01;
        assert(!experiment.has_valid_isolation_attestation());
    }

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) {
                // This callback lies about isolation. The sandbox must not
                // convert its Boolean claim into trusted attestation.
                return SandboxResult{true, true, false, false, true, 0.99, {}};
            });
        assert(outcome == ExperimentOutcome::Improved);
        assert(experiment.candidate_executed);
        assert(!experiment.isolated);
        assert(!experiment.has_valid_isolation_attestation());
        EvolutionSafetyPolicy policy;
        assert(!EvolutionSafetyGate::approve(experiment, policy));
    }

    {
        auto experiment = make_experiment();
        const auto outcome = EvolutionExperimentRunner::run(
            experiment, sandbox, [](const EvolutionProposal&, const SandboxLimits&) {
                return SandboxResult{true, false, true, false, true, 0.99, "timeout"};
            });
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
        assert(!experiment.has_valid_isolation_attestation());
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
