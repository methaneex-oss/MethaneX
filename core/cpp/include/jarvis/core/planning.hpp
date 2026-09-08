#pragma once

#include "cognition.hpp"

#include <cstddef>

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

struct PlanningPolicy {
    double utility_weight{1.0};
    double expected_value_weight{1.0};
    double goal_weight{1.0};
    double urgency_weight{1.0};
    double reversibility_weight{0.25};
    double threat_weight{0.25};
    double risk_weight{1.0};
    double resource_weight{0.5};
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
    explicit Planner(PlanningPolicy policy = {}) : policy_(policy) {}

    Plan build(const std::vector<CandidateAction>& actions, std::size_t horizon) const;
    Plan build(const std::vector<CandidateAction>& actions, std::size_t horizon,
               const PlanningContext& context) const;

    void set_policy(PlanningPolicy policy) noexcept { policy_ = policy; }
    PlanningPolicy policy() const noexcept { return policy_; }

private:
    PlanningPolicy policy_{};
};

} // namespace jarvis::core
