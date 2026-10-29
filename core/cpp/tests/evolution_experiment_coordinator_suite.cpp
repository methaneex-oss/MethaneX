#include "jarvis/core/evolution_experiment_coordinator.hpp"\n#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
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
    assert(!experiment.has_valid_isolation_attestation());

    // Default production configuration ignores callback-supplied numbers and
    // measures baseline/candidate on the same held-out experience in the
    // repository-owned isolated evaluator.
    EvolutionExperiment trusted{
        "trusted-trial-batch",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8},
        0.0, 0.0, 0.05, 0.0};
    EvolutionTrialConfig production;
    production.evaluation_cases = {
        {1.0, 0.5}, {2.0, 1.0}, {3.0, 1.5}, {4.0, 2.0}};
    const CandidateExecutor fake_baseline = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 0.0, {}};
    };
    const CandidateExecutor fake_candidate = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 999.0, {}};
    };
    const auto trusted_batch = EvolutionExperimentCoordinator::run(
        trusted, sandbox, fake_baseline, fake_candidate, production);
    assert(trusted_batch.executed);
    assert(trusted_batch.baseline.count == 4);
    assert(trusted_batch.candidate.count == 4);
    assert(trusted.outcome == ExperimentOutcome::Improved);
    assert(trusted.has_valid_isolation_attestation());
    assert(trusted.candidate_fitness <= 1.0);
    assert(trusted.candidate_fitness > trusted.baseline_fitness);

    EvolutionExperiment simulated_only{
        "simulated-only", EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8},
        0.0, 0.0, 0.05, 0.0};
    const auto rejected = EvolutionExperimentCoordinator::run(
        simulated_only, sandbox, fake_baseline, fake_candidate, EvolutionTrialConfig{});
    assert(!rejected.executed);
    assert(!simulated_only.has_valid_isolation_attestation());
    return 0;
}
