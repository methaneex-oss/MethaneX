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
};

struct TrialComparison {
    double mean_difference{0.0};
    double standard_error{0.0};
    double effect_size{0.0};
    double confidence_level{0.0};
    double confidence_interval_low{0.0};
    double confidence_interval_high{0.0};
    bool valid{false};
};

class EvolutionTrials {
public:
    static TrialStatistics summarize(const std::vector<double>& fitnesses) noexcept;

    static TrialComparison compare(const TrialStatistics& baseline,
                                   const TrialStatistics& candidate,
                                   double confidence_level) noexcept;

    static bool supports_adoption(const TrialStatistics& baseline,
                                  const TrialStatistics& candidate,
                                  double minimum_gain,
                                  double minimum_confidence) noexcept;
};

} // namespace jarvis::core
