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

class EvolutionTrials {
public:
    static TrialStatistics summarize(const std::vector<double>& fitnesses) noexcept;
    static bool supports_adoption(const TrialStatistics& baseline,
                                  const TrialStatistics& candidate,
                                  double minimum_gain,
                                  double minimum_confidence) noexcept;
};

} // namespace jarvis::core
