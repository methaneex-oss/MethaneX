#pragma once

#include "cognition.hpp"

#include <vector>

namespace jarvis::core {

struct DecisionPolicy {
    double utility_weight{1.0};
    double expected_value_weight{1.0};
    double goal_weight{1.0};
    double plan_value_weight{0.5};
    double uncertainty_weight{1.0};
    double threat_weight{1.0};
    double risk_weight{1.0};
    double resource_weight{1.0};
    double consequence_weight{1.0};
    double urgency_weight{0.5};

    double act_threshold{0.5};
    double reject_threshold{-0.5};
    double clarify_uncertainty_threshold{0.75};
    double escalate_threat_threshold{0.75};
    double escalate_risk_threshold{0.65};
};

class DecisionEngine {
public:
    explicit DecisionEngine(DecisionPolicy policy = {}) : policy_(policy) {}

    std::vector<Decision> rank(const std::vector<CandidateAction>& actions,
                               double uncertainty,
                               double threat = 0.0) const;

    std::vector<Decision> decide(const std::vector<CandidateAction>& actions,
                                 const DecisionContext& context) const;

    void set_policy(DecisionPolicy policy) noexcept { policy_ = policy; }
    DecisionPolicy policy() const noexcept { return policy_; }

private:
    DecisionOutcome classify(const CandidateAction& action, double score,
                             const DecisionContext& context) const noexcept;

    DecisionPolicy policy_{};
};

} // namespace jarvis::core
