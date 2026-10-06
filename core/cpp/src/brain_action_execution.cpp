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
    const auto affect = affective_state_model_.state();
    // Affective state contributes to memory significance through continuous
    // evidence. It does not map named emotions to actions.
    const double affective_salience = std::clamp(
        0.70 * attention_state_.salience +
        0.15 * affect.arousal +
        0.15 * affect.tension,
        0.0, 1.0);
    const double affective_confidence = std::clamp(
        assessment.confidence * (0.75 + 0.25 * affect.stability),
        0.0, 1.0);
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
        {"salience", affective_salience},
        {"novelty", std::clamp(state_.novelty, 0.0, 1.0)},
        {"confidence", affective_confidence},
        {"affective_arousal", affect.arousal},
        {"affective_uncertainty", affect.uncertainty},
        {"affective_tension", affect.tension},
        {"affective_stability", affect.stability},
        {"reason", result.reason},
    };

    Event event{0, 0, "action_executor", "action_outcome", std::move(data)};
    event.sequence = memory_.append(event);
    if (event.sequence != 0) {
        ++state_.events_seen;
        state_.cycle = event.sequence;
        replay(event);
        consolidate_experience(event, std::clamp(std::abs(result.outcome.consequence_error), 0.0, 1.0));

        // Persist the appraisal evidence separately from the authoritative
        // action outcome. Replay therefore reconstructs learned appraisal
        // parameters exactly once, without coupling parameter learning to
        // execution-status replay.
        if (result.outcome.observed) {
        Event affective_event{
            0,
            0,
            "affective_learner",
            "affective_learning",
            {{"expected_consequence", result.outcome.expected_consequence},
             {"actual_consequence", result.outcome.actual_consequence},
             {"consequence_error", result.outcome.consequence_error},
             {"utility", result.outcome.actual_consequence},
             {"prediction_error", std::clamp(std::abs(result.outcome.consequence_error), 0.0, 1.0)},
             {"novelty", std::clamp(state_.novelty, 0.0, 1.0)},
             {"salience", affective_salience},
             {"uncertainty", std::clamp(1.0 - assessment.confidence, 0.0, 1.0)},
             {"confidence", affective_confidence},
             {"source_action_sequence", static_cast<std::int64_t>(event.sequence)}}};
        affective_event.sequence = memory_.append(affective_event);
        if (affective_event.sequence != 0) {
            ++state_.events_seen;
            state_.cycle = affective_event.sequence;
            replay(affective_event);
            consolidate_experience(affective_event, std::clamp(std::abs(result.outcome.consequence_error), 0.0, 1.0));
        }
        }

        // The consequence becomes a separate learning experience. This keeps
        // the authoritative action outcome immutable while giving the
        // knowledge/adaptation systems a persisted training event they can
        // replay after restart.
        Event learning_event{
            0,
            0,
            "action_executor",
            "learning",
            {{"action_executor." + result.action.name, reliability},
             {"reliability", reliability},
             {"source_action_sequence", static_cast<std::int64_t>(event.sequence)}}};
        learning_event.sequence = memory_.append(learning_event);
        if (learning_event.sequence != 0) {
            ++state_.events_seen;
            state_.cycle = learning_event.sequence;
            replay(learning_event);
            consolidate_experience(learning_event, 1.0 - reliability);
        }
        sync_self_state();
    }

    return result;
}

} // namespace jarvis::core
