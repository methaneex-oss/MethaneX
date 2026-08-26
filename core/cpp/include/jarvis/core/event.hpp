#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace jarvis::core {

using Scalar = std::variant<std::monostate, bool, std::int64_t, double, std::string>;
using Attributes = std::unordered_map<std::string, Scalar>;

struct Event {
    std::uint64_t sequence{};
    std::uint64_t timestamp_ns{};
    std::string source;
    std::string kind;
    Attributes data;
};

struct Observation {
    Event event;
    double novelty{};
};

} // namespace jarvis::core
