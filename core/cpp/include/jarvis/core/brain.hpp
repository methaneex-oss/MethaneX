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
#include "capability_evaluator.hpp"
#include "capability_execution.hpp"
#include "adaptation.hpp"
#include "learning_loop.hpp"
#include "attention.hpp"
#include "threat.hpp"
#include "resilience.hpp"
#include "evolution.hpp"
#include "evolution_experiment.hpp"
#include "evolution_controller.hpp"
#include "planning.hpp"
#include "reflection.hpp"
#include "knowledge.hpp"
#include "self_model.hpp"
#include "self_state.hpp"
#include "self_testing.hpp"
#include "goals.hpp"
#include "cognitive_goal_outcome.hpp"
#include "intent.hpp"
#include "strategy.hpp"
#include "developmental_learning.hpp"
#include "affective_state.hpp"
#include "affective_learning.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
namespace jarvis::core {
struct BrainState { std::uint64_t cycle{0}; std::uint64_t events_seen{0}; double novelty{0.0}; double attention{0.0}; double threat{0.0}; };
struct BrainSnapshot { BrainState state{}; SelfState self_state{}; AffectiveState affective_state{}; std::vector<Belief> beliefs; std::vector<Prediction> predictions; std::vector<CausalLink> causal_links; std::vector<Goal> goals; };
class Brain {
public:
 explicit Brain(std::filesystem::path journal_path = "data/brain/continuity.bin");
 Observation observe(Event event); double learn(const Evidence& evidence);
 LearningCycle learn_from_prediction(const std::string& key, const Scalar& actual, double fitness);
 std::vector<Belief> beliefs() const; Prediction predict(std::string key, Scalar value, double confidence); Prediction predict_with_context(std::string key, Scalar value, double confidence, double minimum_strength = 0.5, std::size_t minimum_shared_contexts = 2); bool resolve_prediction(const std::string& key, const Scalar& actual); bool resolve_prediction(std::uint64_t prediction_sequence, const Scalar& actual);
 bool assimilate_goal_outcome(const GoalOutcomeEvidence& evidence);
 std::vector<std::pair<std::string, Scalar>> simulate(const std::vector<Belief>& assumptions) const; SimulationResult simulate(const std::vector<Belief>& assumptions, std::size_t horizon) const;
 std::vector<Association> associations() const; std::vector<Association> associated_with(const std::string& key, double minimum_strength = 0.5) const; std::vector<AssociationInference> contextual_associations(const std::string& key, std::size_t max_hops = 2, double minimum_strength = 0.25) const; std::vector<ConceptCandidate> concept_candidates(double minimum_strength = 0.5, std::size_t minimum_shared_contexts = 2) const; std::vector<ConceptCandidate> contextual_concepts(const std::string& key, double minimum_strength = 0.5, std::size_t minimum_shared_contexts = 2) const; std::vector<ConceptMatch> generalized_concepts(const std::string& key, double minimum_strength = 0.5, std::size_t minimum_shared_contexts = 2, double minimum_similarity = 0.5) const;
 std::vector<CausalLink> causal_links() const; std::vector<Decision> choose(const std::vector<CandidateAction>& actions) const; std::vector<Decision> choose_with_affect(const std::vector<CandidateAction>& actions) const; std::vector<Decision> choose_with_developmental_learning(const std::vector<CandidateAction>& actions) const; std::vector<Decision> choose_with_developmental_learning(const std::vector<CandidateAction>& actions, const std::string& context) const;
 ActionExecutionResult execute_action(const ActionAssessment& assessment,
                                      std::function<bool(const CandidateAction&)> execute,
                                      std::function<bool(const CandidateAction&)> verify,
                                      std::function<bool(const CandidateAction&)> rollback = {},
                                      std::function<double(const CandidateAction&)> observe_consequence = {},
                                      ActionAuthorizationContext authorization = {});
 Plan plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const; Plan plan(const std::vector<CandidateAction>& actions, std::size_t horizon, const PlanningContext& context) const; Plan plan_with_affect(const std::vector<CandidateAction>& actions, std::size_t horizon) const; std::vector<ActionAssessment> assess_actions(const std::vector<Decision>& decisions, ActionConstraints constraints = {}) const; std::vector<CapabilityCandidate> evaluate_capabilities(const std::vector<CapabilityDescriptor>& capabilities, CapabilityConstraints constraints = {}) const; CapabilityExecutionResult execute_capability(const CapabilityDescriptor& capability, std::string input, std::vector<std::string> granted_permissions = {}, double maximum_risk = 1.0, CapabilityProvider provider = {});
 Reflection reflect() const; const KnowledgeMetric* knowledge_source(const std::string& source) const noexcept; const AdaptiveMetric* learning_metric(const std::string& key) const noexcept; double learning_confidence(const std::string& key) const noexcept;
 std::vector<LearnedAssociation> developmental_associations() const; std::vector<LearnedStrategy> developmental_strategies() const; const LearnedStrategy* developmental_best_strategy(const std::string& context) const noexcept; const LearnedStrategy* developmental_best_related_strategy(const std::string& context, double minimum_similarity = 0.5) const noexcept; const StrategyParameter* evolution_parameter(const std::string& key) const noexcept; AttentionSignal attention() const; AttentionPolicy attention_policy() const; ThreatAssessment threat() const; Intent intent() const; StrategyContext strategy() const; AffectiveState affective_state() const; AffectiveAppraisal affective_appraisal() const; AffectiveCalibration affective_calibration() const { std::shared_lock lock(mutex_); return affective_learning_model_.calibration(); } std::uint64_t affective_learning_updates() const;
 std::vector<RecoveryPlan> recovery_options() const; bool isolate(const std::string& component); bool recover(const std::string& component, double restored_health); SelfTestReport self_test() const; SelfHealingResult self_heal(const std::string& component, std::function<bool(const std::string&)> repair, std::function<bool(const std::string&)> verify);
 bool register_evolution_parameter(std::string key, double initial); void observe_evolution_fitness(const std::string& key, double fitness); std::vector<EvolutionProposal> evolution_options() const; bool adopt_evolution(const EvolutionProposal& proposal); bool rollback_evolution(const std::string& key); bool record_evolution_evaluation(EvolutionExperiment& experiment); bool adopt_evolution_experiment(EvolutionExperiment& experiment); CanaryDecision observe_evolution_canary(const std::string& parameter_key, const std::string& experiment_id, CanaryObservation observation); std::vector<EvolutionHistoryRecord> evolution_history() const;
 void observe_capability(std::string name, double availability, double performance); bool isolate_capability(const std::string& name); bool restore_capability(const std::string& name, double availability, double performance); bool create_goal(Goal goal); bool activate_goal(const std::string& id); bool update_goal_progress(const std::string& id, double progress); bool complete_goal(const std::string& id); bool abandon_goal(const std::string& id); bool set_goal_priority(const std::string& id, double priority); const Goal* goal(const std::string& id) const noexcept; std::vector<Goal> goals() const; std::vector<Goal> eligible_goals() const;
 const DecisionEngine& decision_engine() const noexcept { return decision_; } const ActionModel& action_model() const noexcept { return action_model_; } const SelfModel& self_model() const noexcept { return self_model_; } const SelfStateModel& self_state_model() const noexcept { return self_state_model_; } const WorldModel& world() const noexcept { return world_; } const Memory& memory() const noexcept { return memory_; } BrainSnapshot snapshot() const; BrainState state() const;
private: void consolidate_experience(const Event& event, double error = 0.0); void process_affective_experience(const Event& event); static double compute_novelty(const Event& event, const std::vector<Event>& history); void replay(const Event& event); void sync_self_state(); bool append_goal_event(const Event& event); Prediction* find_latest_unresolved_prediction(const std::string& key) noexcept; const Prediction* find_latest_unresolved_prediction(const std::string& key) const noexcept; Prediction* find_prediction(std::uint64_t sequence) noexcept; const Prediction* find_prediction(std::uint64_t sequence) const noexcept;
 mutable std::shared_mutex mutex_; BrainState state_{}; WorldModel world_{}; Memory memory_; std::unordered_map<std::string, Belief> beliefs_; std::unordered_set<std::uint64_t> processed_derived_learning_sources_;
 std::unordered_set<std::uint64_t> processed_affective_learning_sources_; std::vector<Prediction> predictions_; AssociationModel association_{}; CausalModel causal_{}; DecisionEngine decision_{}; ActionModel action_model_{}; AdaptationModel adaptation_{}; LearningLoop learning_loop_{}; AttentionModel attention_model_{}; ThreatModel threat_model_{}; ResilienceModel resilience_{}; EvolutionModel evolution_{}; EvolutionHistory evolution_history_{}; EvolutionController evolution_controller_; Planner planner_{}; ReflectionModel reflection_model_{}; KnowledgeModel knowledge_{}; SelfModel self_model_{}; SelfStateModel self_state_model_{}; SelfTestingModel self_testing_model_{}; GoalModel goals_model_{}; IntentModel intent_model_{}; StrategyModel strategy_model_{}; DevelopmentalLearning developmental_learning_{}; AffectiveStateModel affective_state_model_{}; AffectiveLearningModel affective_learning_model_{}; AttentionSignal attention_state_{}; ThreatAssessment threat_state_{};
};
} // namespace jarvis::core