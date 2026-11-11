#include "jarvis/core/adaptation.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

AdaptiveMetric AdaptationModel::observe(const std::string& key, double predicted, double actual) {
    auto& metric = metrics_[key];
    if (!std::isfinite(predicted) || !std::isfinite(actual)) return metric;
    const double p = std::clamp(predicted, 0.0, 1.0);
    const double a = std::clamp(actual, 0.0, 1.0);
    const double error = std::abs(a - p);
    ++metric.observations;

    // Keep both long-term experience and a recency-sensitive signal. The former
    // prevents one surprising observation from erasing learned competence; the
    // latter lets JARVIS adapt quickly when the environment actually changes.
    const double rate = 1.0 / static_cast<double>(metric.observations);
    metric.mean_error += (error - metric.mean_error) * rate;
    const double recent_rate = std::clamp(
        0.35 / std::sqrt(static_cast<double>(metric.observations)), 0.05, 0.35);
    metric.recent_error += (error - metric.recent_error) * recent_rate;
    metric.estimate += (a - metric.estimate) * recent_rate;
    metric.mean_error = std::clamp(metric.mean_error, 0.0, 1.0);
    metric.recent_error = std::clamp(metric.recent_error, 0.0, 1.0);
    metric.estimate = std::clamp(metric.estimate, 0.0, 1.0);
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
    return std::clamp(accuracy * experience, 0.0, 1.0);
}

} // namespace jarvis::core
