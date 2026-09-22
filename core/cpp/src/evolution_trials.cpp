#include "jarvis/core/evolution_trials.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace jarvis::core {
namespace {

double critical_value(double confidence_level) noexcept {
    if (confidence_level == 0.80) return 1.2815515655446004;
    if (confidence_level == 0.90) return 1.6448536269514722;
    if (confidence_level == 0.95) return 1.959963984540054;
    if (confidence_level == 0.98) return 2.3263478740408408;
    if (confidence_level == 0.99) return 2.5758293035489004;
    return std::numeric_limits<double>::quiet_NaN();
}

bool valid_confidence(double value) noexcept {
    return value == 0.80 || value == 0.90 || value == 0.95 ||
           value == 0.98 || value == 0.99;
}

} // namespace

TrialStatistics EvolutionTrials::summarize(const std::vector<double>& values) noexcept {
    TrialStatistics result;
    if (values.empty()) return result;

    double mean = 0.0;
    double m2 = 0.0;
    std::size_t n = 0;
    for (double value : values) {
        if (!std::isfinite(value)) return {};
        ++n;
        const double delta = value - mean;
        mean += delta / static_cast<double>(n);
        const double delta2 = value - mean;
        m2 += delta * delta2;
    }

    result.count = n;
    result.mean = mean;
    result.variance = n > 1 ? m2 / static_cast<double>(n - 1) : 0.0;
    result.standard_error = n > 1
        ? std::sqrt(result.variance / static_cast<double>(n))
        : std::numeric_limits<double>::infinity();
    result.confidence = 0.0;
    return result;
}

TrialComparison EvolutionTrials::compare(const TrialStatistics& baseline,
                                          const TrialStatistics& candidate,
                                          double confidence_level) noexcept {
    TrialComparison result;
    if (baseline.count < 2 || candidate.count < 2 ||
        !valid_confidence(confidence_level) ||
        !std::isfinite(baseline.mean) || !std::isfinite(candidate.mean) ||
        !std::isfinite(baseline.variance) || !std::isfinite(candidate.variance)) {
        return result;
    }

    const double se2 = baseline.variance / static_cast<double>(baseline.count) +
                       candidate.variance / static_cast<double>(candidate.count);
    if (!std::isfinite(se2) || se2 <= 0.0) {
        if (candidate.mean == baseline.mean) {
            result.valid = true;
            result.confidence_level = confidence_level;
            result.mean_difference = 0.0;
            result.confidence_interval_low = 0.0;
            result.confidence_interval_high = 0.0;
        }
        return result;
    }

    result.mean_difference = candidate.mean - baseline.mean;
    result.standard_error = std::sqrt(se2);
    const double pooled_variance =
        ((static_cast<double>(baseline.count - 1) * baseline.variance) +
         (static_cast<double>(candidate.count - 1) * candidate.variance)) /
        static_cast<double>(baseline.count + candidate.count - 2);
    result.effect_size = pooled_variance > 0.0
        ? result.mean_difference / std::sqrt(pooled_variance)
        : 0.0;

    const double z = result.mean_difference / result.standard_error;
    const double critical = critical_value(confidence_level);
    result.confidence_level = confidence_level;
    result.confidence_interval_low = result.mean_difference - critical * result.standard_error;
    result.confidence_interval_high = result.mean_difference + critical * result.standard_error;
    result.valid = std::isfinite(z) && std::isfinite(result.confidence_interval_low) &&
                   std::isfinite(result.confidence_interval_high);
    return result;
}

bool EvolutionTrials::supports_adoption(const TrialStatistics& baseline,
                                         const TrialStatistics& candidate,
                                         double minimum_gain,
                                         double minimum_confidence) noexcept {
    if (!std::isfinite(minimum_gain) || minimum_gain < 0.0 ||
        !valid_confidence(minimum_confidence)) return false;

    const auto comparison = compare(baseline, candidate, minimum_confidence);
    return comparison.valid &&
           comparison.confidence_interval_low > minimum_gain;
}

} // namespace jarvis::core
