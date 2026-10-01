#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double attribute_value(const Attributes& data, const char* key, double fallback) noexcept {
    const auto it = data.find(key);
    if (it == data.end()) return fallback;
    if (const auto* value = std::get_if<double>(&it->second)) return *value;
    if (const auto* value = std::get_if<std::int64_t>(&it->second)) return static_cast<double>(*value);
    return fallback;
}

double unit(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0); }
double signed_unit(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, -1.0, 1.0); }

AffectiveSignal signal_from_event(const Event& event) noexcept {
    double outcome = 0.0;
    double error = unit(attribute_value(event.data, "error", 0.0));
    double novelty = unit(attribute_value(event.data, "novelty", 0.0));
    double salience = unit(attribute_value(event.data, "salience", 0.0));
    double uncertainty = unit(attribute_value(event.data, "uncertainty", error));
    double confidence = unit(attribute_value(event.data, "confidence", 1.0 - error));

    if (event.kind == "action_outcome" || event.kind == "learning") {
        const double reliability = unit(attribute_value(event.data, "reliability", confidence));
        outcome = 2.0 * reliability - 1.0;
        error = 1.0 - reliability;
        confidence = reliability;
    } else if (event.kind == "prediction_outcome") {
        outcome = 1.0 - 2.0 * error;
    } else if (event.kind == "goal_complete") {
        outcome = 1.0;
        salience = std::max(salience, 0.8);
    } else if (event.kind == "goal_progress") {
        outcome = signed_unit(attribute_value(event.data, "delta", 0.0));
    }
    return {signed_unit(outcome), error, novelty, salience, uncertainty, confidence};
}

double utility_from_event(const Event& event, const AffectiveSignal& signal) noexcept {
    if (event.kind == "goal_progress") return signed_unit(attribute_value(event.data, "delta", signal.outcome));
    return signal.outcome;
}

} // namespace

std::vector<Decision> Brain::choose_with_affect(const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);

    // Rebuild both affect and its learned appraisal from the experience
    // journal. The learned mapping therefore develops from consequences and
    // remains reproducible after restart; it is not a hidden process variable.
    AffectiveStateModel affect_model;
    AffectiveLearningModel appraisal_model;
    for (const auto& event : memory_.all()) {
        const auto signal = signal_from_event(event);
        const auto before = affect_model.state();
        const auto after = affect_model.update(signal);
        if (event.kind == "prediction_outcome" || event.kind == "action_outcome" ||
            event.kind == "learning" || event.kind == "goal_progress" || event.kind == "goal_complete") {
            appraisal_model.learn(signal, before, after, utility_from_event(event, signal));
        }
    }

    const auto affect = affect_model.state();
    const auto appraisal = appraisal_model.appraisal();
    DecisionContext context;
    context.uncertainty = std::clamp(1.0 - state_.attention, 0.0, 1.0);
    context.threat = std::clamp(state_.threat, 0.0, 1.0);
    context.valence = affect.valence;
    context.arousal = affect.arousal;
    context.affective_uncertainty = affect.uncertainty;
    context.tension = affect.tension;
    context.stability = affect.stability;

    // Learned appraisal influences the strength of uncertainty/tension
    // weighting, but does not select an action directly.
    context.affective_uncertainty = std::clamp(
        context.affective_uncertainty * (0.75 + 0.25 * appraisal.uncertainty_weight), 0.0, 1.0);
    context.tension = std::clamp(
        context.tension * (0.75 + 0.25 * appraisal.tension_error_weight), 0.0, 1.0);
    return decision_.decide(actions, context);
}

} // namespace jarvis::core
