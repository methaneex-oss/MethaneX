#pragma once

#include "cognition.hpp"

#include <vector>

namespace jarvis::core {

class DecisionEngine {
public:
    std::vector<Decision> rank(const std::vector<CandidateAction>& actions, double uncertainty) const;
};

} // namespace jarvis::core
