#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

enum class HealthState { Healthy, Degraded, Isolated, Recovering };

struct ComponentHealth {
    std::string component;
    HealthState state{HealthState::Healthy};
    double health{1.0};
    std::uint64_t failures{0};
    std::uint64_t recoveries{0};
};

struct RecoveryPlan {
    std::string component;
    std::string strategy;
    double expected_recovery{0.0};
};

class ResilienceModel {
public:
    void observe(const std::string& component, double health_signal);
    std::vector<RecoveryPlan> required_recovery() const;
    bool isolate(const std::string& component);
    bool recover(const std::string& component, double restored_health);
    const ComponentHealth* health(const std::string& component) const noexcept;
    std::vector<ComponentHealth> snapshot() const;

private:
    std::unordered_map<std::string, ComponentHealth> components_;
};

} // namespace jarvis::core
