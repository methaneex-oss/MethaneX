#include "jarvis/core/brain.hpp"

#include <algorithm>

namespace jarvis::core {

std::vector<ConceptCandidate> Brain::contextual_concepts(
    const std::string& key,
    double minimum_strength,
    std::size_t minimum_shared_contexts) const {
    std::shared_lock lock(mutex_);
    if (key.empty()) return {};

    const auto candidates = association_.concept_candidates(
        std::clamp(minimum_strength, 0.0, 1.0), minimum_shared_contexts);

    std::vector<ConceptCandidate> relevant;
    relevant.reserve(candidates.size());
    for (const auto& candidate : candidates) {
        if (std::find(candidate.members.begin(), candidate.members.end(), key) != candidate.members.end()) {
            relevant.push_back(candidate);
        }
    }
    return relevant;
}

std::vector<ConceptMatch> Brain::generalized_concepts(
    const std::string& key,
    double minimum_strength,
    std::size_t minimum_shared_contexts,
    double minimum_similarity) const {
    std::shared_lock lock(mutex_);
    if (key.empty()) return {};
    return association_.generalized_concepts(
        key,
        std::clamp(minimum_strength, 0.0, 1.0),
        minimum_shared_contexts,
        std::clamp(minimum_similarity, 0.0, 1.0));
}

} // namespace jarvis::core
