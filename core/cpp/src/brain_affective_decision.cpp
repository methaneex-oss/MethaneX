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
    const double error = unit(attribute_value(event.data, "error", 0.0));
    const double novelty = unit(attribute_value(event.data, "novelty", 0.0));
    const double salience = unit(attribute_value(event.data, "salience", 0.0));
    const double uncertainty = unit(attribute_value(event.data, "uncertainty", error));
    const double confidence = unit(attribute_value(event.data, "confidence", 1.0 - error));

    // Events describe evidence, not emotional categories. If a producer knows
    // the experienced utility it may provide it explicitly. Otherwise the
    // model uses generic evidence dimensions rather than event-type semantics.
    const auto outcome_it = event.data.find("outcome");
    const auto utility_it = event.data.find("utility");
    double outcome = 0.0;
    if (outcome_it != event.data.end()) outcome = signed_unit(attribute_value(event.data, "outcome", 0.0));
    else if (utility_it != event.data.end()) outcome = signed_unit(attribute_value(event.data, "utility", 0.0));
    else if (event.data.find("reliability") != event.data.end()) {
        outcome = 2.0 * confidence - 1.0;
    } else if (event.data.find("error") != event.data.end()) {
        outcome = 1.0 - 2.0 * error;
    }
    return {outcome, error, novelty, salience, uncertainty, confidence};
}

bool has_outcome_evidence(const Event& event) noexcept {
    return event.data.find("outcome") != event.data.end() ||
           event.data.find("utility") != event.data.end() ||
           event.data.find("reliability") != event.data.end();
}

} // namespace

std::vector<Decision> Brain::choose_with_affect(const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);

    // Reconstruct affect and learned appraisal exclusively from persistent
    // evidence. No event kind is treated as an emotion and no action is
    // prescribed by an affective label.
    AffectiveStateModel affect_model;
    AffectiveLearningModel appraisal_model;
    for (const auto& event : memory_.all()) {
        const auto signal = signal_from_event(event);
        const auto before = affect_model.state();
        const auto after = affect_model.update(signal);
        if (has_outcome_evidence(event)) {
            const double utility = signed_unit(attribute_value(event.data, "utility", signal.outcome));
            appraisal_model.learn(signal, before, after, utility);
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

    context.affective_uncertainty = std::clamp(
        context.affective_uncertainty * (0.75 + 0.25 * appraisal.uncertainty_weight), 0.0, 1.0);
    context.tension = std::clamp(
        context.tension * (0.75 + 0.25 * appraisal.tension_error_weight), 0.0, 1.0);
    return decision_.decide(actions, context);
}

} // namespace jarvis::core
