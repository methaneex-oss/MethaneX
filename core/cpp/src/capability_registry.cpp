#include "jarvis/core/capability_registry.hpp"

#include <algorithm>
#include <utility>

namespace jarvis::core {

bool CapabilityRegistry::register_capability(CapabilityDescriptor descriptor) {
    if (!valid(descriptor)) {
        return false;
    }

    std::unique_lock lock(mutex_);
    const auto existing = std::find_if(
        capabilities_.begin(), capabilities_.end(),
        [&](const CapabilityDescriptor& item) { return item.id == descriptor.id; });
    if (existing != capabilities_.end()) {
        return false;
    }
    capabilities_.push_back(std::move(descriptor));
    return true;
}

bool CapabilityRegistry::unregister_capability(std::string_view id) {
    if (id.empty()) {
        return false;
    }

    std::unique_lock lock(mutex_);
    const auto existing = std::find_if(
        capabilities_.begin(), capabilities_.end(),
        [&](const CapabilityDescriptor& item) { return item.id == id; });
    if (existing == capabilities_.end()) {
        return false;
    }
    capabilities_.erase(existing);
    return true;
}

std::optional<CapabilityDescriptor> CapabilityRegistry::find(std::string_view id) const {
    std::shared_lock lock(mutex_);
    const auto existing = std::find_if(
        capabilities_.begin(), capabilities_.end(),
        [&](const CapabilityDescriptor& item) { return item.id == id; });
    if (existing == capabilities_.end()) {
        return std::nullopt;
    }
    return *existing;
}

std::vector<CapabilityDescriptor> CapabilityRegistry::discover(
    CapabilityAvailability minimum_availability) const {
    std::shared_lock lock(mutex_);
    std::vector<CapabilityDescriptor> result;
    result.reserve(capabilities_.size());
    for (const auto& capability : capabilities_) {
        if (meets_availability(capability.availability, minimum_availability)) {
            result.push_back(capability);
        }
    }
    return result;
}

std::size_t CapabilityRegistry::size() const {
    std::shared_lock lock(mutex_);
    return capabilities_.size();
}

void CapabilityRegistry::clear() {
    std::unique_lock lock(mutex_);
    capabilities_.clear();
}

bool CapabilityRegistry::valid(const CapabilityDescriptor& descriptor) {
    return !descriptor.id.empty() && !descriptor.name.empty() &&
           descriptor.reliability >= 0.0 && descriptor.reliability <= 1.0 &&
           descriptor.estimated_cost >= 0.0;
}

bool CapabilityRegistry::meets_availability(CapabilityAvailability actual,
                                             CapabilityAvailability minimum) {
    return static_cast<std::uint8_t>(actual) >= static_cast<std::uint8_t>(minimum);
}

} // namespace jarvis::core
