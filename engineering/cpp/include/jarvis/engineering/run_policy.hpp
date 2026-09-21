#pragma once

#include <cstddef>

namespace jarvis::engineering {

struct EngineeringRunPolicy {
    std::size_t max_attempts_per_stage{2};
    bool retry_rejected_stages{true};
};

} // namespace jarvis::engineering
