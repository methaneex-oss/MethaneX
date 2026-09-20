#include "jarvis/core/action_authorization.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    CandidateAction action;
    action.name = "repository.read";
    action.risk = 0.2;
    action.reversibility = 1.0;
    action.required_permissions = {"repo:read"};

    ActionAssessment assessment{action, ActionDisposition::execute, true, 0.9, "ready"};
    ActionAuthorizer authorizer;

    const auto denied = authorizer.authorize(assessment);
    assert(!denied.authorized);
    assert(denied.reason == "authorization_permission_denied");

    const auto allowed = authorizer.authorize(
        assessment, ActionAuthorizationContext{{"repo:read"}, 0.5, true});
    assert(allowed.authorized);
    assert(allowed.reason == "authorized");

    const auto risky = authorizer.authorize(
        assessment, ActionAuthorizationContext{{"repo:read"}, 0.1, false});
    assert(!risky.authorized);
    assert(risky.reason == "authorization_risk_exceeded");

    bool executed = false;
    ActionExecutionRequest request{
        assessment,
        [&](const CandidateAction&) { executed = true; return true; },
        [](const CandidateAction&) { return true; },
        {},
        ActionAuthorizationContext{{}, 1.0, false},
    };
    const auto execution = ActionExecutor{}.run(request);
    assert(execution.status == ActionExecutionStatus::rejected);
    assert(execution.reason == "authorization_permission_denied");
    assert(!executed);

    return 0;
}
