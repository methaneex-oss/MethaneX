#include "jarvis/core/cognitive_cycle.hpp"

#include <algorithm>

namespace jarvis::core {

std::optional<Goal> CognitiveCycle::select_goal(const CognitiveCycleInput& input,
                                                const std::vector<Goal>& eligible) const {
    if (eligible.empty()) {
        return std::nullopt;
    }

    if (input.goal_id.has_value()) {
        const auto it = std::find_if(eligible.begin(), eligible.end(), [&](const Goal& goal) {
            return goal.id == *input.goal_id;
        });
        if (it == eligible.end()) {
            return std::nullopt;
        }
        return *it;
    }

    return eligible.front();
}

CognitiveCycleResult CognitiveCycle::run(const CognitiveCycleInput& input) const {
    CognitiveCycleResult result;

    if (input.planning_horizon == 0) {
        result.status = CognitiveCycleStatus::no_action;
        return result;
    }

    result.context.observation = brain_.observe(input.observation);
    result.context.memories = brain_.memory().recall_ranked(input.observation.data, input.memory_limit);
    result.context.beliefs = brain_.beliefs();
    result.context.causal_links = brain_.causal_links();

    ReasoningProblem problem;
    problem.premises = result.context.beliefs;
    problem.causal_links = result.context.causal_links;
    problem.max_steps = input.reasoning_steps;
    result.context.reasoning = ReasoningEngine{}.solve(problem);

    result.context.eligible_goals = brain_.eligible_goals();
    const auto selected = select_goal(input, result.context.eligible_goals);
    if (!selected.has_value()) {
        result.status = input.goal_id.has_value() ? CognitiveCycleStatus::invalid_goal
                                                   : CognitiveCycleStatus::no_goal;
        result.context.reflection = brain_.reflect();
        return result;
    }
    result.context.selected_goal = *selected;

    if (input.candidate_actions.empty()) {
        result.status = CognitiveCycleStatus::no_action;
        result.context.reflection = brain_.reflect();
        return result;
    }

    result.context.plan = brain_.plan(input.candidate_actions, input.planning_horizon);
    if (result.context.plan.steps.empty()) {
        result.status = CognitiveCycleStatus::no_action;
        result.context.reflection = brain_.reflect();
        return result;
    }

    std::vector<CandidateAction> planned_actions;
    planned_actions.reserve(result.context.plan.steps.size());
    for (const auto& step : result.context.plan.steps) {
        planned_actions.push_back(step.action);
    }

    const auto self_state = brain_.self_state_model().snapshot();
    result.context.decision_context = DecisionContext{
        selected->priority,
        selected->progress,
        result.context.plan.expected_value,
        result.context.plan.risk,
        input.resource_budget,
        self_state.uncertainty,
        brain_.threat().score,
        input.deadline_pressure,
    };

    result.context.decisions = brain_.decision_engine().decide(
        planned_actions, result.context.decision_context);
    if (result.context.decisions.empty()) {
        result.status = CognitiveCycleStatus::no_action;
        result.context.reflection = brain_.reflect();
        return result;
    }

    result.context.reflection = brain_.reflect();
    result.status = CognitiveCycleStatus::completed;
    return result;
}

double CognitiveCycle::learn_from_outcome(const Evidence& evidence) const {
    return brain_.learn(evidence);
}

bool CognitiveCycle::resolve_prediction(const std::string& key, const Scalar& actual) const {
    return brain_.resolve_prediction(key, actual);
}

} // namespace jarvis::core
