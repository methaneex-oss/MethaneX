#pragma once

#include <cstddef>
#include <vector>

namespace jarvis::core {

struct TrialStatistics {
    std::size_t count{0};
    double mean{0.0};
    double variance{0.0};
    double standard_error{0.0};
    double confidence{0.0};
    double confidence_interval_low{0.0};
    double confidence_interval_high{0.0};
};

class EvolutionTrials {
public:
    // Summarizes a sample using unbiased sample variance and a two-sided
    // 95% Student-t confidence interval when at least two observations exist.
    static TrialStatistics summarize(const std::vector<double>& fitnesses) noexcept;

    // Baseline/candidate samples are treated as independent. Adoption requires
    // the requested-confidence lower bound of the mean difference to exceed
    // the minimum practical gain.
    static bool supports_adoption(const TrialStatistics& baseline,
                                  const TrialStatistics& candidate,
                                  double minimum_gain,
                                  double minimum_confidence) noexcept;

    static double difference_confidence_interval_low(const TrialStatistics& baseline,
                                                     const TrialStatistics& candidate,
                                                     double confidence_level) noexcept;

    static double difference_confidence_interval_high(const TrialStatistics& baseline,
                                                      const TrialStatistics& candidate,
                                                      double confidence_level) noexcept;

    static double welch_degrees_of_freedom(const TrialStatistics& baseline,
                                            const TrialStatistics& candidate) noexcept;
};

} // namespace jarvis::core
