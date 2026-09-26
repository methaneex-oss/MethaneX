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

} // namespace jarvis::core
