#pragma once

#include "jarvis/core/evolution.hpp"
#include "jarvis/core/evolution_opportunity.hpp"

#include <functional>
#include <vector>

namespace jarvis::core {

using EvolutionCandidateGenerator =
    std::function<std::vector<EvolutionProposal>(const EvolutionOpportunity&)>;

class EvolutionCandidateValidator {
public:
    static std::vector<EvolutionProposal> validate(
        const std::vector<EvolutionProposal>& proposals) noexcept;
};

} // namespace jarvis::core
