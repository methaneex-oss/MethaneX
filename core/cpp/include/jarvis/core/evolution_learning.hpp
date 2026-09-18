#pragma once

#include "jarvis/core/evolution_history.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

struct EvolutionFailureInsight {
    std::string parameter_key;
    std::size_t failures{0};
    std::size_t rollbacks{0};
    double average_failed_gain{0.0};
    double caution{0.0};
};

class EvolutionLearning {
public:
    static EvolutionFailureInsight analyze_failures(const std::string& parameter_key,
                                                     const EvolutionHistory& history);
};

} // namespace jarvis::core
