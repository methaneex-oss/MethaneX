#include "jarvis/core/brain.hpp"

#include <algorithm>

namespace jarvis::core {

Plan Brain::plan_with_affect(const std::vector<CandidateAction>& actions, std::size_t horizon) const {
    std::shared_lock lock(mutex_);

    const auto self = self_state_model_.snapshot();
    const auto eligible = goals_model_.eligible(state_.cycle);
    const auto selected_intent = intent_model_.select(
        eligible, threat_state_.score, self.uncertainty, state_.cycle);
    const auto strategy = strategy_model_.formulate(
        selected_intent, attention_state_, threat_state_.score, self.uncertainty);
    const auto affect = affective_state_model_.state();
    const auto appraisal = affective_learning_model_.appraisal();

    PlanningContext context = strategy.planning;
    context.valence = std::clamp(affect.valence * appraisal.outcome_weight, -1.0, 1.0);
    context.arousal = std::clamp(affect.arousal * appraisal.novelty_weight, 0.0, 1.0);
    context.affective_uncertainty = std::clamp(
        affect.uncertainty * appraisal.uncertainty_weight, 0.0, 1.0);
    context.tension = std::clamp(
        affect.tension * appraisal.tension_error_weight, 0.0, 1.0);
    context.stability = std::clamp(affect.stability, 0.0, 1.0);

    return planner_.build(actions, horizon, context);
}

} // namespace jarvis::core
