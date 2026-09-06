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

double nonnegative(double value) noexcept {
    return std::max(0.0, finite_or_zero(value));
}

} // namespace

Plan Planner::build(const std::vector<CandidateAction>& actions, std::size_t horizon) const {
    return build(actions, horizon, PlanningContext{});
}

Plan Planner::build(const std::vector<CandidateAction>& actions, std::size_t horizon,
                    const PlanningContext& context) const {
    Plan plan{};
    if (actions.empty() || horizon == 0) return plan;

    const double goal_priority = unit(context.goal_priority);
    const double goal_progress = unit(context.goal_progress);
    const double threat = unit(context.threat);
    const double uncertainty = unit(context.uncertainty);
    const double deadline = unit(context.deadline_pressure);
    const double budget = nonnegative(context.resource_budget);
    const double remaining_goal = 1.0 - goal_progress;

    std::vector<CandidateAction> ranked = actions;
    std::stable_sort(ranked.begin(), ranked.end(), [&](const auto& a, const auto& b) {
        const auto score = [&](const CandidateAction& action) {
            const double risk = unit(action.risk);
            const double reversibility = unit(action.reversibility);
            const double cost = nonnegative(action.resource_cost);
            const double cost_ratio = budget > 0.0 ? std::min(1.0, cost / budget) : 0.0;
            const double urgency = unit(action.urgency);

            return finite_or_zero(action.utility)
                + finite_or_zero(action.expected_value) * (1.0 + goal_priority * remaining_goal)
                + deadline * urgency
                + uncertainty * reversibility * 0.25
                + threat * (1.0 - risk) * 0.25
                - risk * (1.0 - reversibility)
                - cost_ratio * 0.5;
        };
        return score(a) > score(b);
    });

    const std::size_t count = std::min(horizon, ranked.size());
    plan.steps.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        const auto& action = ranked[i];
        const double risk = unit(action.risk);
        const double reversibility = unit(action.reversibility);
        const double cost = nonnegative(action.resource_cost);
        const double cost_ratio = budget > 0.0 ? std::min(1.0, cost / budget) : 0.0;
        const double score = finite_or_zero(action.utility)
            + finite_or_zero(action.expected_value) * (1.0 + goal_priority * remaining_goal)
            + deadline * unit(action.urgency)
            + uncertainty * reversibility * 0.25
            + threat * (1.0 - risk) * 0.25
            - risk * (1.0 - reversibility)
            - cost_ratio * 0.5;

        plan.steps.push_back(PlanStep{action, finite_or_zero(score)});
        plan.expected_value += nonnegative(action.expected_value);
        plan.risk = std::clamp(plan.risk + risk * (1.0 - reversibility), 0.0, 1.0);
    }
    return plan;
}

} // namespace jarvis::core
