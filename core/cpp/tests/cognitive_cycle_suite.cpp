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
    input.action_constraints = ActionConstraints{0.5, false};

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
    assert(result.context.action_assessments.size() == result.context.decisions.size());
    assert(result.context.action_assessments.front().action.name == result.context.decisions.front().action.name);
    assert(result.context.action_assessments.front().permitted);

    CognitiveCycleInput constrained = input;
    constrained.action_constraints = ActionConstraints{0.05, false};
    const auto constrained_result = cycle.run(constrained);
    assert(constrained_result.status == CognitiveCycleStatus::completed);
    assert(!constrained_result.context.action_assessments.empty());
    for (const auto& assessment : constrained_result.context.action_assessments) {
        assert(assessment.disposition == ActionDisposition::reject);
        assert(!assessment.permitted);
    }

    const auto prediction = brain.predict("temperature_next", 43.0, 0.8);
    assert(!prediction.key.empty());
    const auto before_reflection = brain.reflect();
    const auto feedback = cycle.process_outcome(
        prediction.key,
        Scalar{45.0},
        Evidence{"sensor", "temperature", Scalar{45.0}, 0.9});
    // resolve_prediction reports prediction correctness; a resolved prediction can
    // still be incorrect, and that error is what feeds adaptation and learning.
    assert(!feedback.prediction_resolved);
    assert(feedback.learned_reliability >= 0.0 && feedback.learned_reliability <= 1.0);
    assert(feedback.reflection.prediction_accuracy <= before_reflection.prediction_accuracy ||
           feedback.reflection.prediction_accuracy == 0.0);
    const auto metric = brain.learning_metric("temperature");
    assert(metric != nullptr);
    assert(metric->observations > 0);

    const auto duplicate_feedback = cycle.process_outcome(prediction.key, Scalar{45.0});
    assert(!duplicate_feedback.prediction_resolved);

    const auto learned = cycle.learn_from_outcome(Evidence{"sensor", "temperature", 43.0, 0.9});
    assert(learned >= 0.0 && learned <= 1.0);

    CognitiveCycleInput invalid = input;
    invalid.goal_id = "missing-goal";
    const auto invalid_result = cycle.run(invalid);
    assert(invalid_result.status == CognitiveCycleStatus::invalid_goal);

    std::filesystem::remove(journal, ec);
    return 0;
}
