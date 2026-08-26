#include "jarvis/core/planning.hpp"

#include <algorithm>

namespace jarvis::core {

Plan Planner::build(const std::vector<CandidateAction>& actions, std::size_t horizon) const {
    Plan plan{};
    if (actions.empty() || horizon == 0) return plan;
    std::vector<CandidateAction> ranked = actions;
    std::sort(ranked.begin(), ranked.end(), [](const auto& a, const auto& b) {
        return (a.utility + a.expected_value - a.risk) > (b.utility + b.expected_value - b.risk);
    });
    const std::size_t count = std::min(horizon, ranked.size());
    plan.steps.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        const auto& action = ranked[i];
        const double score = action.utility + action.expected_value - action.risk * (1.0 - action.reversibility);
        plan.steps.push_back(PlanStep{action, score});
        plan.expected_value += action.expected_value;
        plan.risk = std::clamp(plan.risk + action.risk * (1.0 - action.reversibility), 0.0, 1.0);
    }
    return plan;
}

} // namespace jarvis::core
