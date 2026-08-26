#include "jarvis/core/resilience.hpp"

#include <algorithm>

namespace jarvis::core {

void ResilienceModel::observe(const std::string& component, double health_signal) {
    auto& entry = components_[component];
    entry.component = component;
    const double signal = std::clamp(health_signal, 0.0, 1.0);
    if (signal < entry.health) ++entry.failures;
    entry.health = 0.65 * entry.health + 0.35 * signal;
    if (entry.health >= 0.75) entry.state = HealthState::Healthy;
    else if (entry.health >= 0.35) entry.state = HealthState::Degraded;
    else entry.state = HealthState::Isolated;
}

std::vector<RecoveryPlan> ResilienceModel::required_recovery() const {
    std::vector<RecoveryPlan> plans;
    for (const auto& [name, entry] : components_) {
        if (entry.state == HealthState::Healthy) continue;
        const double expected = std::clamp(1.0 - entry.health, 0.0, 1.0);
        plans.push_back(RecoveryPlan{name, entry.state == HealthState::Isolated ? "isolate-and-restore" : "restore-last-known-good", expected});
    }
    return plans;
}

bool ResilienceModel::isolate(const std::string& component) {
    auto it = components_.find(component);
    if (it == components_.end()) return false;
    it->second.state = HealthState::Isolated;
    return true;
}

bool ResilienceModel::recover(const std::string& component, double restored_health) {
    auto it = components_.find(component);
    if (it == components_.end()) return false;
    it->second.health = std::clamp(restored_health, 0.0, 1.0);
    it->second.state = it->second.health >= 0.75 ? HealthState::Healthy : HealthState::Recovering;
    ++it->second.recoveries;
    return true;
}

const ComponentHealth* ResilienceModel::health(const std::string& component) const noexcept {
    const auto it = components_.find(component);
    return it == components_.end() ? nullptr : &it->second;
}

std::vector<ComponentHealth> ResilienceModel::snapshot() const {
    std::vector<ComponentHealth> result;
    result.reserve(components_.size());
    for (const auto& [_, entry] : components_) result.push_back(entry);
    return result;
}

} // namespace jarvis::core
