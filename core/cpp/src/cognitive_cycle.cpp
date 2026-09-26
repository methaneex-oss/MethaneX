#include "jarvis/core/cognitive_cycle.hpp"

#include <algorithm>
#include <string>

namespace jarvis::core {

std::optional<Goal> CognitiveCycle::select_goal(const CognitiveCycleInput& input,
                                                const std::vector<Goal>& eligible) const {
    if (eligible.empty()) return std::nullopt;
    if (input.goal_id.has_value()) {
        const auto it = std::find_if(eligible.begin(), eligible.end(), [&](const Goal& goal) {
            return goal.id == *input.goal_id;
        });
        if (it == eligible.end()) return std::nullopt;
        return *it;
    }
    return eligible.front();
}

CognitiveCycleResult CognitiveCycle::run(const CognitiveCycleInput& input) const {
    CognitiveCycleResult result;
    if (input.planning_horizon == 0) {
        result.status = CognitiveCycleStatus::no_action;
        return result;
    }

    result.context.observation = brain_.observe(input.observation);
    result.context.memories = brain_.memory().recall_ranked(input.observation.data, input.memory_limit);
    result.context.beliefs = brain_.beliefs();
    result.context.causal_links = brain_.causal_links();

    // Dispute is evidence-state, not a confidence threshold. The World Model
    // records explicit contradictions independently from belief confidence, so
    // cognition must consume that authoritative signal rather than reconstructing
    // dispute from a heuristic cutoff.
    const auto disputed_facts = brain_.world().disputed_facts();
    const auto disputed_relations = brain_.world().disputed_relations();
    std::size_t disputed_beliefs = 0;
    for (auto& belief : result.context.beliefs) {
        belief.disputed = std::any_of(
            disputed_facts.begin(), disputed_facts.end(),
            [&](const Fact& fact) { return fact.predicate == belief.key && fact.disputed; });
        if (belief.disputed) ++disputed_beliefs;
    }

    // Relation contradictions are also epistemic uncertainty even when they do
    // not map to a scalar belief key. Preserve them in the cycle-level uncertainty
    // signal so planning cannot treat a contradictory world model as certain.

    ReasoningProblem problem;
    problem.premises = result.context.beliefs;
    problem.causal_links = result.context.causal_links;
    problem.max_steps = input.reasoning_steps;
    result.context.reasoning = ReasoningEngine{}.solve(problem);

    if (!result.context.causal_links.empty()) {
        const auto simulation = brain_.simulate(result.context.beliefs, input.planning_horizon);
        const std::string prefix = "cycle." + std::to_string(result.context.observation.event.sequence) + ".";
        result.context.predictions.reserve(simulation.predictions.size());
        for (const auto& projected : simulation.predictions) {
            if (projected.key.empty()) continue;
            const auto prediction = brain_.predict(prefix + projected.key, projected.value,
                                                   std::clamp(projected.confidence, 0.0, 1.0));
            if (!prediction.key.empty()) result.context.predictions.push_back(prediction);
        }
    }

    result.context.eligible_goals = brain_.eligible_goals();
    const auto selected = select_goal(input, result.context.eligible_goals);
    if (!selected.has_value()) {
        result.status = input.goal_id.has_value() ? CognitiveCycleStatus::invalid_goal
                                                   : CognitiveCycleStatus::no_goal;
        result.context.reflection = brain_.reflect();
        return result;
    }
    result.context.selected_goal = *selected;

    if (input.candidate_actions.empty()) {
        result.status = CognitiveCycleStatus::no_action;
        result.context.reflection = brain_.reflect();
        return result;
    }

    const auto self_state = brain_.self_state_model().snapshot();
    const double goal_priority = std::clamp(selected->priority, 0.0, 1.0);
    const double goal_progress = std::clamp(selected->progress, 0.0, 1.0);
    const double threat = std::clamp(brain_.threat().score, 0.0, 1.0);
    const double dispute_pressure = result.context.beliefs.empty()
        ? 0.0
        : std::clamp(static_cast<double>(disputed_beliefs) /
                         static_cast<double>(result.context.beliefs.size()),
                     0.0, 1.0);
    const double world_dispute_pressure = std::clamp(
        static_cast<double>(disputed_facts.size() + disputed_relations.size()) /
            static_cast<double>(std::max<std::size_t>(
                1, result.context.beliefs.size() + disputed_relations.size())),
        0.0, 1.0);
    const double uncertainty = std::max(
        std::clamp(self_state.uncertainty, 0.0, 1.0),
        std::max(dispute_pressure, world_dispute_pressure));
    const double deadline_pressure = std::clamp(input.deadline_pressure, 0.0, 1.0);

    std::vector<CandidateAction> learned_actions = input.candidate_actions;
    for (auto& action : learned_actions) {
        if (action.name.empty()) continue;

        if (const auto* metric = brain_.knowledge_source("action_executor." + action.name);
            metric != nullptr && metric->observations > 0) {
            const double reliability = std::clamp(metric->reliability, 0.0, 1.0);
            action.expected_value *= (0.5 + 0.5 * reliability);
            action.risk = std::clamp(action.risk + (1.0 - reliability) * 0.5, 0.0, 1.0);
        }

        // Capability health belongs to cognitive state. A known degraded or
        // isolated capability therefore changes the action's planning profile.
        if (const auto* capability = brain_.self_state_model().capability(action.name);
            capability != nullptr) {
            const double availability = std::clamp(capability->availability, 0.0, 1.0);
            const double performance = std::clamp(capability->performance, 0.0, 1.0);
            const double capability_reliability = availability * performance;
            action.expected_value *= capability_reliability;
            action.risk = std::clamp(action.risk + (1.0 - capability_reliability) * 0.5, 0.0, 1.0);
            if (capability->isolated) {
                action.expected_value = 0.0;
                action.risk = 1.0;
                action.preferred_outcome = DecisionOutcome::reject;
            }
        }
    }

    const PlanningContext planning_context{
        goal_priority, goal_progress, threat, uncertainty,
        input.resource_budget, deadline_pressure,
    };
    result.context.plan = brain_.plan(learned_actions, input.planning_horizon, planning_context);
    if (result.context.plan.steps.empty()) {
        result.status = CognitiveCycleStatus::no_action;
        result.context.reflection = brain_.reflect();
        return result;
    }

    std::vector<CandidateAction> planned_actions;
    planned_actions.reserve(result.context.plan.steps.size());
    for (const auto& step : result.context.plan.steps) planned_actions.push_back(step.action);

    result.context.decision_context = DecisionContext{
        goal_priority, goal_progress, result.context.plan.expected_value,
        result.context.plan.risk, input.resource_budget, uncertainty,
        threat, deadline_pressure,
    };
    result.context.decisions = brain_.decision_engine().decide(
        planned_actions, result.context.decision_context);
    if (result.context.decisions.empty()) {
        result.status = CognitiveCycleStatus::no_action;
        result.context.reflection = brain_.reflect();
        return result;
    }

    result.context.action_assessments = brain_.action_model().assess(
        result.context.decisions, input.action_constraints);
    result.context.reflection = brain_.reflect();
    result.status = CognitiveCycleStatus::completed;
    return result;
}

double CognitiveCycle::learn_from_outcome(const Evidence& evidence) const {
    return brain_.learn(evidence);
}

bool CognitiveCycle::resolve_prediction(const std::string& key, const Scalar& actual) const {
    return brain_.resolve_prediction(key, actual);
}

CognitiveFeedbackResult CognitiveCycle::process_outcome(
    const std::optional<std::string>& prediction_key,
    const Scalar& actual,
    const std::optional<Evidence>& evidence) const {
    CognitiveFeedbackResult result;
    if (prediction_key.has_value() && !prediction_key->empty())
        result.prediction_resolved = resolve_prediction(*prediction_key, actual);
    if (evidence.has_value()) result.learned_reliability = learn_from_outcome(*evidence);
    result.reflection = brain_.reflect();
    return result;
}

} // namespace jarvis::core
