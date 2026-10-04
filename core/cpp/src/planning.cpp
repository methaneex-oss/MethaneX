#include "jarvis/core/planning.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double finite_or_zero(double value) noexcept {
    return std::isfinite(value) ? value : 0.0;
}

double unit(double value) noexcept {
    return std::clamp(finite_or_zero(value), 0.0, 1.0);
}

double signed_unit(double value) noexcept {
    return std::clamp(finite_or_zero(value), -1.0, 1.0);
}

double nonnegative(double value) noexcept {
    return std::max(0.0, finite_or_zero(value));
}

double score_action(const CandidateAction& action, const PlanningContext& context,
                    const PlanningPolicy& policy) noexcept {
    const double risk = unit(action.risk);
    const double reversibility = unit(action.reversibility);
    const double cost = nonnegative(action.resource_cost);
    const double budget = nonnegative(context.resource_budget);
    const double cost_ratio = budget > 0.0 ? cost / budget : (cost > 0.0 ? 1.0 : 0.0);
    const double goal_priority = unit(context.goal_priority);
    const double goal_progress = unit(context.goal_progress);
    const double threat = unit(context.threat);
    const double uncertainty = unit(context.uncertainty);
    const double deadline = unit(context.deadline_pressure);
    const double remaining_goal = 1.0 - goal_progress;

    // Affective dimensions are continuous appraisal signals. They modulate
    // existing planning terms rather than directly selecting an action.
    const double valence = signed_unit(context.valence);
    const double arousal = unit(context.arousal);
    const double affective_uncertainty = unit(context.affective_uncertainty);
    const double tension = unit(context.tension);
    const double stability = unit(context.stability);
    const double affective_utility = policy.affective_value_weight * valence *
                                      finite_or_zero(action.expected_value);
    const double affective_reversibility = policy.affective_uncertainty_weight *
                                            affective_uncertainty * reversibility;
    const double affective_risk_penalty = policy.tension_weight * tension *
                                          risk * (1.0 - reversibility);
    const double stability_modifier = 1.0 + policy.stability_weight *
                                      (1.0 - stability) * arousal;

    return policy.utility_weight * finite_or_zero(action.utility)
        + policy.expected_value_weight * finite_or_zero(action.expected_value)
            * (1.0 + policy.goal_weight * goal_priority * remaining_goal)
        + affective_utility
        + policy.urgency_weight * deadline * unit(action.urgency)
        + policy.reversibility_weight * uncertainty * reversibility
        + affective_reversibility
        + policy.threat_weight * threat * (1.0 - risk)
        - policy.risk_weight * stability_modifier * risk * (1.0 - reversibility)
        - affective_risk_penalty
        - policy.resource_weight * cost_ratio;
}

} // namespace

Plan Planner::build(const std::vector<CandidateAction>& actions, std::size_t horizon) const {
    return build(actions, horizon, PlanningContext{});
}

Plan Planner::build(const std::vector<CandidateAction>& actions, std::size_t horizon,
                    const PlanningContext& context) const {
    Plan plan{};
    if (actions.empty() || horizon == 0) return plan;

    std::vector<CandidateAction> ranked = actions;
    std::stable_sort(ranked.begin(), ranked.end(), [&](const auto& a, const auto& b) {
        return score_action(a, context, policy_) > score_action(b, context, policy_);
    });

    const std::size_t count = std::min(horizon, ranked.size());
    plan.steps.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        const auto& action = ranked[i];
        const double risk = unit(action.risk);
        const double reversibility = unit(action.reversibility);

        plan.steps.push_back(PlanStep{action, score_action(action, context, policy_)});
        plan.expected_value += nonnegative(action.expected_value);
        plan.risk = std::clamp(plan.risk + risk * (1.0 - reversibility), 0.0, 1.0);
    }
    return plan;
}

} // namespace jarvis::core
