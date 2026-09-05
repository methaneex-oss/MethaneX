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
    policy.goal_weight = 0.0;
    policy.plan_value_weight = 0.0;
    policy.uncertainty_weight = 0.0;
    policy.threat_weight = 0.0;
    policy.risk_weight = 0.0;
    policy.resource_weight = 0.0;
    policy.consequence_weight = 0.0;
    policy.urgency_weight = 0.0;
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

    DecisionPolicy integrated_policy{};
    integrated_policy.utility_weight = 1.0;
    integrated_policy.expected_value_weight = 1.0;
    integrated_policy.goal_weight = 1.0;
    integrated_policy.plan_value_weight = 0.5;
    integrated_policy.uncertainty_weight = 0.5;
    integrated_policy.threat_weight = 1.0;
    integrated_policy.risk_weight = 1.0;
    integrated_policy.resource_weight = 1.0;
    integrated_policy.consequence_weight = 1.0;
    integrated_policy.urgency_weight = 1.0;
    integrated_policy.act_threshold = 0.5;
    integrated_policy.reject_threshold = -0.5;
    integrated_policy.clarify_uncertainty_threshold = 0.8;
    integrated_policy.escalate_threat_threshold = 0.8;
    integrated_policy.escalate_risk_threshold = 0.7;
    engine.set_policy(integrated_policy);

    DecisionContext context;
    context.goal_priority = 1.0;
    context.goal_progress = 0.0;
    context.plan_expected_value = 0.4;
    context.plan_risk = 0.1;
    context.resource_budget = 10.0;
    context.uncertainty = 0.1;
    context.threat = 0.0;
    context.deadline_pressure = 0.8;

    CandidateAction act{"act", 0.7, 0.8, 0.1, 0.9, 1.0, 0.0, 0.9};
    CandidateAction recommend{"recommend", 0.7, 0.8, 0.1, 0.9, 1.0, 0.0, 0.9, DecisionOutcome::recommend};
    const auto integrated = engine.decide({act, recommend}, context);
    assert(integrated.size() == 2);
    assert(integrated.front().score >= integrated.back().score);
    assert(integrated.front().outcome == DecisionOutcome::act ||
           integrated.front().outcome == DecisionOutcome::recommend);

    const auto clarify = engine.decide({CandidateAction{"uncertain", 1.0, 1.0, 0.0, 1.0}},
                                       DecisionContext{1.0, 0.0, 0.0, 0.0, 0.0, 0.95, 0.0, 0.0});
    assert(clarify.front().outcome == DecisionOutcome::ask_clarify);

    const auto escalate = engine.decide({CandidateAction{"dangerous", 1.0, 1.0, 0.9, 0.0}},
                                        DecisionContext{1.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.95, 0.0});
    assert(escalate.front().outcome == DecisionOutcome::escalate);

    const auto reject = engine.decide({CandidateAction{"bad", -1.0, -1.0, 0.8, 0.0}}, context);
    assert(reject.front().outcome == DecisionOutcome::reject);

    Planner planner;
    const auto plan = planner.build(actions, 2);
    assert(plan.steps.size() == 2);
    assert(plan.expected_value >= 0.0);
    assert(plan.risk >= 0.0 && plan.risk <= 1.0);

    assert(planner.build(actions, 0).steps.empty());
    assert(planner.build({}, 3).steps.empty());

    return 0;
}
