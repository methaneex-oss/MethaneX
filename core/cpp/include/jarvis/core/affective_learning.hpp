#pragma once

#include "affective_state.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace jarvis::core {

struct AffectiveAppraisal {
    double outcome_weight{0.45};
    double error_weight{0.25};
    double novelty_weight{0.45};
    double salience_weight{0.35};
    double uncertainty_weight{0.60};
    double tension_error_weight{0.55};
};

class AffectiveLearningModel {
public:
    AffectiveAppraisal appraisal() const noexcept { return appraisal_; }

    AffectiveSignal modulate(const AffectiveSignal& raw) const noexcept {
        AffectiveSignal signal = raw;
        signal.outcome = clamp_signed(raw.outcome * ratio(appraisal_.outcome_weight, 0.45));
        signal.prediction_error = clamp_unit(raw.prediction_error * ratio(appraisal_.error_weight, 0.25));
        signal.novelty = clamp_unit(raw.novelty * ratio(appraisal_.novelty_weight, 0.45));
        signal.salience = clamp_unit(raw.salience * ratio(appraisal_.salience_weight, 0.35));
        signal.uncertainty = clamp_unit(raw.uncertainty * ratio(appraisal_.uncertainty_weight, 0.60));
        return signal;
    }

    void learn(const AffectiveSignal& signal, const AffectiveState& before,
               const AffectiveState& after, double observed_utility) noexcept {
        const double utility = clamp_signed(observed_utility);
        const double prediction = std::clamp(after.valence - before.valence, -1.0, 1.0);
        const double error = utility - prediction;
        const double rate = 0.05 + 0.10 * std::abs(error);
        const double relevance = 0.25 + 0.75 * std::clamp((signal.salience + signal.novelty) * 0.5, 0.0, 1.0);

        appraisal_.outcome_weight = adapt(appraisal_.outcome_weight, signal.outcome, utility, rate, relevance);
        appraisal_.error_weight = adapt(appraisal_.error_weight, signal.prediction_error, std::abs(error), rate, relevance);
        appraisal_.novelty_weight = adapt(appraisal_.novelty_weight, signal.novelty, std::abs(error), rate, relevance);
        appraisal_.salience_weight = adapt(appraisal_.salience_weight, signal.salience, std::abs(error), rate, relevance);
        appraisal_.uncertainty_weight = adapt(appraisal_.uncertainty_weight, signal.uncertainty, std::abs(error), rate, relevance);
        appraisal_.tension_error_weight = adapt(appraisal_.tension_error_weight, signal.prediction_error, std::abs(error), rate, relevance);
        ++updates_;
    }

    std::uint64_t updates() const noexcept { return updates_; }

private:
    static double clamp_unit(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0); }
    static double clamp_signed(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, -1.0, 1.0); }
    static double ratio(double value, double baseline) noexcept {
        if (!std::isfinite(value) || !std::isfinite(baseline) || baseline <= 0.0) return 1.0;
        return std::clamp(value / baseline, 0.25, 2.0);
    }
    static double adapt(double weight, double feature, double target, double rate, double relevance) noexcept {
        const double prediction = weight * std::clamp(feature, 0.0, 1.0);
        const double next = weight + rate * relevance * (target - prediction) * (0.5 + 0.5 * std::abs(feature));
        return std::clamp(std::isfinite(next) ? next : weight, 0.0, 2.0);
    }

    AffectiveAppraisal appraisal_{};
    std::uint64_t updates_{0};
};

} // namespace jarvis::core
