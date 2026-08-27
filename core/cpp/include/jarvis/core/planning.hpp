#pragma once

#include "cognition.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

struct PlanStep {
    CandidateAction action;
    double expected_score{0.0};
};

struct Plan {
    std::vector<PlanStep> steps;
    double expected_value{0.0};
    double risk{0.0};
};

class Planner {
public:
    Plan build(const std::vector<CandidateAction>& actions, std::size_t horizon) const;
};

} // namespace jarvis::core
