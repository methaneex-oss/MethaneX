#include "jarvis/core/world_model.hpp"

#include <algorithm>
#include <mutex>

namespace jarvis::core {
namespace {

void accumulate_evidence(Fact& accumulated, const Fact& incoming) {
    const auto previous_observations = std::max<std::uint64_t>(1, accumulated.observations);
    const auto incoming_observations = std::max<std::uint64_t>(1, incoming.observations);
    const long double total = static_cast<long double>(previous_observations) +
                              static_cast<long double>(incoming_observations);
    accumulated.confidence = std::clamp(static_cast<double>(
        (static_cast<long double>(accumulated.confidence) * previous_observations +
         static_cast<long double>(incoming.confidence) * incoming_observations) / total),
        0.0, 1.0);
    accumulated.observations = previous_observations + incoming_observations;
    if (accumulated.first_sequence == 0 ||
        (incoming.first_sequence != 0 &&
         incoming.first_sequence < accumulated.first_sequence)) {
        accumulated.first_sequence = incoming.first_sequence;
    }
    accumulated.updated_sequence = std::max(
        accumulated.updated_sequence, incoming.updated_sequence);
}

long double evidence_weight(const Fact& fact) {
    return static_cast<long double>(std::clamp(fact.confidence, 0.0, 1.0)) *
           static_cast<long double>(std::max<std::uint64_t>(1, fact.observations));
}

} // namespace

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

    // Keep independent support for each observed value while a fact is
    // contested. Repeated evidence for either side accumulates; it must not
    // leave the first conflict permanently disputed merely because the
    // currently selected fact had an equal-confidence tie.
    if (it->value == fact.value) {
        accumulate_evidence(*it, fact);
    } else {
        const auto candidate = std::find_if(
            disputed_facts_.begin(), disputed_facts_.end(),
            [&](const Fact& current) {
                return current.subject == fact.subject &&
                       current.predicate == fact.predicate &&
                       current.value == fact.value;
            });
        if (candidate != disputed_facts_.end()) {
            accumulate_evidence(*candidate, fact);
        } else {
            fact.disputed = true;
            if (fact.first_sequence == 0)
                fact.first_sequence = fact.updated_sequence;
            disputed_facts_.push_back(std::move(fact));
        }
    }

    const auto same_fact = [&](const Fact& candidate) {
        return candidate.subject == it->subject &&
               candidate.predicate == it->predicate;
    };
    Fact* winner = &*it;
    long double strongest = evidence_weight(*winner);
    std::size_t strongest_count = 1;
    for (auto& candidate : disputed_facts_) {
        if (!same_fact(candidate)) continue;
        const long double weight = evidence_weight(candidate);
        if (weight > strongest) {
            strongest = weight;
            winner = &candidate;
            strongest_count = 1;
        } else if (weight == strongest) {
            ++strongest_count;
        }
    }

    if (strongest_count == 1) {
        if (winner != &*it) *it = *winner;
        it->disputed = false;
        disputed_facts_.erase(
            std::remove_if(disputed_facts_.begin(), disputed_facts_.end(), same_fact),
            disputed_facts_.end());
        return;
    }

    it->disputed = true;
    for (auto& candidate : disputed_facts_) {
        if (same_fact(candidate)) candidate.disputed = true;
    }
}

void WorldModel::relate(const Relation& incoming) {
    std::unique_lock lock(mutex_);
    Relation relation = incoming;
    relation.confidence = std::clamp(relation.confidence, 0.0, 1.0);

    const auto exact = std::find_if(relations_.begin(), relations_.end(), [&](const Relation& current) {
        return current.from == relation.from && current.type == relation.type && current.to == relation.to;
    });
    if (exact != relations_.end()) {
        exact->confidence = std::max(exact->confidence, relation.confidence);
        exact->updated_sequence = std::max(exact->updated_sequence, relation.updated_sequence);
        return;
    }

    const auto conflict = std::find_if(relations_.begin(), relations_.end(), [&](const Relation& current) {
        return current.from == relation.from && current.type == relation.type && current.to != relation.to;
    });
    if (conflict != relations_.end()) {
        conflict->disputed = true;
        relation.disputed = true;
    }
    relations_.push_back(std::move(relation));
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
    for (const auto& relation : relations_) if (relation.from == subject) result.push_back(relation);
    return result;
}

std::vector<Fact> WorldModel::facts() const {
    std::shared_lock lock(mutex_);
    return facts_;
}

std::vector<Fact> WorldModel::disputed_facts() const {
    std::shared_lock lock(mutex_);
    std::vector<Fact> result = disputed_facts_;
    for (const auto& fact : facts_) if (fact.disputed) result.push_back(fact);
    return result;
}

std::vector<Relation> WorldModel::disputed_relations() const {
    std::shared_lock lock(mutex_);
    std::vector<Relation> result;
    for (const auto& relation : relations_) if (relation.disputed) result.push_back(relation);
    return result;
}

void WorldModel::clear() {
    std::unique_lock lock(mutex_);
    facts_.clear();
    disputed_facts_.clear();
    relations_.clear();
    disputed_relations_.clear();
}

} // namespace jarvis::core
