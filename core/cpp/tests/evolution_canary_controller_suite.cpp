#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/process_isolation.hpp"
#include "evolution_test_evaluator.hpp"

#include <cassert>
#include <string>

using namespace jarvis::core;

namespace {
void attest_isolated(EvolutionExperiment& experiment) {
    ProcessIsolationBackend backend;
    const IsolatedEvaluationSpec spec{
        IsolatedCommand{"/proc/self/exe", {"--test-evaluator"}, ""},
        "local-test-procedure-v1",
        "baseline:" + experiment.proposal.key + ":" + std::to_string(experiment.proposal.current),
        "candidate:" + experiment.proposal.key + ":" + std::to_string(experiment.proposal.proposed),
        experiment.proposal.current,
        experiment.proposal.proposed};
    EvolutionExperimentRunner::run_isolated_evaluation(experiment, backend, spec);
}
} // namespace

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--test-evaluator")\n        return test_support::run_evolution_test_evaluator(argc, argv);
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
    assert(replay_controller.replay_adoption(replay_experiment));
    assert(replay_controller.replay_adoption(replay_experiment));
    assert(replay_history.for_experiment("exp-replay").size() == 1);
    assert(replay_controller.adoption_journal().get("exp-replay")->state == AdoptionState::Adopted);
    assert(replay_model.rollback("replay.weight"));
    assert(replay_controller.replay_rollback("exp-replay", "replayed"));
    assert(replay_controller.replay_rollback("exp-replay", "replayed"));
    assert(replay_history.for_experiment("exp-replay").size() == 1);
    assert(replay_controller.adoption_journal().get("exp-replay")->state == AdoptionState::RolledBack);

    const auto records = history.for_experiment("exp-canary");
    assert(records.size() >= 2);
    assert(records.back().action == EvolutionRecordAction::RolledBack);
    assert(!records.back().reason.empty());
    return 0;
}
