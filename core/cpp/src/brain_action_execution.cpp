#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

ActionExecutionResult Brain::execute_action(
    const ActionAssessment& assessment,
    std::function<bool(const CandidateAction&)> execute,
    std::function<bool(const CandidateAction&)> verify,
    std::function<bool(const CandidateAction&)> rollback,
    std::function<double(const CandidateAction&)> observe_consequence,
    ActionAuthorizationContext authorization) {
    ActionExecutionRequest request;
    request.assessment = assessment;
    request.execute = std::move(execute);
    request.verify = std::move(verify);
    request.rollback = std::move(rollback);
    request.observe_consequence = std::move(observe_consequence);
    request.authorization = std::move(authorization);

    const auto result = ActionExecutor{}.run(request);

    std::unique_lock lock(mutex_);
    const auto eligible = goals_model_.eligible(state_.cycle);
    const std::string context = eligible.empty() ? "global" : eligible.front().id;
    const double reliability =
        result.status == ActionExecutionStatus::verified ? 1.0 :
        result.status == ActionExecutionStatus::executed ? 0.75 :
        result.status == ActionExecutionStatus::rolled_back ? 0.25 : 0.0;
    Attributes data{
        {"action", result.action.name},
        {"context", context},
        {"status", static_cast<std::int64_t>(result.status)},
        {"authorized", result.authorized},
        {"executed", result.executed},
        {"verified", result.verified},
        {"rolled_back", result.rolled_back},
        {"observed", result.outcome.observed},
        {"expected_consequence", result.outcome.expected_consequence},
        {"actual_consequence", result.outcome.actual_consequence},
        {"consequence_error", result.outcome.consequence_error},
        {"reliability", reliability},
        {"salience", std::clamp(attention_state_.salience, 0.0, 1.0)},
        {"novelty", std::clamp(state_.novelty, 0.0, 1.0)},
        {"confidence", std::clamp(assessment.confidence, 0.0, 1.0)},
        {"reason", result.reason},
    };

    Event event{0, 0, "action_executor", "action_outcome", std::move(data)};
    event.sequence = memory_.append(event);
    if (event.sequence != 0) {
        ++state_.events_seen;
        state_.cycle = event.sequence;
        replay(event);

        consolidate_experience(event, std::clamp(std::abs(result.outcome.consequence_error), 0.0, 1.0));
        sync_self_state();
    }

    return result;
}

} // namespace jarvis::core
