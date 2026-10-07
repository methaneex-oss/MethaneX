#include "jarvis/core/brain.hpp"

namespace jarvis::core {
namespace {
std::string join_ids(const std::vector<std::string>& ids) { std::string out; for (std::size_t i = 0; i < ids.size(); ++i) { if (i != 0) out.push_back('\x1f'); out += ids[i]; } return out; }
}

std::vector<Belief> Brain::beliefs() const { std::shared_lock lock(mutex_); std::vector<Belief> result; result.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) result.push_back(belief); return result; }
Prediction Brain::predict(std::string key, Scalar value, double confidence) { std::unique_lock lock(mutex_); if (key.empty()) return Prediction{}; Prediction prediction{std::move(key), std::move(value), std::clamp(confidence, 0.0, 1.0), 0, false, 0.0}; Event event{0, 0, "brain", "prediction", {{"key", prediction.key}, {"value", prediction.predicted}, {"confidence", prediction.confidence}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return Prediction{}; replay(event); ++state_.events_seen; state_.cycle = event.sequence; consolidate_experience(event); const auto* stored = find_prediction(event.sequence); sync_self_state(); return stored == nullptr ? Prediction{} : *stored; }
bool Brain::resolve_prediction(const std::string& key, const Scalar& actual) { std::uint64_t prediction_sequence = 0; { std::shared_lock lock(mutex_); const auto* prediction = find_latest_unresolved_prediction(key); if (prediction == nullptr) return false; prediction_sequence = prediction->created_sequence; } return resolve_prediction(prediction_sequence, actual); }
bool Brain::resolve_prediction(std::uint64_t prediction_sequence, const Scalar& actual) { std::unique_lock lock(mutex_); const auto* prediction = find_prediction(prediction_sequence); if (prediction == nullptr || prediction->resolved || prediction->key.empty()) return false; double error = prediction->predicted == actual ? 0.0 : 1.0; if (const auto predicted = std::get_if<double>(&prediction->predicted)) if (const auto observed = std::get_if<double>(&actual)) error = std::clamp(std::abs(*observed - *predicted), 0.0, 1.0); Event event{0, 0, "brain", "prediction_outcome", {{"key", prediction->key}, {"prediction_sequence", static_cast<std::int64_t>(prediction_sequence)}, {"actual", actual}, {"error", error}, {"salience", attention_state_.salience}, {"novelty", state_.novelty}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; consolidate_experience(event, error); sync_self_state(); return error == 0.0; }
const StrategyParameter* Brain::evolution_parameter(const std::string& key) const noexcept { std::shared_lock lock(mutex_); return evolution_.parameter(key); }
const KnowledgeMetric* Brain::knowledge_source(const std::string& source) const noexcept { std::shared_lock lock(mutex_); return knowledge_.source_metric(source); }
const AdaptiveMetric* Brain::learning_metric(const std::string& key) const noexcept { std::shared_lock lock(mutex_); return adaptation_.metric(key); }
double Brain::learning_confidence(const std::string& key) const noexcept { std::shared_lock lock(mutex_); return std::clamp(adaptation_.confidence(key), 0.0, 1.0); }
AffectiveState Brain::affective_state() const { std::shared_lock lock(mutex_); return affective_state_model_.state(); }
AffectiveAppraisal Brain::affective_appraisal() const { std::shared_lock lock(mutex_); return affective_learning_model_.appraisal(); }
std::uint64_t Brain::affective_learning_updates() const { std::shared_lock lock(mutex_); return affective_learning_model_.updates(); }
std::vector<LearnedAssociation> Brain::developmental_associations() const { std::shared_lock lock(mutex_); return developmental_learning_.associations(); }
std::vector<LearnedStrategy> Brain::developmental_strategies() const { std::shared_lock lock(mutex_); return developmental_learning_.strategies(); }
const LearnedStrategy* Brain::developmental_best_strategy(const std::string& context) const noexcept { std::shared_lock lock(mutex_); return developmental_learning_.best_strategy(context); }
const LearnedStrategy* Brain::developmental_best_related_strategy(const std::string& context, double minimum_similarity) const noexcept { std::shared_lock lock(mutex_); return developmental_learning_.best_related_strategy(context, minimum_similarity); }
std::vector<std::pair<std::string, Scalar>> Brain::simulate(const std::vector<Belief>& assumptions) const { std::shared_lock lock(mutex_); return causal_.predict(assumptions); }
SimulationResult Brain::simulate(const std::vector<Belief>& assumptions, std::size_t horizon) const { std::shared_lock lock(mutex_); return causal_.simulate(assumptions, horizon); }
std::vector<Association> Brain::associations() const { std::shared_lock lock(mutex_); return association_.all(); }
std::vector<Association> Brain::associated_with(const std::string& key, double minimum_strength) const { std::shared_lock lock(mutex_); return association_.related(key, minimum_strength); }
std::vector<AssociationInference> Brain::contextual_associations(const std::string& key, std::size_t max_hops, double minimum_strength) const { std::shared_lock lock(mutex_); return association_.contextual(key, max_hops, minimum_strength); }
std::vector<ConceptCandidate> Brain::concept_candidates(double minimum_strength, std::size_t minimum_shared_contexts) const { std::shared_lock lock(mutex_); return association_.concept_candidates(minimum_strength, minimum_shared_contexts); }
std::vector<ConceptCandidate> Brain::contextual_concepts(const std::string& key, double minimum_strength, std::size_t minimum_shared_contexts) const { std::shared_lock lock(mutex_); const auto matches = association_.generalized_concepts(key, minimum_strength, minimum_shared_contexts); std::vector<ConceptCandidate> result; result.reserve(matches.size()); for (const auto& match : matches) result.push_back(ConceptCandidate{match.concept_members, match.similarity, static_cast<std::uint64_t>(match.matched_contexts.size()), 0}); return result; }
std::vector<ConceptMatch> Brain::generalized_concepts(const std::string& key, double minimum_strength, std::size_t minimum_shared_contexts, double minimum_similarity) const { std::shared_lock lock(mutex_); return association_.generalized_concepts(key, minimum_strength, minimum_shared_contexts, minimum_similarity); }
std::vector<CausalLink> Brain::causal_links() const { std::shared_lock lock(mutex_); return causal_.links(); }
Prediction* Brain::find_latest_unresolved_prediction(const std::string& key) noexcept { for (auto it = predictions_.rbegin(); it != predictions_.rend(); ++it) if (!it->resolved && it->key == key) return &*it; return nullptr; }
const Prediction* Brain::find_latest_unresolved_prediction(const std::string& key) const noexcept { for (auto it = predictions_.rbegin(); it != predictions_.rend(); ++it) if (!it->resolved && it->key == key) return &*it; return nullptr; }
Prediction* Brain::find_prediction(std::uint64_t sequence) noexcept { for (auto& prediction : predictions_) if (prediction.created_sequence == sequence) return &prediction; return nullptr; }
const Prediction* Brain::find_prediction(std::uint64_t sequence) const noexcept { for (const auto& prediction : predictions_) if (prediction.created_sequence == sequence) return &prediction; return nullptr; }
Intent Brain::intent() const { std::shared_lock lock(mutex_); const auto self = self_state_model_.snapshot(); return intent_model_.select(goals_model_.eligible(state_.cycle), threat_state_.score, self.uncertainty, state_.cycle); }
StrategyContext Brain::strategy() const { std::shared_lock lock(mutex_); const auto self = self_state_model_.snapshot(); const auto selected_intent = intent_model_.select(goals_model_.eligible(state_.cycle), threat_state_.score, self.uncertainty, state_.cycle); return strategy_model_.formulate(selected_intent, attention_state_, threat_state_.score, self.uncertainty); }
bool Brain::assimilate_goal_outcome(const GoalOutcomeEvidence& raw_evidence) {
    GoalOutcomeEvidence evidence = raw_evidence;
    evidence.normalize();
    if (evidence.goal_id.empty()) return false;
    std::unique_lock lock(mutex_);
    const auto* current = goals_model_.get(evidence.goal_id);
    if (current == nullptr) return false;
    evidence.progress_before = std::clamp(current->progress, 0.0, 1.0);
    evidence.normalize();
    evidence.completed = evidence.completed || evidence.progress_after >= 1.0;
    evidence.normalize();

    Event event;
    if (evidence.completed) {
        event = Event{0, 0, "brain", "goal_complete",
                      {{"id", evidence.goal_id},
                       {"confidence", evidence.confidence},
                       {"delta", evidence.delta},
                       {"sequence", static_cast<std::int64_t>(evidence.sequence)}}};
    } else {
        event = Event{0, 0, "brain", "goal_progress",
                      {{"id", evidence.goal_id},
                       {"progress", evidence.progress_after},
                       {"confidence", evidence.confidence},
                       {"delta", evidence.delta},
                       {"sequence", static_cast<std::int64_t>(evidence.sequence)}}};
    }
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return false;
    replay(event);
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}
std::vector<Decision> Brain::choose(const std::vector<CandidateAction>& actions) const { std::shared_lock lock(mutex_); const auto self = self_state_model_.snapshot(); const auto eligible = goals_model_.eligible(state_.cycle); const auto selected_intent = intent_model_.select(eligible, threat_state_.score, self.uncertainty, state_.cycle); const auto strategy = strategy_model_.formulate(selected_intent, attention_state_, threat_state_.score, self.uncertainty); const auto learned = developmental_learning_.best_strategy(eligible.empty() ? "global" : eligible.front().id); std::vector<CandidateAction> developmentally_weighted = actions; if (learned != nullptr) { for (auto& candidate : developmentally_weighted) { if (candidate.name == learned->action) { const double influence = std::clamp(learned->value * learned->confidence, -1.0, 1.0); candidate.utility += 0.25 * influence; candidate.expected_value += 0.25 * influence; } } } const auto plan = planner_.build(developmentally_weighted, 1, strategy.planning); DecisionContext context; context.goal_priority = strategy.planning.goal_priority; context.goal_progress = strategy.planning.goal_progress; context.plan_expected_value = plan.expected_value; context.plan_risk = plan.risk; context.resource_budget = strategy.planning.resource_budget; context.uncertainty = strategy.planning.uncertainty; context.threat = strategy.planning.threat; context.deadline_pressure = strategy.planning.deadline_pressure; return decision_.decide(developmentally_weighted, context); }
std::vector<Decision> Brain::choose_with_affect(const std::vector<CandidateAction>& actions) const { std::shared_lock lock(mutex_); const auto self = self_state_model_.snapshot(); const auto eligible = goals_model_.eligible(state_.cycle); const auto selected_intent = intent_model_.select(eligible, threat_state_.score, self.uncertainty, state_.cycle); const auto strategy = strategy_model_.formulate(selected_intent, attention_state_, threat_state_.score, self.uncertainty); const auto learned = developmental_learning_.best_strategy(eligible.empty() ? "global" : eligible.front().id); std::vector<CandidateAction> developmentally_weighted = actions; if (learned != nullptr) { for (auto& candidate : developmentally_weighted) { if (candidate.name == learned->action) { const double influence = std::clamp(learned->value * learned->confidence, -1.0, 1.0); candidate.utility += 0.25 * influence; candidate.expected_value += 0.25 * influence; } } } const auto plan = planner_.build(developmentally_weighted, 1, strategy.planning); const auto affect = affective_state_model_.state(); const auto appraisal = affective_learning_model_.appraisal(); DecisionContext context; context.goal_priority = strategy.planning.goal_priority; context.goal_progress = strategy.planning.goal_progress; context.plan_expected_value = plan.expected_value; context.plan_risk = plan.risk; context.resource_budget = strategy.planning.resource_budget; context.uncertainty = strategy.planning.uncertainty; context.threat = strategy.planning.threat; context.deadline_pressure = strategy.planning.deadline_pressure; context.valence = affect.valence * appraisal.outcome_weight; context.arousal = affect.arousal * appraisal.novelty_weight; context.affective_uncertainty = affect.uncertainty * appraisal.uncertainty_weight; context.tension = affect.tension * appraisal.tension_error_weight; context.stability = affect.stability; return decision_.decide(developmentally_weighted, context); }
std::vector<ActionAssessment> Brain::assess_actions(const std::vector<Decision>& decisions, ActionConstraints constraints) const { std::shared_lock lock(mutex_); return action_model_.assess(decisions, constraints); }
std::vector<CapabilityCandidate> Brain::evaluate_capabilities(const std::vector<CapabilityDescriptor>& capabilities, CapabilityConstraints constraints) const { std::shared_lock lock(mutex_); return CapabilityEvaluator{}.evaluate(capabilities, constraints); }
CapabilityExecutionResult Brain::execute_capability(const CapabilityDescriptor& capability, std::string input, std::vector<std::string> granted_permissions, double maximum_risk, CapabilityProvider provider) { if (provider.capability_id.empty() || !provider.execute) return {CapabilityExecutionStatus::rejected, capability.id, {}, {}, "capability_provider_required"}; if (provider.capability_id != capability.id) return {CapabilityExecutionStatus::rejected, capability.id, {}, {}, "capability_provider_mismatch"}; CapabilityExecutionBoundary boundary; if (!boundary.register_provider(std::move(provider))) return {CapabilityExecutionStatus::rejected, capability.id, {}, {}, "capability_provider_registration_failed"}; const auto result = boundary.execute(CapabilityExecutionRequest{capability, std::move(input), std::move(granted_permissions), maximum_risk}); if (!capability.id.empty()) { const double reliability = result.status == CapabilityExecutionStatus::succeeded ? 1.0 : result.status == CapabilityExecutionStatus::unavailable ? 0.25 : 0.0; std::unique_lock lock(mutex_); Event event{0, 0, result.provider.empty() ? "capability_executor" : result.provider, "capability_execution", {{"capability_id", capability.id}, {"status", static_cast<std::int64_t>(result.status)}, {"provider", result.provider}, {"reason", result.reason}, {"output", result.output}, {"reliability", reliability}}}; event.sequence = memory_.append(event); if (event.sequence != 0) { ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); } } return result; }
Plan Brain::plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const { std::shared_lock lock(mutex_); return planner_.build(actions, horizon); }
Plan Brain::plan(const std::vector<CandidateAction>& actions, std::size_t horizon, const PlanningContext& context) const { std::shared_lock lock(mutex_); return planner_.build(actions, horizon, context); }
Reflection Brain::reflect() const { std::shared_lock lock(mutex_); std::vector<Belief> beliefs; beliefs.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) beliefs.push_back(belief); std::vector<Prediction> predictions; predictions.reserve(predictions_.size()); for (const auto& prediction : predictions_) predictions.push_back(prediction); const auto calibration = affective_learning_model_.calibration(); return reflection_model_.evaluate(beliefs, predictions, calibration.mean_absolute_error, calibration.learning_rate_scale, calibration.observations); }
AttentionPolicy Brain::attention_policy() const { std::shared_lock lock(mutex_); return attention_model_.policy(); }
AttentionSignal Brain::attention() const { std::shared_lock lock(mutex_); return attention_state_; }
ThreatAssessment Brain::threat() const { std::shared_lock lock(mutex_); return threat_state_; }
std::vector<RecoveryPlan> Brain::recovery_options() const { std::shared_lock lock(mutex_); return resilience_.required_recovery(); }
SelfTestReport Brain::self_test() const { std::shared_lock lock(mutex_); const auto history = memory_.all(); std::vector<DiagnosticCheck> checks; checks.push_back({"journal", "sequence-monotonic", [history] { std::uint64_t previous = 0; for (const auto& event : history) { if (event.sequence == 0 || (previous != 0 && event.sequence <= previous)) return false; previous = event.sequence; } return true; }}); checks.push_back({"brain", "cycle-consistent", [this] { return state_.cycle >= state_.events_seen || state_.events_seen == 0; }}); checks.push_back({"memory", "journal-readable", [history] { return true; }}); checks.push_back({"goals", "goal-state-readable", [this] { return !goals_model_.all().empty() || true; }}); checks.push_back({"self-model", "health-bounded", [this] { const auto h = self_model_.health(); return h.overall >= 0.0 && h.overall <= 1.0; }}); checks.push_back({"cognition", "state-bounded", [this] { return state_.novelty >= 0.0 && state_.novelty <= 1.0 && state_.attention >= 0.0 && state_.attention <= 1.0 && state_.threat >= 0.0 && state_.threat <= 1.0; }}); return self_testing_model_.run(checks); }
SelfHealingResult Brain::self_heal(const std::string& component, std::function<bool(const std::string&)> repair, std::function<bool(const std::string&)> verify) { if (component.empty() || !repair || !verify) return {component, HealingState::RecoveryFailed, "invalid_healing_request"}; const auto result = self_testing_model_.heal(component, [component, &repair] { return repair(component); }, [component, &verify] { return verify(component); }); if (result.state == HealingState::Recovered) recover(component, 1.0); return result; }
bool Brain::create_goal(Goal goal) { std::unique_lock lock(mutex_); if (goal.id.empty() || goal.description.empty() || goals_model_.get(goal.id) != nullptr) return false; goal.priority = std::clamp(goal.priority, 0.0, 1.0); goal.progress = std::clamp(goal.progress, 0.0, 1.0); goal.created_cycle = state_.cycle + 1; Event event{0, 0, "brain", "goal_create", {{"id", goal.id}, {"description", goal.description}, {"priority", goal.priority}, {"progress", goal.progress}, {"created_cycle", static_cast<std::int64_t>(goal.created_cycle)}, {"deadline_cycle", static_cast<std::int64_t>(goal.deadline_cycle)}, {"status", static_cast<std::int64_t>(goal.status)}, {"prerequisites", join_ids(goal.prerequisites)}, {"subgoals", join_ids(goal.subgoals)}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return goals_model_.get(goal.id) != nullptr; }
bool Brain::activate_goal(const std::string& id) { std::unique_lock lock(mutex_); const auto* goal = goals_model_.get(id); if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false; for (const auto& prerequisite : goal->prerequisites) { const auto* dependency = goals_model_.get(prerequisite); if (dependency == nullptr || dependency->status != GoalStatus::completed) return false; } Event event{0, 0, "brain", "goal_activate", {{"id", id}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::update_goal_progress(const std::string& id, double progress) { std::unique_lock lock(mutex_); const double bounded = std::clamp(progress, 0.0, 1.0); const auto* goal = goals_model_.get(id); if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false; if (!std::isfinite(progress)) return false; Event event{0, 0, "brain", "goal_progress", {{"id", id}, {"progress", bounded}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::complete_goal(const std::string& id) { std::unique_lock lock(mutex_); const auto* goal = goals_model_.get(id); if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false; Event event{0, 0, "brain", "goal_complete", {{"id", id}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::abandon_goal(const std::string& id) { std::unique_lock lock(mutex_); const auto* goal = goals_model_.get(id); if (id.empty() || goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false; Event event{0, 0, "brain", "goal_abandon", {{"id", id}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::set_goal_priority(const std::string& id, double priority) { std::unique_lock lock(mutex_); if (!std::isfinite(priority) || goals_model_.get(id) == nullptr) return false; const double bounded = std::clamp(priority, 0.0, 1.0); Event event{0, 0, "brain", "goal_priority", {{"id", id}, {"priority", bounded}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
const Goal* Brain::goal(const std::string& id) const noexcept { std::shared_lock lock(mutex_); return goals_model_.get(id); }
std::vector<Goal> Brain::goals() const { std::shared_lock lock(mutex_); return goals_model_.all(); }
std::vector<Goal> Brain::eligible_goals() const { std::shared_lock lock(mutex_); return goals_model_.eligible(state_.cycle); }
void Brain::observe_capability(std::string name, double availability, double performance) { std::unique_lock lock(mutex_); if (name.empty()) return; const double bounded_availability = std::clamp(availability, 0.0, 1.0); const double bounded_performance = std::clamp(performance, 0.0, 1.0); Event event{0, 0, "brain", "capability_observe", {{"name", name}, {"availability", bounded_availability}, {"performance", bounded_performance}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); }
bool Brain::isolate_capability(const std::string& name) { std::unique_lock lock(mutex_); if (name.empty() || self_model_.capability(name) == nullptr) return false; Event event{0, 0, "brain", "capability_isolate", {{"name", name}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::restore_capability(const std::string& name, double availability, double performance) { std::unique_lock lock(mutex_); const double bounded_availability = std::clamp(availability, 0.0, 1.0); const double bounded_performance = std::clamp(performance, 0.0, 1.0); if (name.empty() || self_model_.capability(name) == nullptr) return false; Event event{0, 0, "brain", "capability_restore", {{"name", name}, {"availability", bounded_availability}, {"performance", bounded_performance}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::isolate(const std::string& component) { std::unique_lock lock(mutex_); if (component.empty() || resilience_.health(component) == nullptr) return false; Event event{0, 0, "brain", "resilience_isolate", {{"component", component}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::recover(const std::string& component, double restored_health) { std::unique_lock lock(mutex_); const double health = std::clamp(restored_health, 0.0, 1.0); if (component.empty() || !std::isfinite(restored_health) || resilience_.health(component) == nullptr) return false; Event event{0, 0, "brain", "resilience_recover", {{"component", component}, {"health", health}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
void Brain::register_evolution_parameter(std::string key, double initial) { std::unique_lock lock(mutex_); if (key.empty()) return; Event event{0, 0, "brain", "evolution_register", {{"key", key}, {"initial", initial}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
void Brain::observe_evolution_fitness(const std::string& key, double fitness) { std::unique_lock lock(mutex_); if (key.empty()) return; Event event{0, 0, "brain", "evolution_fitness", {{"key", key}, {"fitness", fitness}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); }
std::vector<EvolutionProposal> Brain::evolution_options() const { std::shared_lock lock(mutex_); return evolution_.propose(); }
bool Brain::adopt_evolution(const EvolutionProposal& proposal) { std::unique_lock lock(mutex_); if (proposal.key.empty() || evolution_.parameter(proposal.key) == nullptr) return false; Event event{0, 0, "brain", "evolution_adopt", {{"key", proposal.key}, {"current", proposal.current}, {"proposed", proposal.proposed}, {"expected_gain", proposal.expected_gain}, {"confidence", proposal.confidence}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; replay(event); ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::rollback_evolution(const std::string& key) { std::unique_lock lock(mutex_); if (key.empty() || evolution_.parameter(key) == nullptr) return false; if (evolution_.parameter(key)->value == evolution_.parameter(key)->baseline) return false; Event event{0, 0, "brain", "evolution_rollback", {{"key", key}}}; event.sequence = memory_.append(event); if (event.sequence == 0) return false; if (!evolution_.rollback(key)) return false; ++state_.events_seen; state_.cycle = event.sequence; sync_self_state(); return true; }
bool Brain::adopt_evolution_experiment(EvolutionExperiment& experiment) {
    std::unique_lock lock(mutex_);
    if (!evolution_controller_.validate_adoption_for_brain(experiment)) return false;
    Event event{0, 0, "brain", "evolution_adopt",
                {{"key", experiment.proposal.key},
                 {"current", experiment.proposal.current},
                 {"proposed", experiment.proposal.proposed},
                 {"expected_gain", experiment.proposal.expected_gain},
                 {"confidence", experiment.proposal.confidence},
                 {"experiment_id", experiment.id},
                 {"outcome", static_cast<std::int64_t>(experiment.outcome)},
                 {"baseline", experiment.baseline_fitness},
                 {"candidate", experiment.candidate_fitness}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return false;
    if (!evolution_controller_.adopt_for_brain(experiment)) return false;
    evolution_history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Adopted,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "adopted", {}});
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}

CanaryDecision Brain::observe_evolution_canary(const std::string& parameter_key, const std::string& experiment_id, CanaryObservation observation) {
    std::unique_lock lock(mutex_);
    const auto preview = evolution_controller_.preview_canary_for_brain(observation);
    if (preview.reason == "invalid_observation") return preview;

    Event observation_event{0, 0, "brain", "evolution_canary",
                            {{"key", parameter_key},
                             {"experiment_id", experiment_id},
                             {"baseline", observation.baseline_fitness},
                             {"candidate", observation.candidate_fitness}}};
    observation_event.sequence = memory_.append(observation_event);
    if (observation_event.sequence == 0) {
        return CanaryDecision{false, preview.sufficient_evidence, preview.mean_delta,
                              preview.worst_delta, "observation_not_persisted"};
    }
    const auto decision = evolution_controller_.observe_canary_for_brain(observation);
    ++state_.events_seen;
    state_.cycle = observation_event.sequence;

    if (!decision.rollback) {
        sync_self_state();
        return decision;
    }

    Event rollback_event{0, 0, "brain", "evolution_rollback",
                         {{"key", parameter_key},
                          {"experiment_id", experiment_id},
                          {"reason", decision.reason},
                          {"observed_delta", decision.mean_delta}}};
    rollback_event.sequence = memory_.append(rollback_event);
    if (rollback_event.sequence == 0) {
        sync_self_state();
        return CanaryDecision{false, decision.sufficient_evidence, decision.mean_delta,
                              decision.worst_delta, "rollback_not_persisted"};
    }
    if (!evolution_controller_.rollback(parameter_key, experiment_id, decision.reason,
                                         decision.mean_delta)) {
        sync_self_state();
        return CanaryDecision{false, decision.sufficient_evidence, decision.mean_delta,
                              decision.worst_delta, "rollback_failed"};
    }
    ++state_.events_seen;
    state_.cycle = rollback_event.sequence;
    sync_self_state();
    return decision;
}
std::vector<EvolutionHistoryRecord> Brain::evolution_history() const { std::shared_lock lock(mutex_); return evolution_history_.records(); }
BrainSnapshot Brain::snapshot() const { std::shared_lock lock(mutex_); BrainSnapshot snapshot; snapshot.state = state_; snapshot.self_state = self_state_model_.snapshot(); for (const auto& [_, belief] : beliefs_) snapshot.beliefs.push_back(belief); for (const auto& prediction : predictions_) snapshot.predictions.push_back(prediction); snapshot.causal_links = causal_.links(); snapshot.goals = goals_model_.all(); return snapshot; }
BrainState Brain::state() const { std::shared_lock lock(mutex_); return state_; }
bool Brain::append_goal_event(const Event& event) { Event persisted = event; persisted.sequence = memory_.append(persisted); if (persisted.sequence == 0) return false; ++state_.events_seen; state_.cycle = persisted.sequence; sync_self_state(); return true; }

} // namespace jarvis::core
