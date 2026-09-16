#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <vector>

namespace jarvis::core {

enum class CapabilityRisk : std::uint8_t { low, medium, high, critical };

enum class CapabilityAvailability : std::uint8_t { unavailable, degraded, available };

struct CapabilityDescriptor {
    std::string id;
    std::string name;
    std::string description;
    std::vector<std::string> input_schema;
    std::vector<std::string> output_schema;
    std::vector<std::string> permissions;
    double estimated_cost{0.0};
    CapabilityRisk risk{CapabilityRisk::low};
    double reliability{0.0};
    CapabilityAvailability availability{CapabilityAvailability::unavailable};
    bool reversible{false};
};

class CapabilityRegistry {
public:
    bool register_capability(CapabilityDescriptor descriptor);
    bool unregister_capability(std::string_view id);

    std::optional<CapabilityDescriptor> find(std::string_view id) const;
    std::vector<CapabilityDescriptor> discover(
        CapabilityAvailability minimum_availability = CapabilityAvailability::available) const;

    std::size_t size() const;
    void clear();

private:
    static bool valid(const CapabilityDescriptor& descriptor);
    static bool meets_availability(CapabilityAvailability actual,
                                   CapabilityAvailability minimum);

    mutable std::shared_mutex mutex_;
    std::vector<CapabilityDescriptor> capabilities_;
};

} // namespace jarvis::core
