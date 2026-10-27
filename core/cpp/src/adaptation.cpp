#include "jarvis/core/adaptation.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace jarvis::core {

AdaptiveMetric AdaptationModel::observe(const std::string& key, double predicted, double actual) {
    if (!std::isfinite(predicted) || !std::isfinite(actual)) {
        const auto existing = metrics_.find(key);
        return existing == metrics_.end() ? AdaptiveMetric{} : existing->second;
    }
    auto& metric = metrics_[key];
    const double p = predicted;
    const double a = actual;
    const double scale = std::max({1.0, std::abs(p), std::abs(a)});
    const double error = std::clamp(std::abs(a - p) / scale, 0.0, 1.0);

    // The first actual observation establishes the variable's scale and level.
    // A generic prior such as 0.5 is suitable for bounded probabilities, but
    // biases physical quantities toward zero when reused for real-valued data.
    if (metric.observations == 0) {
        metric.estimate = a;
        metric.mean_error = error;
        metric.recent_error = error;
        metric.observations = 1;
        return metric;
    }

    ++metric.observations;

    // Keep both long-term experience and a recency-sensitive signal. A single
    // surprise is common in noisy environments, so it must not erase competence.
    // A sustained run of large errors is stronger evidence that the generating
    // process changed. This is generic change responsiveness, not a stimulus-to-
    // response rule: the evidence is the prediction error sequence itself.
    const bool surprising = error >= 0.75;
    if (surprising) {
        if (metric.consecutive_surprises < std::numeric_limits<std::uint32_t>::max())
            ++metric.consecutive_surprises;
    } else {
        metric.consecutive_surprises = 0;
    }

    const double rate = 1.0 / static_cast<double>(metric.observations);
    metric.mean_error += (error - metric.mean_error) * rate;
    const double recent_rate = std::clamp(
        0.35 / std::sqrt(static_cast<double>(metric.observations)), 0.05, 0.35);
    metric.recent_error += (error - metric.recent_error) * recent_rate;

    // Under ordinary experience, keep the conservative recency rate. Three
    // consecutive large surprises permit a modest acceleration; four or more
    // permit a stronger update. The streak resets as soon as the observations
    // stop being surprising, limiting overreaction to isolated noisy outcomes.
    double estimate_rate = recent_rate;
    if (metric.consecutive_surprises >= 4) {
        estimate_rate = std::max(estimate_rate, 0.30);
    } else if (metric.consecutive_surprises >= 3) {
        estimate_rate = std::max(estimate_rate, 0.15);
    }

    // Use a convex blend instead of (actual - estimate) * rate: subtracting
    // opposite-sign finite values near DBL_MAX can overflow before scaling.
    // The weighted terms stay within the representable range, and long double
    // preserves headroom on platforms where it has a wider exponent range.
    const long double weight = static_cast<long double>(estimate_rate);
    const long double blended_estimate =
        (1.0L - weight) * static_cast<long double>(metric.estimate) +
        weight * static_cast<long double>(a);
    const long double limit =
        static_cast<long double>(std::numeric_limits<double>::max());
    metric.estimate = static_cast<double>(
        std::clamp(blended_estimate, -limit, limit));

    metric.mean_error = std::clamp(metric.mean_error, 0.0, 1.0);
    metric.recent_error = std::clamp(metric.recent_error, 0.0, 1.0);
    if (!std::isfinite(metric.estimate)) metric.estimate = a;
    return metric;
}

const AdaptiveMetric* AdaptationModel::metric(const std::string& key) const noexcept {
    const auto it = metrics_.find(key);
    return it == metrics_.end() ? nullptr : &it->second;
}

double AdaptationModel::confidence(const std::string& key) const noexcept {
    const auto* value = metric(key);
    if (value == nullptr || value->observations == 0) return 0.0;
    const double experience = 1.0 - std::exp(-static_cast<double>(value->observations) / 8.0);
    const double stable_accuracy = 1.0 - value->mean_error;
    const double recent_accuracy = 1.0 - value->recent_error;
    const double accuracy = std::min(stable_accuracy, recent_accuracy);
    // A surprising first observation is still evidence. If confidence were
    // exactly zero whenever the first forecast is maximally wrong, numeric
    // calibration would never move toward the observed value and the model
    // could not learn from its own mistakes. Keep a small evidence-weighted
    // update floor while preserving lower confidence for inaccurate forecasts.
    const double evidence_weight = 0.25 + 0.75 * accuracy;
    return std::clamp(evidence_weight * experience, 0.0, 1.0);
}

} // namespace jarvis::core
