#include "jarvis/core/affective_state.hpp"

namespace jarvis::core {

AffectiveState AffectiveStateModel::update(const AffectiveSignal& raw, double dt) noexcept {
    dt = std::clamp(std::isfinite(dt) ? dt : 1.0, 0.0, 60.0);
    const auto s = AffectiveSignal{
        clamp(raw.outcome), unit(raw.prediction_error), unit(raw.novelty),
        unit(raw.salience), unit(raw.uncertainty), unit(raw.confidence)};

    // Internal state is driven by continuous evidence. No named emotion or
    // fixed emotion-to-action mapping exists in this layer.
    const double integration = std::clamp(dt / (1.0 + dt), 0.0, 1.0);
    const double error_load = s.prediction_error * (0.5 + 0.5 * s.confidence);
    state_.valence = clamp(state_.valence + integration * (0.45 * s.outcome - 0.25 * error_load));
    state_.arousal = unit(state_.arousal + integration * (0.45 * s.novelty + 0.35 * s.salience + 0.20 * s.prediction_error - 0.15));
    state_.uncertainty = unit(0.65 * state_.uncertainty + integration * (0.60 * s.uncertainty + 0.40 * s.prediction_error));
    state_.tension = unit(0.70 * state_.tension + integration * (0.55 * s.prediction_error + 0.30 * s.uncertainty + 0.15 * s.salience));
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
