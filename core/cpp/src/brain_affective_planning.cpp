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
    const auto plan = planner_.build(actions, 1, strategy.planning);

    DecisionContext context;
    context.goal_priority = strategy.planning.goal_priority;
    context.goal_progress = strategy.planning.goal_progress;
    context.plan_expected_value = plan.expected_value;
    context.plan_risk = plan.risk;
    context.resource_budget = strategy.planning.resource_budget;
    context.uncertainty = strategy.planning.uncertainty;
    context.threat = strategy.planning.threat;
    context.deadline_pressure = strategy.planning.deadline_pressure;
    context.valence = valence;
    context.arousal = arousal;
    context.affective_uncertainty = affective_uncertainty;
    context.tension = tension;
    context.stability = stability;

    // Learned strategies are action-selection evidence. The context is supplied
    // by the currently selected intent; the action association is learned from
    // prior consequences. No action preference is hardcoded here.
    std::vector<CandidateAction> adapted_actions = actions;
    if (!selected_intent.id.empty()) {
        for (auto& action : adapted_actions) {
            const auto* learned = developmental_learning_.best_strategy(selected_intent.id);
            if (learned != nullptr && learned->action == action.name) {
                action.utility += learned->value * learned->confidence;
            }
        }
    }

    return decision_.decide(adapted_actions, context);
}

} // namespace jarvis::core
