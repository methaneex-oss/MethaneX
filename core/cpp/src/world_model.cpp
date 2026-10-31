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
    accumulated.latest_evidence_confidence = incoming.latest_evidence_confidence;
    if (accumulated.first_sequence == 0 ||
        (incoming.first_sequence != 0 &&
         incoming.first_sequence < accumulated.first_sequence)) {
        accumulated.first_sequence = incoming.first_sequence;
    }
    accumulated.updated_sequence = std::max(
        accumulated.updated_sequence, incoming.updated_sequence);
}

void accumulate_evidence(Relation& accumulated, const Relation& incoming) {
    const auto previous_observations = std::max<std::uint64_t>(1, accumulated.observations);
    const auto incoming_observations = std::max<std::uint64_t>(1, incoming.observations);
    const long double total = static_cast<long double>(previous_observations) +
                              static_cast<long double>(incoming_observations);
    accumulated.confidence = std::clamp(static_cast<double>(
        (static_cast<long double>(accumulated.confidence) * previous_observations +
         static_cast<long double>(incoming.confidence) * incoming_observations) / total),
        0.0, 1.0);
    accumulated.observations = previous_observations + incoming_observations;
    accumulated.latest_evidence_confidence = incoming.latest_evidence_confidence;
    if (accumulated.first_sequence == 0 ||
        (incoming.first_sequence != 0 &&
         incoming.first_sequence < accumulated.first_sequence)) {
        accumulated.first_sequence = incoming.first_sequence;
    }
    accumulated.updated_sequence = std::max(
        accumulated.updated_sequence, incoming.updated_sequence);
}

} // namespace

void WorldModel::observe(const Fact& incoming) {
    std::unique_lock lock(mutex_);
    Fact fact = incoming;
    fact.confidence = std::clamp(fact.confidence, 0.0, 1.0);
    fact.latest_evidence_confidence = fact.confidence;
    fact.observations = std::max<std::uint64_t>(1, fact.observations);
    const auto it = std::find_if(facts_.begin(), facts_.end(), [&](const Fact& current) {
        return current.subject == fact.subject && current.predicate == fact.predicate;
    });
    if (it == facts_.end()) {
        if (fact.first_sequence == 0)
            fact.first_sequence = fact.updated_sequence;
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
    bool has_conflict = false;
    bool has_unsequenced_conflict = false;
    std::uint64_t latest_conflict_sequence = 0;
    for (const auto& candidate : disputed_facts_) {
        if (!same_fact(candidate)) continue;
        has_conflict = true;
        if (candidate.first_sequence == 0) {
            has_unsequenced_conflict = true;
        } else {
            latest_conflict_sequence = std::max(
                latest_conflict_sequence, candidate.first_sequence);
        }
    }

    if (!has_conflict) {
        it->disputed = false;
        return;
    }

    // A source can revise its own earlier claim, but repeated observations
    // cannot accumulate artificial support. Resolve only when exactly one
    // alternative has a fresh post-conflict observation whose reliability is
    // strictly higher than every competing alternative's aggregate mean.
    Fact* resolving_candidate = nullptr;
    std::size_t resolving_candidates = 0;
    const auto consider_candidate = [&](Fact& candidate) {
        double strongest_competing_confidence = 0.0;
        const auto consider_competitor = [&](const Fact& competitor) {
            if (same_fact(competitor) && competitor.value != candidate.value) {
                strongest_competing_confidence = std::max(
                    strongest_competing_confidence, competitor.confidence);
            }
        };
        consider_competitor(*it);
        for (const auto& competitor : disputed_facts_)
            consider_competitor(competitor);
        if (candidate.updated_sequence > latest_conflict_sequence &&
            candidate.latest_evidence_confidence > strongest_competing_confidence) {
            resolving_candidate = &candidate;
            ++resolving_candidates;
        }
    };
    consider_candidate(*it);
    for (auto& candidate : disputed_facts_) {
        if (same_fact(candidate)) consider_candidate(candidate);
    }

    if (resolving_candidates == 1 && resolving_candidate != nullptr &&
        !has_unsequenced_conflict && latest_conflict_sequence != 0) {
        if (resolving_candidate != &*it) *it = *resolving_candidate;
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
    relation.latest_evidence_confidence = relation.confidence;
    relation.observations = std::max<std::uint64_t>(1, relation.observations);
    if (relation.first_sequence == 0)
        relation.first_sequence = relation.updated_sequence;

    const std::string relation_from = relation.from;
    const std::string relation_type = relation.type;
    const std::string relation_to = relation.to;
    const auto exact = std::find_if(relations_.begin(), relations_.end(), [&](const Relation& current) {
        return current.from == relation_from && current.type == relation_type && current.to == relation_to;
    });
    if (exact != relations_.end()) {
        accumulate_evidence(*exact, relation);
    } else {
        relation.disputed = true;
        relations_.push_back(std::move(relation));
    }

    // Conflicting destinations are competing hypotheses for one relation.
    // A fresh, strictly stronger post-conflict observation may revise this source's own claim,
    // but repetition count never manufactures independent support.
    const auto same_relation = [&](const Relation& candidate) {
        return candidate.from == relation_from && candidate.type == relation_type;
    };
    bool has_unsequenced_conflict = false;
    std::uint64_t latest_conflict_sequence = 0;
    std::size_t relation_count = 0;
    for (const auto& candidate : relations_) {
        if (!same_relation(candidate)) continue;
        ++relation_count;
        if (candidate.first_sequence == 0) {
            has_unsequenced_conflict = true;
        } else {
            latest_conflict_sequence = std::max(
                latest_conflict_sequence, candidate.first_sequence);
        }
    }

    if (relation_count == 1) {
        const auto only = std::find_if(relations_.begin(), relations_.end(), same_relation);
        if (only != relations_.end()) only->disputed = false;
        return;
    }

    Relation* resolving_candidate = nullptr;
    std::size_t resolving_candidates = 0;
    for (auto& candidate : relations_) {
        if (!same_relation(candidate)) continue;
        double strongest_competing_confidence = 0.0;
        for (const auto& competitor : relations_) {
            if (same_relation(competitor) && competitor.to != candidate.to) {
                strongest_competing_confidence = std::max(
                    strongest_competing_confidence, competitor.confidence);
            }
        }
        if (candidate.updated_sequence > latest_conflict_sequence &&
            candidate.latest_evidence_confidence > strongest_competing_confidence) {
            resolving_candidate = &candidate;
            ++resolving_candidates;
        }
    }

    if (resolving_candidates == 1 && resolving_candidate != nullptr &&
        !has_unsequenced_conflict && latest_conflict_sequence != 0) {
        const std::string winning_from = resolving_candidate->from;
        const std::string winning_type = resolving_candidate->type;
        const std::string winning_to = resolving_candidate->to;
        for (auto& candidate : relations_) {
            if (same_relation(candidate))
                candidate.disputed = candidate.to != winning_to;
        }
        relations_.erase(
            std::remove_if(relations_.begin(), relations_.end(),
                [&](const Relation& candidate) {
                    return candidate.from == winning_from &&
                           candidate.type == winning_type &&
                           candidate.to != winning_to;
                }),
            relations_.end());
        const auto resolved = std::find_if(relations_.begin(), relations_.end(),
            [&](const Relation& candidate) {
                return candidate.from == winning_from &&
                       candidate.type == winning_type &&
                       candidate.to == winning_to;
            });
        if (resolved != relations_.end()) resolved->disputed = false;
        return;
    }

    for (auto& candidate : relations_) {
        if (same_relation(candidate)) candidate.disputed = true;
    }
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
