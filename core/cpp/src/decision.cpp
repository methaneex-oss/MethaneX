#include "jarvis/core/decision.hpp"

#include <algorithm>

namespace jarvis::core {

std::vector<Decision> DecisionEngine::rank(const std::vector<CandidateAction>& actions, double uncertainty) const {
    std::vector<Decision> result;
    result.reserve(actions.size());
    for (const auto& action : actions) {
        const double exploration = std::clamp(uncertainty, 0.0, 1.0) * std::clamp(action.reversibility, 0.0, 1.0);
        const double risk_cost = action.risk * (1.0 - std::clamp(action.reversibility, 0.0, 1.0));
        result.push_back({action, action.utility + action.expected_value + exploration - risk_cost});
    }
    std::sort(result.begin(), result.end(), [](const Decision& a, const Decision& b) { return a.score > b.score; });
    return result;
}

} // namespace jarvis::core
