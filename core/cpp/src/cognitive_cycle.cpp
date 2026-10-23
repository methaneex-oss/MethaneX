#include "jarvis/core/cognitive_cycle.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {
namespace {

std::string infer_developmental_context(const CognitiveCycleInput& input,
                                        const Goal& goal) {
    if (!input.developmental_context.empty()) return input.developmental_context;

    // Build a stable, feature-grounded context for downstream memory retrieval
    // and strategy transfer. Numeric features use logarithmic magnitude bands:
    // this preserves coarse state information without memorizing raw readings.
    std::string context = "observation " + input.observation.kind;
    if (!input.observation.source.empty()) context += " source " + input.observation.source;
    bool has_context_feature = false;
    std::vector<std::pair<std::string, const Scalar*>> features;
    features.reserve(input.observation.data.size());
    for (const auto& [key, value] : input.observation.data)
        features.emplace_back(key, &value);
    std::sort(features.begin(), features.end(),
              [](const auto& left, const auto& right) { return left.first < right.first; });

    for (const auto& [key, value_ptr] : features) {
        const auto& value = *value_ptr;
        context += " " + key;
        if (const auto* text_value = std::get_if<std::string>(&value)) {
            if (!text_value->empty()) {
                context += " " + *text_value;
                has_context_feature = true;
            }
        } else if (const auto* boolean_value = std::get_if<bool>(&value)) {
            context += *boolean_value ? " true" : " false";
            has_context_feature = true;
        } else {
            double numeric = 0.0;
            if (const auto* numeric_value = std::get_if<double>(&value)) {
                numeric = *numeric_value;
            } else if (const auto* integer_value = std::get_if<std::int64_t>(&value)) {
                numeric = static_cast<double>(*integer_value);
            } else {
                continue;
            }
            if (!std::isfinite(numeric)) continue;
            has_context_feature = true;
            if (numeric == 0.0) {
                context += " zero";
            } else {
                context += numeric < 0.0 ? " negative" : " positive";
                context += " scale " +
                    std::to_string(std::ilogb(std::abs(numeric)));
            }
        }
    }
    return has_context_feature ? context : goal.id;
}

} // namespace

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
    // Retrieve from prior experience before recording the current observation.
    // Otherwise the just-appended observation can match itself and make recall
    // appear nonempty, suppressing the episodic continuity fallback.
    result.context.memories =
        brain_.memory().recall_ranked(input.observation.data, input.memory_limit);

    // Observation similarity and action experience are separate retrieval
    // channels. A nonempty observation match must not hide the exact action
    // outcomes needed to evaluate candidate actions, especially after a sensor
    // schema changes or unrelated observations dominate the generic top-k.
    // Retrieve a bounded set per candidate and merge by durable sequence so
    // later planning can validate action, context, observation and evidence.
    if (input.memory_limit > 0) {
        for (const auto& action : input.candidate_actions) {
            if (action.name.empty()) continue;
            const auto action_memories = brain_.memory().recall_ranked(
                {{"action", Scalar{action.name}}}, input.memory_limit,
                "action_outcome");
            for (const auto& memory : action_memories) {
                if (memory.event.kind != "action_outcome") continue;
                const auto already_present = std::find_if(
                    result.context.memories.begin(), result.context.memories.end(),
                    [&](const MemoryRecord& existing) {
                        return existing.event.sequence == memory.event.sequence;
                    });
                if (already_present == result.context.memories.end())
                    result.context.memories.push_back(memory);
            }
        }
    }

    // A featureless observation or an unseen action still needs continuity.
    // Use salient episodic traces only when neither retrieval channel found
    // anything; targeted action recall above prevents unrelated matches from
    // suppressing a useful episode for a known candidate.
    if (result.context.memories.empty() && input.memory_limit > 0) {
        result.context.memories =
            brain_.memory().salient(input.memory_limit, MemoryTier::Episodic);
    }
    result.context.observation = brain_.observe(input.observation);
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
        infer_developmental_context(input, *selected);

    // Action-only recall can still be crowded out by recent outcomes from
    // different situations involving the same action. Retrieve exact-context
    // outcomes separately after the selected goal determines the context, then
    // merge them into the same evidence set. This preserves local experience
    // without preventing the broader strategy learner from transferring across
    // related contexts.
    if (input.memory_limit > 0) {
        for (const auto& action : input.candidate_actions) {
            if (action.name.empty()) continue;
            const auto contextual_memories = brain_.memory().recall_ranked(
                {{"action", Scalar{action.name}},
                 {"context", Scalar{developmental_context}}},
                input.memory_limit, "action_outcome", true);
            for (const auto& memory : contextual_memories) {
                const auto already_present = std::find_if(
                    result.context.memories.begin(), result.context.memories.end(),
                    [&](const MemoryRecord& existing) {
                        return existing.event.sequence == memory.event.sequence;
                    });
                if (already_present == result.context.memories.end())
                    result.context.memories.push_back(memory);
            }
        }
    }

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
        double episodic_weight = 0.0;
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
        } else {
            // Episodic fallback: older or imported journals may contain outcome
            // traces without a corresponding developmental-strategy record.
            // Use those traces only when neither direct nor transferred strategy
            // evidence exists for this action, preventing the same experience
            // from being counted once as a strategy and again as an episode.
            double episodic_value = 0.0;
            for (const auto& memory : result.context.memories) {
                const auto& event = memory.event;
                if (event.kind != "action_outcome") continue;
                const auto action_it = event.data.find("action");
                const auto context_it = event.data.find("context");
                const auto observed_it = event.data.find("observed");
                const auto actual_it = event.data.find("actual_consequence");
                if (action_it == event.data.end() || context_it == event.data.end() ||
                    observed_it == event.data.end() || actual_it == event.data.end()) continue;
                const auto* remembered_action = std::get_if<std::string>(&action_it->second);
                const auto* remembered_context = std::get_if<std::string>(&context_it->second);
                const auto* observed = std::get_if<bool>(&observed_it->second);
                if (remembered_action == nullptr || remembered_context == nullptr ||
                    observed == nullptr || !*observed ||
                    *remembered_action != action.name ||
                    *remembered_context != developmental_context) continue;
                double reward = 0.0;
                if (const auto* value = std::get_if<double>(&actual_it->second)) {
                    reward = *value;
                } else if (const auto* value = std::get_if<std::int64_t>(&actual_it->second)) {
                    reward = static_cast<double>(*value);
                } else {
                    continue;
                }
                if (!std::isfinite(reward)) continue;
                // Memory's default confidence is initialized from the event's
                // operational reliability. Multiplying that metadata by the same
                // event field again would square the evidence weight; worse, it
                // would let executor failure erase a confidently observed world
                // consequence. Prefer explicit evidence confidence, then legacy
                // reliability, and use memory metadata only when the event has
                // neither field.
                double reliability = std::clamp(
                    std::isfinite(memory.confidence) ? memory.confidence : 0.0,
                    0.0, 1.0);
                const auto evidence_it = event.data.find("evidence_reliability");
                const auto reliability_it = event.data.find("reliability");
                const auto selected_reliability =
                    evidence_it != event.data.end() ? evidence_it : reliability_it;
                if (selected_reliability != event.data.end()) {
                    if (const auto* value = std::get_if<double>(&selected_reliability->second)) {
                        if (!std::isfinite(*value)) continue;
                        reliability = std::clamp(*value, 0.0, 1.0);
                    } else if (const auto* value = std::get_if<std::int64_t>(&selected_reliability->second)) {
                        reliability = std::clamp(static_cast<double>(*value), 0.0, 1.0);
                    } else {
                        continue;
                    }
                }
                const double weight = reliability;
                episodic_value += weight * std::clamp(reward, -1.0, 1.0);
                episodic_weight += weight;
            }
            if (episodic_weight > 0.0) {
                // Keep episodic-only influence deliberately weaker than an
                // explicitly learned strategy; this is a fallback prior.
                const double influence = std::clamp(
                    0.5 * episodic_value / episodic_weight, -0.5, 0.5);
                action.utility += influence;
                action.expected_value = std::clamp(
                    action.expected_value + influence, -1.0, 1.0);
            }
        }
        // Exploration is needed precisely when local evidence is absent. Apply
        // the information-gathering incentive even if no related memory matched;
        // otherwise a sparse memory system can never discover an alternative.
        // Existing local evidence bypasses this branch and remains authoritative.
        // Episodic outcomes are local evidence too. Do not grant a fully
        // untried-action exploration bonus to a candidate whose own observed
        // outcomes were just used to bias its score; that bonus can otherwise
        // cancel the memory signal and make recall look behaviorally inert.
        const double local_evidence_weight = std::max(
            std::clamp(transferred_weight, 0.0, 1.0),
            std::clamp(episodic_weight, 0.0, 1.0));
        action.utility += 0.75 * exploration_pressure *
            (1.0 - local_evidence_weight);
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
