#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

struct AffectiveReplay {
    AffectiveStateModel state;
    AffectiveLearningModel learning;

    void apply(const Event& event) noexcept {
        AffectiveSignal signal{};
        double utility = 0.0;
        bool learn = false;

        if (event.kind == "prediction_outcome") {
            const double error = std::clamp(std::abs(event.data.contains("error") ?
                (std::get_if<double>(&event.data.at("error")) ? *std::get_if<double>(&event.data.at("error")) : 0.0) : 0.0), 0.0, 1.0);
            signal.outcome = 1.0 - 2.0 * error;
            signal.prediction_error = error;
            signal.novelty = std::clamp(event.data.contains("novelty") && std::get_if<double>(&event.data.at("novelty")) ? *std::get_if<double>(&event.data.at("novelty")) : 0.0, 0.0, 1.0);
            signal.salience = std::clamp(event.data.contains("salience") && std::get_if<double>(&event.data.at("salience")) ? *std::get_if<double>(&event.data.at("salience")) : 0.5, 0.0, 1.0);
            signal.confidence = std::clamp(1.0 - error, 0.0, 1.0);
            utility = signal.outcome;
            learn = true;
        } else if (event.kind == "action_outcome") {
            const double reliability = std::clamp(event.data.contains("reliability") && std::get_if<double>(&event.data.at("reliability")) ? *std::get_if<double>(&event.data.at("reliability")) : 0.5, 0.0, 1.0);
            signal.outcome = 2.0 * reliability - 1.0;
            signal.prediction_error = 1.0 - reliability;
            signal.novelty = std::clamp(event.data.contains("novelty") && std::get_if<double>(&event.data.at("novelty")) ? *std::get_if<double>(&event.data.at("novelty")) : 0.0, 0.0, 1.0);
            signal.salience = std::clamp(event.data.contains("salience") && std::get_if<double>(&event.data.at("salience")) ? *std::get_if<double>(&event.data.at("salience")) : 0.5, 0.0, 1.0);
            signal.confidence = reliability;
            utility = signal.outcome;
            learn = true;
        } else if (event.kind == "goal_progress") {
            const double progress = std::clamp(event.data.contains("progress") && std::get_if<double>(&event.data.at("progress")) ? *std::get_if<double>(&event.data.at("progress")) : 0.0, 0.0, 1.0);
            signal.outcome = 2.0 * progress - 1.0;
            signal.salience = std::clamp(event.data.contains("confidence") && std::get_if<double>(&event.data.at("confidence")) ? *std::get_if<double>(&event.data.at("confidence")) : 0.5, 0.0, 1.0);
            signal.confidence = signal.salience;
            utility = signal.outcome;
            learn = true;
        } else if (event.kind == "observation" || event.kind == "learning") {
            signal.salience = event.kind == "learning" ? 0.7 : 0.4;
            signal.novelty = 0.2;
            signal.confidence = event.kind == "learning" ? 0.7 : 0.5;
        } else {
            return;
        }

        const auto before = state.state();
        const auto after = state.update(signal);
        if (learn) learning.learn(signal, before, after, utility);
    }
};

AffectiveReplay replay_affect(const Memory& memory) {
    AffectiveReplay replay;
    for (const auto& event : memory.all()) replay.apply(event);
    return replay;
}

} // namespace

std::vector<Decision> Brain::choose_with_affect(const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);
    const auto self = self_state_model_.snapshot();
    const auto eligible = goals_model_.eligible(state_.cycle);
    const auto selected_intent = intent_model_.select(eligible, threat_state_.score, self.uncertainty, state_.cycle);
    const auto strategy = strategy_model_.formulate(selected_intent, attention_state_, threat_state_.score, self.uncertainty);
    const auto plan = planner_.build(actions, 1, strategy.planning);

    const auto replay = replay_affect(memory_);
    const auto affect = replay.state.state();

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
    context.affective_uncertainty = affect.uncertainty;
    context.tension = affect.tension;
    context.stability = affect.stability;
    return decision_.decide(actions, context);
}

} // namespace jarvis::core
