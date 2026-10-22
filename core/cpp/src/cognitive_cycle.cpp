#include "jarvis/core/cognitive_cycle.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace jarvis::core {

std::optional<Goal> CognitiveCycle::select_goal(const CognitiveCycleInput& input,
                                                const std::vector<Goal>& eligible) const {
    if (eligible.empty()) return std::nullopt;
    if (input.goal_id.has_value()) {
        const auto it = std::find_if(eligible.begin(), eligible.end(), [&](const Goal& goal) { return goal.id == *input.goal_id; });
        if (it == eligible.end()) return std::nullopt;
        return *it;
    }
    return eligible.front();
}

CognitiveCycleResult CognitiveCycle::run(const CognitiveCycleInput& input) const {
    CognitiveCycleResult result;
    if (input.planning_horizon == 0) { result.status = CognitiveCycleStatus::no_action; return result; }
    result.context.observation = brain_.observe(input.observation);
    result.context.memories = brain_.memory().recall_ranked(input.observation.data, input.memory_limit);
    result.context.beliefs = brain_.beliefs();
    result.context.causal_links = brain_.causal_links();
    result.context.affective_state = brain_.affective_state();
    result.context.affective_appraisal = brain_.affective_appraisal();
    result.context.attention = brain_.attention();
    const auto disputed_facts = brain_.world().disputed_facts();
    const auto disputed_relations = brain_.world().disputed_relations();
    std::size_t disputed_beliefs = 0;
    for (auto& belief : result.context.beliefs) {
        belief.disputed = std::any_of(disputed_facts.begin(), disputed_facts.end(), [&](const Fact& fact) { return fact.predicate == belief.key && fact.disputed; });
        if (belief.disputed) ++disputed_beliefs;
    }
    ReasoningProblem problem{result.context.beliefs, result.context.causal_links, input.reasoning_steps};
    result.context.reasoning = ReasoningEngine{}.solve(problem);
    if (!result.context.causal_links.empty()) {
        const auto simulation = brain_.simulate(result.context.beliefs, input.planning_horizon);
        result.context.predictions.reserve(simulation.predictions.size());
        for (const auto& projected : simulation.predictions) {
            if (projected.key.empty()) continue;
            const auto prediction = brain_.predict(projected.key, projected.value, std::clamp(projected.confidence, 0.0, 1.0));
            if (!prediction.key.empty()) result.context.predictions.push_back(prediction);
        }
    }
    result.context.eligible_goals = brain_.eligible_goals();
    const auto selected = select_goal(input, result.context.eligible_goals);
    if (!selected.has_value()) {
        result.status = input.goal_id.has_value() ? CognitiveCycleStatus::invalid_goal : CognitiveCycleStatus::no_goal;
        result.context.reflection = brain_.reflect();
        return result;
    }
    result.context.selected_goal = *selected;
    if (input.candidate_actions.empty()) { result.status = CognitiveCycleStatus::no_action; result.context.reflection = brain_.reflect(); return result; }
    const double goal_priority = std::clamp(selected->priority, 0.0, 1.0);
    const double goal_progress = std::clamp(selected->progress, 0.0, 1.0);
    const double threat = std::clamp(brain_.threat().score, 0.0, 1.0);
    const double dispute_pressure = result.context.beliefs.empty() ? 0.0 : std::clamp(static_cast<double>(disputed_beliefs) / static_cast<double>(result.context.beliefs.size()), 0.0, 1.0);
    const double world_dispute_pressure = std::clamp(static_cast<double>(disputed_facts.size() + disputed_relations.size()) / static_cast<double>(std::max<std::size_t>(1, result.context.beliefs.size() + disputed_relations.size())), 0.0, 1.0);
    // The self-state uncertainty currently mirrors inverse attention salience
    // (Brain::sync_self_state), so combining both as independent probabilities
    // double-counts one signal and can make greater attention LOWER uncertainty.
    // Use the current attended evidence's uncertainty, then let disputed world
    // evidence raise it. This keeps attention causally relevant to planning
    // without treating low salience itself as a second, contradictory estimate.
    const double attended_uncertainty = std::clamp(
        result.context.attention.salience * result.context.attention.uncertainty, 0.0, 1.0);
    const double uncertainty = std::max(
        attended_uncertainty, std::max(dispute_pressure, world_dispute_pressure));
    const double deadline_pressure = std::clamp(input.deadline_pressure, 0.0, 1.0);
    std::vector<CandidateAction> learned_actions = input.candidate_actions;
    // Do not plan with a capability that the self-model has marked unavailable
    // or isolated. Capability observations describe current operational ability,
    // not merely a preference to be traded off against utility.
    learned_actions.erase(
        std::remove_if(learned_actions.begin(), learned_actions.end(),
            [&](const CandidateAction& action) {
                if (action.name.empty()) return true;
                const auto* capability = brain_.self_model().capability(action.name);
                return capability != nullptr &&
                       (capability->isolated || capability->availability <= 0.0);
            }),
        learned_actions.end());
    for (auto& action : learned_actions) {
        if (action.name.empty()) continue;

        // Prefer outcome-derived executor reliability when available. Otherwise,
        // use the self-model's learned capability performance so capability
        // evidence also affects planning before a separate executor metric exists.
        double reliability = 1.0;
        bool has_reliability_evidence = false;
        if (const auto* metric = brain_.knowledge_source("action_executor." + action.name);
            metric != nullptr && metric->observations > 0) {
            reliability = std::clamp(std::isfinite(metric->reliability)
                                         ? metric->reliability : 0.0, 0.0, 1.0);
            has_reliability_evidence = true;
        } else if (const auto* capability = brain_.self_model().capability(action.name);
                   capability != nullptr) {
            reliability = std::clamp(std::isfinite(capability->performance)
                                         ? capability->performance : 0.0, 0.0, 1.0);
            has_reliability_evidence = true;
        }

        if (has_reliability_evidence) {
            // Retain a non-zero floor so one poor estimate does not erase an
            // action entirely; evidence instead changes utility, forecast, and risk.
            const double learned_reliability = 0.25 + 0.75 * reliability;
            action.utility *= learned_reliability;
            action.expected_value *= learned_reliability;
            // Reliability should inform risk, not create a self-sealing failure
            // loop. A single failed attempt can be an executor outage; if its
            // penalty pushes action confidence below the execution threshold,
            // that action can never be tried again to gather corrective evidence.
            // Keep the risk adjustment bounded while still letting poor
            // reliability reduce utility and increase risk.
            action.risk = std::clamp(action.risk + (1.0 - reliability) * 0.1, 0.0, 1.0);
        }
    }

    // Developmental strategy evidence is applied before planning so the learned
    // change can propagate through the normal planner and decision engine.
    const std::string developmental_context =
        input.developmental_context.empty() ? selected->id : input.developmental_context;
    const auto stored_strategies = brain_.developmental_strategies();
    const auto related_strategies = brain_.developmental_related_strategies(developmental_context);
    // A transferred strategy is a prior, not a prohibition. When the current
    // context has no direct evidence for a candidate, reserve some utility for
    // information gain. This lets a surprising local outcome trigger trials of
    // alternatives that were poor in a related context instead of trapping the
    // learner in a self-confirming transfer loop. The bonus affects exploration
    // value only; it does not fabricate a positive predicted consequence.
    const double exploration_pressure = std::clamp(
        std::max({result.context.attention.uncertainty,
                  result.context.affective_state.uncertainty,
                  result.context.affective_state.tension}),
        0.0, 1.0);

    // Use exact-context experience whenever that action has been tried locally.
    // For actions with no local evidence, still allow bounded transfer from
    // related contexts. An exact-context observation for one action must not
    // disable generalization for every other candidate action.
    for (auto& action : learned_actions) {
        double direct_evidence = 0.0;
        double direct_weight = 0.0;
        for (const auto& strategy : stored_strategies) {
            if (strategy.context != developmental_context ||
                strategy.action != action.name) continue;
            const double weight = std::clamp(strategy.confidence, 0.0, 1.0);
            direct_evidence += weight * std::clamp(strategy.value, -1.0, 1.0);
            direct_weight += weight;
        }

        if (direct_weight > 0.0) {
            // Direct experience remains stronger than generalization for an
            // action already tried in this context.
            const double influence = std::clamp(
                direct_evidence / std::max(1.0, direct_weight), -1.0, 1.0);
            action.utility += influence;
            action.expected_value = std::clamp(
                action.expected_value + influence, -1.0, 1.0);
            continue;
        }

        double transferred_evidence = 0.0;
        double transferred_weight = 0.0;
        for (const auto& evidence : related_strategies) {
            if (evidence.strategy.action != action.name) continue;
            const double weight = std::clamp(evidence.similarity, 0.0, 1.0) *
                                  std::clamp(evidence.strategy.confidence, 0.0, 1.0);
            if (weight <= 0.0) continue;
            transferred_evidence += weight *
                std::clamp(evidence.strategy.value, -1.0, 1.0);
            transferred_weight += weight;
        }
        if (transferred_weight > 0.0) {
            // Transfer is bounded and weaker than direct evidence. Normalize
            // overlapping memories so duplicate related contexts cannot amplify
            // the same preference without bound.
            const double influence = std::clamp(
                1.25 * transferred_evidence / std::max(1.0, transferred_weight),
                -1.0, 1.0);
            action.utility += influence;
            action.expected_value = std::clamp(
                action.expected_value + influence, -1.0, 1.0);
        }
        // Exploration is needed precisely when local evidence is absent. Apply
        // the information-gathering incentive even if no related memory matched;
        // otherwise a sparse memory system can never discover an alternative.
        // Existing local evidence bypasses this branch and remains authoritative.
        action.utility += 0.75 * exploration_pressure *
            (1.0 - std::clamp(transferred_weight, 0.0, 1.0));
    }
    const auto& affect = result.context.affective_state;
    const auto& appraisal = result.context.affective_appraisal;
    const double affective_uncertainty = std::clamp(
        affect.uncertainty * appraisal.uncertainty_weight, 0.0, 1.0);
    const double tension = std::clamp(
        affect.tension * appraisal.tension_error_weight, 0.0, 1.0);
    const double valence = std::clamp(
        affect.valence * appraisal.outcome_weight, -1.0, 1.0);
    const double arousal = std::clamp(
        affect.arousal * appraisal.novelty_weight, 0.0, 1.0);
    const double stability = std::clamp(affect.stability, 0.0, 1.0);
    const PlanningContext planning_context{
        goal_priority,
        goal_progress,
        threat,
        uncertainty,
        input.resource_budget,
        deadline_pressure,
        valence,
        arousal,
        affective_uncertainty,
        tension,
        stability};
    result.context.plan = brain_.plan(learned_actions, input.planning_horizon, planning_context);
    if (result.context.plan.steps.empty()) { result.status = CognitiveCycleStatus::no_action; result.context.reflection = brain_.reflect(); return result; }
    std::vector<CandidateAction> planned_actions;
    planned_actions.reserve(result.context.plan.steps.size());
    for (const auto& step : result.context.plan.steps) planned_actions.push_back(step.action);
    result.context.decision_context = DecisionContext{
        goal_priority,
        goal_progress,
        result.context.plan.expected_value,
        result.context.plan.risk,
        input.resource_budget,
        uncertainty,
        threat,
        deadline_pressure,
        valence,
        arousal,
        affective_uncertainty,
        tension,
        stability};
    result.context.decisions = brain_.decision_engine().decide(planned_actions, result.context.decision_context);
    if (result.context.decisions.empty()) { result.status = CognitiveCycleStatus::no_action; result.context.reflection = brain_.reflect(); return result; }
    result.context.action_assessments = brain_.action_model().assess(result.context.decisions, input.action_constraints);
    // Preserve the exact context used for learned decision bias through the
    // authorization/execution boundary; otherwise outcome learning falls back
    // to the goal ID and cannot update the context that shaped this decision.
    for (auto& assessment : result.context.action_assessments) {
        assessment.developmental_context = developmental_context;
    }
    result.context.reflection = brain_.reflect();
    result.status = CognitiveCycleStatus::completed;
    return result;
}

