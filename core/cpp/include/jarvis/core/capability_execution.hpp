#pragma once

#include "capability_registry.hpp"

#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

enum class CapabilityExecutionStatus : std::uint8_t {
    succeeded,
    rejected,
    unavailable,
    failed,
};

struct CapabilityExecutionRequest {
    CapabilityDescriptor capability;
    std::string input;
    std::vector<std::string> granted_permissions;
    double maximum_risk{1.0};
};

struct CapabilityExecutionResult {
    CapabilityExecutionStatus status{CapabilityExecutionStatus::failed};
    std::string capability_id;
    std::string output;
    std::string provider;
    std::string reason;

    static CapabilityExecutionResult success(
        std::string capability_id, std::string output, std::string provider);
};

struct CapabilityProvider {
    std::string capability_id;
    std::function<CapabilityExecutionResult(const CapabilityExecutionRequest&)> execute;
};

class CapabilityExecutionBoundary {
public:
    bool register_provider(CapabilityProvider provider);
    bool unregister_provider(const std::string& capability_id);

    CapabilityExecutionResult execute(const CapabilityExecutionRequest& request) const;

private:
    static bool has_permission(const std::vector<std::string>& granted,
                               const std::string& required) noexcept;
    static int risk_rank(CapabilityRisk risk) noexcept;

    mutable std::mutex mutex_;
    std::unordered_map<std::string, CapabilityProvider> providers_;
};

} // namespace jarvis::core
