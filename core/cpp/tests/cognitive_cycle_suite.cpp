#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <filesystem>
#include <string>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_cycle_suite.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

    Brain brain(journal);
    CognitiveCycle cycle(brain);

    Goal goal;
    goal.id = "stabilize";
    goal.description = "Stabilize the observed system";
    goal.priority = 1.0;
    goal.created_cycle = 0;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    CognitiveCycleInput input;
    input.observation = Event{0, 0, "sensor", "observation", {{"temperature", 42.0}, {"status", std::string("unstable")}}};
    input.candidate_actions = {
        CandidateAction{"stabilize", 0.9, 0.8, 0.2, 1.0, 1.0, 0.0, 0.8},
        CandidateAction{"inspect", 0.6, 0.5, 0.1, 1.0, 0.5, 0.0, 0.4, DecisionOutcome::recommend},
    };
    input.goal_id = goal.id;
    input.planning_horizon = 2;
    input.memory_limit = 4;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.deadline_pressure = 0.5;

    const auto result = cycle.run(input);
    assert(result.status == CognitiveCycleStatus::completed);
    assert(result.context.observation.event.sequence != 0);
    assert(!result.context.beliefs.empty());
    assert(!result.context.eligible_goals.empty());
    assert(result.context.selected_goal.id == goal.id);
    assert(!result.context.plan.steps.empty());
    assert(!result.context.decisions.empty());
    assert(result.context.decisions.front().action.name == result.context.plan.steps.front().action.name);
    assert(result.context.decision_context.goal_priority == goal.priority);
    assert(result.context.decision_context.plan_expected_value == result.context.plan.expected_value);
    assert(result.context.decision_context.resource_budget == input.resource_budget);
    assert(result.context.decision_context.deadline_pressure == input.deadline_pressure);

    const auto learned = cycle.learn_from_outcome(Evidence{"sensor", "temperature", 43.0, 0.9});
    assert(learned >= 0.0 && learned <= 1.0);

    CognitiveCycleInput invalid = input;
    invalid.goal_id = "missing-goal";
    const auto invalid_result = cycle.run(invalid);
    assert(invalid_result.status == CognitiveCycleStatus::invalid_goal);

    std::filesystem::remove(journal, ec);
    return 0;
}
