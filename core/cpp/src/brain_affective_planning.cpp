#include "jarvis/core/brain.hpp"

#include <algorithm>

namespace jarvis::core {

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
    const auto exact = developmental_learning_.best_strategy(context);
    const auto learned = exact != nullptr ? exact : developmental_learning_.best_related_strategy(context);
    std::vector<CandidateAction> adapted_actions = actions;
    if (learned != nullptr) {
        const double similarity = exact == learned ? 1.0 : 0.5;
        for (auto& action : adapted_actions) {
            if (learned->action == action.name) {
                const double influence = std::clamp(learned->value * learned->confidence * similarity, -1.0, 1.0);
                action.utility += influence;
            }
        }
    }
    auto planning_context = strategy.planning;
    planning_context.valence = valence;
    planning_context.arousal = arousal;
    planning_context.affective_uncertainty = affective_uncertainty;
    planning_context.tension = tension;
    planning_context.stability = stability;
    const auto plan = planner_.build(adapted_actions, 1, planning_context);
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
    const auto exact = developmental_learning_.best_strategy(context);
    const auto learned = exact != nullptr ? exact : developmental_learning_.best_related_strategy(context);
    std::vector<CandidateAction> adapted_actions = actions;
    if (learned != nullptr) {
        const double similarity = exact == learned ? 1.0 : 0.5;
        for (auto& action : adapted_actions) {
            if (learned->action == action.name) {
                const double influence = std::clamp(learned->value * learned->confidence * similarity, -1.0, 1.0);
                action.utility += influence;
            }
        }
    }
    auto planning_context = strategy.planning;
    planning_context.valence = valence;
    planning_context.arousal = arousal;
    planning_context.affective_uncertainty = affective_uncertainty;
    planning_context.tension = tension;
    planning_context.stability = stability;
    const auto plan = planner_.build(adapted_actions, 1, planning_context);
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
