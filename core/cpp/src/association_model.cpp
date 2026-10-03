#include "jarvis/core/association_model.hpp"

#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>
#include <utility>

namespace jarvis::core {
namespace {

std::string other_endpoint(const Association& association, const std::string& key) {
    return association.left == key ? association.right : association.left;
}

} // namespace

void AssociationModel::observe(const std::vector<Belief>& before,
                               const std::vector<Belief>& after,
                               std::uint64_t sequence) {
    // Existing implementation retained; association updates remain experience
    // driven and are keyed by observed state transitions.
    for (const auto& lhs : before) {
        const auto rhs_it = std::find_if(after.begin(), after.end(), [&](const Belief& rhs) { return rhs.key != lhs.key; });
        if (rhs_it == after.end()) continue;
        auto& association = upsert(lhs.key, rhs_it->key);
        const bool lhs_changed = std::find_if(after.begin(), after.end(), [&](const Belief& value) { return value.key == lhs.key && value.value != lhs.value; }) != after.end();
        const bool rhs_changed = rhs_it->value != lhs.value;
        ++association.observations;
        association.updated_sequence = sequence;
        if (lhs_changed || rhs_changed) association.strength = std::clamp(association.strength + 0.05, 0.0, 1.0);
        association.confidence = std::clamp(association.confidence + 0.02, 0.0, 1.0);
    }
}

std::vector<Association> AssociationModel::all() const { return associations_; }
std::vector<Association> AssociationModel::related(const std::string& key, double minimum_strength) const {
    const double threshold = std::clamp(minimum_strength, 0.0, 1.0);
    std::vector<Association> result;
    for (const auto& association : associations_) if ((association.left == key || association.right == key) && association.strength >= threshold) result.push_back(association);
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) { return a.strength > b.strength; });
    return result;
}

std::vector<AssociationInference> AssociationModel::contextual(const std::string& key,
                                                                std::size_t max_hops,
                                                                double minimum_strength) const {
    std::vector<AssociationInference> result;
    if (key.empty() || max_hops == 0 || associations_.empty()) return result;
    const double threshold = std::clamp(minimum_strength, 0.0, 1.0);
    std::unordered_map<std::string, double> best_strength;
    std::unordered_map<std::string, std::size_t> best_hops;
    std::vector<std::pair<std::string, double>> frontier{{key, 1.0}};
    for (std::size_t hop = 1; hop <= max_hops && !frontier.empty(); ++hop) {
        std::vector<std::pair<std::string, double>> next;
        for (const auto& [current, path_strength] : frontier) {
            for (const auto& association : associations_) {
                if (association.left != current && association.right != current) continue;
                const auto neighbor = other_endpoint(association, current);
                if (neighbor == key) continue;
                // A modest path-length discount prevents arbitrary multi-hop
                // amplification while retaining useful second-order context.
                const double hop_decay = std::pow(0.95, static_cast<double>(hop - 1));
                const double candidate = path_strength *
                    std::clamp(association.strength, 0.0, 1.0) * hop_decay;
                if (candidate < threshold) continue;
                const auto it = best_strength.find(neighbor);
                if (it == best_strength.end() || candidate > it->second) {
                    best_strength[neighbor] = candidate;
                    best_hops[neighbor] = hop;
                    next.emplace_back(neighbor, candidate);
                }
            }
        }
        frontier = std::move(next);
    }
    result.reserve(best_strength.size());
    for (const auto& [neighbor, strength] : best_strength)
        result.push_back(AssociationInference{neighbor, strength, best_hops[neighbor]});
    std::sort(result.begin(), result.end(), [](const AssociationInference& lhs, const AssociationInference& rhs) {
        if (lhs.strength != rhs.strength) return lhs.strength > rhs.strength;
        if (lhs.hops != rhs.hops) return lhs.hops < rhs.hops;
        return lhs.key < rhs.key;
    });
    return result;
}

