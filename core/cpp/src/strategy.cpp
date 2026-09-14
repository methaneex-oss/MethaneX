#include "jarvis/core/strategy.hpp"

#include <algorithm>

namespace jarvis::core {

StrategyContext StrategyModel::formulate(const Intent& intent, const AttentionSignal& attention,
                                         double threat, double uncertainty,
                                         double resource_budget) const {
    StrategyContext result;
    result.intent = intent;
    result.attention = std::clamp(attention.salience, 0.0, 1.0);
    result.planning.goal_priority = intent.priority;
    result.planning.goal_progress = 1.0 - intent.priority * intent.confidence;
    result.planning.threat = std::clamp(threat, 0.0, 1.0);
    result.planning.uncertainty = std::clamp(uncertainty, 0.0, 1.0);
    result.planning.resource_budget = std::max(0.0, resource_budget);
    result.planning.deadline_pressure = std::clamp(std::max(intent.urgency, result.attention), 0.0, 1.0);
    return result;
}

} // namespace jarvis::core
