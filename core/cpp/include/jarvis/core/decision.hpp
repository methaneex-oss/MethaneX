#pragma once

#include "cognition.hpp"

#include <vector>

namespace jarvis::core {

class DecisionEngine {
public:
    std::vector<Decision> rank(const std::vector<CandidateAction>& actions, double uncertainty, double threat = 0.0) const;
};

} // namespace jarvis::core
