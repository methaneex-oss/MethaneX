#include "jarvis/core/association_model.hpp"

#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace jarvis::core {
namespace {

bool same_pair(const Association& association, const std::string& left, const std::string& right) {
    return (association.left == left && association.right == right) ||
           (association.left == right && association.right == left);
}

bool changed(const std::vector<Belief>& before, const Belief& current) {
    const auto prior = std::find_if(before.begin(), before.end(), [&](const Belief& belief) {
        return belief.key == current.key;
    });
    return prior != before.end() && prior->value != current.value;
}

std::string other_endpoint(const Association& association, const std::string& key) {
    return association.left == key ? association.right : association.left;
}

}

void AssociationModel::observe(const std::vector<Belief>& before,
                               const std::vector<Belief>& after,
                               std::uint64_t sequence,
                               double observation_reliability) {
    const double transition_reliability = std::clamp(observation_reliability, 0.0, 1.0);
    std::set<std::string> changed_keys;
    std::set<std::string> present_keys;
    for (const auto& current : after) {
        present_keys.insert(current.key);
        if (changed(before, current)) changed_keys.insert(current.key);
    }

    for (auto& association : associations_) {
        if (present_keys.count(association.left) == 0 ||
            present_keys.count(association.right) == 0) continue;
        const bool left_changed = changed_keys.count(association.left) != 0;
        const bool right_changed = changed_keys.count(association.right) != 0;
        if (left_changed == right_changed) continue;
        ++association.contradictory_observations;
        association.strength = std::clamp(association.strength * 0.85, 0.0, 1.0);
        association.confidence = std::clamp(association.confidence * 0.90, 0.0, 1.0);
        association.last_sequence = sequence;
    }

    std::vector<const Belief*> changed_beliefs;
    changed_beliefs.reserve(after.size());
    for (const auto& current : after)
        if (changed(before, current)) changed_beliefs.push_back(&current);

    for (std::size_t i = 0; i < changed_beliefs.size(); ++i) {
        const auto& current = *changed_beliefs[i];
        for (std::size_t j = i + 1; j < changed_beliefs.size(); ++j) {
            const auto& other = *changed_beliefs[j];
            const auto pair = std::minmax(current.key, other.key);
            const double evidence = transition_reliability;
            auto it = std::find_if(associations_.begin(), associations_.end(), [&](const Association& item) {
                return same_pair(item, current.key, other.key);
            });
            if (it == associations_.end()) {
                associations_.push_back(
                    Association{pair.first, pair.second, evidence, evidence, 1, sequence, 0});
                continue;
            }
            it->strength = std::clamp(it->strength + (evidence - it->strength) * 0.15, 0.0, 1.0);
            it->confidence = std::clamp(it->confidence + (evidence - it->confidence) * 0.10, 0.0, 1.0);
            ++it->observations;
            it->last_sequence = sequence;
        }
    }
}

std::vector<Association> AssociationModel::all() const { return associations_; }

std::vector<Association> AssociationModel::related(const std::string& key, double minimum_strength) const {
    std::vector<Association> result;
    const double threshold = std::clamp(minimum_strength, 0.0, 1.0);
    for (const auto& association : associations_) {
        if (association.strength < threshold) continue;
        if (association.left == key || association.right == key) result.push_back(association);
    }
    std::sort(result.begin(), result.end(), [](const Association& lhs, const Association& rhs) {
        if (lhs.strength != rhs.strength) return lhs.strength > rhs.strength;
        return lhs.observations > rhs.observations;
    });
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
                const double candidate = path_strength * std::clamp(association.strength, 0.0, 1.0);
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

std::vector<ConceptCandidate> AssociationModel::concept_candidates(
    double minimum_strength, std::size_t minimum_shared_contexts) const {
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
            const double coherence = static_cast<double>(shared) /
                static_cast<double>(std::max<std::size_t>(1, std::min(lhs.size(), rhs.size())));
            result.push_back(ConceptCandidate{{nodes[i], nodes[j]}, coherence,
                                              observations[nodes[i]] + observations[nodes[j]],
                                              contradictions[nodes[i]] + contradictions[nodes[j]]});
        }
    }
    std::sort(result.begin(), result.end(), [](const ConceptCandidate& lhs, const ConceptCandidate& rhs) {
        if (lhs.coherence != rhs.coherence) return lhs.coherence > rhs.coherence;
        if (lhs.supporting_observations != rhs.supporting_observations)
            return lhs.supporting_observations > rhs.supporting_observations;
        return lhs.members < rhs.members;
    });
    return result;
}


std::vector<ConceptMatch> AssociationModel::generalized_concepts(
    const std::string& key, double minimum_strength,
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
                if (association.left == member && std::find(candidate.members.begin(), candidate.members.end(), association.right) == candidate.members.end())
                    concept_contexts.insert(association.right);
                else if (association.right == member && std::find(candidate.members.begin(), candidate.members.end(), association.left) == candidate.members.end())
                    concept_contexts.insert(association.left);
            }
        }
        std::vector<std::string> matched;
        std::set_intersection(key_contexts.begin(), key_contexts.end(),
                              concept_contexts.begin(), concept_contexts.end(),
                              std::back_inserter(matched));
        if (matched.size() < minimum_shared_contexts) continue;
        const std::size_t union_size = key_contexts.size() + concept_contexts.size() - matched.size();
        const double similarity = static_cast<double>(matched.size()) /
            static_cast<double>(std::max<std::size_t>(1, union_size));
        if (similarity < similarity_threshold) continue;
        result.push_back(ConceptMatch{candidate.members, std::move(matched), similarity,
                                      std::clamp(candidate.coherence * similarity, 0.0, 1.0)});
    }
    std::sort(result.begin(), result.end(), [](const ConceptMatch& lhs, const ConceptMatch& rhs) {
        if (lhs.similarity != rhs.similarity) return lhs.similarity > rhs.similarity;
        if (lhs.evidence_strength != rhs.evidence_strength) return lhs.evidence_strength > rhs.evidence_strength;
        return lhs.concept_members < rhs.concept_members;
    });
    return result;
}

void AssociationModel::apply_prediction_feedback(const std::vector<std::string>& concept_members,
                                                 bool successful,
                                                 double evidence_strength,
                                                 std::uint64_t sequence) {
    if (concept_members.size() < 2) return;
    const double evidence = std::clamp(evidence_strength, 0.0, 1.0);
    const double learning_rate = successful ? 0.12 * evidence : 0.18 * evidence;
    for (std::size_t i = 0; i < concept_members.size(); ++i) {
        for (std::size_t j = i + 1; j < concept_members.size(); ++j) {
            auto it = std::find_if(associations_.begin(), associations_.end(), [&](const Association& item) {
                return same_pair(item, concept_members[i], concept_members[j]);
            });
            if (it == associations_.end()) continue;
            if (successful) {
                it->strength = std::clamp(it->strength + (1.0 - it->strength) * learning_rate, 0.0, 1.0);
                it->confidence = std::clamp(it->confidence + (1.0 - it->confidence) * (learning_rate * 0.8), 0.0, 1.0);
            } else {
                it->strength = std::clamp(it->strength * (1.0 - learning_rate), 0.0, 1.0);
                it->confidence = std::clamp(it->confidence * (1.0 - learning_rate * 0.7), 0.0, 1.0);
                ++it->contradictory_observations;
            }
            it->last_sequence = sequence;
        }
    }
}

} // namespace jarvis::core
