#pragma once

#include "cognition.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

struct PlanningContext {
    double goal_priority{0.0};
    double goal_progress{0.0};
    double threat{0.0};
    double uncertainty{0.0};
    double resource_budget{0.0};
    double deadline_pressure{0.0};
};

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
    Plan build(const std::vector<CandidateAction>& actions, std::size_t horizon,
               const PlanningContext& context) const;
};

} // namespace jarvis::core
