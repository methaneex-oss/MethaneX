#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double attribute_value(const Attributes& data, const char* key, double fallback) noexcept {
    const auto it = data.find(key);
    if (it == data.end()) return fallback;
    if (const auto* value = std::get_if<double>(&it->second)) return *value;
    if (const auto* value = std::get_if<std::int64_t>(&it->second)) return static_cast<double>(*value);
    return fallback;
}

double unit(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0); }
double signed_unit(double value) noexcept { return std::clamp(std::isfinite(value) ? value : 0.0, -1.0, 1.0); }

double goal_outcome(const Event& event) noexcept {
    if (event.kind == "goal_complete") return 1.0;
    if (event.kind == "goal_abandon") return -1.0;
    if (event.kind == "goal_progress") return 2.0 * unit(attribute_value(event.data, "progress", 0.0)) - 1.0;
    return 0.0;
}

AffectiveSignal signal_from_event(const Event& event) noexcept {
    const double error = unit(attribute_value(event.data, "error", 0.0));
    const double novelty = unit(attribute_value(event.data, "novelty", 0.0));
    const double salience = unit(attribute_value(event.data, "salience", 0.0));
    const double uncertainty = unit(attribute_value(event.data, "uncertainty", error));
    const double confidence = unit(attribute_value(event.data, "confidence", 1.0 - error));
    double outcome = goal_outcome(event);
    if (event.data.find("outcome") != event.data.end()) outcome = signed_unit(attribute_value(event.data, "outcome", outcome));
    else if (event.data.find("utility") != event.data.end()) outcome = signed_unit(attribute_value(event.data, "utility", outcome));
    else if (event.data.find("reliability") != event.data.end()) outcome = 2.0 * confidence - 1.0;
    else if (event.data.find("error") != event.data.end()) outcome = 1.0 - 2.0 * error;
    return {outcome, error, novelty, salience, uncertainty, confidence};
}

bool has_outcome_evidence(const Event& event) noexcept {
    return event.kind == "prediction_outcome" || event.kind == "action_outcome" ||
           event.kind == "goal_complete" || event.kind == "goal_abandon" || event.kind == "goal_progress" ||
           event.data.find("outcome") != event.data.end() ||
           event.data.find("utility") != event.data.end() ||
           event.data.find("reliability") != event.data.end();
}

double observed_utility(const Event& event, const AffectiveSignal& signal) noexcept {
    if (event.kind == "prediction_outcome") return 1.0 - 2.0 * signal.prediction_error;
    if (event.kind == "action_outcome") return 2.0 * signal.confidence - 1.0;
    if (event.kind == "goal_complete" || event.kind == "goal_abandon" || event.kind == "goal_progress") return signal.outcome;
    return signed_unit(attribute_value(event.data, "utility", signal.outcome));
}

struct ReconstructedAffect {
    AffectiveState state{};
    AffectiveAppraisal appraisal{};
    std::uint64_t updates{0};
};

ReconstructedAffect reconstruct_affect(const Memory& memory) {
    AffectiveStateModel affect_model;
    AffectiveLearningModel appraisal_model;
    for (const auto& event : memory.all()) {
        const auto signal = signal_from_event(event);
        const auto before = affect_model.state();
        const auto after = affect_model.update(signal);
        if (has_outcome_evidence(event)) appraisal_model.learn(signal, before, after, observed_utility(event, signal));
    }
    return {affect_model.state(), appraisal_model.appraisal(), appraisal_model.updates()};
}

} // namespace

std::vector<Decision> Brain::choose_with_affect(const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);
    const auto reconstructed = reconstruct_affect(memory_);
    const auto& affect = reconstructed.state;
    const auto& appraisal = reconstructed.appraisal;

    const auto self = self_state_model_.snapshot();
    const auto eligible = goals_model_.eligible(state_.cycle);
    const auto selected_intent = intent_model_.select(eligible, threat_state_.score, self.uncertainty, state_.cycle);
    const auto strategy = strategy_model_.formulate(selected_intent, attention_state_, threat_state_.score, self.uncertainty);
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
    context.valence = affect.valence;
    context.arousal = affect.arousal;
    context.affective_uncertainty = std::clamp(affect.uncertainty * (0.75 + 0.25 * appraisal.uncertainty_weight), 0.0, 1.0);
    context.tension = std::clamp(affect.tension * (0.75 + 0.25 * appraisal.tension_error_weight), 0.0, 1.0);
    context.stability = affect.stability;
    return decision_.decide(actions, context);
}

AffectiveState Brain::affective_state() const {
    std::shared_lock lock(mutex_);
    return reconstruct_affect(memory_).state;
}

AffectiveAppraisal Brain::affective_appraisal() const {
    std::shared_lock lock(mutex_);
    return reconstruct_affect(memory_).appraisal;
}

std::uint64_t Brain::affective_learning_updates() const {
    std::shared_lock lock(mutex_);
    return reconstruct_affect(memory_).updates;
}

} // namespace jarvis::core
