#include "jarvis/core/evolution_trials.hpp"

#include <array>
#include <cmath>
#include <limits>

namespace jarvis::core {
namespace {

constexpr double kDefaultConfidence = 0.95;

double normal_quantile(double confidence) noexcept {
    const double p = (1.0 + confidence) * 0.5;
    if (!(p > 0.5 && p < 1.0)) return std::numeric_limits<double>::infinity();
    const double t = std::sqrt(-2.0 * std::log(1.0 - p));
    const double c0 = 2.515517;
    const double c1 = 0.802853;
    const double c2 = 0.010328;
    const double d1 = 1.432788;
    const double d2 = 0.189269;
    const double d3 = 0.001308;
    return t - (c0 + c1 * t + c2 * t * t) /
        (1.0 + d1 * t + d2 * t * t + d3 * t * t * t);
}

double student_t_critical(double confidence, double degrees_of_freedom) noexcept {
    if (!std::isfinite(confidence) || confidence <= 0.0 || confidence >= 1.0 ||
        !std::isfinite(degrees_of_freedom) || degrees_of_freedom <= 0.0) {
        return std::numeric_limits<double>::infinity();
    }

    // Exact two-sided 95% Student-t critical values for df 1..30.
    constexpr std::array<double, 30> t95{
        12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365, 2.306, 2.262, 2.228,
        2.201, 2.179, 2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 2.093, 2.086,
        2.080, 2.074, 2.069, 2.064, 2.060, 2.056, 2.052, 2.048, 2.045, 2.042
    };
    if (std::abs(confidence - kDefaultConfidence) < 1e-12) {
        if (degrees_of_freedom <= 30.0) {
            const auto index = static_cast<std::size_t>(std::ceil(degrees_of_freedom));
            return t95[index == 0 ? 0 : index - 1];
        }
        return 1.959964;
    }

    // Non-95% levels use a documented normal approximation rather than
    // pretending that an exact Student-t quantile is available here.
    return normal_quantile(confidence);
}

bool valid_statistics(const TrialStatistics& s) noexcept {
    return s.count >= 2 && std::isfinite(s.mean) && std::isfinite(s.variance) &&
           s.variance >= 0.0 && std::isfinite(s.standard_error) &&
           s.standard_error >= 0.0;
}

} // namespace

TrialStatistics EvolutionTrials::summarize(const std::vector<double>& values) noexcept {
    TrialStatistics result;
    if (values.empty()) return result;

    double mean = 0.0;
    double m2 = 0.0;
    std::size_t n = 0;
    for (const double value : values) {
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

    if (n < 2 || !std::isfinite(result.standard_error)) return result;

    const double critical = student_t_critical(kDefaultConfidence, static_cast<double>(n - 1));
    const double margin = critical * result.standard_error;
    if (!std::isfinite(margin)) return {};
    result.confidence = kDefaultConfidence;
    result.confidence_interval_low = result.mean - margin;
    result.confidence_interval_high = result.mean + margin;
    return result;
}

double EvolutionTrials::welch_degrees_of_freedom(
    const TrialStatistics& baseline,
    const TrialStatistics& candidate) noexcept {
    if (!valid_statistics(baseline) || !valid_statistics(candidate)) return 0.0;
    const double a = baseline.variance / static_cast<double>(baseline.count);
    const double b = candidate.variance / static_cast<double>(candidate.count);
    const double numerator = (a + b) * (a + b);
    const double denominator =
        (a * a) / static_cast<double>(baseline.count - 1) +
        (b * b) / static_cast<double>(candidate.count - 1);
    if (denominator == 0.0) return std::numeric_limits<double>::infinity();
    return numerator / denominator;
}

double EvolutionTrials::difference_confidence_interval_low(
    const TrialStatistics& baseline,
    const TrialStatistics& candidate,
    double confidence_level) noexcept {
    if (!valid_statistics(baseline) || !valid_statistics(candidate) ||
        !std::isfinite(confidence_level) || confidence_level <= 0.0 ||
        confidence_level >= 1.0) return std::numeric_limits<double>::quiet_NaN();

    const double standard_error = std::sqrt(
        baseline.variance / static_cast<double>(baseline.count) +
        candidate.variance / static_cast<double>(candidate.count));
    const double df = welch_degrees_of_freedom(baseline, candidate);
    const double critical = student_t_critical(confidence_level, df);
    if (!std::isfinite(standard_error) || !std::isfinite(critical)) {
        // Zero-variance samples have an exact zero-width difference interval.
        if (standard_error == 0.0) return candidate.mean - baseline.mean;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return (candidate.mean - baseline.mean) - critical * standard_error;
}

double EvolutionTrials::difference_confidence_interval_high(
    const TrialStatistics& baseline,
    const TrialStatistics& candidate,
    double confidence_level) noexcept {
    if (!valid_statistics(baseline) || !valid_statistics(candidate) ||
        !std::isfinite(confidence_level) || confidence_level <= 0.0 ||
        confidence_level >= 1.0) return std::numeric_limits<double>::quiet_NaN();

    const double standard_error = std::sqrt(
        baseline.variance / static_cast<double>(baseline.count) +
        candidate.variance / static_cast<double>(candidate.count));
    const double df = welch_degrees_of_freedom(baseline, candidate);
    const double critical = student_t_critical(confidence_level, df);
    if (!std::isfinite(standard_error) || !std::isfinite(critical)) {
        if (standard_error == 0.0) return candidate.mean - baseline.mean;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return (candidate.mean - baseline.mean) + critical * standard_error;
}

bool EvolutionTrials::supports_adoption(const TrialStatistics& baseline,
                                         const TrialStatistics& candidate,
                                         double minimum_gain,
                                         double minimum_confidence) noexcept {
    if (!valid_statistics(baseline) || !valid_statistics(candidate) ||
        !std::isfinite(minimum_gain) || minimum_gain < 0.0 ||
        !std::isfinite(minimum_confidence) || minimum_confidence <= 0.0 ||
        minimum_confidence >= 1.0) return false;

    const double lower = difference_confidence_interval_low(
        baseline, candidate, minimum_confidence);
    return std::isfinite(lower) && lower > minimum_gain;
}

} // namespace jarvis::core
