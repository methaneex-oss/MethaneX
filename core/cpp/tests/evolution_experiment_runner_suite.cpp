#include "jarvis/core/evolution_experiment_runner.hpp"
#include "evolution_test_evaluator.hpp"
#include "jarvis/core/evolution_safety.hpp"

#include <cassert>
#include <chrono>
#include <string>
#include <filesystem>
#include <cmath>

using namespace jarvis::core;

namespace {
std::string evaluator_executable;
void attest_isolated(EvolutionExperiment& experiment) {
    if (!EvolutionExperimentRunner::register_trusted_evaluator(
            "jarvis.test.fixture.v1", evaluator_executable,
            {"--test-evaluator-from-parameter"})) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return;
    }
    ProcessIsolationLimits isolation_limits;
    isolation_limits.sandbox.timeout = std::chrono::milliseconds{5000};
    isolation_limits.max_cpu_seconds = 10;
    ProcessIsolationBackend backend(isolation_limits);
    const IsolatedCommand command{
        evaluator_executable,
        {"--test-evaluator-from-parameter"},
        "", "jarvis.test.fixture.v1",
        EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
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
    if (!EvolutionExperimentRunner::set_evidence_authentication_key(
            "jarvis-test-evidence-key-2026-10-30-32bytes-minimum")) return 2;
    if (!EvolutionExperimentRunner::register_trusted_evaluator(
            "jarvis.test.fixture.v1", evaluator_executable,
            {"--test-evaluator-from-parameter"})) return 1;
    if (!EvolutionExperimentRunner::register_trusted_evaluator(
            "jarvis.test.parameter-fitness.v1", evaluator_executable,
            {"--test-evaluator-from-parameter"})) return 1;
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
        ProcessIsolationBackend backend;
        const IsolatedCommand unregistered_evaluator{
            evaluator_executable,
            {"--test-evaluator-from-parameter"}, "",
            "jarvis.unregistered.fixture.v1",
            EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
        const auto rejected = EvolutionExperimentRunner::run_isolated_command(
            experiment, backend, unregistered_evaluator);
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
        assert(std::abs(experiment.baseline_fitness - experiment.proposal.current) < 1e-12);
        assert(std::abs(experiment.candidate_fitness - experiment.proposal.proposed) < 1e-12);
        experiment.candidate_fitness += 0.01;
        assert(!experiment.has_valid_isolation_attestation());
        experiment.candidate_fitness -= 0.01;
        experiment.evaluation_procedure_id += "-tampered";
        assert(!experiment.has_valid_isolation_attestation());
    }

    {
        auto experiment = make_experiment();
        experiment.candidate_fitness = 0.86;
        ProcessIsolationLimits isolation_limits;
        isolation_limits.sandbox.timeout = std::chrono::milliseconds{5000};
        isolation_limits.max_cpu_seconds = 10;
        ProcessIsolationBackend backend(isolation_limits);
        IsolatedCommand pinned{
            evaluator_executable,
            {"--test-evaluator-from-parameter"},
            "", "jarvis.test.fixture.v1",
            EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
        pinned.expected_executable_fingerprint = "wrong-executable-fingerprint";
        const auto outcome = EvolutionExperimentRunner::run_isolated_command(
            experiment, backend, pinned);
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
        assert(!experiment.has_valid_isolation_attestation());
    }

    {
        auto experiment = make_experiment();
        ProcessIsolationLimits isolation_limits;
        isolation_limits.sandbox.timeout = std::chrono::milliseconds{5000};
        isolation_limits.max_cpu_seconds = 10;
        ProcessIsolationBackend backend(isolation_limits);
        const IsolatedCommand evaluator{
            evaluator_executable, {"--test-evaluator-from-parameter"}, "",
            "jarvis.test.parameter-fitness.v1",
            EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
        const auto outcome = EvolutionExperimentRunner::run_isolated_command(
            experiment, backend, evaluator);
        assert(outcome == ExperimentOutcome::Improved);
        assert(experiment.has_valid_isolation_attestation());
        assert(std::abs(experiment.baseline_fitness - experiment.proposal.current) < 1e-12);
        assert(std::abs(experiment.candidate_fitness - experiment.proposal.proposed) < 1e-12);
        assert(EvolutionExperimentRunner::authenticate_persisted_evidence(experiment));
        auto tampered = experiment;
        tampered.candidate_fitness += 0.05;
        assert(!EvolutionExperimentRunner::restore_trusted_attestation(tampered));
        auto intact = experiment;
        intact.clear_isolation_attestation();
        assert(EvolutionExperimentRunner::restore_trusted_attestation(intact));
        assert(intact.has_valid_isolation_attestation());
    }

    {
        auto experiment = make_experiment();
        const IsolatedCommand unregistered{
            evaluator_executable,
            {"--test-evaluator-from-parameter"},
            "", "jarvis.unregistered.fixture.v1",
            EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
        ProcessIsolationLimits isolation_limits;
        isolation_limits.sandbox.timeout = std::chrono::milliseconds{5000};
        isolation_limits.max_cpu_seconds = 10;
        ProcessIsolationBackend backend(isolation_limits);
        const auto outcome = EvolutionExperimentRunner::run_isolated_command(
            experiment, backend, unregistered);
        assert(outcome == ExperimentOutcome::Invalid);
        assert(!experiment.candidate_executed);
        assert(!experiment.has_valid_isolation_attestation());
    }

    {
        auto experiment = make_experiment();
        experiment.candidate_fitness = 0.86;
        ProcessIsolationLimits weak_limits;
        weak_limits.require_no_new_privileges = false;
        weak_limits.require_network_syscall_block = false;
        weak_limits.sandbox.timeout = std::chrono::milliseconds{5000};
        ProcessIsolationBackend weak_backend(weak_limits);
        const IsolatedCommand command{
            evaluator_executable,
            {"--test-evaluator-from-parameter"},
            "", "jarvis.test.fixture.v1",
            EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
        const auto outcome = EvolutionExperimentRunner::run_isolated_command(
            experiment, weak_backend, command);
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


    {
        // A journal editor can copy the registered evaluator identity and
        // recompute public artifact fingerprints without running the evaluator.
        // Fabricated fitness values must not recreate the private attestation.
        auto restored = make_experiment();
        restored.candidate_executed = true;
        restored.isolated = true;
        restored.outcome = ExperimentOutcome::Improved;
        restored.baseline_fitness = 0.1;
        restored.candidate_fitness = 0.99;
        restored.evaluation_procedure_id = "jarvis.test.fixture.v1";
        restored.evaluator_executable_fingerprint =
            EvolutionExperimentRunner::executable_fingerprint(evaluator_executable);
        restored.baseline_artifact_id = EvolutionExperiment::artifact_fingerprint(
            restored.proposal.key + "\x1f" +
            EvolutionExperiment::format_parameter_value(restored.proposal.current) + "\x1f" +
            restored.evaluation_procedure_id);
        restored.candidate_artifact_id = EvolutionExperiment::artifact_fingerprint(
            restored.proposal.key + "\x1f" +
            EvolutionExperiment::format_parameter_value(restored.proposal.proposed) + "\x1f" +
            restored.evaluation_procedure_id);
        assert(!EvolutionExperimentRunner::restore_trusted_attestation(restored));
        assert(!restored.has_valid_isolation_attestation());
    }

    return 0;
}
