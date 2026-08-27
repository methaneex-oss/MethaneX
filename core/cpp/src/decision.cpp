#include "jarvis/core/decision.hpp"

#include <algorithm>

namespace jarvis::core {

std::vector<Decision> DecisionEngine::rank(const std::vector<CandidateAction>& actions, double uncertainty, double threat) const {
    const double bounded_uncertainty = std::clamp(uncertainty, 0.0, 1.0);
    const double bounded_threat = std::clamp(threat, 0.0, 1.0);
    std::vector<Decision> result;
    result.reserve(actions.size());
    for (const auto& action : actions) {
        const double reversibility = std::clamp(action.reversibility, 0.0, 1.0);
        const double exploration = bounded_uncertainty * reversibility;
        const double risk_cost = action.risk * (1.0 - reversibility);
        const double threat_bias = bounded_threat * (1.0 - action.risk);
        result.push_back({action, action.utility + action.expected_value + exploration + threat_bias - risk_cost});
    }
    std::sort(result.begin(), result.end(), [](const Decision& a, const Decision& b) { return a.score > b.score; });
    return result;
}

} // namespace jarvis::core
