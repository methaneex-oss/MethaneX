// Cognitive core: persistent state, reasoning, adaptation, recovery and evolution.
#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <mutex>
#include <sstream>
#include <utility>

namespace jarvis::core {
namespace {
std::uint64_t now_ns() noexcept { return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()); }
const std::string* string_value(const Attributes& data, const std::string& key) { const auto it = data.find(key); return it == data.end() ? nullptr : std::get_if<std::string>(&it->second); }
double double_value(const Attributes& data, const std::string& key, double fallback = 0.0) { const auto it = data.find(key); if (it == data.end()) return fallback; if (const auto value = std::get_if<double>(&it->second)) return *value; if (const auto value = std::get_if<std::int64_t>(&it->second)) return static_cast<double>(*value); return fallback; }
bool numeric_value(const Scalar& value, long double& result) {
    if (const auto* integer = std::get_if<std::int64_t>(&value)) {
        result = static_cast<long double>(*integer);
        return true;
    }
    if (const auto* numeric = std::get_if<double>(&value);
        numeric != nullptr && std::isfinite(*numeric)) {
        result = static_cast<long double>(*numeric);
        return true;
    }
    return false;
}
bool valid_prediction_outcome_event(const Event& event, const Prediction* prediction) {
    const auto* key = string_value(event.data, "key");
    const auto actual = event.data.find("actual");
    if (key == nullptr || key->empty() || actual == event.data.end() ||
        prediction == nullptr || prediction->resolved || prediction->key != *key) return false;
    const auto sequence = event.data.find("prediction_sequence");
    if (sequence != event.data.end()) {
        const auto* value = std::get_if<std::int64_t>(&sequence->second);
        if (value == nullptr || *value <= 0 ||
            static_cast<std::uint64_t>(*value) != prediction->created_sequence) return false;
    }
    if (const auto* value = std::get_if<double>(&actual->second);
        value != nullptr && !std::isfinite(*value)) return false;
    if (const auto* value = std::get_if<double>(&prediction->predicted);
        value != nullptr && !std::isfinite(*value)) return false;

    const double error = double_value(event.data, "error", 1.0);
    if (!std::isfinite(error) || error < 0.0 || error > 1.0) return false;

    // These fields are consumed by affective processing before the remaining
    // learning handlers run. Reject malformed metadata at the journal boundary
    // rather than allowing NaN to contaminate affect or attention state.
    const auto valid_optional_unit = [&](const char* name) {
        const auto field = event.data.find(name);
        if (field == event.data.end()) return true;
        if (const auto* value = std::get_if<double>(&field->second))
            return std::isfinite(*value) && *value >= 0.0 && *value <= 1.0;
        if (const auto* value = std::get_if<std::int64_t>(&field->second))
            return *value == 0 || *value == 1;
        return false;
    };
    if (!valid_optional_unit("salience") || !valid_optional_unit("novelty"))
        return false;

    double expected_error = prediction->predicted == actual->second ? 0.0 : 1.0;
    long double predicted_numeric = 0.0L;
    long double actual_numeric = 0.0L;
    if (numeric_value(prediction->predicted, predicted_numeric) &&
        numeric_value(actual->second, actual_numeric)) {
        const long double scale = std::max({
            1.0L, std::abs(predicted_numeric), std::abs(actual_numeric)});
        expected_error = std::clamp(static_cast<double>(
            std::abs(actual_numeric - predicted_numeric) / scale), 0.0, 1.0);
    }
    const auto model = event.data.find("error_model");
    if (model != event.data.end()) {
        const auto* version = std::get_if<std::int64_t>(&model->second);
        if (version == nullptr || *version != 2) return false;
        return std::abs(error - expected_error) <= 1e-12;
    }
    // Only historical Brain-authored records may use the older binary
    // mismatch error. Unversioned external events must satisfy current math.
    return std::abs(error - expected_error) <= 1e-12 ||
           (event.source == "brain" &&
            prediction->predicted != actual->second && error == 1.0);
}
std::uint64_t integer_value(const Attributes& data, const std::string& key, std::uint64_t fallback = 0) { const auto it = data.find(key); if (it == data.end()) return fallback; if (const auto value = std::get_if<std::int64_t>(&it->second)) return *value < 0 ? fallback : static_cast<std::uint64_t>(*value); if (const auto value = std::get_if<double>(&it->second)) return *value < 0.0 ? fallback : static_cast<std::uint64_t>(*value); return fallback; }
std::string join_ids(const std::vector<std::string>& ids) { std::ostringstream out; for (std::size_t i = 0; i < ids.size(); ++i) { if (i != 0) out << '\x1f'; out << ids[i]; } return out.str(); }
std::vector<std::string> split_ids(const std::string& value) { std::vector<std::string> result; std::size_t start = 0; while (start <= value.size()) { const auto end = value.find('\x1f', start); const auto token = value.substr(start, end == std::string::npos ? std::string::npos : end - start); if (!token.empty()) result.push_back(token); if (end == std::string::npos) break; start = end + 1; } return result; }
GoalStatus goal_status_value(std::int64_t value) { switch (value) { case 0: return GoalStatus::pending; case 1: return GoalStatus::active; case 2: return GoalStatus::completed; case 3: return GoalStatus::abandoned; default: return GoalStatus::pending; } }
}
Brain::Brain(std::filesystem::path journal_path) : memory_(256, std::move(journal_path)), evolution_controller_(evolution_, evolution_history_) { const auto history = memory_.all(); for (const auto& event : history) replay(event); state_.events_seen = static_cast<std::uint64_t>(history.size()); if (!history.empty()) state_.cycle = history.back().sequence; sync_self_state(); }
void Brain::consolidate_experience(const Event& event, double error) {
    double salience = attention_state_.salience; double novelty = state_.novelty; double confidence = 0.5;
    if (const auto it = event.data.find("salience"); it != event.data.end()) if (const auto* value = std::get_if<double>(&it->second)) salience = *value;
    if (const auto it = event.data.find("novelty"); it != event.data.end()) if (const auto* value = std::get_if<double>(&it->second)) novelty = *value;
    if (const auto it = event.data.find("reliability"); it != event.data.end()) if (const auto* value = std::get_if<double>(&it->second)) confidence = *value;
    if (const auto it = event.data.find("confidence"); it != event.data.end()) if (const auto* value = std::get_if<double>(&it->second)) confidence = *value;
    const auto affect = affective_state_model_.state();
    const double affective_significance = std::clamp(0.25 * std::abs(affect.valence) + 0.25 * affect.arousal + 0.25 * affect.uncertainty + 0.25 * affect.tension, 0.0, 1.0);
    salience = std::max(std::clamp(salience, 0.0, 1.0), affective_significance);
    memory_.consolidate(event.sequence, salience, novelty, error, std::clamp(confidence, 0.0, 1.0));
}
void Brain::process_affective_experience(const Event& event) {
    if (const auto it = event.data.find("affective_relevant");
        it != event.data.end() && std::get_if<bool>(&it->second) != nullptr &&
        !*std::get_if<bool>(&it->second)) return;
    const auto before = affective_state_model_.state(); AffectiveSignal signal{}; double utility = 0.0; bool relevant = false;
    if (event.kind == "prediction_outcome") {
        const double error = std::clamp(double_value(event.data, "error", 1.0), 0.0, 1.0);
        // Prediction error is unsigned surprise, not outcome utility. Without
        // explicit task-specific utility evidence, a mismatch must not be
        // interpreted as a positive reward merely because 1 - error is positive.
        signal.outcome = 0.0;
        signal.prediction_error = error;
        signal.novelty = std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0);
        signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0);
        signal.confidence = std::clamp(1.0 - error, 0.0, 1.0);
        utility = 0.0;
        relevant = true;
    }
    else if (event.kind == "action_outcome") { const auto expected = event.data.find("expected_consequence"); const auto actual = event.data.find("actual_consequence"); const auto consequence_error = event.data.find("consequence_error"); const auto observed = event.data.find("observed"); const bool has_observed_consequence = observed != event.data.end() && std::get_if<bool>(&observed->second) != nullptr && *std::get_if<bool>(&observed->second); if (has_observed_consequence && expected != event.data.end() && actual != event.data.end() && consequence_error != event.data.end()) { const double actual_value = double_value(event.data, "actual_consequence"); const double error = double_value(event.data, "consequence_error"); const double reliability = std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0); signal.outcome = std::clamp(actual_value, -1.0, 1.0); signal.prediction_error = std::clamp(std::abs(error), 0.0, 1.0); signal.novelty = std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0); signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0); signal.confidence = reliability; utility = actual_value; relevant = true; } else {
            // Execution reliability is not consequence utility. If no valid
            // consequence was observed, keep valence neutral and represent the
            // missing outcome as uncertainty rather than inventing reward.
            signal.outcome = 0.0;
            signal.prediction_error = 0.0;
            signal.uncertainty = 1.0;
            signal.novelty = std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0);
            signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0);
            signal.confidence = 0.0;
            utility = 0.0;
            relevant = true;
        } }
    else if (event.kind == "affective_learning") { const auto source = integer_value(event.data, "source_action_sequence", 0); if (source != 0 && !processed_affective_learning_sources_.insert(source).second) return; affective_learning_model_.learn(AffectiveOutcomeEvidence{double_value(event.data, "expected_consequence"), double_value(event.data, "actual_consequence"), double_value(event.data, "consequence_error"), double_value(event.data, "utility", double_value(event.data, "actual_consequence")), double_value(event.data, "prediction_error"), double_value(event.data, "novelty", state_.novelty), double_value(event.data, "salience", attention_state_.salience), double_value(event.data, "uncertainty", 0.0), double_value(event.data, "confidence", 0.5)}); return; }
    else if (event.kind == "learning") { signal.outcome = 2.0 * std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0) - 1.0; signal.confidence = std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0); signal.novelty = state_.novelty; signal.salience = attention_state_.salience; utility = signal.outcome; relevant = true; }
    else if (event.kind == "observation") { const double confidence = std::clamp(double_value(event.data, "confidence", 0.5), 0.0, 1.0); signal.outcome = std::clamp(double_value(event.data, "outcome", 0.0), -1.0, 1.0); signal.prediction_error = std::clamp(double_value(event.data, "prediction_error", 0.0), 0.0, 1.0); signal.novelty = std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0); signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0); signal.uncertainty = 1.0 - confidence; signal.confidence = confidence; utility = signal.outcome; relevant = true; }
    else if (event.kind == "goal_progress" || event.kind == "goal_complete") { const double progress = event.kind == "goal_complete" ? 1.0 : std::clamp(double_value(event.data, "progress", 0.0), 0.0, 1.0); signal.outcome = 2.0 * progress - 1.0; signal.prediction_error = 1.0 - progress; signal.novelty = state_.novelty; signal.salience = attention_state_.salience; signal.confidence = progress; utility = signal.outcome; relevant = true; }
    if (!relevant) return;
    signal = affective_learning_model_.modulate(signal); const auto after = affective_state_model_.update(signal); if (event.kind != "action_outcome") affective_learning_model_.learn(signal, before, after, utility);
}
void Brain::sync_self_state() { const auto goals = goals_model_.all(); std::vector<GoalState> active_goals; active_goals.reserve(goals.size()); for (const auto& goal : goals) if (goal.status == GoalStatus::active) active_goals.push_back(GoalState{goal.id, goal.priority, true}); self_state_model_.set_goals(std::move(active_goals)); const auto capability_health = self_model_.health(); self_state_model_.set_activity(state_.events_seen == 0 ? "idle" : "cognitive_processing"); self_state_model_.set_workload(std::clamp(std::max(state_.threat, 1.0 - capability_health.overall), 0.0, 1.0)); self_state_model_.set_uncertainty(std::clamp(1.0 - state_.attention, 0.0, 1.0)); self_state_model_.set_health(CognitiveHealth{std::clamp(capability_health.overall * (1.0 - state_.threat * 0.5), 0.0, 1.0), capability_health.overall, std::clamp(1.0 - state_.novelty * 0.1, 0.0, 1.0), capability_health.overall}); for (const auto& capability : self_model_.capabilities()) self_state_model_.set_resource_pressure(capability.name, std::clamp(1.0 - (capability.availability * capability.performance), 0.0, 1.0)); self_state_model_.advance_cycle(state_.events_seen); }
void Brain::replay(const Event& event) {
    state_.cycle = std::max(state_.cycle, event.sequence);

    // Validate prediction feedback before any subsystem mutates. Otherwise a
    // duplicate or malformed outcome can alter affect even when prediction
    // resolution itself is rejected below.
    if (event.kind == "prediction_outcome") {
        const auto sequence = integer_value(event.data, "prediction_sequence", 0);
        const auto* key = string_value(event.data, "key");
        const Prediction* prediction = sequence != 0
            ? find_prediction(sequence)
            : (key == nullptr ? nullptr : find_latest_unresolved_prediction(*key));
        if (!valid_prediction_outcome_event(event, prediction)) return;
    }

    process_affective_experience(event);
    if (event.kind == "goal_create") { const auto* id = string_value(event.data, "id"); const auto* description = string_value(event.data, "description"); if (id == nullptr || description == nullptr) return; Goal goal{*id, *description, double_value(event.data, "priority"), double_value(event.data, "progress"), event.sequence, integer_value(event.data, "deadline_cycle"), goal_status_value(static_cast<std::int64_t>(integer_value(event.data, "status"))), string_value(event.data, "prerequisites") ? split_ids(*string_value(event.data, "prerequisites")) : std::vector<std::string>{}, string_value(event.data, "subgoals") ? split_ids(*string_value(event.data, "subgoals")) : std::vector<std::string>{}}; goals_model_.create(std::move(goal)); return; }
    if (event.kind == "goal_activate") { if (const auto* id = string_value(event.data, "id")) goals_model_.activate(*id); return; }
    if (event.kind == "goal_progress") { if (const auto* id = string_value(event.data, "id")) goals_model_.update_progress(*id, double_value(event.data, "progress")); return; }
    if (event.kind == "goal_complete") { if (const auto* id = string_value(event.data, "id")) goals_model_.complete(*id); return; }
    if (event.kind == "goal_abandon") { if (const auto* id = string_value(event.data, "id")) goals_model_.abandon(*id); return; }
    if (event.kind == "goal_priority") { if (const auto* id = string_value(event.data, "id")) goals_model_.set_priority(*id, double_value(event.data, "priority")); return; }
    if (event.kind == "prediction") { const auto* key = string_value(event.data, "key"); const auto value = event.data.find("value"); if (key == nullptr || value == event.data.end()) return; PredictionContext context{}; if (const auto* members = string_value(event.data, "concept_members")) context.concept_members = split_ids(*members); context.evidence_strength = std::clamp(double_value(event.data, "evidence_strength"), 0.0, 1.0); predictions_.push_back(Prediction{*key, value->second, std::clamp(double_value(event.data, "confidence"), 0.0, 1.0), event.sequence, false, 0.0, std::move(context)}); return; }
    if (event.kind == "prediction_outcome") {
        const auto* key = string_value(event.data, "key");
        if (key == nullptr) return;
        const auto prediction_sequence = integer_value(event.data, "prediction_sequence", 0);
        Prediction* prediction = prediction_sequence != 0
            ? find_prediction(prediction_sequence)
            : find_latest_unresolved_prediction(*key);
        if (prediction == nullptr || prediction->resolved) return;

        prediction->resolved = true;
        prediction->error = std::clamp(double_value(event.data, "error", 1.0), 0.0, 1.0);
        const auto actual = event.data.find("actual");
        if (actual != event.data.end()) {
            long double predicted_numeric = 0.0L;
            long double actual_numeric = 0.0L;
            if (numeric_value(prediction->predicted, predicted_numeric) &&
                numeric_value(actual->second, actual_numeric)) {
                adaptation_.observe(*key,
                                    static_cast<double>(predicted_numeric),
                                    static_cast<double>(actual_numeric));
            }

            // Every observed outcome teaches associations, developmental memory,
            // and attention. Numeric adaptation is an additional path, not a
            // prerequisite for learning from categorical or boolean outcomes.
            association_.apply_prediction_feedback(
                prediction->context.concept_members,
                prediction->error <= 0.0,
                prediction->context.evidence_strength,
                event.sequence);
            const auto affect = affective_state_model_.state();
            const double affective_significance = std::clamp(
                0.25 * std::abs(affect.valence) + 0.25 * affect.arousal +
                0.25 * affect.uncertainty + 0.25 * affect.tension, 0.0, 1.0);
            developmental_learning_.observe_association(
                *key, "prediction_outcome",
                LearningSignal{
                    // Prediction accuracy is not task utility. With no explicit
                    // reward evidence, record surprise and relevance but do not
                    // manufacture a positive developmental reward.
                    prediction->error,
                    0.0,
                    std::clamp(double_value(event.data, "salience", prediction->confidence), 0.0, 1.0),
                    std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0),
                    affective_significance});
            const AttentionSignal signal{
                *key,
                std::clamp(double_value(event.data, "salience", prediction->confidence), 0.0, 1.0),
                std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0),
                1.0 - prediction->confidence,
                0.0};
            if (prediction->error > 0.0) attention_model_.reinforce(signal, prediction->error);
            else attention_model_.suppress(signal, 0.1);
        }
        return;
    }
    if (event.kind == "action_outcome") {
        const auto* action = string_value(event.data, "action"); const auto* context = string_value(event.data, "context"); if (action == nullptr || context == nullptr || action->empty() || context->empty()) return;
        const double reliability = std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0); const auto status = static_cast<ActionExecutionStatus>(integer_value(event.data, "status")); const char* status_name = "unknown"; switch (status) { case ActionExecutionStatus::rejected: status_name = "rejected"; break; case ActionExecutionStatus::prepared: status_name = "prepared"; break; case ActionExecutionStatus::executed: status_name = "executed"; break; case ActionExecutionStatus::verified: status_name = "verified"; break; case ActionExecutionStatus::failed: status_name = "failed"; break; case ActionExecutionStatus::cancelled: status_name = "cancelled"; break; case ActionExecutionStatus::rolled_back: status_name = "rolled_back"; break; }
        const std::string belief_key = "action." + *action; beliefs_[belief_key] = Belief{belief_key, std::string(status_name), reliability, 1, event.sequence, false}; const auto observed = event.data.find("observed"); const bool has_observed_consequence = observed != event.data.end() && std::get_if<bool>(&observed->second) != nullptr && *std::get_if<bool>(&observed->second); const double prediction_error = has_observed_consequence ? std::clamp(std::abs(double_value(event.data, "consequence_error")), 0.0, 1.0) : 1.0 - reliability; const double reward = has_observed_consequence ? std::clamp(double_value(event.data, "actual_consequence"), -1.0, 1.0) : 0.0; const auto affect = affective_state_model_.state(); const double affective_significance = std::clamp(0.25 * std::abs(affect.valence) + 0.25 * affect.arousal + 0.25 * affect.uncertainty + 0.25 * affect.tension, 0.0, 1.0); if (has_observed_consequence) developmental_learning_.observe_strategy(*context, *action, LearningSignal{prediction_error, reward, std::clamp(double_value(event.data, "salience", 0.0), 0.0, 1.0), std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0), affective_significance}); const AttentionSignal signal{*action, std::clamp(double_value(event.data, "salience", 0.0), 0.0, 1.0), std::clamp(double_value(event.data, "novelty", state_.novelty), 0.0, 1.0), prediction_error, 0.0}; if (has_observed_consequence && reward > 0.0) attention_model_.reinforce(signal, reward); else if (has_observed_consequence && reward < 0.0) attention_model_.suppress(signal, -reward); return;
    }
    if (event.kind == "evolution_evaluated") {
        const auto* id = string_value(event.data, "experiment_id");
        const auto* key = string_value(event.data, "key");
        if (id != nullptr && key != nullptr) {
            EvolutionExperiment experiment{
                *id,
                EvolutionProposal{*key,
                                  double_value(event.data, "current"),
                                  double_value(event.data, "proposed"),
                                  double_value(event.data, "expected_gain"),
                                  double_value(event.data, "confidence")},
                double_value(event.data, "baseline"),
                double_value(event.data, "candidate"),
                0.0,
                double_value(event.data, "confidence"),
                static_cast<ExperimentOutcome>(integer_value(event.data, "outcome")),
                true};
            evolution_controller_.replay_evaluation(experiment);
        }
        return;
    }
    if (event.kind == "evolution_register") { if (const auto* key = string_value(event.data, "key")) evolution_.register_parameter(*key, double_value(event.data, "initial")); return; }
    if (event.kind == "evolution_fitness") { if (const auto* key = string_value(event.data, "key")) evolution_.observe_fitness(*key, double_value(event.data, "fitness")); return; }
    if (event.kind == "evolution_canary") {
        const auto baseline = double_value(event.data, "baseline");
        const auto candidate = double_value(event.data, "candidate");
        if (std::isfinite(baseline) && std::isfinite(candidate))
            evolution_controller_.observe_canary_for_brain(
                string_value(event.data, "experiment_id") ? *string_value(event.data, "experiment_id") : "",
                CanaryObservation{baseline, candidate});
        return;
    }
    if (event.kind == "evolution_adopt") {
        const auto* key = string_value(event.data, "key");
        if (key != nullptr) {
            const auto* experiment_id = string_value(event.data, "experiment_id");
            const EvolutionProposal proposal{*key, double_value(event.data, "current"),
                                             double_value(event.data, "proposed"),
                                             double_value(event.data, "expected_gain"),
                                             double_value(event.data, "confidence")};
            if (experiment_id != nullptr && !experiment_id->empty()) {
                EvolutionExperiment experiment{
                    *experiment_id,
                    proposal,
                    double_value(event.data, "baseline", proposal.current),
                    double_value(event.data, "candidate", proposal.proposed),
                    0.0,
                    proposal.confidence,
                    static_cast<ExperimentOutcome>(integer_value(event.data, "outcome")),
                    true};
                const auto adoption = evolution_controller_.adoption_journal().get(*experiment_id);
                if (adoption.has_value() &&
                    (adoption->state == AdoptionState::Adopted ||
                     adoption->state == AdoptionState::RolledBack)) return;
                if (!evolution_.adopt(proposal)) return;
                if (!evolution_controller_.replay_adoption(experiment)) {
                    evolution_.restore_previous(*key);
                    return;
                }
                evolution_history_.append(EvolutionHistoryRecord{
                    *experiment_id, *key, EvolutionRecordAction::Adopted,
                    experiment.outcome, experiment.baseline_fitness,
                    experiment.candidate_fitness, experiment.confidence, 0,
                    "replayed", {}});
            } else {
                evolution_.adopt(proposal);
            }
        }
        return;
    }
    if (event.kind == "evolution_rollback") {
        const auto* key = string_value(event.data, "key");
        if (key != nullptr) {
            const auto* experiment_id = string_value(event.data, "experiment_id");
            if (experiment_id != nullptr && !experiment_id->empty()) {
                const auto record = evolution_controller_.adoption_journal().get(*experiment_id);
                if (!record.has_value() || record->state == AdoptionState::RolledBack ||
                    record->state != AdoptionState::Adopted) return;
                if (!evolution_.rollback(*key)) return;
                const auto reason = string_value(event.data, "reason");
                if (!evolution_controller_.replay_rollback(
                        *experiment_id, reason != nullptr ? *reason : "replayed")) {
                    evolution_.restore_previous(*key);
                    return;
                }
                evolution_history_.append(EvolutionHistoryRecord{
                    *experiment_id, *key, EvolutionRecordAction::RolledBack,
                    ExperimentOutcome::Degraded, 0.0,
                    double_value(event.data, "observed_delta"), 0.0, 0,
                    reason != nullptr ? *reason : "replayed", *experiment_id});
            } else {
                evolution_.rollback(*key);
            }
        }
        return;
    }
    if (event.kind == "resilience_isolate") { if (const auto* component = string_value(event.data, "component")) resilience_.isolate(*component); return; }
    if (event.kind == "resilience_recover") { if (const auto* component = string_value(event.data, "component")) resilience_.recover(*component, double_value(event.data, "health")); return; }
    if (event.kind == "capability_observe") { if (const auto* name = string_value(event.data, "name")) self_model_.observe_capability(*name, double_value(event.data, "availability"), double_value(event.data, "performance")); return; }
    if (event.kind == "capability_isolate") { if (const auto* name = string_value(event.data, "name")) self_model_.isolate(*name); return; }
    if (event.kind == "capability_restore") { if (const auto* name = string_value(event.data, "name")) self_model_.restore(*name, double_value(event.data, "availability"), double_value(event.data, "performance")); return; }
    if (event.kind != "observation" && event.kind != "learning") return;
    if (event.kind == "learning") {
        const source = integer_value(event.data, "source_action_sequence", 0);
        if (source != 0 && !processed_derived_learning_sources_.insert(source).second) return;
    }
    const double reliability = event.kind == "learning" ? std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0) : 0.7;
    if (event.kind == "learning") for (const auto& [key, value] : event.data) if (key != "reliability") { knowledge_.assimilate(Evidence{event.source, key, value, reliability}); break; }
    std::vector<Belief> before; before.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) before.push_back(belief);
    for (const auto& [key, value] : event.data) { if (event.kind == "learning" && key == "reliability") continue; const auto it = beliefs_.find(key); if (it == beliefs_.end()) beliefs_.emplace(key, Belief{key, value, reliability, 1, event.sequence}); else { const bool same = it->second.value == value; it->second.value = value; it->second.confidence = same ? std::min(0.999, it->second.confidence + (1.0 - it->second.confidence) * reliability) : std::max(0.05, it->second.confidence * (1.0 - reliability)); it->second.disputed = !same && it->second.observations > 0; ++it->second.observations; it->second.updated_sequence = event.sequence; } world_.observe(Fact{event.source, key, value, reliability, 1}); const auto subject = string_value(event.data, "subject"); const auto predicate = string_value(event.data, "predicate"); const auto object = string_value(event.data, "object"); if (subject != nullptr && predicate != nullptr && object != nullptr) world_.relate(Relation{*subject, *predicate, *object, reliability, event.sequence, false}); }
    std::vector<Belief> after; after.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) after.push_back(belief); causal_.observe_transition(before, after); association_.observe(before, after, event.sequence);
    if (event.kind == "observation") {
        const auto history = memory_.recent(2); std::vector<Event> previous; if (history.size() > 1) previous.push_back(history[1]);
        const double novelty = compute_novelty(event, previous); double strongest = 0.0; for (const auto& [_, belief] : beliefs_) strongest = std::max(strongest, belief.confidence);
        threat_state_ = threat_model_.assess(event); state_.novelty = novelty; state_.threat = threat_state_.score;
        const auto health = event.data.find("health"); if (health != event.data.end()) resilience_.observe(event.source, std::clamp(double_value(event.data, "health", 1.0), 0.0, 1.0));
        const auto affect = affective_state_model_.state();
        const double internal_activation = std::clamp(0.25 * std::abs(affect.valence) + 0.25 * affect.arousal + 0.25 * affect.uncertainty + 0.25 * affect.tension, 0.0, 1.0);
        attention_state_ = attention_model_.score(event, novelty, strongest, internal_activation);
        state_.attention = attention_state_.salience;
        const double outcome = double_value(event.data, "outcome", 0.0);
        if (outcome > 0.0) attention_model_.reinforce(attention_state_, std::clamp(outcome, 0.0, 1.0)); else if (outcome < 0.0) attention_model_.suppress(attention_state_, std::clamp(-outcome, 0.0, 1.0));
    }
}
Observation Brain::observe(Event event) {
    std::unique_lock lock(mutex_);
    if (event.kind == "prediction_outcome") {
        const auto sequence = integer_value(event.data, "prediction_sequence", 0);
        const auto* key = string_value(event.data, "key");
        const Prediction* prediction = sequence != 0
            ? find_prediction(sequence)
            : (key == nullptr ? nullptr : find_latest_unresolved_prediction(*key));
        if (!valid_prediction_outcome_event(event, prediction)) return Observation{};
    }
    event.timestamp_ns = event.timestamp_ns == 0 ? now_ns() : event.timestamp_ns;
    const auto previous = memory_.recent(1);
    const double novelty = compute_novelty(event, previous);
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return Observation{};
    ++state_.events_seen;
    state_.cycle = event.sequence;
    replay(event);
    state_.novelty = novelty;
    consolidate_experience(event);
    sync_self_state();
    return Observation{std::move(event), novelty};
}
double Brain::learn(const Evidence& evidence) { std::unique_lock lock(mutex_); if (evidence.key.empty()) return 0.0; const double reliability = std::clamp(evidence.reliability, 0.0, 1.0); Event event{0, now_ns(), evidence.source, "learning", {{evidence.key, evidence.value}, {"reliability", reliability}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return 0.0; ++state_.events_seen; state_.cycle = event.sequence; replay(event); sync_self_state(); if (const auto* metric = knowledge_.source_metric(evidence.source)) return metric->reliability; return reliability; }
LearningCycle Brain::learn_from_prediction(const std::string& key, const Scalar& actual, double fitness) {
    std::unique_lock lock(mutex_);
    LearningCycle cycle{};
    if (key.empty() || !std::isfinite(fitness)) return cycle;

    const auto* prediction = find_latest_unresolved_prediction(key);
    if (prediction == nullptr) return cycle;
    if (const auto* value = std::get_if<double>(&actual);
        value != nullptr && !std::isfinite(*value)) return cycle;
    if (const auto* value = std::get_if<double>(&prediction->predicted);
        value != nullptr && !std::isfinite(*value)) return cycle;

    double error = prediction->predicted == actual ? 0.0 : 1.0;
    long double predicted_numeric = 0.0L;
    long double actual_numeric = 0.0L;
    if (numeric_value(prediction->predicted, predicted_numeric) &&
        numeric_value(actual, actual_numeric)) {
        const long double scale = std::max({
            1.0L, std::abs(predicted_numeric), std::abs(actual_numeric)});
        error = std::clamp(static_cast<double>(
            std::abs(actual_numeric - predicted_numeric) / scale), 0.0, 1.0);
    } else if (prediction->predicted != actual) {
        // Preserve the legacy contract for categorical learning: this API
        // requires an interpretable matching outcome when no numeric error
        // can be computed. General categorical feedback uses resolve_prediction.
        return cycle;
    }

    Event outcome{0, now_ns(), "brain", "prediction_outcome",
                  {{"key", prediction->key},
                   {"prediction_sequence", static_cast<std::int64_t>(prediction->created_sequence)},
                   {"actual", actual},
                   {"error", error},
                   {"salience", attention_state_.salience},
                   {"novelty", state_.novelty}}};
    outcome.sequence = memory_.append(outcome);
    if (outcome.sequence == 0) return cycle;
    ++state_.events_seen;
    state_.cycle = outcome.sequence;
    replay(outcome);
    if (const auto* metric = adaptation_.metric(key); metric != nullptr)
        cycle.adaptation = *metric;

    Event fitness_event{0, now_ns(), "brain", "evolution_fitness",
                        {{"key", key}, {"fitness", std::clamp(fitness, -1.0, 1.0)}}};
    fitness_event.sequence = memory_.append(fitness_event);
    if (fitness_event.sequence == 0) return cycle;
    ++state_.events_seen;
    state_.cycle = fitness_event.sequence;
    replay(fitness_event);
    cycle.proposals = evolution_.propose();
    sync_self_state();
    return cycle;
}

} // namespace jarvis::core
