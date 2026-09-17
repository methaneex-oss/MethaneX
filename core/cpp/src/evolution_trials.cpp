#include "jarvis/core/evolution_trials.hpp"

#include <cmath>
#include <limits>

namespace jarvis::core {

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
    result.standard_error = n > 1 ? std::sqrt(result.variance / static_cast<double>(n)) :
                                    std::numeric_limits<double>::infinity();
    result.confidence = n > 1 && std::isfinite(result.standard_error)
        ? std::clamp(1.0 / (1.0 + result.standard_error), 0.0, 1.0)
        : 0.0;
    return result;
}

bool EvolutionTrials::supports_adoption(const TrialStatistics& baseline,
                                         const TrialStatistics& candidate,
                                         double minimum_gain,
                                         double minimum_confidence) noexcept {
    if (baseline.count < 2 || candidate.count < 2 || !std::isfinite(minimum_gain) ||
        minimum_gain < 0.0 || !std::isfinite(minimum_confidence) ||
        minimum_confidence < 0.0 || minimum_confidence > 1.0) return false;

    const double gain = candidate.mean - baseline.mean;
    const double combined_confidence = std::min(baseline.confidence, candidate.confidence);
    return std::isfinite(gain) && gain > minimum_gain && combined_confidence >= minimum_confidence;
}

} // namespace jarvis::core
