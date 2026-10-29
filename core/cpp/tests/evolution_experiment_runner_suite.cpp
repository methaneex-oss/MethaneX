#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_digest.hpp"
#include "jarvis/core/evolution_safety.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

using namespace jarvis::core;

namespace {
std::string baseline_artifact_path;
std::string candidate_artifact_path;
EvolutionExperiment make_experiment() {
    return EvolutionExperiment{
        "runner-test", EvolutionProposal{"strategy.weight", 0.4, 0.5, 0.1, 0.8},
        0.70, 0.0, 0.05, 0.95};
}
}

int main(int argc, char** argv) {
    assert(detail::sha256_hex("abc") == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    if (argc > 1 && std::string(argv[1]) == "--trusted-test-evaluator") {
        if (argc != 14 || std::string(argv[2]) != "--jarvis-evaluate-v1") return 21;
        std::ifstream artifact(argv[9]);
        std::string score_text;
        if (!artifact || !(artifact >> score_text)) return 22;
        const double fitness = std::stod(score_text);
        std::cout << "JARVIS_EVAL_V1\t" << argv[3] << "\t" << argv[4] << "\t"
                  << argv[5] << "\t" << argv[6] << "\t" << argv[7] << "\t"
                  << argv[8] << "\t" << argv[10] << "\t" << argv[11] << "\t"
                  << argv[12] << "\t" << argv[13] << "\t" << fitness;
        return 0;
    }
    const auto temp = std::filesystem::temp_directory_path();
    baseline_artifact_path = (temp / "jarvis_runner_baseline_artifact.txt").string();
    candidate_artifact_path = (temp / "jarvis_runner_candidate_artifact.txt").string();
    { std::ofstream out(baseline_artifact_path); out << "0.70"; }
    { std::ofstream out(candidate_artifact_path); out << "0.80"; }
    EvolutionSandbox sandbox;

    {
        auto experiment = make_experiment();
        ProcessIsolationBackend backend;
        const IsolatedCommand command{"/bin/sh", {"-c", "printf 0.86"}, ""};
        const auto outcome = EvolutionExperimentRunner::run_isolated_command(
            experiment, backend, command);
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
        assert(!experiment.has_valid_evaluation_evidence());
    }

    {
        auto experiment = make_experiment();
        ProcessIsolationLimits limits;
        limits.require_no_new_privileges = true;
        limits.require_privilege_drop = true;
        limits.require_network_syscall_block = true;
        ProcessIsolationBackend backend(limits);
        IsolatedEvaluationProcedure procedure{
            IsolatedCommand{argv[0], {"--trusted-test-evaluator"}, ""},
            "runner-suite-local-evaluator-v1", "linear-fitness-v1",
            baseline_artifact_path, candidate_artifact_path, detail::sha256_file(argv[0])};
        TrialStatistics baseline, candidate;
        const auto outcome = EvolutionExperimentRunner::run_isolated_evaluation(
            experiment, backend, procedure, 4, 4, 0.5, &baseline, &candidate);
        assert(outcome == ExperimentOutcome::Improved);
        assert(experiment.candidate_executed);
        assert(experiment.has_valid_isolation_attestation());
        assert(experiment.has_valid_evaluation_evidence());
        assert(baseline.count == 4 && candidate.count == 4);
        assert(candidate.mean > baseline.mean);
        const auto original_candidate_digest = experiment.candidate_artifact_digest;
        experiment.candidate_artifact_digest += "tampered";
        assert(!experiment.has_valid_isolation_attestation());
        assert(!experiment.has_valid_evaluation_evidence());
        experiment.candidate_artifact_digest = original_candidate_digest;
        experiment.candidate_fitness += 0.01;
        assert(!experiment.has_valid_isolation_attestation());
        assert(!experiment.has_valid_evaluation_evidence());
    }

    {
        auto experiment = make_experiment();
        ProcessIsolationLimits limits;
        limits.require_no_new_privileges = true;
        limits.require_network_syscall_block = true;
        ProcessIsolationBackend backend(limits);
        IsolatedEvaluationProcedure untrusted{
            IsolatedCommand{argv[0], {"--trusted-test-evaluator"}, ""},
            "runner-suite-local-evaluator-v1", "linear-fitness-v1",
            baseline_artifact_path, candidate_artifact_path, "wrong-pinned-digest"};
        const auto outcome = EvolutionExperimentRunner::run_isolated_evaluation(
            experiment, backend, untrusted, 4, 4, 0.5);
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.has_valid_evaluation_evidence());
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
