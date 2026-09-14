#include "jarvis/core/action_execution.hpp"

namespace jarvis::core {

ActionExecutionResult ActionExecutor::run(const ActionExecutionRequest& request) const {
    ActionExecutionResult result;
    result.action = request.assessment.action;
    result.authorized = request.assessment.permitted &&
                        request.assessment.disposition == ActionDisposition::execute;
    if (!result.authorized) {
        result.status = ActionExecutionStatus::rejected;
        result.reason = request.assessment.reason.empty() ? "action_not_authorized" : request.assessment.reason;
        return result;
    }

    result.status = ActionExecutionStatus::prepared;
    if (!request.execute) {
        result.status = ActionExecutionStatus::failed;
        result.reason = "no_execution_handler";
        return result;
    }

    bool executed = false;
    try {
        executed = request.execute(result.action);
    } catch (...) {
        result.status = ActionExecutionStatus::failed;
        result.reason = "execution_exception";
        return result;
    }
    if (!executed) {
        result.status = ActionExecutionStatus::failed;
        result.reason = "execution_failed";
        return result;
    }
    result.executed = true;
    result.status = ActionExecutionStatus::executed;

    if (!request.verify) {
        result.status = ActionExecutionStatus::failed;
        result.reason = "no_verification_handler";
    } else {
        bool verified = false;
        try {
            verified = request.verify(result.action);
        } catch (...) {
            verified = false;
        }
        if (verified) {
            result.verified = true;
            result.status = ActionExecutionStatus::verified;
            result.reason = "verified";
            return result;
        }
        result.status = ActionExecutionStatus::failed;
        result.reason = "verification_failed";
    }

    if (request.rollback) {
        bool rolled_back = false;
        try {
            rolled_back = request.rollback(result.action);
        } catch (...) {
            rolled_back = false;
        }
        if (rolled_back) {
            result.rolled_back = true;
            result.status = ActionExecutionStatus::rolled_back;
            result.reason = "verification_failed_rolled_back";
        }
    }
    return result;
}

} // namespace jarvis::core
