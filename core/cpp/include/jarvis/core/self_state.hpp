#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

struct GoalState {
    std::string id;
    double priority{0.0};
    bool active{false};

    friend bool operator==(const GoalState&, const GoalState&) = default;
};

struct CognitiveHealth {
    double overall{1.0};
    double memory{1.0};
    double reasoning{1.0};
    double execution{1.0};

    friend bool operator==(const CognitiveHealth&, const CognitiveHealth&) = default;
};

struct SelfState {
    std::uint64_t revision{0};
    std::uint64_t cycle{0};
    std::uint64_t events_seen{0};
    std::string activity;
    CognitiveHealth health{};
    double workload{0.0};
    double uncertainty{0.0};
    std::vector<GoalState> active_goals;
    std::unordered_map<std::string, double> resource_pressure;
};

class SelfStateModel {
public:
    void set_activity(std::string activity);
    void set_health(CognitiveHealth health);
    void set_workload(double workload);
    void set_uncertainty(double uncertainty);
    void set_goals(std::vector<GoalState> goals);
    void set_resource_pressure(std::string resource, double pressure);
    void advance_cycle(std::uint64_t events_seen);
    SelfState snapshot() const;

private:
    void touch() noexcept;
    SelfState state_{};
};

} // namespace jarvis::core
