#include "jarvis/core/evolution_experiment_coordinator.hpp"
#include "jarvis/core/evolution_orchestrator.hpp"
#include "jarvis/core/evolution_digest.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace jarvis::core;

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--trusted-test-evaluator") {
        if (argc != 14 || std::string(argv[2]) != "--jarvis-evaluate-v1") return 21;
        std::ifstream artifact(argv[9]);
        std::string coefficient_text;
        if (!artifact || !(artifact >> coefficient_text)) return 22;
        const double coefficient = std::stod(coefficient_text);
        const double evaluated_value = std::stod(argv[6]);
        if (std::abs(coefficient - evaluated_value) > 1e-12) return 23;
        double squared_error = 0.0;
        for (double input = 1.0; input <= 4.0; input += 1.0) {
            const double error = coefficient * input - 0.8 * input;
            squared_error += error * error;
        }
        const double fitness = 1.0 / (1.0 + squared_error / 4.0);
        std::cout << "JARVIS_EVAL_V1\t" << argv[3] << "\t" << argv[4] << "\t"
                  << argv[5] << "\t" << argv[6] << "\t" << argv[7] << "\t"
                  << argv[8] << "\t" << argv[10] << "\t" << argv[11] << "\t"
                  << argv[12] << "\t" << argv[13] << "\t" << fitness;
        return 0;
    }

    const std::string evaluator_path = std::filesystem::absolute(argv[0]).string();
    EvolutionExperiment experiment{
        "trial-batch",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8},
        0.0, 0.0, 0.05, 0.0, ExperimentOutcome::Pending, false};

    EvolutionSandbox sandbox;
    const CandidateExecutor baseline = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 0.70, {}};
    };
    const CandidateExecutor candidate = [](const EvolutionProposal&, const SandboxLimits&) {
        return SandboxResult{true, true, false, false, true, 0.80, {}};
    };

    // Callback simulations remain useful, but the default production policy
    // must never accept them as isolated evaluation evidence.
    const auto simulated_rejected = EvolutionExperimentCoordinator::run(
        experiment, sandbox, baseline, candidate, EvolutionTrialConfig{});
    assert(!simulated_rejected.executed);
    assert(!experiment.has_valid_evaluation_evidence());

    // Explicit simulation mode still works for unit testing.
    experiment = EvolutionExperiment{
        "trial-batch-simulation",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8},
        0.0, 0.0, 0.05, 0.0, ExperimentOutcome::Pending, false};
    const auto simulated = EvolutionExperimentCoordinator::run(
        experiment, sandbox, baseline, candidate, EvolutionTrialConfig{4, 4, 0.05, 0.5, false});
    assert(simulated.executed);
    assert(simulated.baseline.count == 4 && simulated.candidate.count == 4);
    assert(experiment.outcome == ExperimentOutcome::Improved);
    assert(!experiment.has_valid_evaluation_evidence());

    const auto temp = std::filesystem::temp_directory_path();
    const auto baseline_path = (temp / "jarvis_coordinator_baseline_artifact.txt").string();
    const auto candidate_path = (temp / "jarvis_coordinator_candidate_artifact.txt").string();
    { std::ofstream out(baseline_path); out << std::setprecision(17) << 0.4; }
    { std::ofstream out(candidate_path); out << std::setprecision(17) << 0.5; }

    EvolutionExperiment production_experiment{
        "trial-batch-isolated",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8},
        0.0, 0.0, 0.05, 0.0, ExperimentOutcome::Pending, false};
    ProcessIsolationBackend backend;
    IsolatedEvaluationProcedure procedure{
        IsolatedCommand{evaluator_path, {"--trusted-test-evaluator"}, ""},
        "coordinator-suite-local-evaluator-v1", "artifact-score-v1",
        baseline_path, candidate_path, detail::sha256_file(evaluator_path)};

    // This uses the coordinator's default trial configuration (isolation on),
    // and measures both artifact states through the same pinned local evaluator.
    const auto isolated = EvolutionExperimentCoordinator::run(
        production_experiment, backend, procedure, EvolutionTrialConfig{});
    assert(isolated.executed);
    assert(isolated.baseline.count == 4 && isolated.candidate.count == 4);
    assert(isolated.outcome == ExperimentOutcome::Improved);
    assert(production_experiment.has_valid_evaluation_evidence());
    assert(production_experiment.has_valid_isolation_attestation());
    assert(production_experiment.baseline_artifact_digest !=
           production_experiment.candidate_artifact_digest);

    // The orchestrator's production entry point must route generated candidates
    // through the same isolated evaluator, then record, adopt, and canary the winner.
    EvolutionModel model;
    model.register_parameter("planner.weight", 0.4);
    EvolutionHistory history;
    EvolutionSafetyPolicy controller_policy;
    controller_policy.trusted_evaluator_digest = detail::sha256_file(evaluator_path);
    EvolutionController controller(model, history, controller_policy);
    EvolutionCandidateGenerator generator = [](const EvolutionOpportunity&) {
        return std::vector<EvolutionProposal>{
            EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.8}};
    };
    const EvolutionOpportunity opportunity{
        "local-evaluator-opportunity", "unit-test", 0.9, 0.9, 0.4, 0.5, 8, 1, 8};
    const auto now = std::chrono::steady_clock::now();
    EvolutionOrchestrator orchestrator;
    const auto orchestrated = orchestrator.run_isolated(
        opportunity, generator, backend, procedure, history,
        now, now - std::chrono::seconds(10), true, &controller);
    assert(orchestrated.experiments.size() == 1);
    assert(orchestrated.experiments.front().has_valid_evaluation_evidence());
    assert(orchestrated.experiments.front().outcome == ExperimentOutcome::Improved);
    assert(orchestrated.adopted == 1);
    const auto* adopted_parameter = model.parameter("planner.weight");
    assert(adopted_parameter != nullptr && adopted_parameter->value == 0.5);

    std::error_code ec;
    std::filesystem::remove(baseline_path, ec);
    std::filesystem::remove(candidate_path, ec);
    return 0;
}
