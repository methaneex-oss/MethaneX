#pragma once

#include "event.hpp"
#include "world_model.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace jarvis::core {

struct WorldEvent {
    std::uint64_t sequence{0};
    std::uint64_t timestamp_ns{0};
    std::string source;
    std::string kind;
};

struct WorldSnapshot {
    std::uint64_t sequence{0};
    std::uint64_t timestamp_ns{0};
    std::vector<Fact> facts;
    std::vector<Relation> relations;
};

class WorldState {
public:
    void apply(const Event& event);
    void observe(const Fact& fact);
    void relate(const Relation& relation);
    WorldSnapshot snapshot() const;
    std::vector<WorldEvent> history() const;
    std::optional<WorldSnapshot> at(std::uint64_t sequence) const;
    void clear();

private:
    void checkpoint(std::uint64_t sequence, std::uint64_t timestamp_ns);
    WorldModel model_{};
    std::vector<WorldEvent> history_;
    std::vector<WorldSnapshot> snapshots_;
};

} // namespace jarvis::core
