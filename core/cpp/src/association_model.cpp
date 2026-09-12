#include "jarvis/core/association_model.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

bool same_pair(const Association& association, const std::string& left, const std::string& right) {
    return (association.left == left && association.right == right) ||
           (association.left == right && association.right == left);
}

}

void AssociationModel::observe(const std::vector<Belief>& before,
                               const std::vector<Belief>& after,
                               std::uint64_t sequence) {
    for (const auto& current : after) {
        const auto prior = std::find_if(before.begin(), before.end(), [&](const Belief& belief) {
            return belief.key == current.key;
        });
        if (prior == before.end() || prior->value == current.value) continue;

        for (const auto& other : after) {
            if (other.key == current.key || other.confidence <= 0.0) continue;
            const double evidence = std::clamp(current.confidence * other.confidence, 0.0, 1.0);
            auto it = std::find_if(associations_.begin(), associations_.end(), [&](const Association& item) {
                return same_pair(item, current.key, other.key);
            });
            if (it == associations_.end()) {
                associations_.push_back(Association{current.key, other.key, evidence, evidence, 1, sequence});
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

} // namespace jarvis::core
