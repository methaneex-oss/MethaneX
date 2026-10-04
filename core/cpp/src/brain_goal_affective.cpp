#include "jarvis/core/brain.hpp"

namespace jarvis::core {

bool Brain::assimilate_goal_outcome_with_affect(const GoalOutcomeEvidence& raw_evidence) {
    GoalOutcomeEvidence evidence = raw_evidence;
    evidence.normalize();
    if (evidence.goal_id.empty()) return false;

    std::unique_lock lock(mutex_);
    const auto* current = goals_model_.get(evidence.goal_id);
    if (current == nullptr) return false;

    evidence.progress_before = std::clamp(current->progress, 0.0, 1.0);
    evidence.normalize();

    const double expected = std::clamp(current->outcome_momentum, -1.0, 1.0);
    const double actual = std::clamp(evidence.delta, -1.0, 1.0);
    const double consequence_error = std::clamp(actual - expected, -1.0, 1.0);
    const double prediction_error = std::abs(consequence_error);
    const double salience = std::clamp(std::abs(actual), 0.0, 1.0);
    const double novelty = std::clamp(1.0 - evidence.confidence, 0.0, 1.0);
    const double uncertainty = novelty;

    if (!goals_model_.update_progress(evidence.goal_id, evidence.progress_after)) return false;

    Event progress_event{0, 0, "brain", "goal_progress", {
        {"id", evidence.goal_id},
        {"progress", evidence.progress_after},
        {"confidence", evidence.confidence},
        {"delta", evidence.delta},
        {"sequence", static_cast<std::int64_t>(evidence.sequence)}
    }};
    progress_event.sequence = memory_.append(progress_event);
    if (progress_event.sequence == 0) return false;
    ++state_.events_seen;
    state_.cycle = progress_event.sequence;
    replay(progress_event);

    const AffectiveSignal signal{
        actual,
        prediction_error,
        novelty,
        salience,
        uncertainty,
        evidence.confidence
    };
    const auto before = affective_state_model_.state();
    affective_state_model_.update(signal, 1.0);
    const auto after = affective_state_model_.state();

    const AffectiveOutcomeEvidence affective_evidence{
        expected,
        actual,
        consequence_error,
        actual,
        prediction_error,
        novelty,
        salience,
        uncertainty,
        evidence.confidence
    };
    affective_learning_model_.learn(affective_evidence);

    Event affective_event{0, 0, "brain", "affective_learning", {
        {"goal_id", evidence.goal_id},
        {"expected_consequence", expected},
        {"actual_consequence", actual},
        {"consequence_error", consequence_error},
        {"utility", actual},
        {"prediction_error", prediction_error},
        {"novelty", novelty},
        {"salience", salience},
        {"uncertainty", uncertainty},
        {"confidence", evidence.confidence},
        {"valence_before", before.valence},
        {"valence_after", after.valence}
    }};
    affective_event.sequence = memory_.append(affective_event);
    if (affective_event.sequence == 0) return false;
    ++state_.events_seen;
    state_.cycle = affective_event.sequence;
    replay(affective_event);

    if (evidence.completed) {
        const auto* completed_goal = goals_model_.get(evidence.goal_id);
        if (completed_goal == nullptr || completed_goal->status != GoalStatus::completed) return false;
        Event complete_event{0, 0, "brain", "goal_complete", {
            {"id", evidence.goal_id},
            {"confidence", evidence.confidence},
            {"sequence", static_cast<std::int64_t>(evidence.sequence)}
        }};
        complete_event.sequence = memory_.append(complete_event);
        if (complete_event.sequence == 0) return false;
        ++state_.events_seen;
        state_.cycle = complete_event.sequence;
        replay(complete_event);
    }

    sync_self_state();
    return true;
}

} // namespace jarvis::core
