#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_digest.hpp"
#include "jarvis/core/process_isolation.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace jarvis::core;

namespace {
std::string evaluator_path;
std::string baseline_artifact_path;
std::string candidate_artifact_path;

void write_artifacts(const EvolutionExperiment& experiment) {
    { std::ofstream out(baseline_artifact_path); out << std::setprecision(17) << experiment.proposal.current; }
    { std::ofstream out(candidate_artifact_path); out << std::setprecision(17) << experiment.proposal.proposed; }
}
void attest_isolated(EvolutionExperiment& experiment) {
    write_artifacts(experiment);
    ProcessIsolationBackend backend;
    IsolatedEvaluationProcedure procedure{
        IsolatedCommand{evaluator_path, {"--trusted-test-evaluator"}, ""},
        "canary-suite-local-evaluator-v1", "held-out-linear-regression-v1",
        baseline_artifact_path, candidate_artifact_path, detail::sha256_file(evaluator_path)};
    const auto outcome = EvolutionExperimentRunner::run_isolated_evaluation(
        experiment, backend, procedure, 4, 4, 0.5);
    assert(outcome == ExperimentOutcome::Improved);
}
} // namespace

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--trusted-test-evaluator") {
        if (argc != 14 || std::string(argv[2]) != "--jarvis-evaluate-v1") return 21;
        std::ifstream artifact(argv[9]);
        std::string coefficient_text;
        if (!artifact || !(artifact >> coefficient_text)) return 22;
        const double coefficient = std::stod(coefficient_text);
        if (std::abs(coefficient - std::stod(argv[6])) > 1e-12) return 23;
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

    evaluator_path = std::filesystem::absolute(argv[0]).string();
    const auto temp = std::filesystem::temp_directory_path();
    baseline_artifact_path = (temp / "jarvis_canary_baseline_artifact.txt").string();
    candidate_artifact_path = (temp / "jarvis_canary_candidate_artifact.txt").string();

    EvolutionModel model;
    model.register_parameter("reasoning.weight", 0.4);
    EvolutionHistory history;
    EvolutionSafetyPolicy policy;
    policy.minimum_confidence = 0.8;

    EvolutionController controller(model, history, policy);
    EvolutionExperiment experiment{
        "exp-canary",
        EvolutionProposal{"reasoning.weight", 0.4, 0.5, 0.1, 0.95},
        0.70, 0.84, 0.05, 0.95, ExperimentOutcome::Improved, true};
    attest_isolated(experiment);

    assert(controller.record_evaluation(experiment));
    assert(controller.adopt(experiment));
    const auto* adopted = model.parameter("reasoning.weight");
    assert(adopted != nullptr && adopted->value != adopted->baseline);
    const auto adoption_record = controller.adoption_journal().get("exp-canary");
    assert(adoption_record.has_value());
    assert(adoption_record->state == AdoptionState::Adopted);
    const auto adoption_history = history.for_experiment("exp-canary");
    assert(adoption_history.size() == 2);
    assert(adoption_history.front().action == EvolutionRecordAction::Evaluated);
    assert(adoption_history.back().action == EvolutionRecordAction::Adopted);

    controller.observe_canary("reasoning.weight", "exp-canary", {0.84, 0.82});
    controller.observe_canary("reasoning.weight", "exp-canary", {0.84, 0.80});
    const auto decision = controller.observe_canary("reasoning.weight", "exp-canary", {0.84, 0.78});
    assert(decision.sufficient_evidence);
    assert(decision.rollback);

    const auto* restored = model.parameter("reasoning.weight");
    assert(restored != nullptr && restored->value == restored->baseline);

    EvolutionModel isolated_model;
    isolated_model.register_parameter("planner.weight", 0.4);
    EvolutionHistory isolated_history;
    EvolutionController isolated(isolated_model, isolated_history, policy);
    EvolutionExperiment second{
        "exp-second",
        EvolutionProposal{"planner.weight", 0.4, 0.5, 0.1, 0.95},
        0.70, 0.84, 0.05, 0.95, ExperimentOutcome::Improved, true};
    attest_isolated(second);
    assert(isolated.record_evaluation(second));
    assert(isolated.adopt(second));
    const auto preview = isolated.preview_canary_for_brain("exp-second", {0.84, 0.83});
    assert(!preview.sufficient_evidence);
    const auto first = isolated.observe_canary_for_brain("exp-second", {0.84, 0.83});
    assert(!first.sufficient_evidence);
    const auto second_decision = isolated.observe_canary_for_brain("exp-other", {0.84, 0.70});
    assert(!second_decision.sufficient_evidence);
    const auto second_continued = isolated.observe_canary_for_brain("exp-second", {0.84, 0.83});
    assert(!second_continued.sufficient_evidence);
    const auto third = isolated.observe_canary_for_brain("exp-second", {0.84, 0.83});
    assert(third.sufficient_evidence);
    assert(!third.rollback);

    EvolutionModel replay_model;
    replay_model.register_parameter("replay.weight", 0.4);
    EvolutionHistory replay_history;
    EvolutionController replay_controller(replay_model, replay_history, policy);
    EvolutionExperiment replay_experiment{
        "exp-replay",
        EvolutionProposal{"replay.weight", 0.4, 0.5, 0.1, 0.95},
        0.70, 0.84, 0.05, 0.95, ExperimentOutcome::Improved, true};
    attest_isolated(replay_experiment);
    assert(replay_controller.replay_evaluation(replay_experiment));
    assert(replay_controller.replay_evaluation(replay_experiment));
    assert(replay_history.for_experiment("exp-replay").size() == 1);
    assert(replay_controller.adoption_journal().get("exp-replay")->state == AdoptionState::Pending);
    assert(replay_model.adopt(replay_experiment.proposal));
    assert(replay_controller.replay_adoption(replay_experiment));
    assert(replay_controller.replay_adoption(replay_experiment));
    assert(replay_history.for_experiment("exp-replay").size() == 2);
    assert(replay_controller.adoption_journal().get("exp-replay")->state == AdoptionState::Adopted);
    assert(replay_model.rollback("replay.weight"));
    assert(replay_controller.replay_rollback("exp-replay", "replayed"));
    assert(replay_controller.replay_rollback("exp-replay", "replayed"));
    assert(replay_history.for_experiment("exp-replay").size() == 2);
    assert(replay_controller.adoption_journal().get("exp-replay")->state == AdoptionState::RolledBack);

    const auto records = history.for_experiment("exp-canary");
    assert(records.size() >= 2);
    assert(records.back().action == EvolutionRecordAction::RolledBack);
    assert(!records.back().reason.empty());

    std::error_code ec;
    std::filesystem::remove(baseline_artifact_path, ec);
    std::filesystem::remove(candidate_artifact_path, ec);
    return 0;
}
