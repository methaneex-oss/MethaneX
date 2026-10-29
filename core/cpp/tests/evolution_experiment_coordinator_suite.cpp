#include "jarvis/core/evolution_experiment_coordinator.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/process_isolation.hpp"
#include "evolution_test_evaluator.hpp"

#include <cassert>
#include <string>

using namespace jarvis::core;

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--test-evaluator")\n        return test_support::run_evolution_test_evaluator(argc, argv);
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

    // The default policy must reject simulated callback results, because
    // EvolutionSandbox deliberately strips callback-provided isolation claims.
    EvolutionExperiment simulated{
        "default-simulated", EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8},
        0.0, 0.0, 0.01, 0.0};
    const auto rejected = EvolutionExperimentCoordinator::run(
        simulated, sandbox, baseline, candidate, EvolutionTrialConfig{});
    assert(!rejected.executed);
    assert(simulated.outcome == ExperimentOutcome::Invalid);

    // The production route measures baseline and candidate with the same
    // local evaluator procedure and identity-bound artifacts.
    EvolutionExperiment isolated{
        "default-isolated", EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8},
        0.0, 0.0, 0.01, 0.0};
    ProcessIsolationBackend backend;
    const IsolatedEvaluationSpec spec{
        IsolatedCommand{"/proc/self/exe", {"--test-evaluator"}, ""},
        "local-test-procedure-v1", "baseline:planner.weight:0.4",
        "candidate:planner.weight:0.5", 0.4, 0.5};
    const auto isolated_batch = EvolutionExperimentCoordinator::run_isolated(
        isolated, backend, spec, EvolutionTrialConfig{4, 4, 0.05, 0.5, true});
    assert(isolated_batch.executed);
    assert(isolated_batch.baseline.count == 4);
    assert(isolated_batch.candidate.count == 4);
    assert(isolated.has_valid_isolation_attestation());
    assert(isolated.outcome == ExperimentOutcome::Improved);
    assert(isolated.candidate_fitness > isolated.baseline_fitness);
    return 0;
}
