#include "jarvis/core/self_state.hpp"

#include <algorithm>
#include <utility>

namespace jarvis::core {

void SelfStateModel::set_activity(std::string activity) {
    state_.activity = std::move(activity);
}

void SelfStateModel::set_health(CognitiveHealth health) {
    state_.health.overall = std::clamp(health.overall, 0.0, 1.0);
    state_.health.memory = std::clamp(health.memory, 0.0, 1.0);
    state_.health.reasoning = std::clamp(health.reasoning, 0.0, 1.0);
    state_.health.execution = std::clamp(health.execution, 0.0, 1.0);
}

void SelfStateModel::set_workload(double workload) {
    state_.workload = std::clamp(workload, 0.0, 1.0);
}

void SelfStateModel::set_uncertainty(double uncertainty) {
    state_.uncertainty = std::clamp(uncertainty, 0.0, 1.0);
}

void SelfStateModel::set_goals(std::vector<GoalState> goals) {
    state_.active_goals = std::move(goals);
}

void SelfStateModel::set_resource_pressure(std::string resource, double pressure) {
    state_.resource_pressure[std::move(resource)] = std::clamp(pressure, 0.0, 1.0);
}

void SelfStateModel::advance_cycle(std::uint64_t events_seen) {
    ++state_.cycle;
    state_.events_seen = events_seen;
}

SelfState SelfStateModel::snapshot() const {
    return state_;
}

} // namespace jarvis::core
