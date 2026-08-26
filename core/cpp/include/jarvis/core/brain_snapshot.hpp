#pragma once

#include "jarvis/core/brain.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct BrainSnapshot {
    std::uint64_t cycle{0};
    std::uint64_t events_seen{0};
    double novelty{0.0};
    double attention{0.0};
    double threat{0.0};
    std::vector<Belief> beliefs;
    std::vector<Prediction> predictions;
};

} // namespace jarvis::core
