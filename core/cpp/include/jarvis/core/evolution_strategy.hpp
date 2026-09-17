#pragma once

#include "jarvis/core/evolution_history.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

struct EvolutionCandidateScore {
    std::string parameter_key;
    double score{0.0};
    std::size_t prior_experiments{0};
    std::size_t prior_successes{0};
    std::size_t prior_failures{0};
};

class EvolutionStrategy {
public:
    static std::vector<EvolutionCandidateScore> rank(const std::vector<EvolutionProposal>& proposals,
                                                     const EvolutionHistory& history);
};

} // namespace jarvis::core
