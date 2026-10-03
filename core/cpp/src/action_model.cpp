#include "jarvis/core/action_model.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double unit(double value) noexcept {
    if (!std::isfinite(value)) return 0.0;
    return std::clamp(value, 0.0, 1.0);
}

} // namespace

std::vector<ActionAssessment> ActionModel::assess(
    const std::vector<Decision>& decisions, ActionConstraints constraints) const {
    constraints.maximum_risk = unit(constraints.maximum_risk);
    std::vector<ActionAssessment> result;
    result.reserve(decisions.size());

    for (const auto& decision : decisions) {
        const double risk = unit(decision.action.risk);
        const double confidence = unit(1.0 - risk) * unit(decision.score >= 0.0 ? 1.0 : 0.0);
        ActionAssessment assessment{decision.action, ActionDisposition::recommend, false, confidence, {}};

        if (risk > constraints.maximum_risk) {
            assessment.disposition = ActionDisposition::reject;
            assessment.reason = "Action exceeds the configured risk constraint.";
        } else if (constraints.require_reversible && unit(decision.action.reversibility) < 1.0) {
            assessment.disposition = ActionDisposition::clarify;
            assessment.reason = "Action requires reversibility that is not guaranteed.";
        } else if (confidence >= 0.75) {
            assessment.disposition = ActionDisposition::execute;
            assessment.permitted = true;
            assessment.reason = "Action satisfies the supplied execution constraints.";
        } else {
            assessment.disposition = ActionDisposition::recommend;
            assessment.reason = "Action is plausible but requires higher confidence for autonomous execution.";
        }
        result.push_back(std::move(assessment));
    }
    return result;
}

} // namespace jarvis::core
