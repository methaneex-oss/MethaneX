#include "jarvis/core/world_state.hpp"

#include <algorithm>

namespace jarvis::core {

void WorldState::apply(const Event& event) {
    model_.observe(Fact{event.source, event.kind, event.kind, 0.5, 1});
    history_.push_back(WorldEvent{event.sequence, event.timestamp_ns, event.source, event.kind});
    snapshots_.push_back(WorldSnapshot{event.sequence, event.timestamp_ns, model_.facts(), {}});
}

WorldSnapshot WorldState::snapshot() const {
    const auto facts = model_.facts();
    WorldSnapshot result;
    if (!history_.empty()) {
        result.sequence = history_.back().sequence;
        result.timestamp_ns = history_.back().timestamp_ns;
    }
    result.facts = facts;
    for (const auto& fact : facts) {
        (void)fact;
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
    history_.clear();
    snapshots_.clear();
}

} // namespace jarvis::core
