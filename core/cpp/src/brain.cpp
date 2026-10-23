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
bool valid_action_outcome_event(const Event& event) {
    // An outcome without an action/context identity cannot be connected to a
    // strategy or a decision context. Reject it before affective processing so
    // malformed records cannot alter global state while being ignored by the
    // action-specific handler later in replay.
    const auto* action = string_value(event.data, "action");
    const auto* context = string_value(event.data, "context");
    if (action == nullptr || action->empty() ||
        context == nullptr || context->empty()) return false;

    // Outcome events are trusted learning input. Reject an explicitly supplied
    // execution status outside the enum instead of interpreting unknown values
    // as successful/failed evidence during replay.
    const auto status = event.data.find("status");
    if (status != event.data.end()) {
        const auto* value = std::get_if<std::int64_t>(&status->second);
        if (value == nullptr || *value < 0 ||
            *value > static_cast<std::int64_t>(ActionExecutionStatus::rolled_back))
            return false;
    }

    const auto valid_finite_numeric = [&](const char* name) {
        const auto field = event.data.find(name);
        if (field == event.data.end()) return true;
        if (const auto* value = std::get_if<double>(&field->second))
            return std::isfinite(*value);
        return std::get_if<std::int64_t>(&field->second) != nullptr;
    };
    const auto valid_optional_unit = [&](const char* name) {
        const auto field = event.data.find(name);
        if (field == event.data.end()) return true;
        if (const auto* value = std::get_if<double>(&field->second))
            return std::isfinite(*value) && *value >= 0.0 && *value <= 1.0;
        if (const auto* value = std::get_if<std::int64_t>(&field->second))
            return *value == 0 || *value == 1;
        return false;
    };

    // Outcome records feed affect, attention, and developmental strategy
    // learning. Reject malformed numeric evidence before any of those models
    // can observe it, including when the journal is replayed after restart.
    if (!valid_finite_numeric("expected_consequence") ||
        !valid_finite_numeric("actual_consequence") ||
        !valid_finite_numeric("consequence_error") ||
        !valid_optional_unit("reliability") ||
        !valid_optional_unit("evidence_reliability") ||
        !valid_optional_unit("confidence") ||
        !valid_optional_unit("salience") ||
        !valid_optional_unit("novelty")) return false;

    const auto observed = event.data.find("observed");
    // If supplied, observed must be an actual boolean. Treating malformed
    // metadata as "not observed" would silently downgrade a corrupt world
    // consequence into execution-only evidence and train the wrong pathway.
    if (observed != event.data.end() &&
        std::get_if<bool>(&observed->second) == nullptr) return false;
    const bool has_observed_consequence =
        observed != event.data.end() &&
        *std::get_if<bool>(&observed->second);
    if (!has_observed_consequence) return true;

    // Strategy learning needs the observed consequence and its error. The
    // expected consequence is optional for legacy strategy-only events; affective
    // appraisal separately requires it before treating the event as a comparison.
    return event.data.find("actual_consequence") != event.data.end() &&
           event.data.find("consequence_error") != event.data.end();
}
bool valid_affective_learning_event(const Event& event) {
    // Affective appraisal updates are persisted learning input. Validate them
    // before recording a source as consumed or mutating calibration.
    const auto source = event.data.find("source_action_sequence");
    const auto* source_sequence = source == event.data.end()
        ? nullptr : std::get_if<std::int64_t>(&source->second);
    if (source_sequence == nullptr || *source_sequence <= 0) return false;

    const auto finite_numeric = [&](const char* name, bool required) {
        const auto field = event.data.find(name);
        if (field == event.data.end()) return !required;
        if (const auto* value = std::get_if<double>(&field->second))
            return std::isfinite(*value);
        return std::get_if<std::int64_t>(&field->second) != nullptr;
    };
    const auto unit_value = [&](const char* name) {
        const auto field = event.data.find(name);
        if (field == event.data.end()) return true;
        if (const auto* value = std::get_if<double>(&field->second))
            return std::isfinite(*value) && *value >= 0.0 && *value <= 1.0;
        if (const auto* value = std::get_if<std::int64_t>(&field->second))
            return *value == 0 || *value == 1;
        return false;
    };
    return finite_numeric("expected_consequence", true) &&
           finite_numeric("actual_consequence", true) &&
           finite_numeric("consequence_error", true) &&
           finite_numeric("utility", true) &&
           event.data.find("prediction_error") != event.data.end() &&
           unit_value("prediction_error") &&
           unit_value("novelty") && unit_value("salience") &&
           unit_value("uncertainty") && unit_value("confidence");
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
    const auto utility = event.data.find("outcome_utility");
    if (utility != event.data.end()) {
        if (const auto* value = std::get_if<double>(&utility->second)) {
            if (!std::isfinite(*value) || *value < -1.0 || *value > 1.0) return false;
        } else if (const auto* value = std::get_if<std::int64_t>(&utility->second)) {
            if (*value < -1 || *value > 1) return false;
        } else {
            return false;
        }
    }

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
    // Evidence confidence is distinct from operational execution reliability.
    // A failed action can be highly certain evidence that an attempted strategy
    // failed; do not down-rank that experience merely because execution reliability
    // was low. Preserve legacy confidence/reliability fallbacks when the explicit
    // evidence-confidence field is absent.
    if (const auto it = event.data.find("reliability"); it != event.data.end())
        if (const auto* value = std::get_if<double>(&it->second)) confidence = *value;
    if (const auto it = event.data.find("confidence"); it != event.data.end())
        if (const auto* value = std::get_if<double>(&it->second)) confidence = *value;
    if (const auto it = event.data.find("evidence_reliability"); it != event.data.end())
        if (const auto* value = std::get_if<double>(&it->second)) confidence = *value;
    const auto affect = affective_state_model_.state();
    const double affective_significance = std::clamp(0.25 * std::abs(affect.valence) + 0.25 * affect.arousal + 0.25 * affect.uncertainty + 0.25 * affect.tension, 0.0, 1.0);
    salience = std::max(std::clamp(salience, 0.0, 1.0), affective_significance);
    memory_.consolidate(event.sequence, salience, novelty, error, std::clamp(confidence, 0.0, 1.0));
}
void Brain::process_affective_experience(const Event& event, bool external_observation) {
    if (const auto it = event.data.find("affective_relevant");
        it != event.data.end() && std::get_if<bool>(&it->second) != nullptr &&
        !*std::get_if<bool>(&it->second)) return;
    const auto before = affective_state_model_.state(); AffectiveSignal signal{}; double utility = 0.0; bool relevant = false;
    if (event.kind == "prediction_outcome") {
        const double error = std::clamp(double_value(event.data, "error", 1.0), 0.0, 1.0);
        // Prediction error is unsigned surprise, not outcome utility. Without
        // explicit task-specific utility evidence, a mismatch must not be
        // interpreted as a positive reward merely because 1 - error is positive.
        const auto explicit_utility = event.data.find("outcome_utility");
        const bool has_explicit_utility = explicit_utility != event.data.end();
        const double observed_utility = has_explicit_utility
            ? std::clamp(double_value(event.data, "outcome_utility"), -1.0, 1.0)
            : 0.0;
        signal.outcome = observed_utility;
        signal.prediction_error = error;
        signal.novelty = std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0);
        signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0);
        // Explicit utility is trusted outcome evidence; prediction confidence
        // remains separate and cannot erase the supplied outcome's valence.
        signal.confidence = has_explicit_utility ? 1.0 : std::clamp(1.0 - error, 0.0, 1.0);
        utility = observed_utility;
        relevant = true;
    }
    else if (event.kind == "action_outcome") { const auto expected = event.data.find("expected_consequence"); const auto actual = event.data.find("actual_consequence"); const auto consequence_error = event.data.find("consequence_error"); const auto observed = event.data.find("observed"); const bool has_observed_consequence = observed != event.data.end() && std::get_if<bool>(&observed->second) != nullptr && *std::get_if<bool>(&observed->second); if (has_observed_consequence && expected != event.data.end() && actual != event.data.end() && consequence_error != event.data.end()) { const double actual_value = double_value(event.data, "actual_consequence"); const double error = double_value(event.data, "consequence_error"); const double reliability = std::clamp(
            double_value(event.data, "evidence_reliability",
                         double_value(event.data, "reliability", 0.5)),
            0.0, 1.0);
        signal.outcome = std::clamp(actual_value, -1.0, 1.0);
        signal.prediction_error = std::clamp(std::abs(error), 0.0, 1.0);
        signal.novelty = std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0);
        signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0);
        signal.confidence = reliability;
        utility = actual_value;
        relevant = true; } else {
            // Execution reliability is not consequence utility. If no valid
            // consequence was observed, keep valence neutral and represent the
            // missing outcome as uncertainty rather than inventing reward.
            signal.outcome = 0.0;
            signal.prediction_error = 0.0;
            signal.uncertainty = 1.0;
            signal.novelty = std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0);
            signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0);
            signal.confidence = 0.0;
            utility = 0.0;
            relevant = true;
        } }
    else if (event.kind == "affective_learning") { const auto source = integer_value(event.data, "source_action_sequence", 0); if (source != 0 && !processed_affective_learning_sources_.insert(source).second) return; affective_learning_model_.learn(AffectiveOutcomeEvidence{double_value(event.data, "expected_consequence"), double_value(event.data, "actual_consequence"), double_value(event.data, "consequence_error"), double_value(event.data, "utility", double_value(event.data, "actual_consequence")), double_value(event.data, "prediction_error"), double_value(event.data, "novelty", 0.0), double_value(event.data, "salience", attention_state_.salience), double_value(event.data, "uncertainty", 0.0), double_value(event.data, "confidence", 0.5)}); return; }
    else if (event.kind == "learning") {
        const double reliability =
            std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0);
        // Evidence reliability describes how strongly to trust a fact, not
        // whether that fact is good or bad. Only explicit task utility changes
        // affective valence; uncertainty represents weak evidence.
        signal.outcome = std::clamp(
            double_value(event.data, "outcome_utility", 0.0), -1.0, 1.0);
        signal.confidence = reliability;
        signal.uncertainty = 1.0 - reliability;
        signal.novelty = std::clamp(
            double_value(event.data, "novelty", state_.novelty), 0.0, 1.0);
        signal.salience = std::clamp(
            double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0);
        utility = signal.outcome;
        relevant = true;
    }
    else if (event.kind == "observation" || external_observation) { const double confidence = std::clamp(double_value(event.data, "confidence", 0.5), 0.0, 1.0); signal.outcome = std::clamp(double_value(event.data, "outcome", 0.0), -1.0, 1.0); signal.prediction_error = std::clamp(double_value(event.data, "prediction_error", 0.0), 0.0, 1.0); signal.novelty = std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0); signal.salience = std::clamp(double_value(event.data, "salience", attention_state_.salience), 0.0, 1.0); signal.uncertainty = 1.0 - confidence; signal.confidence = confidence; utility = signal.outcome; relevant = true; }
    else if (event.kind == "goal_progress" || event.kind == "goal_complete") { const double progress = event.kind == "goal_complete" ? 1.0 : std::clamp(double_value(event.data, "progress", 0.0), 0.0, 1.0); signal.outcome = 2.0 * progress - 1.0; signal.prediction_error = 1.0 - progress; signal.novelty = state_.novelty; signal.salience = attention_state_.salience; signal.confidence = progress; utility = signal.outcome; relevant = true; }
    if (!relevant) return;
    signal = affective_learning_model_.modulate(signal); const auto after = affective_state_model_.update(signal); if (event.kind != "action_outcome") affective_learning_model_.learn(signal, before, after, utility);
}
void Brain::sync_self_state() { const auto goals = goals_model_.all(); std::vector<GoalState> active_goals; active_goals.reserve(goals.size()); for (const auto& goal : goals) if (goal.status == GoalStatus::active) active_goals.push_back(GoalState{goal.id, goal.priority, true}); self_state_model_.set_goals(std::move(active_goals)); const auto capability_health = self_model_.health(); self_state_model_.set_activity(state_.events_seen == 0 ? "idle" : "cognitive_processing"); self_state_model_.set_workload(std::clamp(std::max(state_.threat, 1.0 - capability_health.overall), 0.0, 1.0)); self_state_model_.set_uncertainty(std::clamp(1.0 - state_.attention, 0.0, 1.0)); self_state_model_.set_health(CognitiveHealth{std::clamp(capability_health.overall * (1.0 - state_.threat * 0.5), 0.0, 1.0), capability_health.overall, std::clamp(1.0 - state_.novelty * 0.1, 0.0, 1.0), capability_health.overall}); for (const auto& capability : self_model_.capabilities()) self_state_model_.set_resource_pressure(capability.name, std::clamp(1.0 - (capability.availability * capability.performance), 0.0, 1.0)); self_state_model_.advance_cycle(state_.events_seen); }
bool Brain::valid_affective_learning_source(const Event& event) const {
    const auto source = event.data.find("source_action_sequence");
    const auto* sequence = source == event.data.end()
        ? nullptr : std::get_if<std::int64_t>(&source->second);
    if (sequence == nullptr || *sequence <= 0) return false;

    const auto history = memory_.all();
    const auto source_event = std::find_if(
        history.begin(), history.end(), [sequence](const Event& candidate) {
            return candidate.sequence == static_cast<std::uint64_t>(*sequence);
        });
    if (source_event == history.end() || source_event->kind != "action_outcome" ||
        !valid_action_outcome_event(*source_event)) return false;

    const auto observed = source_event->data.find("observed");
    if (observed == source_event->data.end()) return false;
    const auto* observed_value = std::get_if<bool>(&observed->second);
    if (observed_value == nullptr || !*observed_value) return false;

    // The appraisal update must describe the same consequence as its
    // authoritative action event, not an unrelated or fabricated source.
    for (const char* field : {"expected_consequence", "actual_consequence",
                              "consequence_error"}) {
        const auto source_value = source_event->data.find(field);
        const auto learning_value = event.data.find(field);
        if (source_value == source_event->data.end() ||
            learning_value == event.data.end()) return false;
        const auto number = [](const Scalar& value, double& out) {
            if (const auto* d = std::get_if<double>(&value)) {
                out = *d;
                return std::isfinite(out);
            }
            if (const auto* i = std::get_if<std::int64_t>(&value)) {
                out = static_cast<double>(*i);
                return true;
            }
            return false;
        };
        double source_number = 0.0;
        double learning_number = 0.0;
        if (!number(source_value->second, source_number) ||
            !number(learning_value->second, learning_number) ||
            std::abs(source_number - learning_number) > 1e-12) return false;
    }
    return true;
}

