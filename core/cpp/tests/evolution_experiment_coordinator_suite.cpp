#include "jarvis/core/evolution_experiment_coordinator.hpp"
#include "evolution_test_evaluator.hpp"

#include <cassert>
#include <chrono>
#include <string>
#include <filesystem>

using namespace jarvis::core;

namespace {
std::string evaluator_executable;
IsolatedCommand evaluator_command(const EvolutionExperiment& experiment) {
    return IsolatedCommand{
        evaluator_executable,
        {"--test-evaluator-from-parameter"},
        "", "jarvis.test.fixture.v1",
        EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
}
}

int main(int argc, char** argv) {
    if (test_support::run_evolution_evaluator_fixture(argc, argv)) return 0;
    evaluator_executable = std::filesystem::absolute(argv[0]).string();
    if (!EvolutionExperimentRunner::register_trusted_evaluator(
            "jarvis.test.fixture.v1", evaluator_executable,
            {"--test-evaluator-from-parameter"})) return 1;
    assert(EvolutionExperimentRunner::register_trusted_evaluator(
        "jarvis.test.fixture.v1", evaluator_executable));
    EvolutionExperiment experiment{
        "trial-batch",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.9},
        0.0, 0.0, 0.05, 0.0, ExperimentOutcome::Pending, false};

    EvolutionSandbox sandbox;
    const CandidateExecutor baseline = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 0.70, {}};
    };
    const CandidateExecutor candidate = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 0.80, {}};
    };

    const auto batch = EvolutionExperimentCoordinator::run(
        experiment, sandbox, baseline, candidate, EvolutionTrialConfig{4, 4, 0.05, 0.5, false});

    assert(batch.executed);
    assert(batch.baseline.count == 4);
    assert(batch.candidate.count == 4);
    assert(experiment.candidate_executed);
    assert(experiment.outcome == ExperimentOutcome::Improved);
    assert(experiment.candidate_fitness > experiment.baseline_fitness);

    EvolutionExperiment untrusted_callback_experiment{
        "untrusted-callback",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.9},
        0.0, 0.0, 0.05, 0.0, ExperimentOutcome::Pending, false};
    const auto untrusted_callback_batch = EvolutionExperimentCoordinator::run(
        untrusted_callback_experiment, sandbox, baseline, candidate);
    assert(!untrusted_callback_batch.executed);
    assert(!untrusted_callback_experiment.candidate_executed);

    EvolutionExperiment isolated_experiment{
        "isolated-trial-batch",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.9},
        0.70, 0.80, 0.05, 0.0, ExperimentOutcome::Pending, false};
    ProcessIsolationLimits isolation_limits;
    isolation_limits.sandbox.timeout = std::chrono::milliseconds{5000};
    isolation_limits.max_cpu_seconds = 10;
    ProcessIsolationBackend backend(isolation_limits);
    EvolutionExperiment mismatched_trials{
        "mismatched-trials",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.9},
        0.0, 0.0, 0.05, 0.0, ExperimentOutcome::Pending, false};
    EvolutionTrialConfig mismatched_trial_config;
    mismatched_trial_config.baseline_trials = 3;
    mismatched_trial_config.candidate_trials = 4;
    const auto mismatched_batch = EvolutionExperimentCoordinator::run_isolated(
        mismatched_trials, backend, evaluator_command(mismatched_trials), mismatched_trial_config);
    assert(mismatched_batch.outcome == ExperimentOutcome::Invalid);
    assert(!mismatched_trials.candidate_executed);

    const auto isolated_batch = EvolutionExperimentCoordinator::run_isolated(
        isolated_experiment, backend, evaluator_command(isolated_experiment));
    assert(isolated_batch.executed);
    assert(isolated_batch.outcome == ExperimentOutcome::Improved);
    assert(isolated_experiment.has_valid_isolation_attestation());
    assert(isolated_experiment.baseline_artifact_id != isolated_experiment.candidate_artifact_id);

    EvolutionExperiment invalid_experiment{
        "isolated-invalid-trial",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.9},
        0.70, 0.80, 0.05, 0.0, ExperimentOutcome::Pending, false};
    const auto invalid_batch = EvolutionExperimentCoordinator::run_isolated(
        invalid_experiment, backend,
        IsolatedCommand{"/bin/sh", {"-c", "printf 0.99"}, "", "jarvis.test.fixture.v1"});
    assert(!invalid_batch.executed);
    assert(!invalid_experiment.candidate_executed);
    return 0;
}
