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
    std::set<std::pair<std::string, std::string>> processed;
    for (const auto& current : after) {
        if (!changed(before, current)) continue;

        for (const auto& other : after) {
            if (other.key == current.key || other.confidence <= 0.0) continue;
            const auto pair = std::minmax(current.key, other.key);
            if (!processed.emplace(pair).second) continue;

            // A contradictory observation can lower stored belief confidence. That is
            // a belief-update consequence, not evidence that the observation itself was
            // unreliable. Changed participants therefore use transition reliability;
            // unchanged context uses its retained belief confidence.
            const double current_evidence = transition_reliability;
            const double other_evidence = changed(before, other)
                ? transition_reliability
                : other.confidence;
            const double evidence = std::clamp(std::min(current_evidence, other_evidence), 0.0, 1.0);
            auto it = std::find_if(associations_.begin(), associations_.end(), [&](const Association& item) {
                return same_pair(item, current.key, other.key);
            });
            if (it == associations_.end()) {
                associations_.push_back(Association{pair.first, pair.second, evidence, evidence, 1, sequence});
                continue;
            }
            it->strength = std::clamp(it->strength + (evidence - it->strength) * 0.15, 0.0, 1.0);
            it->confidence = std::clamp(it->confidence + (evidence - it->confidence) * 0.10, 0.0, 1.0);
            ++it->observations;
            it->last_sequence = sequence;
        }
    }
}

std::vector<Association> AssociationModel::all() const {
    return associations_;
}

std::vector<Association> AssociationModel::related(const std::string& key,
                                                    double minimum_strength) const {
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

    std::sort(result.begin(), result.end(), [](const AssociationInference& lhs,
                                               const AssociationInference& rhs) {
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
    for (const auto& association : associations_) {
        if (association.strength < threshold) continue;
        neighbors[association.left].insert(association.right);
        neighbors[association.right].insert(association.left);
        observations[association.left] += association.observations;
        observations[association.right] += association.observations;
    }

    std::vector<std::string> nodes;
    nodes.reserve(neighbors.size());
    for (const auto& [node, _] : neighbors) nodes.push_back(node);
    std::sort(nodes.begin(), nodes.end());

    // Two experiences become candidates for the same learned concept only when
    // they repeatedly share independent contextual neighbors. This is a
    // structural hypothesis, not a semantic label supplied by the program.
    std::unordered_map<std::string, std::set<std::string>> candidate_graph;
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        for (std::size_t j = i + 1; j < nodes.size(); ++j) {
            const auto& lhs = neighbors[nodes[i]];
            const auto& rhs = neighbors[nodes[j]];
            std::size_t shared = 0;
            for (const auto& neighbor : lhs) {
                if (rhs.count(neighbor) != 0) ++shared;
            }
            if (shared >= minimum_shared_contexts) {
                candidate_graph[nodes[i]].insert(nodes[j]);
                candidate_graph[nodes[j]].insert(nodes[i]);
            }
        }
    }

    std::set<std::string> visited;
    for (const auto& [start, _] : candidate_graph) {
        if (visited.count(start) != 0) continue;
        std::vector<std::string> members;
        std::vector<std::string> stack{start};
        while (!stack.empty()) {
            const auto node = stack.back();
            stack.pop_back();
            if (!visited.insert(node).second) continue;
            members.push_back(node);
            for (const auto& next : candidate_graph[node])
                if (visited.count(next) == 0) stack.push_back(next);
        }
        if (members.size() < 2) continue;

        double coherence = 0.0;
        std::size_t pairs = 0;
        for (std::size_t i = 0; i < members.size(); ++i) {
            for (std::size_t j = i + 1; j < members.size(); ++j) {
                const auto& lhs = neighbors[members[i]];
                const auto& rhs = neighbors[members[j]];
                std::size_t shared = 0;
                for (const auto& neighbor : lhs)
                    if (rhs.count(neighbor) != 0) ++shared;
                coherence += static_cast<double>(shared) /
                             static_cast<double>(std::max<std::size_t>(
                                 1, std::min(lhs.size(), rhs.size())));
                ++pairs;
            }
        }
        coherence = pairs == 0 ? 0.0 : coherence / static_cast<double>(pairs);

        std::uint64_t support = 0;
        for (const auto& member : members) support += observations[member];
        std::sort(members.begin(), members.end());
        result.push_back(ConceptCandidate{std::move(members), coherence, support});
    }

    std::sort(result.begin(), result.end(), [](const ConceptCandidate& lhs,
                                               const ConceptCandidate& rhs) {
        if (lhs.coherence != rhs.coherence) return lhs.coherence > rhs.coherence;
        if (lhs.supporting_observations != rhs.supporting_observations)
            return lhs.supporting_observations > rhs.supporting_observations;
        return lhs.members < rhs.members;
    });
    return result;
}

} // namespace jarvis::core
