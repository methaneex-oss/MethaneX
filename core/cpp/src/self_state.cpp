#include "jarvis/core/self_state.hpp"

#include <algorithm>
#include <utility>

namespace jarvis::core {

// Layer 1 self-state is deliberately a state model, not a policy engine.
void SelfStateModel::touch() noexcept {
    ++state_.revision;
}

void SelfStateModel::set_activity(std::string activity) {
    if (state_.activity == activity) return;
    state_.activity = std::move(activity);
    touch();
}

void SelfStateModel::set_health(CognitiveHealth health) {
    health.overall = std::clamp(health.overall, 0.0, 1.0);
    health.memory = std::clamp(health.memory, 0.0, 1.0);
    health.reasoning = std::clamp(health.reasoning, 0.0, 1.0);
    health.execution = std::clamp(health.execution, 0.0, 1.0);
    if (state_.health == health) return;
    state_.health = health;
    touch();
}

void SelfStateModel::set_workload(double workload) {
    workload = std::clamp(workload, 0.0, 1.0);
    if (state_.workload == workload) return;
    state_.workload = workload;
    touch();
}

void SelfStateModel::set_uncertainty(double uncertainty) {
    uncertainty = std::clamp(uncertainty, 0.0, 1.0);
    if (state_.uncertainty == uncertainty) return;
    state_.uncertainty = uncertainty;
    touch();
}

void SelfStateModel::set_goals(std::vector<GoalState> goals) {
    if (state_.active_goals == goals) return;
    state_.active_goals = std::move(goals);
    touch();
}

void SelfStateModel::set_resource_pressure(std::string resource, double pressure) {
    if (resource.empty()) return;
    pressure = std::clamp(pressure, 0.0, 1.0);
    const auto it = state_.resource_pressure.find(resource);
    if (it != state_.resource_pressure.end() && it->second == pressure) return;
    state_.resource_pressure[std::move(resource)] = pressure;
    touch();
}

void SelfStateModel::advance_cycle(std::uint64_t events_seen) {
    if (state_.events_seen == events_seen) return;
    ++state_.cycle;
    state_.events_seen = events_seen;
    touch();
}

SelfState SelfStateModel::snapshot() const {
    return state_;
}

} // namespace jarvis::core
