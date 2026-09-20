#pragma once

#include "action_model.hpp"
#include "action_authorization.hpp"

#include <functional>
#include <string>

namespace jarvis::core {

enum class ActionExecutionStatus : std::uint8_t {
    rejected,
    prepared,
    executed,
    verified,
    failed,
    cancelled,
    rolled_back,
};

struct ActionExecutionRequest {
    ActionAssessment assessment;
    std::function<bool(const CandidateAction&)> execute;
    std::function<bool(const CandidateAction&)> verify;
    std::function<bool(const CandidateAction&)> rollback;
    ActionAuthorizationContext authorization{};
};

struct ActionExecutionResult {
    CandidateAction action;
    ActionExecutionStatus status{ActionExecutionStatus::rejected};
    bool authorized{false};
    bool executed{false};
    bool verified{false};
    bool rolled_back{false};
    std::string reason;
};

class ActionExecutor {
public:
    ActionExecutionResult run(const ActionExecutionRequest& request) const;
};

} // namespace jarvis::core
