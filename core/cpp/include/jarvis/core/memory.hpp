#pragma once

#include "event.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <shared_mutex>
#include <string>
#include <vector>

namespace jarvis::core {

// Memory is continuity: recent state remains available to cognition while
// the complete event sequence remains recoverable for reconstruction.
class Memory {
public:
    explicit Memory(std::size_t working_limit = 256);

    std::uint64_t append(Event event);
    std::optional<Event> latest() const;
    std::vector<Event> recent(std::size_t limit) const;
    std::vector<Event> by_source(const std::string& source, std::size_t limit = 0) const;
    std::vector<Event> by_kind(const std::string& kind, std::size_t limit = 0) const;
    std::size_t size() const noexcept;
    std::uint64_t next_sequence() const noexcept;

private:
    mutable std::shared_mutex mutex_;
    std::vector<Event> continuity_;
    std::size_t working_limit_;
    std::uint64_t next_sequence_{1};
};

} // namespace jarvis::core
