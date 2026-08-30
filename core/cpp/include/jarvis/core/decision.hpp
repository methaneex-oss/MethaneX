#pragma once

#include "cognition.hpp"

#include <vector>

namespace jarvis::core {

struct DecisionPolicy {
    double utility_weight{1.0};
    double expected_value_weight{1.0};
    double uncertainty_weight{1.0};
    double threat_weight{1.0};
    double risk_weight{1.0};
};

class DecisionEngine {
public:
    explicit DecisionEngine(DecisionPolicy policy = {}) : policy_(policy) {}

    std::vector<Decision> rank(const std::vector<CandidateAction>& actions,
                               double uncertainty,
                               double threat = 0.0) const;

    void set_policy(DecisionPolicy policy) noexcept { policy_ = policy; }
    DecisionPolicy policy() const noexcept { return policy_; }

private:
    DecisionPolicy policy_{};
};

} // namespace jarvis::core
