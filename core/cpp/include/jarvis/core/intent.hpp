#pragma once

#include "cognition.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct Intent {
    std::string id;
    std::string description;
    double priority{0.0};
    double confidence{0.0};
    double urgency{0.0};
    double uncertainty{0.0};
    std::uint64_t created_cycle{0};
};

class IntentModel {
public:
    Intent select(const std::vector<Goal>& goals, double threat,
                  double uncertainty, std::uint64_t cycle) const;
};

} // namespace jarvis::core
