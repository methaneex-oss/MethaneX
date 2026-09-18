#include "jarvis/core/evolution_strategy.hpp"
#include "jarvis/core/evolution_learning.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

std::vector<EvolutionCandidateScore> EvolutionStrategy::rank(
    const std::vector<EvolutionProposal>& proposals,
    const EvolutionHistory& history) {
    std::vector<EvolutionCandidateScore> ranked;
    ranked.reserve(proposals.size());

    for (const auto& proposal : proposals) {
        const auto records = history.for_parameter(proposal.key);
        std::size_t successes = 0;
        std::size_t failures = 0;
        for (const auto& record : records) {
            if (record.action == EvolutionRecordAction::Adopted &&
                record.outcome == ExperimentOutcome::Improved) ++successes;
            else if (record.action == EvolutionRecordAction::Rejected ||
                     record.action == EvolutionRecordAction::RolledBack ||
                     record.outcome == ExperimentOutcome::Degraded) ++failures;
        }

        const auto insight = EvolutionLearning::analyze_failures(proposal.key, history);
        const double prior = static_cast<double>(records.size());
        const double empirical_success = (static_cast<double>(successes) + 1.0) / (prior + 2.0);
        const double novelty = 1.0 / (1.0 + prior);
        const double confidence = std::clamp(proposal.confidence, 0.0, 1.0);
        const double score = confidence * 0.45 + empirical_success * 0.30 +
                             novelty * 0.15 + (1.0 - insight.caution) * 0.10;

        ranked.push_back(EvolutionCandidateScore{
            proposal.key, score, records.size(), successes, failures});
    }

    std::sort(ranked.begin(), ranked.end(), [](const auto& a, const auto& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.parameter_key < b.parameter_key;
    });
    return ranked;
}

} // namespace jarvis::core
