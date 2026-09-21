#include "jarvis/core/capability_execution.hpp"

#include <algorithm>
#include <cmath>
#include <exception>
#include <utility>

namespace jarvis::core {

CapabilityExecutionResult CapabilityExecutionResult::success(
    std::string capability_id, std::string output, std::string provider) {
    return {CapabilityExecutionStatus::succeeded,
            std::move(capability_id), std::move(output), std::move(provider), ""};
}

bool CapabilityExecutionBoundary::register_provider(CapabilityProvider provider) {
    if (provider.capability_id.empty() || !provider.execute) {
        return false;
    }
    std::lock_guard lock(mutex_);
    return providers_.emplace(provider.capability_id, std::move(provider)).second;
}

bool CapabilityExecutionBoundary::unregister_provider(const std::string& capability_id) {
    if (capability_id.empty()) {
        return false;
    }
    std::lock_guard lock(mutex_);
    return providers_.erase(capability_id) != 0;
}

CapabilityExecutionResult CapabilityExecutionBoundary::execute(
    const CapabilityExecutionRequest& request) const {
    const auto rejected = [&](CapabilityExecutionStatus status, const char* reason) {
        return CapabilityExecutionResult{status, request.capability.id, {}, {}, reason};
    };

    if (request.capability.id.empty()) {
        return rejected(CapabilityExecutionStatus::rejected, "capability_id_missing");
    }
    if (request.capability.availability == CapabilityAvailability::unavailable) {
        return rejected(CapabilityExecutionStatus::unavailable, "capability_unavailable");
    }

    const double maximum_risk = std::isfinite(request.maximum_risk)
        ? std::clamp(request.maximum_risk, 0.0, 1.0) : 0.0;
    const double capability_risk =
        static_cast<double>(risk_rank(request.capability.risk)) / 3.0;
    if (capability_risk > maximum_risk) {
        return rejected(CapabilityExecutionStatus::rejected, "authorization_risk_exceeded");
    }

    for (const auto& permission : request.capability.permissions) {
        if (permission.empty() || !has_permission(request.granted_permissions, permission)) {
            return rejected(CapabilityExecutionStatus::rejected,
                            "authorization_permission_denied");
        }
    }

    CapabilityProvider provider;
    {
        std::lock_guard lock(mutex_);
        const auto found = providers_.find(request.capability.id);
        if (found == providers_.end()) {
            return rejected(CapabilityExecutionStatus::unavailable,
                            "capability_provider_unavailable");
        }
        provider = found->second;
    }

    try {
        auto result = provider.execute(request);
        if (result.capability_id.empty()) {
            result.capability_id = request.capability.id;
        }
        if (result.provider.empty()) {
            result.provider = provider.capability_id;
        }
        return result;
    } catch (const std::exception& error) {
        return {CapabilityExecutionStatus::failed, request.capability.id, {},
                provider.capability_id, error.what()};
    } catch (...) {
        return {CapabilityExecutionStatus::failed, request.capability.id, {},
                provider.capability_id, "unknown_capability_provider_failure"};
    }
}

bool CapabilityExecutionBoundary::has_permission(
    const std::vector<std::string>& granted, const std::string& required) noexcept {
    return std::find(granted.begin(), granted.end(), required) != granted.end();
}

int CapabilityExecutionBoundary::risk_rank(CapabilityRisk risk) noexcept {
    switch (risk) {
    case CapabilityRisk::low: return 0;
    case CapabilityRisk::medium: return 1;
    case CapabilityRisk::high: return 2;
    case CapabilityRisk::critical: return 3;
    }
    return 3;
}

} // namespace jarvis::core
