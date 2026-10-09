#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <limits>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_brain_action_consequence_integration.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    Brain brain(journal);
    Goal goal;
    goal.id = "consequence-development";
    goal.description = "Prefer actions with better observed consequences";
    goal.priority = 0.8;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    CognitiveCycle cycle(brain);
    CognitiveCycleInput input;
    input.goal_id = goal.id;
    input.developmental_context = goal.id;
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    input.observation = Event{0, 1, "sensor", "observation", {{"temperature", 20.0}}};
    CandidateAction calibrate;
    calibrate.name = "calibrate";
    calibrate.utility = 0.8;
    calibrate.expected_value = 0.8;
    calibrate.confidence = 0.9;
    calibrate.risk = 0.1;
    calibrate.reversibility = 1.0;
    CandidateAction wait;
    wait.name = "wait";
    wait.utility = 0.8;
    wait.expected_value = 0.8;
    wait.confidence = 0.9;
    wait.risk = 0.1;
    wait.reversibility = 1.0;
    input.candidate_actions = {calibrate, wait};

    const auto before_learning = cycle.run(input);
    assert(before_learning.status == CognitiveCycleStatus::completed);
    assert(!before_learning.context.plan.steps.empty());
    assert(before_learning.context.plan.steps.front().action.name == "calibrate");

    ActionAssessment assessment;
    assessment.action = calibrate;
    assessment.action.expected_consequence = 0.8;
    assessment.disposition = ActionDisposition::execute;
    assessment.permitted = true;
    assessment.confidence = 0.9;

    bool executed = false;
    const auto result = brain.execute_action(
        assessment,
        [&](const CandidateAction&) { executed = true; return true; },
        [&](const CandidateAction&) { return executed; },
        {},
        [](const CandidateAction&) { return -0.2; });

    assert(result.authorized);
    assert(result.executed);
    assert(result.verified);
    assert(result.outcome.observed);
    assert(std::abs(result.action.expected_consequence - 0.8) < 1e-9);
    assert(std::abs(result.outcome.actual_consequence + 0.2) < 1e-9);
    assert(std::abs(result.outcome.consequence_error + 1.0) < 1e-9);

    bool saw_action_outcome = false;
    for (const auto& event : brain.memory().all()) {
        if (event.kind != "action_outcome") continue;
        saw_action_outcome = true;
        assert(std::get<std::string>(event.data.at("action")) == "calibrate");
        assert(std::abs(std::get<double>(event.data.at("expected_consequence")) - 0.8) < 1e-9);
        assert(std::abs(std::get<double>(event.data.at("actual_consequence")) + 0.2) < 1e-9);
        assert(std::abs(std::get<double>(event.data.at("consequence_error")) + 1.0) < 1e-9);
    }
    assert(saw_action_outcome);
    assert(brain.affective_learning_updates() > 0);

    // A successful execution with no valid consequence observation is not
    // evidence that the action was neutral or beneficial.
    ActionAssessment unobserved_assessment;
    unobserved_assessment.action = wait;
    unobserved_assessment.disposition = ActionDisposition::execute;
    unobserved_assessment.permitted = true;
    unobserved_assessment.confidence = 0.9;
    const auto affect_before_unobserved = brain.affective_state();
    bool unobserved_executed = false;
    const auto unobserved_result = brain.execute_action(
        unobserved_assessment,
        [&](const CandidateAction&) { unobserved_executed = true; return true; },
        [&](const CandidateAction&) { return unobserved_executed; },
        {},
        [](const CandidateAction&) {
            return std::numeric_limits<double>::quiet_NaN();
        });
    assert(unobserved_result.executed);
    assert(unobserved_result.verified);
    assert(!unobserved_result.outcome.observed);
    const auto affect_after_unobserved = brain.affective_state();
    assert(std::abs(affect_after_unobserved.valence - affect_before_unobserved.valence) < 1e-12);
    assert(affect_after_unobserved.uncertainty > affect_before_unobserved.uncertainty);
    bool unobserved_strategy_created = false;
    for (const auto& strategy : brain.developmental_strategies()) {
        if (strategy.context == goal.id && strategy.action == "wait") {
            unobserved_strategy_created = true;
            break;
        }
    }
    assert(!unobserved_strategy_created);

    const auto* learned_strategy = brain.developmental_best_strategy(goal.id);
    assert(learned_strategy != nullptr);
    assert(learned_strategy->action == "calibrate");
    assert(learned_strategy->value < 0.0);
    input.observation = Event{0, 2, "sensor", "observation", {{"temperature", 21.0}}};
    const auto after_learning = cycle.run(input);
    assert(after_learning.status == CognitiveCycleStatus::completed);
    assert(!after_learning.context.plan.steps.empty());
    assert(after_learning.context.plan.steps.front().action.name == "wait");

    const auto live_affect = brain.affective_state();
    Brain restored(journal);
    assert(restored.affective_learning_updates() > 0);
    const auto restored_affect = restored.affective_state();
    assert(restored_affect.updates == live_affect.updates);
    assert(std::abs(restored_affect.valence - live_affect.valence) < 1e-12);
    assert(std::abs(restored_affect.uncertainty - live_affect.uncertainty) < 1e-12);
    assert(std::abs(restored_affect.tension - live_affect.tension) < 1e-12);
    const auto* restored_strategy = restored.developmental_best_strategy(goal.id);
    assert(restored_strategy != nullptr);
    assert(restored_strategy->action == "calibrate");
    assert(restored_strategy->value < 0.0);
    CognitiveCycle restored_cycle(restored);
    input.observation = Event{0, 3, "sensor", "observation", {{"temperature", 22.0}}};
    const auto after_restart = restored_cycle.run(input);
    assert(after_restart.status == CognitiveCycleStatus::completed);
    assert(!after_restart.context.plan.steps.empty());
    assert(after_restart.context.plan.steps.front().action.name == "wait");
    bool restored_action_outcome = false;
    for (const auto& event : restored.memory().all()) {
        if (event.kind == "action_outcome") {
            restored_action_outcome = true;
            break;
        }
    }
    assert(restored_action_outcome);

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