double CognitiveCycle::learn_from_outcome(const Evidence& evidence) const { return brain_.learn(evidence); }
bool CognitiveCycle::resolve_prediction(const std::string& key, const Scalar& actual) const { return brain_.resolve_prediction(key, actual); }

CognitiveFeedbackResult CognitiveCycle::process_outcome(
    const Prediction& prediction, const Scalar& actual,
    const std::optional<Evidence>& evidence, const std::optional<std::string>& goal_id,
    const std::optional<double>& goal_progress, double goal_confidence,
    std::optional<double> outcome_utility) const {
    return process_outcome(prediction.key, actual, evidence, goal_id, goal_progress,
                           goal_confidence, prediction.created_sequence, outcome_utility);
}

CognitiveFeedbackResult CognitiveCycle::process_outcome(
    const std::optional<std::string>& prediction_key, const Scalar& actual,
    const std::optional<Evidence>& evidence, const std::optional<std::string>& goal_id,
    const std::optional<double>& goal_progress, double goal_confidence,
    std::optional<std::uint64_t> prediction_sequence,
    std::optional<double> outcome_utility) const {
    CognitiveFeedbackResult result;
    if (prediction_sequence.has_value()) {
        const auto feedback = brain_.resolve_prediction_feedback(*prediction_sequence, actual, outcome_utility);
        result.prediction_resolved = feedback != PredictionFeedbackStatus::rejected;
    } else if (prediction_key.has_value() && !prediction_key->empty()) {
        const auto feedback = brain_.resolve_prediction_feedback(*prediction_key, actual, outcome_utility);
        result.prediction_resolved = feedback != PredictionFeedbackStatus::rejected;
    }
    if (evidence.has_value()) result.learned_reliability = learn_from_outcome(*evidence);
    if (goal_id.has_value() && goal_progress.has_value()) {
        GoalOutcomeEvidence goal_evidence{*goal_id, 0.0, std::clamp(*goal_progress, 0.0, 1.0), 0.0, *goal_progress >= 1.0, std::clamp(goal_confidence, 0.0, 1.0), brain_.state().cycle};
        if (const auto* goal = brain_.goal(*goal_id); goal != nullptr) goal_evidence.progress_before = goal->progress;
        result.goal_progress_assimilated = brain_.assimilate_goal_outcome(goal_evidence);
    }
    result.affective_state = brain_.affective_state();
    result.affective_appraisal = brain_.affective_appraisal();
    result.reflection = brain_.reflect();
    return result;
}

} // namespace jarvis::core
