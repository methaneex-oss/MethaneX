#include "jarvis/core/action_authorization.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

bool ActionAuthorizer::has_permission(
    const std::vector<std::string>& granted,
    const std::string& required) noexcept {
    return std::find(granted.begin(), granted.end(), required) != granted.end();
}

ActionAuthorizationResult ActionAuthorizer::authorize(
    const ActionAssessment& assessment,
    const ActionAuthorizationContext& context) const {
    if (!assessment.permitted || assessment.disposition != ActionDisposition::execute) {
        return {false, assessment.reason.empty() ? "action_not_permitted" : assessment.reason};
    }

    const double maximum_risk = std::isfinite(context.maximum_risk)
        ? std::clamp(context.maximum_risk, 0.0, 1.0) : 0.0;
    const double risk = std::isfinite(assessment.action.risk)
        ? std::clamp(assessment.action.risk, 0.0, 1.0) : 1.0;

    if (risk > maximum_risk) {
        return {false, "authorization_risk_exceeded"};
    }
    if (context.require_reversible &&
        (!std::isfinite(assessment.action.reversibility) ||
         std::clamp(assessment.action.reversibility, 0.0, 1.0) < 1.0)) {
        return {false, "authorization_requires_reversible_action"};
    }

    for (const auto& permission : assessment.action.required_permissions) {
        if (permission.empty() || !has_permission(context.granted_permissions, permission)) {
            return {false, "authorization_permission_denied"};
        }
    }

    return {true, "authorized"};
}

} // namespace jarvis::core
