#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cmath>
#include <mutex>

namespace jarvis::core {

Observation Brain::observe(Event event) {
    std::unique_lock lock(mutex_);
    event.sequence = ++state_.events_seen;
    state_.cycle++;
    const double novelty = compute_novelty(event, history_);
    state_.novelty = novelty;
    history_.push_back(event);

    for (const auto& [key, value] : event.data) {
        world_.observe(Fact{event.source, key, value, 0.7, 1});
    }
    return Observation{std::move(event), novelty};
}

BrainState Brain::state() const {
    std::shared_lock lock(mutex_);
    return state_;
}

double Brain::compute_novelty(const Event& event, const std::vector<Event>& history) {
    if (history.empty()) return 1.0;
    const auto& previous = history.back();
    std::size_t differences = event.data.size();
    for (const auto& [key, value] : event.data) {
        const auto it = previous.data.find(key);
        if (it != previous.data.end() && it->second == value) {
            --differences;
        }
    }
    const double denominator = std::max<std::size_t>(1, event.data.size());
    return std::clamp(static_cast<double>(differences) / denominator, 0.0, 1.0);
}

} // namespace jarvis::core
