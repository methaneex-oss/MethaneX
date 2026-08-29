#include "jarvis/core/world_state.hpp"

#include <algorithm>

namespace jarvis::core {

void WorldState::checkpoint(std::uint64_t sequence, std::uint64_t timestamp_ns) {
    WorldSnapshot snapshot;
    snapshot.sequence = sequence;
    snapshot.timestamp_ns = timestamp_ns;
    snapshot.facts = model_.facts();
    for (const auto& fact : snapshot.facts) {
        const auto relations = model_.relations_from(fact.subject);
        snapshot.relations.insert(snapshot.relations.end(), relations.begin(), relations.end());
    }
    snapshots_.push_back(std::move(snapshot));
}

void WorldState::apply(const Event& event) {
    for (const auto& [key, value] : event.data) {
        model_.observe(Fact{event.source, key, value, 0.5, 1});
    }
    if (event.data.empty()) {
        model_.observe(Fact{event.source, event.kind, event.kind, 0.5, 1});
    }
    history_.push_back(WorldEvent{event.sequence, event.timestamp_ns, event.source, event.kind});
    checkpoint(event.sequence, event.timestamp_ns);
}

void WorldState::observe(const Fact& fact) {
    model_.observe(fact);
    checkpoint(history_.empty() ? 0 : history_.back().sequence,
               history_.empty() ? 0 : history_.back().timestamp_ns);
}

void WorldState::relate(const Relation& relation) {
    model_.relate(relation);
    checkpoint(history_.empty() ? 0 : history_.back().sequence,
               history_.empty() ? 0 : history_.back().timestamp_ns);
}

WorldSnapshot WorldState::snapshot() const {
    WorldSnapshot result;
    if (!history_.empty()) {
        result.sequence = history_.back().sequence;
        result.timestamp_ns = history_.back().timestamp_ns;
    }
    result.facts = model_.facts();
    for (const auto& fact : result.facts) {
        const auto relations = model_.relations_from(fact.subject);
        result.relations.insert(result.relations.end(), relations.begin(), relations.end());
    }
    return result;
}

std::vector<WorldEvent> WorldState::history() const {
    return history_;
}

std::optional<WorldSnapshot> WorldState::at(std::uint64_t sequence) const {
    const auto it = std::find_if(snapshots_.rbegin(), snapshots_.rend(),
        [sequence](const WorldSnapshot& snapshot) { return snapshot.sequence <= sequence; });
    if (it == snapshots_.rend()) return std::nullopt;
    return *it;
}

void WorldState::clear() {
    model_.clear();
    history_.clear();
    snapshots_.clear();
}

} // namespace jarvis::core
