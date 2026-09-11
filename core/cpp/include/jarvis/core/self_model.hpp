#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

struct CapabilityState {
    std::string name;
    double availability{1.0};
    double performance{1.0};
    bool isolated{false};
};

struct SelfCapabilityHealth {
    double availability{1.0};
    double performance{1.0};
    double overall{1.0};
};

class SelfModel {
public:
    void observe_capability(const std::string& name, double availability, double performance);
    bool isolate(const std::string& name);
    bool restore(const std::string& name, double availability, double performance);
    const CapabilityState* capability(const std::string& name) const noexcept;
    std::vector<CapabilityState> capabilities() const;
    SelfCapabilityHealth health() const noexcept;

private:
    std::unordered_map<std::string, CapabilityState> capabilities_;
};

} // namespace jarvis::core
