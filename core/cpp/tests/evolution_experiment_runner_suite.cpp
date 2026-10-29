#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_safety.hpp"

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
int run_test_evaluator(int argc, char** argv) {
    std::string procedure, parameter, artifact, value_text;
    for (int i = 1; i + 1 < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--procedure") procedure = argv[++i];
        else if (arg == "--parameter") parameter = argv[++i];
        else if (arg == "--artifact") artifact = argv[++i];
        else if (arg == "--value") value_text = argv[++i];
    }
    if (procedure.empty() || parameter.empty() || artifact.empty() || value_text.empty()) return 2;
    const double value = std::stod(value_text);
    const double fitness = procedure == "equal-fitness" ? 0.70 : 0.70 + value - 0.40;
    std::cout << "JARVIS_EVAL_V1\nprocedure=" << procedure
              << "\nparameter=" << parameter << "\nvalue=" << value_text
              << "\nartifact=" << artifact << "\nfitness="
              << std::setprecision(17) << fitness << "\n";
    return 0;
}
EvolutionExperiment make_experiment() {
    return EvolutionExperiment{
        "runner-test", EvolutionProposal{"strategy.weight", 0.4, 0.5, 0.1, 0.8},
        0.70, 0.0, 0.05, 0.95};
}
}

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--test-evaluator")
        return run_test_evaluator(argc, argv);
    EvolutionSandbox sandbox;

    {
        auto experiment = make_experiment();
        ProcessIsolationBackend backend;
        IsolatedEvaluationSpec spec{
            IsolatedCommand{"/proc/self/exe", {"--test-evaluator"}, ""},
            "local-test-procedure-v1", "baseline-artifact-1", "candidate-artifact-1",
            0.4, 0.5};
        const auto outcome = EvolutionExperimentRunner::run_isolated_evaluation(
            experiment, backend, spec);
        assert(outcome == ExperimentOutcome::Improved);
        assert(experiment.candidate_executed);
        assert(experiment.has_valid_isolation_attestation());
        assert(std::abs(experiment.baseline_fitness - 0.70) < 1e-12);
        assert(std::abs(experiment.candidate_fitness - 0.80) < 1e-12);
        experiment.candidate_fitness += 0.01;
        assert(!experiment.has_valid_isolation_attestation());
    }

    {
        auto experiment = make_experiment();
        ProcessIsolationBackend backend;
        const auto outcome = EvolutionExperimentRunner::run_isolated_command(
            experiment, backend, IsolatedCommand{"/bin/sh", {"-c", "printf 0.99"}, ""});
        assert(outcome == ExperimentOutcome::Invalid);
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
