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

// An execution outcome is deliberately separated from authorization and
// verification. The executor records what the action was expected to cause
// and, when a consequence observer is supplied, what actually happened. This
// gives cognitive/learning layers evidence without embedding semantic emotion
// rules in the executor.
struct ActionOutcome {
    bool observed{false};
    double actual_consequence{0.0};
    double consequence_error{0.0};
};

struct ActionExecutionRequest {
    ActionAssessment assessment;
    std::function<bool(const CandidateAction&)> execute;
    std::function<bool(const CandidateAction&)> verify;
    std::function<bool(const CandidateAction&)> rollback;
    std::function<double(const CandidateAction&)> observe_consequence;
    ActionAuthorizationContext authorization{};
};

struct ActionExecutionResult {
    CandidateAction action;
    ActionExecutionStatus status{ActionExecutionStatus::rejected};
    bool authorized{false};
    bool executed{false};
    bool verified{false};
    bool rolled_back{false};
    ActionOutcome outcome{};
    std::string reason;
};

class ActionExecutor {
public:
    ActionExecutionResult run(const ActionExecutionRequest& request) const;
};

} // namespace jarvis::core
