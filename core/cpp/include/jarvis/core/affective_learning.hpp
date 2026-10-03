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

// Outcome evidence separates what was expected from what actually happened.
// The learner uses consequence error to adapt appraisal sensitivity; it does
// not encode semantic emotion rules.
struct AffectiveOutcomeEvidence {
    double expected_consequence{0.0};
    double actual_consequence{0.0};
    double consequence_error{0.0};
    double utility{0.0};
    double prediction_error{0.0};
    double novelty{0.0};
    double salience{0.0};
    double uncertainty{0.0};
    double confidence{0.5};
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
        signal.tension_error = clamp_unit(raw.prediction_error * ratio(appraisal_.tension_error_weight, 0.55));
        return signal;
    }

    void learn(const AffectiveOutcomeEvidence& evidence) noexcept {
        const double expected = clamp_signed(evidence.expected_consequence);
        const double actual = clamp_signed(evidence.actual_consequence);
        const double consequence_error = clamp_signed(
            std::isfinite(evidence.consequence_error)
                ? evidence.consequence_error
                : actual - expected);
        const double utility = clamp_signed(evidence.utility);
        const double magnitude = std::abs(consequence_error);
        const double rate = 0.03 + 0.12 * magnitude;
        const double relevance = 0.25 + 0.75 * std::clamp(
            0.35 * clamp_unit(evidence.salience) +
            0.25 * clamp_unit(evidence.novelty) +
            0.20 * clamp_unit(evidence.confidence) +
            0.20 * clamp_unit(evidence.uncertainty), 0.0, 1.0);

        appraisal_.outcome_weight = adapt_sensitivity(appraisal_.outcome_weight, std::abs(expected), std::abs(utility), rate, relevance);
        appraisal_.error_weight = adapt_sensitivity(appraisal_.error_weight, clamp_unit(evidence.prediction_error), magnitude, rate, relevance);
        appraisal_.novelty_weight = adapt_sensitivity(appraisal_.novelty_weight, clamp_unit(evidence.novelty), magnitude, rate, relevance);
        appraisal_.salience_weight = adapt_sensitivity(appraisal_.salience_weight, clamp_unit(evidence.salience), magnitude, rate, relevance);
        appraisal_.uncertainty_weight = adapt_sensitivity(appraisal_.uncertainty_weight, clamp_unit(evidence.uncertainty), magnitude, rate, relevance);
        appraisal_.tension_error_weight = adapt_sensitivity(appraisal_.tension_error_weight, clamp_unit(evidence.prediction_error), magnitude, rate, relevance);
        ++updates_;
    }

    // Compatibility adapter for callers that have not yet persisted explicit
    // expected/actual consequence fields. The adapter reconstructs an expected
    // consequence from the observed consequence and prediction-error magnitude;
    // it no longer derives the expectation from the affective state transition.
    void learn(const AffectiveSignal& signal, const AffectiveState& /*before*/,
               const AffectiveState& /*after*/, double observed_utility) noexcept {
        const double actual = clamp_signed(observed_utility);
        const double signed_error = std::copysign(clamp_unit(signal.prediction_error),
                                                   actual == 0.0 ? 1.0 : actual);
        const double expected = clamp_signed(actual - signed_error);
        learn(AffectiveOutcomeEvidence{
            expected,
            actual,
            clamp_signed(actual - expected),
            actual,
            signal.prediction_error,
            signal.novelty,
            signal.salience,
            signal.uncertainty,
            signal.confidence});
    }

    std::uint64_t updates() const noexcept { return updates_; }

private:
    static double clamp_unit(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0); }
    static double clamp_signed(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, -1.0, 1.0); }
    static double ratio(double value, double baseline) noexcept {
        if (!std::isfinite(value) || !std::isfinite(baseline) || baseline <= 0.0) return 1.0;
        return std::clamp(value / baseline, 0.25, 2.0);
    }
    static double adapt_sensitivity(double weight, double feature, double target,
                                    double rate, double relevance) noexcept {
        feature = clamp_unit(feature);
        target = clamp_unit(target);
        const double prediction = std::clamp(weight, 0.0, 2.0) * feature;
        const double error = target - prediction;
        const double next = weight + rate * relevance * error * feature;
        return std::clamp(std::isfinite(next) ? next : weight, 0.0, 2.0);
    }

    AffectiveAppraisal appraisal_{};
    std::uint64_t updates_{0};
};

} // namespace jarvis::core
