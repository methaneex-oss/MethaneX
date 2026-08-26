#pragma once

#include "event.hpp"
#include "world_model.hpp"
#include <cstdint>
#include <shared_mutex>
#include <string>
#include <vector>

namespace jarvis::core {

struct BrainState {
    std::uint64_t cycle{0};
    std::uint64_t events_seen{0};
    double novelty{0.0};
};

class Brain {
public:
    Observation observe(Event event);
    const WorldModel& world() const noexcept { return world_; }
    BrainState state() const;

private:
    static double compute_novelty(const Event& event, const std::vector<Event>& history);

    mutable std::shared_mutex mutex_;
    BrainState state_{};
    WorldModel world_{};
    std::vector<Event> history_;
};

} // namespace jarvis::core
