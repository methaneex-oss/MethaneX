#include "jarvis/core/world_model.hpp"

#include <algorithm>

namespace jarvis::core {

void WorldModel::observe(const Fact& incoming) {
    std::unique_lock lock(mutex_);
    const auto it = std::find_if(facts_.begin(), facts_.end(), [&](const Fact& fact) {
        return fact.subject == incoming.subject && fact.predicate == incoming.predicate;
    });
    if (it == facts_.end()) {
        facts_.push_back(incoming);
        return;
    }
    if (it->value == incoming.value) {
        const double n = static_cast<double>(it->observations);
        it->confidence = (it->confidence * n + incoming.confidence) / (n + 1.0);
        ++it->observations;
    } else if (incoming.confidence > it->confidence) {
        *it = incoming;
    } else {
        it->confidence *= 0.95;
    }
}

void WorldModel::relate(const Relation& relation) {
    std::unique_lock lock(mutex_);
    relations_.push_back(relation);
}

std::optional<Fact> WorldModel::query(const std::string& subject, const std::string& predicate) const {
    std::shared_lock lock(mutex_);
    const auto it = std::find_if(facts_.begin(), facts_.end(), [&](const Fact& fact) {
        return fact.subject == subject && fact.predicate == predicate;
    });
    if (it == facts_.end()) return std::nullopt;
    return *it;
}

std::vector<Relation> WorldModel::relations_from(const std::string& subject) const {
    std::shared_lock lock(mutex_);
    std::vector<Relation> result;
    for (const auto& relation : relations_) {
        if (relation.from == subject) result.push_back(relation);
    }
    return result;
}

std::vector<Fact> WorldModel::facts() const {
    std::shared_lock lock(mutex_);
    return facts_;
}

} // namespace jarvis::core
