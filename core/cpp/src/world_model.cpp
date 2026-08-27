#include "jarvis/core/world_model.hpp"

#include <algorithm>
#include <mutex>

namespace jarvis::core {

void WorldModel::observe(const Fact& incoming) {
    std::unique_lock lock(mutex_);
    Fact fact = incoming;
    fact.confidence = std::clamp(fact.confidence, 0.0, 1.0);
    fact.observations = std::max<std::uint64_t>(1, fact.observations);
    const auto it = std::find_if(facts_.begin(), facts_.end(), [&](const Fact& current) {
        return current.subject == fact.subject && current.predicate == fact.predicate;
    });
    if (it == facts_.end()) {
        facts_.push_back(std::move(fact));
        return;
    }
    if (it->value == fact.value) {
        const double n = static_cast<double>(it->observations);
        it->confidence = (it->confidence * n + fact.confidence) / (n + 1.0);
        it->observations += fact.observations;
    } else if (fact.confidence > it->confidence) {
        *it = std::move(fact);
    } else {
        it->confidence = std::max(0.0, it->confidence * 0.95);
    }
}

void WorldModel::relate(const Relation& incoming) {
    std::unique_lock lock(mutex_);
    Relation relation = incoming;
    relation.confidence = std::clamp(relation.confidence, 0.0, 1.0);
    const auto it = std::find_if(relations_.begin(), relations_.end(), [&](const Relation& current) {
        return current.from == relation.from && current.type == relation.type && current.to == relation.to;
    });
    if (it == relations_.end()) relations_.push_back(std::move(relation));
    else it->confidence = std::max(it->confidence, relation.confidence);
}

std::optional<Fact> WorldModel::query(const std::string& subject, const std::string& predicate) const {
    std::shared_lock lock(mutex_);
    const auto it = std::find_if(facts_.begin(), facts_.end(), [&](const Fact& fact) { return fact.subject == subject && fact.predicate == predicate; });
    if (it == facts_.end()) return std::nullopt;
    return *it;
}

std::vector<Relation> WorldModel::relations_from(const std::string& subject) const {
    std::shared_lock lock(mutex_);
    std::vector<Relation> result;
    for (const auto& relation : relations_) if (relation.from == subject) result.push_back(relation);
    return result;
}

std::vector<Fact> WorldModel::facts() const {
    std::shared_lock lock(mutex_);
    return facts_;
}

} // namespace jarvis::core
