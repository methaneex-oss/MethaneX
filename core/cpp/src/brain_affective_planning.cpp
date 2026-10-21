#include "jarvis/core/brain.hpp"

#include <algorithm>

namespace jarvis::core {
namespace {

// Use the same evidence aggregation as CognitiveCycle: direct experiences
// take precedence over generalization, but all observed actions in the chosen
// context contribute. This prevents one "best" record from hiding contrary
// outcomes for another action, and weights transfer by actual similarity.
void apply_developmental_evidence(std::vector<CandidateAction>& actions,
                                  const DevelopmentalLearning& learning,
                                  const std::string& context) {
    const auto strategies = learning.strategies();
    const bool has_exact_context = std::any_of(
        strategies.begin(), strategies.end(),
        [&](const LearnedStrategy& strategy) {
            return strategy.context == context;
        });

    const auto related = has_exact_context
        ? std::vector<RelatedLearnedStrategy>{}
        : learning.related_strategies(context);

    for (auto& action : actions) {
        double weighted_evidence = 0.0;
        double total_weight = 0.0;
        if (has_exact_context) {
            for (const auto& evidence : strategies) {
                if (evidence.context != context || evidence.action != action.name)
                    continue;
                const double weight = std::clamp(evidence.confidence, 0.0, 1.0);
                weighted_evidence += weight * std::clamp(evidence.value, -1.0, 1.0);
                total_weight += weight;
            }
        } else {
            for (const auto& evidence : related) {
                if (evidence.strategy.action != action.name) continue;
                const double weight =
                    std::clamp(evidence.similarity, 0.0, 1.0) *
                    std::clamp(evidence.strategy.confidence, 0.0, 1.0);
                if (weight <= 0.0) continue;
                weighted_evidence += weight *
                    std::clamp(evidence.strategy.value, -1.0, 1.0);
                total_weight += weight;
            }
        }
        if (total_weight <= 0.0) continue;
        const double influence = std::clamp(
            weighted_evidence / std::max(1.0, total_weight), -1.0, 1.0);
        action.utility += influence;
        action.expected_value = std::clamp(
            action.expected_value + influence, -1.0, 1.0);
    }
}

Plan Brain::plan_with_affect(const std::vector<CandidateAction>& actions, std::size_t horizon) const {
    std::shared_lock lock(mutex_);

    const auto self = self_state_model_.snapshot();
    const auto eligible = goals_model_.eligible(state_.cycle);
    const auto affect = affective_state_model_.state();
    const auto appraisal = affective_learning_model_.appraisal();

    const double valence = std::clamp(affect.valence * appraisal.outcome_weight, -1.0, 1.0);
    const double arousal = std::clamp(affect.arousal * appraisal.novelty_weight, 0.0, 1.0);
    const double affective_uncertainty = std::clamp(
        affect.uncertainty * appraisal.uncertainty_weight, 0.0, 1.0);
    const double tension = std::clamp(
        affect.tension * appraisal.tension_error_weight, 0.0, 1.0);
    const double stability = std::clamp(affect.stability, 0.0, 1.0);

    const auto selected_intent = intent_model_.select_with_affect(
        eligible, threat_state_.score, self.uncertainty,
        valence, arousal, affective_uncertainty, tension, stability,
        state_.cycle);
    const auto strategy = strategy_model_.formulate(
        selected_intent, attention_state_, threat_state_.score, self.uncertainty);

    PlanningContext context = strategy.planning;
    context.valence = valence;
    context.arousal = arousal;
    context.affective_uncertainty = affective_uncertainty;
    context.tension = tension;
    context.stability = stability;

    return planner_.build(actions, horizon, context);
}

std::vector<Decision> Brain::choose_with_developmental_learning(
    const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);
    const auto eligible = goals_model_.eligible(state_.cycle);
    const std::string context = eligible.empty() ? "global" : eligible.front().id;
    const auto self = self_state_model_.snapshot();
    const auto affect = affective_state_model_.state();
    const auto appraisal = affective_learning_model_.appraisal();
    const double valence = std::clamp(affect.valence * appraisal.outcome_weight, -1.0, 1.0);
    const double arousal = std::clamp(affect.arousal * appraisal.novelty_weight, 0.0, 1.0);
    const double affective_uncertainty = std::clamp(affect.uncertainty * appraisal.uncertainty_weight, 0.0, 1.0);
    const double tension = std::clamp(affect.tension * appraisal.tension_error_weight, 0.0, 1.0);
    const double stability = std::clamp(affect.stability, 0.0, 1.0);
    const auto selected_intent = intent_model_.select_with_affect(
        eligible, threat_state_.score, self.uncertainty,
        valence, arousal, affective_uncertainty, tension, stability,
        state_.cycle);
    const auto strategy = strategy_model_.formulate(
        selected_intent, attention_state_, threat_state_.score, self.uncertainty);
    std::vector<CandidateAction> adapted_actions = actions;
    apply_developmental_evidence(adapted_actions, developmental_learning_, context);
    auto planning_context = strategy.planning;
    planning_context.valence = valence;
    planning_context.arousal = arousal;
    planning_context.affective_uncertainty = affective_uncertainty;
    planning_context.tension = tension;
    planning_context.stability = stability;
    // Keep shared plan context grounded in the unmodified candidate set.
    // Otherwise improving one learned action changes plan_expected_value for
    // every candidate and unintentionally raises unrelated actions' scores.
    const auto plan = planner_.build(actions, 1, planning_context);
    DecisionContext context_data;
    context_data.goal_priority = strategy.planning.goal_priority;
    context_data.goal_progress = strategy.planning.goal_progress;
    context_data.plan_expected_value = plan.expected_value;
    context_data.plan_risk = plan.risk;
    context_data.resource_budget = strategy.planning.resource_budget;
    context_data.uncertainty = strategy.planning.uncertainty;
    context_data.threat = strategy.planning.threat;
    context_data.deadline_pressure = strategy.planning.deadline_pressure;
    context_data.valence = valence;
    context_data.arousal = arousal;
    context_data.affective_uncertainty = affective_uncertainty;
    context_data.tension = tension;
    context_data.stability = stability;
    return decision_.decide(adapted_actions, context_data);
}

std::vector<Decision> Brain::choose_with_developmental_learning(
    const std::vector<CandidateAction>& actions, const std::string& context) const {
    std::shared_lock lock(mutex_);
    const auto eligible = goals_model_.eligible(state_.cycle);
    const auto self = self_state_model_.snapshot();
    const auto affect = affective_state_model_.state();
    const auto appraisal = affective_learning_model_.appraisal();
    const double valence = std::clamp(affect.valence * appraisal.outcome_weight, -1.0, 1.0);
    const double arousal = std::clamp(affect.arousal * appraisal.novelty_weight, 0.0, 1.0);
    const double affective_uncertainty = std::clamp(affect.uncertainty * appraisal.uncertainty_weight, 0.0, 1.0);
    const double tension = std::clamp(affect.tension * appraisal.tension_error_weight, 0.0, 1.0);
    const double stability = std::clamp(affect.stability, 0.0, 1.0);
    const auto selected_intent = intent_model_.select_with_affect(
        eligible, threat_state_.score, self.uncertainty,
        valence, arousal, affective_uncertainty, tension, stability,
        state_.cycle);
    const auto strategy = strategy_model_.formulate(
        selected_intent, attention_state_, threat_state_.score, self.uncertainty);
    std::vector<CandidateAction> adapted_actions = actions;
    apply_developmental_evidence(adapted_actions, developmental_learning_, context);
    auto planning_context = strategy.planning;
    planning_context.valence = valence;
    planning_context.arousal = arousal;
    planning_context.affective_uncertainty = affective_uncertainty;
    planning_context.tension = tension;
    planning_context.stability = stability;
    // Keep shared plan context grounded in the unmodified candidate set.
    // Otherwise improving one learned action changes plan_expected_value for
    // every candidate and unintentionally raises unrelated actions' scores.
    const auto plan = planner_.build(actions, 1, planning_context);
    DecisionContext context_data;
    context_data.goal_priority = strategy.planning.goal_priority;
    context_data.goal_progress = strategy.planning.goal_progress;
    context_data.plan_expected_value = plan.expected_value;
    context_data.plan_risk = plan.risk;
    context_data.resource_budget = strategy.planning.resource_budget;
    context_data.uncertainty = strategy.planning.uncertainty;
    context_data.threat = strategy.planning.threat;
    context_data.deadline_pressure = strategy.planning.deadline_pressure;
    context_data.valence = valence;
    context_data.arousal = arousal;
    context_data.affective_uncertainty = affective_uncertainty;
    context_data.tension = tension;
    context_data.stability = stability;
    return decision_.decide(adapted_actions, context_data);
}

} // namespace jarvis::core
