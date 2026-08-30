#include "jarvis/core/decision.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double finite_or_zero(double value) noexcept {
    return std::isfinite(value) ? value : 0.0;
}

double bounded_weight(double value) noexcept {
    return std::max(0.0, finite_or_zero(value));
}

double bounded_unit(double value) noexcept {
    return std::clamp(finite_or_zero(value), 0.0, 1.0);
}

} // namespace

std::vector<Decision> DecisionEngine::rank(const std::vector<CandidateAction>& actions,
                                           double uncertainty,
                                           double threat) const {
    const double bounded_uncertainty = bounded_unit(uncertainty);
    const double bounded_threat = bounded_unit(threat);
    const double utility_weight = bounded_weight(policy_.utility_weight);
    const double value_weight = bounded_weight(policy_.expected_value_weight);
    const double uncertainty_weight = bounded_weight(policy_.uncertainty_weight);
    const double threat_weight = bounded_weight(policy_.threat_weight);
    const double risk_weight = bounded_weight(policy_.risk_weight);

    std::vector<Decision> result;
    result.reserve(actions.size());
    for (const auto& action : actions) {
        const double utility = finite_or_zero(action.utility);
        const double expected_value = finite_or_zero(action.expected_value);
        const double risk = bounded_unit(action.risk);
        const double reversibility = bounded_unit(action.reversibility);
        const double exploration = bounded_uncertainty * reversibility;
        const double risk_cost = risk * (1.0 - reversibility);
        const double threat_bias = bounded_threat * (1.0 - risk);
        const double score = utility_weight * utility
            + value_weight * expected_value
            + uncertainty_weight * exploration
            + threat_weight * threat_bias
            - risk_weight * risk_cost;
        result.push_back({action, finite_or_zero(score)});
    }

    std::sort(result.begin(), result.end(), [](const Decision& a, const Decision& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.action.name < b.action.name;
    });
    return result;
}

} // namespace jarvis::core
