#include "jarvis/core/cognitive_cycle.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {
namespace {

std::string context_path_segment(const std::string& value) {
    // Context segments are persisted as part of a hierarchical key. Lossy
    // replacement (for example, '/' -> '_') aliases distinct observations and
    // can transfer a learned strategy into an unrelated context. Escape both
    // the separator and escape marker so encoding is reversible and collision-free.
    constexpr char hex[] = "0123456789ABCDEF";
    std::string encoded;
    encoded.reserve(value.size());
    for (const unsigned char ch : value) {
        if (ch == '/' || ch == '%') {
            encoded.push_back('%');
            encoded.push_back(hex[(ch >> 4) & 0x0F]);
            encoded.push_back(hex[ch & 0x0F]);
        } else {
            encoded.push_back(static_cast<char>(ch));
        }
    }
    return encoded;
}

std::string context_feature_segment(const std::string& value) {
    std::string encoded = context_path_segment(value);
    // "/values/" is a structural delimiter in inferred contexts. A feature
    // label or observed descriptor equal to "values" must not be mistaken for
    // that delimiter by developmental-learning's context parser. Escape the
    // first byte only for this reserved segment; ordinary values remain legible.
    if (encoded == "values") return "%76alues";
    return encoded;
}

std::string infer_developmental_context(const CognitiveCycleInput& input,
                                        const Goal& goal,
                                        const PerceptualRepresentation& representation) {
    if (!input.developmental_context.empty()) return input.developmental_context;

    // Keep the situation's identity (observation kind, source and feature schema)
    // ahead of observed values. This gives developmental learning a meaningful
    // hierarchy: changing a value changes the leaf evidence, not the identity of
    // the entire situation. Numeric leaves use logarithmic magnitude bands.
    std::string context = "observation/" + context_path_segment(input.observation.kind);
    if (!input.observation.source.empty())
        context += "/source/" + context_path_segment(input.observation.source);

    bool has_context_feature = false;
    std::vector<std::pair<std::string, const Scalar*>> features;
    features.reserve(representation.nodes.size());
    for (const auto& node : representation.nodes) {
        // Task and world bookkeeping identify the experiment/episode; they are
        // not observations about the current situation. In particular, a
        // world-supplied context label must not leak the answer into learning
        // when callers leave developmental_context empty.
        if (node.label == "task" || node.label == "context" ||
            node.label == "world_episode" || node.label == "world_step" ||
            node.label == "world_terminal") continue;
        const auto value = node.attributes.find("value");
        if (value != node.attributes.end())
            features.emplace_back(node.label, &value->second);
    }
    std::sort(features.begin(), features.end(),
              [](const auto& left, const auto& right) { return left.first < right.first; });

    std::vector<std::string> labels;
    std::vector<std::string> values;
    labels.reserve(features.size());
    values.reserve(features.size());
    for (const auto& [key, value_ptr] : features) {
        const auto& value = *value_ptr;
        std::string descriptor;
        if (const auto* text_value = std::get_if<std::string>(&value)) {
            if (text_value->empty()) continue;
            descriptor = *text_value;
        } else if (const auto* boolean_value = std::get_if<bool>(&value)) {
            descriptor = *boolean_value ? "true" : "false";
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
            if (numeric == 0.0) {
                descriptor = "zero";
            } else {
                descriptor = numeric < 0.0 ? "negative" : "positive";
                descriptor += "-scale-" +
                    std::to_string(std::ilogb(std::abs(numeric)));
            }
        }
        labels.push_back(context_feature_segment(key));
        values.push_back(context_feature_segment(descriptor));
        has_context_feature = true;
    }

    if (!has_context_feature) {
        // Preserve observation identity even when perception has no usable
        // features. Falling back to goal.id alone collapses distinct
        // featureless situations into one learned context and leaks strategies
        // between unrelated observations that happen to serve the same goal.
        context += "/goal/" + context_path_segment(goal.id);
        return context;
    }
    // Keep transfer within the active goal unless a future mechanism
    // explicitly establishes cross-goal equivalence.
    context += "/goal/" + context_path_segment(goal.id);
    context += "/features";
    for (const auto& label : labels) context += "/" + label;
    context += "/values";
    for (const auto& value : values) context += "/" + value;
    return context;
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

    // When the caller has not committed this cycle to a specific goal, let the
    // learned intent mechanism choose among active objectives. Goal-list order
    // is a deterministic fallback for systems that have only pending goals.
    const auto intent = brain_.intent();
    if (!intent.id.empty()) {
        const auto selected = std::find_if(
            eligible.begin(), eligible.end(),
            [&](const Goal& goal) { return goal.id == intent.id; });
        if (selected != eligible.end()) return *selected;
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
    // Capture forecasts made since the previous observation. The next actual
    // observation can resolve a forecast only when it contains the same world
    // variable; action-consequence forecasts have their own authoritative
    // execution-feedback path and are deliberately excluded here.
    std::vector<Prediction> forecasts_since_last_observation;
    std::uint64_t previous_observation_sequence = 0;
    if (input.observation.kind == "observation") {
        previous_observation_sequence =
            brain_.memory().latest_sequence_by_kind("observation");
        for (const auto& prediction : brain_.snapshot().predictions) {
            if (prediction.resolved ||
                prediction.created_sequence <= previous_observation_sequence ||
                prediction.key.rfind("action_consequence|", 0) == 0)
                continue;
            forecasts_since_last_observation.push_back(prediction);
        }
    }

    // Record the original experience first so perception providers can attach
    // semantic evidence to its durable journal sequence. Caller-supplied events
    // commonly have sequence zero; passing that through would make an otherwise
    // valid representation impossible to trace back to the experience that
    // produced it. Memory retrieval above intentionally remains pre-observation.
    result.context.observation = brain_.observe(input.observation);
    const auto& committed_observation = result.context.observation.event;

    // Resolve only forecasts made after the preceding observation and before
    // this one. A matching, newly updated belief supplies observed evidence;
    // metadata and unchanged beliefs cannot resolve a forecast. This connects
    // causal projections to the same durable prediction-error learning path as
    // action consequences without inventing counterfactual outcomes for actions
    // the brain did not take.
    if (input.observation.kind == "observation" &&
        committed_observation.sequence != 0 &&
        !forecasts_since_last_observation.empty()) {
        const auto updated_beliefs = brain_.beliefs();
        for (const auto& prediction : forecasts_since_last_observation) {
            if (prediction.created_sequence >= committed_observation.sequence) continue;
            const auto actual = std::find_if(
                updated_beliefs.begin(), updated_beliefs.end(),
                [&](const Belief& belief) {
                    return belief.key == prediction.key &&
                           belief.updated_sequence == committed_observation.sequence &&
                           belief.value.index() == prediction.predicted.index();
                });
            if (actual != updated_beliefs.end())
                (void)brain_.resolve_prediction_feedback(
                    prediction.created_sequence, actual->value);
        }
    }
    const auto& observed_event = result.context.observation.event;
    // Normalize once at the cycle boundary. Providers receive the committed
    // event (including its assigned sequence and persisted novelty appraisal),
    // while the original event remains the source of durable memory and replay.
    result.context.representation = perception_pipeline_.process(
        PerceptionInput{observed_event.timestamp_ns, observed_event.source,
                        observed_event.kind, observed_event.data},
        PerceptionContext{observed_event.sequence, {}, {}});
    // A perception provider may extract stable features that are absent from
    // the raw sensor payload. Use those features as additional retrieval cues,
    // not as asserted beliefs: this lets structured perception reconnect the
    // present situation with prior experience without treating a hypothesis as
    // a fact. The current observation is excluded because it is already journaled.
    if (input.memory_limit > 0) {
        for (const auto& node : result.context.representation.nodes) {
            if (node.attributes.empty()) continue;

            // Normalized attribute nodes store their observed value under the
            // generic "value" slot. Recall needs the semantic label as the key
            // as well; querying only {"value": ...} discards the feature that
            // connects this perception to prior raw experiences.
            Attributes retrieval_cues = node.attributes;
            if (const auto value = node.attributes.find("value");
                value != node.attributes.end() && !node.label.empty()) {
                retrieval_cues.insert_or_assign(node.label, value->second);
            }
            const auto perceptual_memories = brain_.memory().recall_ranked(
                retrieval_cues, input.memory_limit);
            for (const auto& memory : perceptual_memories) {
                if (memory.event.sequence == observed_event.sequence) continue;
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
    result.context.beliefs = brain_.beliefs();
    result.context.causal_links = brain_.causal_links();
    result.context.affective_state = brain_.affective_state();
    result.context.affective_appraisal = brain_.affective_appraisal();
    result.context.attention = brain_.attention();
    const auto disputed_facts = brain_.world().disputed_facts();
    const auto disputed_relations = brain_.world().disputed_relations();
    std::size_t disputed_beliefs = 0;
    for (auto& belief : result.context.beliefs) {
        // The belief store may already mark a conflict that is not represented
        // as a predicate in the current world-model fact set. Merge evidence
        // from both sources instead of erasing that conflict during reasoning.
        belief.disputed = belief.disputed ||
            std::any_of(disputed_facts.begin(), disputed_facts.end(),
                [&](const Fact& fact) {
                    return fact.predicate == belief.key && fact.disputed;
                });
        if (belief.disputed) ++disputed_beliefs;
    }
    ReasoningProblem problem{result.context.beliefs, result.context.causal_links, input.reasoning_steps};
    result.context.reasoning = ReasoningEngine{}.solve(problem);
    if (!result.context.causal_links.empty()) {
        // Feed supported deductions into forward simulation. Keeping reasoning
        // as a display-only side result would leave the causal predictor and
        // planner blind to conclusions already derived from current evidence.
        // Contradictory reasoning has no trusted conclusions, so fall back to
        // the observed belief set rather than simulating from an empty premise.
        const auto& simulation_assumptions =
            result.context.reasoning.valid &&
                    !result.context.reasoning.conclusions.empty()
                ? result.context.reasoning.conclusions
                : result.context.beliefs;
        const auto simulation = brain_.simulate(
            simulation_assumptions, input.planning_horizon);
        result.context.predictions.reserve(simulation.predictions.size());
        for (const auto& projected : simulation.predictions) {
            if (projected.key.empty()) continue;
            const auto prediction = brain_.predict(projected.key, projected.value, std::clamp(projected.confidence, 0.0, 1.0));
            if (!prediction.key.empty()) result.context.predictions.push_back(prediction);
        }
    }
    // Prediction confidence is evidence about how uncertain the projected
    // world state remains. Feed it into planning rather than leaving predictions
    // as a side-channel for inspection only.
    double prediction_uncertainty = 0.0;
    if (!result.context.predictions.empty()) {
        for (const auto& prediction : result.context.predictions) {
            prediction_uncertainty += 1.0 -
                std::clamp(prediction.confidence, 0.0, 1.0);
        }
        prediction_uncertainty /= static_cast<double>(
            result.context.predictions.size());
    }

    // Reflection is the brain's metacognitive readout of its current evidence.
    // Compute it before planning so uncertainty discovered by reflection can
    // influence this cycle's risk/exploration balance, rather than being only
    // a report attached after the decision has already been made.
    result.context.reflection = brain_.reflect();
    result.context.eligible_goals = brain_.eligible_goals();
    const auto selected = select_goal(input, result.context.eligible_goals);
    if (!selected.has_value()) {
        result.status = input.goal_id.has_value() ? CognitiveCycleStatus::invalid_goal : CognitiveCycleStatus::no_goal;
        return result;
    }
    result.context.selected_goal = *selected;
    if (input.candidate_actions.empty()) { result.status = CognitiveCycleStatus::no_action; return result; }
    // Reuse the strategy model's appraisal when its intent matches the goal
    // actually selected for this cycle. Explicit caller-selected goals remain
    // authoritative; a different internally preferred intent must not override
    // them.
    const auto strategy_context = brain_.strategy();
    const bool strategy_matches_goal =
        !strategy_context.intent.id.empty() &&
        strategy_context.intent.id == selected->id;
    const double goal_priority = std::clamp(
        strategy_matches_goal ? strategy_context.planning.goal_priority
                              : selected->priority,
        0.0, 1.0);
    const double goal_progress = std::clamp(
        strategy_matches_goal ? strategy_context.planning.goal_progress
                              : selected->progress,
        0.0, 1.0);
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
    // Sensory confidence must influence the decision, not remain metadata
    // attached to a representation. A provider's low-confidence interpretation
    // (or an observation with no usable features) should increase uncertainty
    // and make information-gathering actions more valuable.
    const double perceptual_uncertainty = result.context.representation.nodes.empty()
        ? 1.0
        : 1.0 - std::clamp(result.context.representation.confidence, 0.0, 1.0);
    const double uncertainty = std::max({
        attended_uncertainty,
        dispute_pressure,
        world_dispute_pressure,
        result.context.reflection.uncertainty,
        prediction_uncertainty,
        perceptual_uncertainty});
    const double strategy_deadline_pressure = strategy_matches_goal
        ? strategy_context.planning.deadline_pressure : 0.0;
    const double deadline_pressure = std::clamp(
        std::max(input.deadline_pressure, strategy_deadline_pressure), 0.0, 1.0);
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
        infer_developmental_context(input, *selected, result.context.representation);

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

    // Calibrate action consequence expectations from observed outcomes in the
    // exact developmental context. This is evidence-derived, not a fixed action
    // mapping: without valid local observations the caller's prior is preserved.
    for (auto& action : learned_actions) {
        double weighted_consequence = 0.0;
        double evidence_weight = 0.0;
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

            double consequence = 0.0;
            if (const auto* value = std::get_if<double>(&actual_it->second)) {
                consequence = *value;
            } else if (const auto* value = std::get_if<std::int64_t>(&actual_it->second)) {
                consequence = static_cast<double>(*value);
            } else {
                continue;
            }
            if (!std::isfinite(consequence)) continue;

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
            if (reliability <= 0.0) continue;
            weighted_consequence += reliability * std::clamp(consequence, -1.0, 1.0);
            evidence_weight += reliability;
        }
        if (evidence_weight > 0.0) {
            // Treat the caller's expectation as a weak prior, not as a value to
            // discard after one observation. A single noisy consequence should
            // influence learning without fully replacing the prior; repeated
            // reliable experience progressively dominates it. This is a
            // statistical regularizer, not an action-to-outcome rule.
            constexpr double prior_observation_weight = 1.0;
            const double prior_consequence =
                std::clamp(action.expected_consequence, -1.0, 1.0);
            action.expected_consequence = std::clamp(
                (prior_observation_weight * prior_consequence +
                 weighted_consequence) /
                    (prior_observation_weight + evidence_weight),
                -1.0, 1.0);
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
                  result.context.affective_state.tension,
                  result.context.reflection.uncertainty,
                  prediction_uncertainty,
                  perceptual_uncertainty}),
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

        // When the complete context is unseen, use the learned contributions
        // of its individual observed features before falling back to nearest-
        // context retrieval. This supports transfer across novel combinations
        // without treating a shared context prefix as evidence of equivalence.
        const auto feature_estimate =
            brain_.developmental_feature_strategy_estimate(
                developmental_context, action.name);
        if (feature_estimate.matched_features > 0 &&
            feature_estimate.matched_features == feature_estimate.feature_count &&
            feature_estimate.confidence >= 0.5) {
            const double influence = std::clamp(
                1.25 * feature_estimate.value * feature_estimate.confidence,
                -1.0, 1.0);
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
    if (result.context.plan.steps.empty()) { result.status = CognitiveCycleStatus::no_action; return result; }
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
    if (result.context.decisions.empty()) { result.status = CognitiveCycleStatus::no_action; return result; }
    result.context.action_assessments = brain_.action_model().assess(result.context.decisions, input.action_constraints);
    // Preserve the exact context used for learned decision bias through the
    // authorization/execution boundary; otherwise outcome learning falls back
    // to the goal ID and cannot update the context that shaped this decision.
    for (auto& assessment : result.context.action_assessments) {
        assessment.developmental_context = developmental_context;
    }
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
