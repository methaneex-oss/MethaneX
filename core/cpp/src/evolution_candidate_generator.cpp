#include "jarvis/core/evolution_candidate_generator.hpp"

#include <cmath>
#include <unordered_set>

namespace jarvis::core {

std::vector<EvolutionProposal> EvolutionCandidateValidator::validate(
    const std::vector<EvolutionProposal>& proposals) noexcept {
    std::vector<EvolutionProposal> result;
    std::unordered_set<std::string> keys;
    result.reserve(proposals.size());

    for (const auto& proposal : proposals) {
        if (proposal.key.empty() || !std::isfinite(proposal.current) ||
            !std::isfinite(proposal.proposed) || !std::isfinite(proposal.expected_gain) ||
            !std::isfinite(proposal.confidence) || proposal.confidence < 0.0 ||
            proposal.confidence > 1.0) {
            continue;
        }
        if (!keys.insert(proposal.key).second) continue;
        result.push_back(proposal);
    }
    return result;
}

} // namespace jarvis::core
