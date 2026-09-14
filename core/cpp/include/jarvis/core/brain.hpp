#pragma once

#include "event.hpp"
#include "memory.hpp"
#include "world_model.hpp"
#include "cognition.hpp"
#include "association_model.hpp"
#include "causal_model.hpp"
#include "decision.hpp"
#include "action_model.hpp"
#include "action_execution.hpp"
#include "adaptation.hpp"
#include "attention.hpp"
#include "threat.hpp"
#include "resilience.hpp"
#include "evolution.hpp"
#include "planning.hpp"
#include "reflection.hpp"
#include "knowledge.hpp"
#include "self_model.hpp"
#include "self_state.hpp"
#include "goals.hpp"
#include "intent.hpp"
#include "strategy.hpp"

#include <cstdint>
#include <filesystem>
#include <functional>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace jarvis::core {

struct BrainState {
    std::uint64_t cycle{0};
    std::uint64_t events_seen{0};
    double novelty{0.0};
    double attention{0.0};
    double threat{0.0};
};

struct BrainSnapshot {
    BrainState state{};
    SelfState self_state{};
    std::vector<Belief> beliefs;
    std::vector<Prediction> predictions;
    std::vector<CausalLink> causal_links;
    std::vector<Goal> goals;
};

class Brain {
public:
    explicit Brain(std::filesystem::path journal_path = "data/brain/continuity.bin");
    Observation observe(Event event);
    double learn(const Evidence& evidence);
    std::vector<Belief> beliefs() const;
    Prediction predict(std::string key, Scalar value, double confidence);
    bool resolve_prediction(const std::string& key, const Scalar& actual);
    std::vector<std::pair<std::string, Scalar>> simulate(const std::vector<Belief>& assumptions) const;
    SimulationResult simulate(const std::vector<Belief>& assumptions, std::size_t horizon) const;
    std::vector<Association> associations() const;
    std::vector<Association> associated_with(const std::string& key, double minimum_strength = 0.5) const;
    std::vector<CausalLink> causal_links() const;

    std::vector<Decision> choose(const std::vector<CandidateAction>& actions) const;

    Plan plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const;
    Plan plan(const std::vector<CandidateAction>& actions, std::size_t horizon,
              const PlanningContext& context) const;
    std::vector<ActionAssessment> assess_actions(const std::vector<Decision>& decisions,
                                                  ActionConstraints constraints = {}) const;
    ActionExecutionResult execute_action(const ActionAssessment& assessment,
                                          std::function<bool(const CandidateAction&)> execute,
                                          std::function<bool(const CandidateAction&)> verify,
                                          std::function<bool(const CandidateAction&)> rollback = {}) {
        ActionExecutionRequest request{assessment, std::move(execute), std::move(verify), std::move(rollback)};
        const auto result = ActionExecutor{}.run(request);
        const double reliability = result.status == ActionExecutionStatus::verified ? 1.0 :
                                   result.status == ActionExecutionStatus::rolled_back ? 0.25 : 0.5;
        if (!result.action.name.empty()) {
            learn(Evidence{"action_executor", "action." + result.action.name,
                           std::string(result.reason), reliability});
        }
        return result;
    }
    Reflection reflect() const;
    const KnowledgeMetric* knowledge_source(const std::string& source) const noexcept;
    const AdaptiveMetric* learning_metric(const std::string& key) const noexcept;
    double learning_confidence(const std::string& key) const noexcept;
    AttentionSignal attention() const;
    ThreatAssessment threat() const;
    Intent intent() const {
        std::shared_lock lock(mutex_);
        return intent_model_.select(goals_model_.eligible(state_.cycle), threat_state_.score,
                                    self_state_model_.snapshot().uncertainty, state_.cycle);
    }
    StrategyContext strategy() const {
        std::shared_lock lock(mutex_);
        const auto self = self_state_model_.snapshot();
        const auto current_intent = intent_model_.select(goals_model_.eligible(state_.cycle),
                                                         threat_state_.score, self.uncertainty,
                                                         state_.cycle);
        return strategy_model_.formulate(current_intent, attention_state_,
                                         threat_state_.score, self.uncertainty);
    }
    std::vector<RecoveryPlan> recovery_options() const;
    bool isolate(const std::string& component);
    bool recover(const std::string& component, double restored_health);
    void register_evolution_parameter(std::string key, double initial);
    void observe_evolution_fitness(const std::string& key, double fitness);
    std::vector<EvolutionProposal> evolution_options() const;
    bool adopt_evolution(const EvolutionProposal& proposal);
    bool rollback_evolution(const std::string& key);
    void observe_capability(std::string name, double availability, double performance);
    bool isolate_capability(const std::string& name);
    bool restore_capability(const std::string& name, double availability, double performance);

    bool create_goal(Goal goal);
    bool activate_goal(const std::string& id);
    bool update_goal_progress(const std::string& id, double progress);
    bool complete_goal(const std::string& id);
    bool abandon_goal(const std::string& id);
    bool set_goal_priority(const std::string& id, double priority);
    const Goal* goal(const std::string& id) const noexcept;
    std::vector<Goal> goals() const;
    std::vector<Goal> eligible_goals() const;

    const DecisionEngine& decision_engine() const noexcept { return decision_; }
    const ActionModel& action_model() const noexcept { return action_model_; }
    const SelfModel& self_model() const noexcept { return self_model_; }
    const SelfStateModel& self_state_model() const noexcept { return self_state_model_; }
    const WorldModel& world() const noexcept { return world_; }
    const Memory& memory() const noexcept { return memory_; }
    BrainSnapshot snapshot() const;
    BrainState state() const;

private:
    static double compute_novelty(const Event& event, const std::vector<Event>& history);
    void replay(const Event& event);
    void sync_self_state();
    bool append_goal_event(const Event& event);

    mutable std::shared_mutex mutex_;
    BrainState state_{};
    WorldModel world_{};
    Memory memory_;
    std::unordered_map<std::string, Belief> beliefs_;
    std::unordered_map<std::string, Prediction> predictions_;
    AssociationModel association_{};
    CausalModel causal_{};
    DecisionEngine decision_{};
    ActionModel action_model_{};
    AdaptationModel adaptation_{};
    AttentionModel attention_model_{};
    ThreatModel threat_model_{};
    ResilienceModel resilience_{};
    EvolutionModel evolution_{};
    Planner planner_{};
    ReflectionModel reflection_model_{};
    KnowledgeModel knowledge_{};
    SelfModel self_model_{};
    SelfStateModel self_state_model_{};
    GoalModel goals_model_{};
    IntentModel intent_model_{};
    StrategyModel strategy_model_{};
    AttentionSignal attention_state_{};
    ThreatAssessment threat_state_{};
};

} // namespace jarvis::core
