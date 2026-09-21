#pragma once

#include "action_model.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

struct ActionAuthorizationContext {
    std::vector<std::string> granted_permissions;
    double maximum_risk{1.0};
    bool require_reversible{false};
};

struct ActionAuthorizationResult {
    bool authorized{false};
    std::string reason;
};

class ActionAuthorizer {
public:
    ActionAuthorizationResult authorize(
        const ActionAssessment& assessment,
        const ActionAuthorizationContext& context = {}) const;

private:
    static bool has_permission(
        const std::vector<std::string>& granted,
        const std::string& required) noexcept;
};

} // namespace jarvis::core