std::vector<ConceptCandidate> AssociationModel::concept_candidates(double minimum_strength, std::size_t minimum_shared_contexts) const {
    std::vector<ConceptCandidate> result;
    if (associations_.empty() || minimum_shared_contexts == 0) return result;
    const double threshold = std::clamp(minimum_strength, 0.0, 1.0);
    std::unordered_map<std::string, std::set<std::string>> neighbors;
    std::unordered_map<std::string, std::uint64_t> observations;
    std::unordered_map<std::string, std::uint64_t> contradictions;
    for (const auto& association : associations_) {
        if (association.strength < threshold) continue;
        neighbors[association.left].insert(association.right);
        neighbors[association.right].insert(association.left);
        observations[association.left] += association.observations;
        observations[association.right] += association.observations;
        contradictions[association.left] += association.contradictory_observations;
        contradictions[association.right] += association.contradictory_observations;
    }
    std::vector<std::string> nodes;
    nodes.reserve(neighbors.size());
    for (const auto& [node, _] : neighbors) nodes.push_back(node);
    std::sort(nodes.begin(), nodes.end());
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        for (std::size_t j = i + 1; j < nodes.size(); ++j) {
            const auto& lhs = neighbors[nodes[i]];
            const auto& rhs = neighbors[nodes[j]];
            std::size_t shared = 0;
            for (const auto& neighbor : lhs) if (rhs.count(neighbor) != 0) ++shared;
            if (shared < minimum_shared_contexts) continue;
            const double coherence = static_cast<double>(shared) / static_cast<double>(std::max<std::size_t>(1, std::min(lhs.size(), rhs.size())));
            result.push_back(ConceptCandidate{{nodes[i], nodes[j]}, coherence, observations[nodes[i]] + observations[nodes[j]], contradictions[nodes[i]] + contradictions[nodes[j]]});
        }
    }
    std::sort(result.begin(), result.end(), [](const ConceptCandidate& lhs, const ConceptCandidate& rhs) {
        if (lhs.coherence != rhs.coherence) return lhs.coherence > rhs.coherence;
        if (lhs.supporting_observations != rhs.supporting_observations) return lhs.supporting_observations > rhs.supporting_observations;
        return lhs.members < rhs.members;
    });
    return result;
}

std::vector<ConceptMatch> AssociationModel::generalized_concepts(const std::string& key, double minimum_strength,
                                                                 std::size_t minimum_shared_contexts, double minimum_similarity) const {
    std::vector<ConceptMatch> result;
    if (key.empty() || minimum_shared_contexts == 0) return result;
    const double threshold = std::clamp(minimum_strength, 0.0, 1.0);
    const double similarity_threshold = std::clamp(minimum_similarity, 0.0, 1.0);
    std::set<std::string> key_contexts;
    for (const auto& association : associations_) {
        if (association.strength < threshold) continue;
        if (association.left == key) key_contexts.insert(association.right);
        else if (association.right == key) key_contexts.insert(association.left);
    }
    if (key_contexts.size() < minimum_shared_contexts) return result;
    const auto candidates = concept_candidates(threshold, minimum_shared_contexts);
    for (const auto& candidate : candidates) {
        std::set<std::string> concept_contexts;
        for (const auto& member : candidate.members) {
            for (const auto& association : associations_) {
                if (association.strength < threshold) continue;
                if (association.left == member && std::find(candidate.members.begin(), candidate.members.end(), association.right) == candidate.members.end()) concept_contexts.insert(association.right);
                else if (association.right == member && std::find(candidate.members.begin(), candidate.members.end(), association.left) == candidate.members.end()) concept_contexts.insert(association.left);
            }
        }
        std::size_t shared = 0;
        for (const auto& context : key_contexts) if (concept_contexts.count(context) != 0) ++shared;
        const double similarity = static_cast<double>(shared) / static_cast<double>(std::max<std::size_t>(1, std::max(key_contexts.size(), concept_contexts.size())));
        if (shared >= minimum_shared_contexts && similarity >= similarity_threshold) result.push_back(ConceptMatch{candidate.members, similarity, std::vector<std::string>(key_contexts.begin(), key_contexts.end())});
    }
    return result;
}

Association& AssociationModel::upsert(const std::string& left, const std::string& right) {
    auto ordered_left = left;
    auto ordered_right = right;
    if (ordered_right < ordered_left) std::swap(ordered_left, ordered_right);
    for (auto& association : associations_) if (association.left == ordered_left && association.right == ordered_right) return association;
    associations_.push_back(Association{ordered_left, ordered_right, 0.5, 0.5, 0, 0, 0});
    return associations_.back();
}

void AssociationModel::apply_prediction_feedback(const std::vector<std::string>& members, bool correct, double evidence_strength, std::uint64_t sequence) {
    if (members.size() < 2) return;
    const double evidence = std::clamp(evidence_strength, 0.0, 1.0);
    for (std::size_t i = 0; i < members.size(); ++i) for (std::size_t j = i + 1; j < members.size(); ++j) {
        auto& association = upsert(members[i], members[j]);
        ++association.observations;
        association.updated_sequence = sequence;
        if (correct) association.strength = std::clamp(association.strength + 0.08 * evidence, 0.0, 1.0);
        else { ++association.contradictory_observations; association.strength = std::clamp(association.strength * (1.0 - 0.08 * evidence), 0.0, 1.0); }
        association.confidence = std::clamp(association.confidence + (correct ? 0.04 : -0.04) * evidence, 0.0, 1.0);
    }
}

} // namespace jarvis::core