void Brain::replay(const Event& event, bool external_observation) {
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
    if (event.kind == "action_outcome" &&
        !valid_action_outcome_event(event)) return;

    if (event.kind == "affective_learning" &&
        (!valid_affective_learning_event(event) ||
         !valid_affective_learning_source(event))) return;

    const auto persisted_external = event.data.find("_external_observation");
    const bool was_externally_observed =
        persisted_external != event.data.end() &&
        std::get_if<bool>(&persisted_external->second) != nullptr &&
        *std::get_if<bool>(&persisted_external->second);
    process_affective_experience(event, external_observation || was_externally_observed);
    if (event.kind == "goal_create") { const auto* id = string_value(event.data, "id"); const auto* description = string_value(event.data, "description"); if (id == nullptr || description == nullptr) return; Goal goal{*id, *description, double_value(event.data, "priority"), double_value(event.data, "progress"), event.sequence, integer_value(event.data, "deadline_cycle"), goal_status_value(static_cast<std::int64_t>(integer_value(event.data, "status"))), string_value(event.data, "prerequisites") ? split_ids(*string_value(event.data, "prerequisites")) : std::vector<std::string>{}, string_value(event.data, "subgoals") ? split_ids(*string_value(event.data, "subgoals")) : std::vector<std::string>{}}; goals_model_.create(std::move(goal)); return; }
    if (event.kind == "goal_activate") { if (const auto* id = string_value(event.data, "id")) goals_model_.activate(*id); return; }
    if (event.kind == "goal_progress") { if (const auto* id = string_value(event.data, "id")) { const double progress = double_value(event.data, "progress"); if (progress < 1.0) goals_model_.update_progress(*id, progress); } return; }
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
                    // Prediction error is unsigned surprise. Only explicit
                    // environmental utility supplies a signed learning target.
                    prediction->error,
                    std::clamp(double_value(event.data, "outcome_utility", 0.0), -1.0, 1.0),
                    std::clamp(double_value(event.data, "salience", prediction->confidence), 0.0, 1.0),
                    std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0),
                    affective_significance,
                    std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0)});
            const AttentionSignal signal{
                *key,
                std::clamp(double_value(event.data, "salience", prediction->confidence), 0.0, 1.0),
                std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0),
                1.0 - prediction->confidence,
                0.0,
                0.0,
                prediction->error};
            if (prediction->error > 0.0) attention_model_.reinforce(signal, prediction->error);
            else attention_model_.suppress(signal, 0.1);
        }
        return;
    }
    if (event.kind == "action_outcome") {
        const auto* action = string_value(event.data, "action"); const auto* context = string_value(event.data, "context"); if (action == nullptr || context == nullptr || action->empty() || context->empty()) return;
        const double reliability = std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0); const auto status = static_cast<ActionExecutionStatus>(integer_value(event.data, "status")); if (status != ActionExecutionStatus::rejected) self_model_.update_performance(*action, reliability); const char* status_name = "unknown"; switch (status) { case ActionExecutionStatus::rejected: status_name = "rejected"; break; case ActionExecutionStatus::prepared: status_name = "prepared"; break; case ActionExecutionStatus::executed: status_name = "executed"; break; case ActionExecutionStatus::verified: status_name = "verified"; break; case ActionExecutionStatus::failed: status_name = "failed"; break; case ActionExecutionStatus::cancelled: status_name = "cancelled"; break; case ActionExecutionStatus::rolled_back: status_name = "rolled_back"; break; }
        const std::string belief_key = "action." + *action; beliefs_[belief_key] = Belief{belief_key, std::string(status_name), reliability, 1, event.sequence, false}; const auto observed = event.data.find("observed"); const bool has_observed_consequence = observed != event.data.end() && std::get_if<bool>(&observed->second) != nullptr && *std::get_if<bool>(&observed->second); const double prediction_error = has_observed_consequence ? std::clamp(std::abs(double_value(event.data, "consequence_error")), 0.0, 1.0) : 1.0 - reliability; const double reward = has_observed_consequence ? std::clamp(double_value(event.data, "actual_consequence"), -1.0, 1.0) : 0.0; const auto affect = affective_state_model_.state(); const double affective_significance = std::clamp(0.25 * std::abs(affect.valence) + 0.25 * affect.arousal + 0.25 * affect.uncertainty + 0.25 * affect.tension, 0.0, 1.0); if (has_observed_consequence) {
            // Consequence quality and executor status are different evidence
            // dimensions. An action may fail verification after it has already
            // changed the world; when its consequence was observed, retain that
            // outcome as learning evidence instead of dropping it because the
            // operational status maps to zero reliability.
            const double consequence_confidence = std::clamp(
                double_value(event.data, "evidence_reliability", reliability),
                0.0, 1.0);
            developmental_learning_.observe_strategy(
                *context, *action,
                LearningSignal{prediction_error, reward,
                    std::clamp(double_value(event.data, "salience", 0.0), 0.0, 1.0),
                    std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0),
                    affective_significance,
                    consequence_confidence});
        } else if (status != ActionExecutionStatus::rejected &&
                   status != ActionExecutionStatus::prepared) {
            // When no consequence observer is available, execution/verification
            // still supplies evidence about the action's operational reliability.
            // Keep that signal distinct from real-world consequence evidence:
            // successful execution is positive capability evidence, while a
            // failed attempt or rollback is negative strategy evidence.
            const double execution_outcome = std::clamp(2.0 * reliability - 1.0, -1.0, 1.0);
            // For executor-generated events, operational reliability describes
            // whether the action succeeded; it is not confidence in the evidence
            // that the attempt failed or succeeded. Use explicit evidence
            // confidence when present, while retaining legacy event semantics.
            const double evidence_reliability = std::clamp(
                double_value(event.data, "evidence_reliability", reliability),
                0.0, 1.0);
            developmental_learning_.observe_strategy(
                *context, *action,
                LearningSignal{1.0 - reliability, execution_outcome,
                    std::clamp(double_value(event.data, "salience", 0.0), 0.0, 1.0),
                    std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0),
                    affective_significance,
                    evidence_reliability});
        } // Attention tracks learning relevance, not whether an outcome was pleasant.
        // Suppressing the global feature weights after a harmful consequence made
        // the brain less sensitive to the very surprise it needed to investigate.
        // Keep consequence prediction error separate from execution reliability;
        // an absent consequence is uncertainty, not a failed prediction.
        const double consequence_error_signal = has_observed_consequence
            ? prediction_error : 0.0;
        const double evidence_uncertainty = has_observed_consequence
            ? 1.0 - std::clamp(
                double_value(event.data, "evidence_reliability", reliability),
                0.0, 1.0)
            : 1.0;
        const AttentionSignal signal{
            *action,
            std::clamp(double_value(event.data, "salience", 0.0), 0.0, 1.0),
            std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0),
            evidence_uncertainty,
            0.0,
            0.0,
            consequence_error_signal};
        const double learning_relevance = std::max({
            has_observed_consequence ? std::abs(reward) : 0.0,
            evidence_uncertainty,
            consequence_error_signal});
        if (learning_relevance > 0.0)
            attention_model_.reinforce(signal, learning_relevance);
        return;
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
    // Explicit internal-event handlers above have already consumed their
    // event types. A remaining event is new external experience, even when its
    // modality-specific kind is not literally "observation"; whitelisting that
    // one string would silently discard new sensors and environment events.
    if (event.kind == "affective_learning") return;
    if (event.kind == "learning") {
        const auto source = integer_value(event.data, "source_action_sequence", 0);
        if (source != 0 && !processed_derived_learning_sources_.insert(source).second) return;
    }
    const double reliability = event.kind == "learning"
        ? std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0)
        : 0.7;

    // A learning event carries one evidence item plus appraisal metadata. Read
    // its explicit payload rather than taking the first unordered-map entry;
    // otherwise replay can assimilate salience/novelty as knowledge or learn a
    // different fact depending on hash iteration order.
    std::vector<std::pair<std::string, Scalar>> facts;
    if (event.kind == "learning") {
        const auto* evidence_key = string_value(event.data, "evidence_key");
        const auto evidence_value = event.data.find("evidence_value");
        if (evidence_key != nullptr && !evidence_key->empty() &&
            evidence_value != event.data.end()) {
            facts.emplace_back(*evidence_key, evidence_value->second);
            knowledge_.assimilate(
                KnowledgeEvidence{event.source, *evidence_key,
                                  evidence_value->second, reliability});
        } else {
            // Backward compatibility for journal entries written before the
            // explicit evidence payload was introduced.
            for (const auto& [key, value] : event.data) {
                if (key == "reliability" || key == "salience" || key == "novelty" ||
                    key == "confidence" || key == "evidence_key" ||
                    key == "evidence_value" || key == "source_action_sequence")
                    continue;
                facts.emplace_back(key, value);
                knowledge_.assimilate(KnowledgeEvidence{event.source, key, value, reliability});
                break;
            }
        }
    } else {
        for (const auto& [key, value] : event.data) {
            // Appraisal metadata describes an experience; it is not a world fact.
            if (key == "_external_observation" || key == "novelty" || key == "salience" || key == "urgency" ||
                key == "prediction_error" || key == "outcome" || key == "confidence")
                continue;
            facts.emplace_back(key, value);
        }
    }

    std::vector<Belief> before;
    before.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) before.push_back(belief);
    for (const auto& [key, value] : facts) {
        const auto it = beliefs_.find(key);
        if (it == beliefs_.end()) {
            beliefs_.emplace(key, Belief{key, value, reliability, 1, event.sequence});
        } else {
            const bool same = it->second.value == value;
            it->second.value = value;
            it->second.confidence = same
                ? std::min(0.999, it->second.confidence +
                      (1.0 - it->second.confidence) * reliability)
                : std::max(0.05, it->second.confidence * (1.0 - reliability));
            it->second.disputed = !same && it->second.observations > 0;
            ++it->second.observations;
            it->second.updated_sequence = event.sequence;
        }
        world_.observe(Fact{event.source, key, value, reliability, 1});
    }
    const auto subject = string_value(event.data, "subject");
    const auto predicate = string_value(event.data, "predicate");
    const auto object = string_value(event.data, "object");
    if (subject != nullptr && predicate != nullptr && object != nullptr)
        world_.relate(Relation{*subject, *predicate, *object, reliability,
                               event.sequence, false});

    std::vector<Belief> after;
    after.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) after.push_back(belief);
    causal_.observe_transition(before, after);
    association_.observe(before, after, event.sequence);
    if (event.kind != "learning") {
        // Brain::observe persists the novelty appraisal with the event. During
        // startup replay Memory already contains the complete journal, so
        // memory_.recent() describes the journal tail, not the prefix preceding
        // this event. Recomputing here from that tail makes attention and later
        // affective learning depend on restart-time journal contents.
        double novelty = 0.0;
        const auto stored_novelty = event.data.find("novelty");
        if (stored_novelty != event.data.end()) {
            novelty = std::clamp(double_value(event.data, "novelty", 0.0), 0.0, 1.0);
        } else {
            // Compatibility fallback for historical observations written before
            // novelty was persisted. Do not allow malformed values to propagate.
            const auto history = memory_.recent(2);
            std::vector<Event> previous;
            if (history.size() > 1) previous.push_back(history[1]);
            novelty = std::clamp(compute_novelty(event, previous), 0.0, 1.0);
        }
        // Estimate confidence from evidence relevant to this observation. A
        // globally strong, unrelated belief must not suppress uncertainty here.
        double relevant_confidence = 0.5;
        const auto explicit_confidence = event.data.find("confidence");
        if (explicit_confidence != event.data.end()) {
            relevant_confidence = std::clamp(
                double_value(event.data, "confidence", 0.5), 0.0, 1.0);
        } else {
            double confidence_sum = 0.0;
            std::size_t relevant_count = 0;
            for (const auto& [key, value] : event.data) {
                (void)value;
                if (key == "_external_observation" || key == "novelty" || key == "salience" || key == "urgency" ||
                    key == "prediction_error" || key == "outcome" || key == "health" ||
                    key == "subject" || key == "predicate" || key == "object") continue;
                const auto belief = beliefs_.find(key);
                if (belief == beliefs_.end()) continue;
                confidence_sum += std::clamp(belief->second.confidence, 0.0, 1.0);
                ++relevant_count;
            }
            if (relevant_count != 0)
                relevant_confidence = confidence_sum / static_cast<double>(relevant_count);
        }
        threat_state_ = threat_model_.assess(event); state_.novelty = novelty; state_.threat = threat_state_.score;
        const auto health = event.data.find("health"); if (health != event.data.end()) resilience_.observe(event.source, std::clamp(double_value(event.data, "health", 1.0), 0.0, 1.0));
        const auto affect = affective_state_model_.state();
        const double internal_activation = std::clamp(0.25 * std::abs(affect.valence) + 0.25 * affect.arousal + 0.25 * affect.uncertainty + 0.25 * affect.tension, 0.0, 1.0);
        attention_state_ = attention_model_.score(event, novelty, relevant_confidence, internal_activation);
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
    if (event.kind == "action_outcome" &&
        !valid_action_outcome_event(event)) return Observation{};
    if (event.kind == "affective_learning" &&
        (!valid_affective_learning_event(event) ||
         !valid_affective_learning_source(event))) return Observation{};
    event.timestamp_ns = event.timestamp_ns == 0 ? now_ns() : event.timestamp_ns;
    const auto previous = memory_.recent(1);
    const double novelty = compute_novelty(event, previous);
    // Persist the novelty appraisal with the experience. Replay must consume
    // the same evidence as the live pass; falling back to mutable state_.novelty
    // makes affective updates depend on whether the event is observed live or
    // reconstructed after restart.
    event.data.try_emplace("novelty", novelty);
    // External observation is part of the experience, not a transient call flag.
    // Persist it so affective appraisal replays identically after restart.
    event.data.insert_or_assign("_external_observation", true);
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return Observation{};
    ++state_.events_seen;
    state_.cycle = event.sequence;
    replay(event, true);
    state_.novelty = novelty;
    consolidate_experience(event);
    sync_self_state();
    return Observation{std::move(event), novelty};
}
double Brain::learn(const Evidence& evidence) {
    std::unique_lock lock(mutex_);
    if (evidence.key.empty() || evidence.source.empty() ||
        !std::isfinite(evidence.reliability)) return 0.0;

    const double reliability = std::clamp(evidence.reliability, 0.0, 1.0);
    const auto history = memory_.recent(256);
    Event event{0, now_ns(), evidence.source, "learning",
        {{"evidence_key", evidence.key},
         {"evidence_value", evidence.value},
         {"reliability", reliability},
         {"salience", std::clamp(attention_state_.salience, 0.0, 1.0)},
         {"novelty", compute_novelty(
             Event{0, 0, evidence.source, "learning",
                   {{"evidence_key", evidence.key},
                    {"evidence_value", evidence.value},
                    {"reliability", reliability}}},
             history)}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return 0.0;
    ++state_.events_seen;
    state_.cycle = event.sequence;
    replay(event);
    state_.novelty = std::clamp(
        double_value(event.data, "novelty", state_.novelty), 0.0, 1.0);
    consolidate_experience(event);
    sync_self_state();
    if (const auto* metric = knowledge_.source_metric(evidence.source))
        return metric->reliability;
    return reliability;
}
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
                   {"error_model", std::int64_t{2}},
                   {"salience", attention_state_.salience},
                   {"novelty", state_.novelty}}};
    outcome.sequence = memory_.append(outcome);
    if (outcome.sequence == 0) return cycle;
    ++state_.events_seen;
    state_.cycle = outcome.sequence;
    replay(outcome);
    // Keep the legacy prediction-learning API on the same durable experience
    // path as resolve_prediction_feedback: replay updates cognitive models,
    // while consolidation makes this outcome retrievable by learned salience,
    // novelty, error, and confidence after restart.
    consolidate_experience(outcome, error);
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

    // Prediction feedback updates the fitness history, but proposals must also
    // pass through the durable adoption path. Merely returning proposals leaves
    // the learned parameter unchanged, so repeated experience never affects the
    // mechanism that generated the proposal.
    for (const auto& proposal : cycle.proposals) {
        if (proposal.key != key || proposal.confidence < 0.75 ||
            proposal.expected_gain <= 0.0) {
            continue;
        }
        Event adoption{0, now_ns(), "brain", "evolution_adopt",
                       {{"key", proposal.key},
                        {"current", proposal.current},
                        {"proposed", proposal.proposed},
                        {"expected_gain", proposal.expected_gain},
                        {"confidence", proposal.confidence}}};
        adoption.sequence = memory_.append(adoption);
        if (adoption.sequence == 0) break;
        ++state_.events_seen;
        state_.cycle = adoption.sequence;
        replay(adoption);
        const auto* adopted = evolution_.parameter(key);
        if (adopted != nullptr && adopted->value == proposal.proposed) {
            ++cycle.adopted;
        }
        break;
    }

    sync_self_state();
    return cycle;
}

} // namespace jarvis::core
