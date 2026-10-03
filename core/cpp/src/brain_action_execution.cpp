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
    Attributes data{
        {"action", result.action.name},
        {"context", std::string("action:") + result.action.name},
        {"status", static_cast<std::int64_t>(result.status)},
        {"authorized", result.authorized},
        {"executed", result.executed},
        {"verified", result.verified},
        {"rolled_back", result.rolled_back},
        {"expected_consequence", result.action.expected_consequence},
        {"actual_consequence", result.outcome.actual_consequence},
        {"consequence_error", result.outcome.consequence_error},
        {"outcome_observed", result.outcome.observed},
        {"reliability", result.outcome.observed
            ? std::clamp(0.5 + 0.25 * result.outcome.consequence_error, 0.0, 1.0)
            : 0.5},
        {"reason", result.reason},
    };

    Event event{0, 0, "action_executor", "action_outcome", std::move(data)};
    event.sequence = memory_.append(event);
    if (event.sequence != 0) {
        ++state_.events_seen;
        state_.cycle = event.sequence;
        replay(event);

        // The action event carries complete consequence evidence. Feed that
        // representation directly into appraisal learning rather than making
        // the learner infer expectation from an affective-state transition.
        if (result.outcome.observed) {
            const double expected = std::clamp(result.action.expected_consequence, -1.0, 1.0);
            const double actual = std::clamp(result.outcome.actual_consequence, -1.0, 1.0);
            const double error = std::clamp(result.outcome.consequence_error, -2.0, 2.0);
            const double novelty = std::clamp(state_.novelty, 0.0, 1.0);
            const double salience = std::clamp(attention_state_.salience, 0.0, 1.0);
            const double confidence = std::clamp(1.0 - std::abs(error) / 2.0, 0.0, 1.0);
            affective_learning_model_.learn(AffectiveOutcomeEvidence{
                expected,
                actual,
                error,
                actual,
                std::clamp(std::abs(error), 0.0, 1.0),
                novelty,
                salience,
                std::clamp(1.0 - confidence, 0.0, 1.0),
                confidence});
        }

        consolidate_experience(event, std::clamp(std::abs(result.outcome.consequence_error), 0.0, 1.0));
        sync_self_state();
    }

    return result;
}

} // namespace jarvis::core
