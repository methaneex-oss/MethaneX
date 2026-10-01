#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double unit(double value) noexcept {
    return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0);
}

double signed_unit(double value) noexcept {
    return std::clamp(std::isfinite(value) ? value : 0.0, -1.0, 1.0);
}

AffectiveSignal signal_from_event(const Event& event) noexcept {
    double outcome = 0.0;
    double error = unit(double_value(event.data, "error", 0.0));
    double novelty = unit(double_value(event.data, "novelty", 0.0));
    double salience = unit(double_value(event.data, "salience", 0.0));
    double uncertainty = unit(double_value(event.data, "uncertainty", error));
    double confidence = unit(double_value(event.data, "confidence", 1.0 - error));

    if (event.kind == "action_outcome" || event.kind == "learning") {
        const double reliability = unit(double_value(event.data, "reliability", confidence));
        outcome = 2.0 * reliability - 1.0;
        error = 1.0 - reliability;
        confidence = reliability;
    } else if (event.kind == "prediction_outcome") {
        outcome = 1.0 - 2.0 * error;
    } else if (event.kind == "goal_complete") {
        outcome = 1.0;
        salience = std::max(salience, 0.8);
    } else if (event.kind == "goal_progress") {
        const double delta = double_value(event.data, "delta", 0.0);
        outcome = signed_unit(delta);
        confidence = unit(double_value(event.data, "confidence", confidence));
    } else if (event.kind == "observation") {
        outcome = 0.0;
    }

    return {signed_unit(outcome), error, novelty, salience, uncertainty, confidence};
}

} // namespace

std::vector<Decision> Brain::choose_with_affect(const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);

    // Reconstruct affect from the same persistent experience journal used by
    // the rest of the brain. This makes the decision signal replayable rather
    // than depending on an opaque process-local emotion variable.
    AffectiveStateModel model;
    for (const auto& event : memory_.all()) {
        model.update(signal_from_event(event));
    }
    const auto affect = model.state();

    DecisionContext context;
    context.uncertainty = std::clamp(1.0 - state_.attention, 0.0, 1.0);
    context.threat = std::clamp(state_.threat, 0.0, 1.0);
    context.valence = affect.valence;
    context.arousal = affect.arousal;
    context.affective_uncertainty = affect.uncertainty;
    context.tension = affect.tension;
    context.stability = affect.stability;
    return decision_.decide(actions, context);
}

} // namespace jarvis::core
