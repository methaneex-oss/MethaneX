#include "jarvis/core/brain.hpp"
#include "jarvis/core/cognitive_cycle.hpp"
#include "jarvis/core/action_execution.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>

using namespace jarvis::core;

int main() {
    ActionAssessment permitted;
    permitted.action = CandidateAction{"protect", 0.9, 0.9, 0.1, 1.0, 0.1, 0.0, 0.9, DecisionOutcome::act};
    permitted.disposition = ActionDisposition::execute;
    permitted.permitted = true;

    bool executed = false;
    bool rolled_back = false;
    const auto verified = ActionExecutor{}.run(ActionExecutionRequest{
        permitted,
        [&](const CandidateAction&) { executed = true; return true; },
        [&](const CandidateAction&) { return executed; },
        [&](const CandidateAction&) { rolled_back = true; return true; }});
    assert(verified.status == ActionExecutionStatus::verified);
    assert(verified.authorized && verified.executed && verified.verified);
    assert(!rolled_back);
    assert(std::abs(verified.outcome.expected_consequence - permitted.action.expected_consequence) < 1e-9);

    // Explicit consequence observation preserves the expectation and derives
    // prediction error from the real observed consequence. No semantic
    // emotion mapping is involved.
    auto consequence_action = permitted;
    consequence_action.action.expected_consequence = 0.8;
    const auto consequence = ActionExecutor{}.run(ActionExecutionRequest{
        consequence_action,
        [](const CandidateAction&) { return true; },
        [](const CandidateAction&) { return true; },
        {},
        [](const CandidateAction&) { return 0.2; }});
    assert(consequence.outcome.observed);
    assert(std::abs(consequence.outcome.expected_consequence - 0.8) < 1e-9);
    assert(std::abs(consequence.outcome.actual_consequence - 0.2) < 1e-9);
    assert(std::abs(consequence.outcome.consequence_error + 0.6) < 1e-9);
    assert(std::abs(consequence.action.expected_consequence - 0.8) < 1e-9);

    bool failing_execution = false;
    const auto failed = ActionExecutor{}.run(ActionExecutionRequest{
        permitted,
        [&](const CandidateAction&) { failing_execution = true; return false; },
        [&](const CandidateAction&) { return true; },
        {}});
    assert(failing_execution);
    assert(failed.status == ActionExecutionStatus::failed);
    assert(!failed.executed);
    assert(std::abs(failed.outcome.expected_consequence - permitted.action.expected_consequence) < 1e-9);

    const auto rejected = ActionExecutor{}.run(ActionExecutionRequest{
        ActionAssessment{permitted.action, ActionDisposition::reject, false, 0.1, "risk_limit"},
        [&](const CandidateAction&) { return true; },
        [&](const CandidateAction&) { return true; },
        {}});
    assert(rejected.status == ActionExecutionStatus::rejected);
    assert(!rejected.authorized);
    assert(std::abs(rejected.outcome.expected_consequence - permitted.action.expected_consequence) < 1e-9);

    bool verify_failed = false;
    bool rollback_called = false;
    const auto rollback = ActionExecutor{}.run(ActionExecutionRequest{
        permitted,
        [&](const CandidateAction&) { return true; },
        [&](const CandidateAction&) { verify_failed = true; return false; },
        [&](const CandidateAction&) { rollback_called = true; return true; }});
    assert(verify_failed && rollback_called);
    assert(rollback.status == ActionExecutionStatus::rolled_back);
    assert(rollback.executed && rollback.rolled_back && !rollback.verified);

    const auto journal = std::filesystem::temp_directory_path() / "jarvis_phase7_action_test.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    Brain brain(journal);
    assert(brain.create_goal(Goal{"goal-alpha", "protect the system", 0.8, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
    assert(brain.activate_goal("goal-alpha"));

    // Establish the pre-learning behavior with two close candidates. The
    // baseline should prefer protect before consequence evidence exists.
    CognitiveCycle cognitive_cycle(brain);
    CognitiveCycleInput cognitive_input;
    cognitive_input.observation = Event{0, 0, "sensor", "observation", {{"context", "goal-alpha"}}};
    cognitive_input.goal_id = "goal-alpha";
    cognitive_input.developmental_context = "goal-alpha";
    cognitive_input.planning_horizon = 2;
    cognitive_input.resource_budget = 10.0;
    CandidateAction protect_action = permitted.action;
    protect_action.utility = 0.80;
    protect_action.expected_value = 0.80;
    CandidateAction wait_action = permitted.action;
    wait_action.name = "wait";
    wait_action.utility = 0.78;
    wait_action.expected_value = 0.80;
    cognitive_input.candidate_actions = {protect_action, wait_action};
    const auto baseline_cycle = cognitive_cycle.run(cognitive_input);
    assert(baseline_cycle.status == CognitiveCycleStatus::completed);
    assert(!baseline_cycle.context.plan.steps.empty());
    assert(baseline_cycle.context.plan.steps.front().action.name == "protect");

    const auto before_appraisal = brain.affective_appraisal();
    auto learning_assessment = permitted;
    learning_assessment.action.expected_consequence = 0.9;
    const auto result = brain.execute_action(
        learning_assessment,
        [](const CandidateAction&) { return true; },
        [](const CandidateAction&) { return true; },
        {},
        [](const CandidateAction&) { return -0.4; });
    assert(result.status == ActionExecutionStatus::verified);
    assert(result.outcome.observed);
    assert(std::abs(result.outcome.consequence_error + 1.3) < 1e-9);

    const auto after_appraisal = brain.affective_appraisal();
    assert(brain.affective_learning_updates() > 0);
    assert(
        std::abs(after_appraisal.outcome_weight - before_appraisal.outcome_weight) > 1e-12 ||
        std::abs(after_appraisal.error_weight - before_appraisal.error_weight) > 1e-12 ||
        std::abs(after_appraisal.novelty_weight - before_appraisal.novelty_weight) > 1e-12 ||
        std::abs(after_appraisal.salience_weight - before_appraisal.salience_weight) > 1e-12 ||
        std::abs(after_appraisal.uncertainty_weight - before_appraisal.uncertainty_weight) > 1e-12 ||
        std::abs(after_appraisal.tension_error_weight - before_appraisal.tension_error_weight) > 1e-12);

    const auto learned = brain.beliefs();
    bool saw_action_feedback = false;
    for (const auto& belief : learned) {
        if (belief.key == "action.protect") {
            saw_action_feedback = true;
            assert(std::get<std::string>(belief.value) == "verified");
        }
    }
    assert(saw_action_feedback);
    const auto strategies = brain.developmental_strategies();
    assert(strategies.size() == 1);
    assert(strategies.front().context == "goal-alpha");
    assert(strategies.front().action == "protect");
    assert(strategies.front().value < 0.0);
    const auto* best = brain.developmental_best_strategy("goal-alpha");
    assert(best != nullptr && best->action == "protect");

    // The same evidence must alter actual planning, not merely fill a memory
    // structure: the negative observed consequence demotes protect below wait.
    const auto learned_cycle_result = cognitive_cycle.run(cognitive_input);
    assert(learned_cycle_result.status == CognitiveCycleStatus::completed);
    assert(!learned_cycle_result.context.plan.steps.empty());
    assert(learned_cycle_result.context.plan.steps.front().action.name == "wait");
    bool protect_utility_was_reduced = false;
    for (const auto& step : learned_cycle_result.context.plan.steps) {
        if (step.action.name == "protect") {
            protect_utility_was_reduced = step.action.utility < protect_action.utility;
        }
    }
    assert(protect_utility_was_reduced);

    Brain restored(journal);
    const auto restored_strategies = restored.developmental_strategies();
    assert(restored_strategies.size() == 1);
    assert(restored_strategies.front().context == "goal-alpha");
    assert(restored_strategies.front().action == "protect");
    CognitiveCycle restored_cycle(restored);
    const auto replayed_behavior = restored_cycle.run(cognitive_input);
    assert(replayed_behavior.status == CognitiveCycleStatus::completed);
    assert(!replayed_behavior.context.plan.steps.empty());
    assert(replayed_behavior.context.plan.steps.front().action.name == "wait");
    std::filesystem::remove(journal, ec);
    return 0;
}
