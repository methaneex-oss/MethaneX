#include "jarvis/core/self_model.hpp"

#include <algorithm>

namespace jarvis::core {

void SelfModel::observe_capability(const std::string& name, double availability, double performance) {
    auto& state = capabilities_[name];
    state.name = name;
    state.availability = std::clamp(availability, 0.0, 1.0);
    state.performance = std::clamp(performance, 0.0, 1.0);
    state.isolated = false;
}

bool SelfModel::isolate(const std::string& name) {
    auto it = capabilities_.find(name);
    if (it == capabilities_.end()) return false;
    it->second.isolated = true;
    it->second.availability = 0.0;
    return true;
}

bool SelfModel::restore(const std::string& name, double availability, double performance) {
    auto it = capabilities_.find(name);
    if (it == capabilities_.end()) return false;
    it->second.isolated = false;
    it->second.availability = std::clamp(availability, 0.0, 1.0);
    it->second.performance = std::clamp(performance, 0.0, 1.0);
    return true;
}

const CapabilityState* SelfModel::capability(const std::string& name) const noexcept {
    const auto it = capabilities_.find(name);
    return it == capabilities_.end() ? nullptr : &it->second;
}

std::vector<CapabilityState> SelfModel::capabilities() const {
    std::vector<CapabilityState> result;
    result.reserve(capabilities_.size());
    for (const auto& [_, state] : capabilities_) result.push_back(state);
    return result;
}

} // namespace jarvis::core
