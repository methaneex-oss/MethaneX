#include "jarvis/core/decision.hpp"
#include "jarvis/core/planning.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

using namespace jarvis::core;

int main() {
    const std::vector<CandidateAction> actions{
        {"alpha", 0.7, 0.4, 0.2, 1.0},
        {"beta", 0.6, 0.8, 0.1, 0.5},
        {"gamma", 0.9, 0.1, 0.9, 0.0}
    };

    DecisionEngine engine;
    const auto ranked = engine.rank(actions, 0.0, 0.0);
    assert(ranked.size() == actions.size());
    assert(ranked.front().action.name == "beta");

    DecisionPolicy policy{};
    policy.utility_weight = 2.0;
    policy.expected_value_weight = 0.0;
    policy.uncertainty_weight = 0.0;
    policy.threat_weight = 0.0;
    policy.risk_weight = 0.0;
    engine.set_policy(policy);
    const auto utility_ranked = engine.rank(actions, 0.0, 0.0);
    assert(utility_ranked.front().action.name == "gamma");

    const auto bounded = engine.rank({
        {"nan", std::numeric_limits<double>::quiet_NaN(), 0.0, 0.0, 1.0},
        {"inf", std::numeric_limits<double>::infinity(), 0.0, 0.0, 1.0},
        {"finite", 0.2, 0.0, 0.0, 1.0}
    }, 5.0, -5.0);
    for (const auto& decision : bounded) assert(std::isfinite(decision.score));

    const auto tie = engine.rank({
        {"zeta", 1.0, 0.0, 0.0, 1.0},
        {"alpha", 1.0, 0.0, 0.0, 1.0}
    }, 0.0, 0.0);
    assert(tie[0].action.name == "alpha");
    assert(tie[1].action.name == "zeta");

    Planner planner;
    const auto plan = planner.build(actions, 2);
    assert(plan.steps.size() == 2);
    assert(plan.expected_value >= 0.0);
    assert(plan.risk >= 0.0 && plan.risk <= 1.0);

    assert(planner.build(actions, 0).steps.empty());
    assert(planner.build({}, 3).steps.empty());

    return 0;
}
