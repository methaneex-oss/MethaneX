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
    const double rate = 1.0 / static_cast<double>(metric.observations);
    metric.mean_error += (error - metric.mean_error) * rate;
    metric.estimate += (a - metric.estimate) * rate;
    metric.mean_error = std::clamp(metric.mean_error, 0.0, 1.0);
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
    return std::clamp((1.0 - value->mean_error) * experience, 0.0, 1.0);
}

} // namespace jarvis::core
