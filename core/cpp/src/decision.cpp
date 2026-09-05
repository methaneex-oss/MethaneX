#include "jarvis/core/decision.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double finite_or_zero(double value) noexcept {
    return std::isfinite(value) ? value : 0.0;
}

double bounded_weight(double value) noexcept {
    return std::max(0.0, finite_or_zero(value));
}

double bounded_unit(double value) noexcept {
    return std::clamp(finite_or_zero(value), 0.0, 1.0);
}

double bounded_nonnegative(double value) noexcept {
    return std::max(0.0, finite_or_zero(value));
}

} // namespace

std::vector<Decision> DecisionEngine::rank(const std::vector<CandidateAction>& actions,
                                           double uncertainty,
                                           double threat) const {
    DecisionContext context;
    context.uncertainty = uncertainty;
    context.threat = threat;
    return decide(actions, context);
}

std::vector<Decision> DecisionEngine::decide(const std::vector<CandidateAction>& actions,
                                             const DecisionContext& context) const {
    const double uncertainty = bounded_unit(context.uncertainty);
    const double threat = bounded_unit(context.threat);
    const double goal_priority = bounded_unit(context.goal_priority);
    const double goal_progress = bounded_unit(context.goal_progress);
    const double plan_value = finite_or_zero(context.plan_expected_value);
    const double plan_risk = bounded_unit(context.plan_risk);
    const double budget = bounded_nonnegative(context.resource_budget);
    const double deadline_pressure = bounded_unit(context.deadline_pressure);

    const double utility_weight = bounded_weight(policy_.utility_weight);
    const double value_weight = bounded_weight(policy_.expected_value_weight);
    const double goal_weight = bounded_weight(policy_.goal_weight);
    const double plan_value_weight = bounded_weight(policy_.plan_value_weight);
    const double uncertainty_weight = bounded_weight(policy_.uncertainty_weight);
    const double threat_weight = bounded_weight(policy_.threat_weight);
    const double risk_weight = bounded_weight(policy_.risk_weight);
    const double resource_weight = bounded_weight(policy_.resource_weight);
    const double consequence_weight = bounded_weight(policy_.consequence_weight);
    const double urgency_weight = bounded_weight(policy_.urgency_weight);

    std::vector<Decision> result;
    result.reserve(actions.size());
    for (const auto& action : actions) {
        const double utility = finite_or_zero(action.utility);
        const double expected_value = finite_or_zero(action.expected_value);
        const double risk = bounded_unit(action.risk);
        const double reversibility = bounded_unit(action.reversibility);
        const double resource_cost = bounded_nonnegative(action.resource_cost);
        const double consequence = bounded_unit(action.expected_consequence);
        const double urgency = bounded_unit(action.urgency);

        const double goal_alignment = goal_priority * (1.0 - goal_progress);
        const double plan_alignment = plan_value - plan_risk;
        const double exploration = uncertainty * reversibility;
        const double threat_bias = threat * (1.0 - risk);
        const double resource_cost_score = budget > 0.0
            ? std::min(1.0, resource_cost / budget) : 0.0;
        const double score = utility_weight * utility
            + value_weight * expected_value
            + goal_weight * goal_alignment
            + plan_value_weight * plan_alignment
            + uncertainty_weight * exploration
            + threat_weight * threat_bias
            + urgency_weight * (deadline_pressure * urgency)
            - risk_weight * risk * (1.0 - reversibility)
            - resource_weight * resource_cost_score
            - consequence_weight * consequence;

        const double safe_score = finite_or_zero(score);
        result.push_back({action, safe_score, classify(action, safe_score, context)});
    }

    std::sort(result.begin(), result.end(), [](const Decision& a, const Decision& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.action.name < b.action.name;
    });
    return result;
}

DecisionOutcome DecisionEngine::classify(const CandidateAction& action, double score,
                                          const DecisionContext& context) const noexcept {
    const double uncertainty = bounded_unit(context.uncertainty);
    const double threat = bounded_unit(context.threat);
    const double risk = bounded_unit(action.risk);

    if (threat >= bounded_unit(policy_.escalate_threat_threshold) &&
        risk >= bounded_unit(policy_.escalate_risk_threshold)) {
        return DecisionOutcome::escalate;
    }
    if (uncertainty >= bounded_unit(policy_.clarify_uncertainty_threshold)) {
        return DecisionOutcome::ask_clarify;
    }
    if (score <= finite_or_zero(policy_.reject_threshold)) {
        return DecisionOutcome::reject;
    }
    if (score >= finite_or_zero(policy_.act_threshold)) {
        return action.preferred_outcome;
    }
    return DecisionOutcome::defer;
}

} // namespace jarvis::core
