#include "jarvis/core/affective_state.hpp"

namespace jarvis::core {
namespace {
AffectiveAppraisalWeights sanitize_weights(AffectiveAppraisalWeights w) noexcept {
    auto bounded=[](double v){ return std::clamp(std::isfinite(v) ? v : 0.0, 0.0, 2.0); };
    w.outcome_weight=bounded(w.outcome_weight); w.error_weight=bounded(w.error_weight);
    w.novelty_weight=bounded(w.novelty_weight); w.salience_weight=bounded(w.salience_weight);
    w.uncertainty_weight=bounded(w.uncertainty_weight); w.tension_error_weight=bounded(w.tension_error_weight);
    return w;
}
}

AffectiveState AffectiveStateModel::update(const AffectiveSignal& signal, double dt) noexcept {
    return update(signal, AffectiveAppraisalWeights{}, dt);
}

AffectiveState AffectiveStateModel::update(const AffectiveSignal& raw, const AffectiveAppraisalWeights& raw_weights, double dt) noexcept {
    dt = std::clamp(std::isfinite(dt) ? dt : 1.0, 0.0, 60.0);
    const auto w = sanitize_weights(raw_weights);
    const auto s = AffectiveSignal{
        clamp(raw.outcome),
        unit(raw.prediction_error),
        unit(raw.novelty),
        unit(raw.salience),
        unit(raw.uncertainty),
        unit(raw.confidence),
        unit(raw.tension_error)};
    const double integration = std::clamp(dt / (1.0 + dt), 0.0, 1.0);
    const double error_load = s.prediction_error * (0.5 + 0.5 * s.confidence);
    const double tension_error = s.tension_error > 0.0 ? s.tension_error : s.prediction_error;
    const double normalization = 0.25 + 0.75 * std::max({w.outcome_weight, w.error_weight, w.novelty_weight, w.salience_weight, w.uncertainty_weight, w.tension_error_weight});
    state_.valence = clamp(state_.valence + integration * ((w.outcome_weight * s.outcome - w.error_weight * error_load) / normalization));
    state_.arousal = unit(state_.arousal + integration * ((w.novelty_weight * s.novelty + w.salience_weight * s.salience + w.error_weight * s.prediction_error) / normalization - 0.15));
    state_.uncertainty = unit(0.65 * state_.uncertainty + integration * ((w.uncertainty_weight * s.uncertainty + w.error_weight * s.prediction_error) / normalization));
    state_.tension = unit(0.70 * state_.tension + integration * ((w.tension_error_weight * tension_error + 0.5 * w.uncertainty_weight * s.uncertainty + 0.25 * w.salience_weight * s.salience) / normalization));
    state_.stability = unit(1.0 - 0.55 * state_.uncertainty - 0.45 * state_.tension);
    ++state_.updates;
    return state_;
}

AffectiveState AffectiveStateModel::decay(double dt) noexcept {
    dt = std::clamp(std::isfinite(dt) ? dt : 1.0, 0.0, 60.0);
    const double retention = std::exp(-0.08 * dt);
    state_.valence = clamp(state_.valence * retention);
    state_.arousal = unit(state_.arousal * std::exp(-0.12 * dt));
    state_.uncertainty = unit(state_.uncertainty * std::exp(-0.06 * dt));
    state_.tension = unit(state_.tension * std::exp(-0.10 * dt));
    state_.stability = unit(1.0 - 0.55 * state_.uncertainty - 0.45 * state_.tension);
    return state_;
}

} // namespace jarvis::core
