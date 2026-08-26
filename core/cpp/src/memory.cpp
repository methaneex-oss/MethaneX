#include "jarvis/core/memory.hpp"

#include <algorithm>
#include <mutex>

namespace jarvis::core {

Memory::Memory(std::size_t working_limit)
    : working_limit_(std::max<std::size_t>(1, working_limit)) {}

std::uint64_t Memory::append(Event event) {
    std::unique_lock lock(mutex_);
    if (event.sequence == 0) event.sequence = next_sequence_++;
    else next_sequence_ = std::max(next_sequence_, event.sequence + 1);
    continuity_.push_back(std::move(event));
    return continuity_.back().sequence;
}

std::optional<Event> Memory::latest() const {
    std::shared_lock lock(mutex_);
    if (continuity_.empty()) return std::nullopt;
    return continuity_.back();
}

std::vector<Event> Memory::recent(std::size_t limit) const {
    std::shared_lock lock(mutex_);
    const auto count = std::min(limit == 0 ? working_limit_ : limit, continuity_.size());
    return std::vector<Event>(continuity_.end() - static_cast<std::ptrdiff_t>(count), continuity_.end());
}

std::vector<Event> Memory::by_source(const std::string& source, std::size_t limit) const {
    std::shared_lock lock(mutex_);
    std::vector<Event> result;
    for (auto it = continuity_.rbegin(); it != continuity_.rend(); ++it) {
        if (it->source == source) result.push_back(*it);
        if (limit != 0 && result.size() >= limit) break;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<Event> Memory::by_kind(const std::string& kind, std::size_t limit) const {
    std::shared_lock lock(mutex_);
    std::vector<Event> result;
    for (auto it = continuity_.rbegin(); it != continuity_.rend(); ++it) {
        if (it->kind == kind) result.push_back(*it);
        if (limit != 0 && result.size() >= limit) break;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::size_t Memory::size() const noexcept {
    std::shared_lock lock(mutex_);
    return continuity_.size();
}

std::uint64_t Memory::next_sequence() const noexcept {
    std::shared_lock lock(mutex_);
    return next_sequence_;
}

} // namespace jarvis::core
