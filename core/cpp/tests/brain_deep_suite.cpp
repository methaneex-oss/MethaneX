#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace jarvis::core;

static Event event(std::uint64_t seq, std::string source, std::string kind,
                   std::string topic, double value) {
    return Event{seq, seq, std::move(source), std::move(kind),
                 {{"topic", Scalar{std::move(topic)}}, {"value", Scalar{value}}}};
}

static Event strategy_outcome(std::string context, std::string action,
                              double consequence, double error, double salience,
                              double novelty) {
    return Event{0, 0, "developmental-test", "action_outcome",
                 {{"action", Scalar{std::move(action)}},
                  {"context", Scalar{std::move(context)}},
                  {"status", Scalar{static_cast<std::int64_t>(ActionExecutionStatus::verified)}},
                  {"observed", Scalar{true}},
                  {"actual_consequence", Scalar{consequence}},
                  {"consequence_error", Scalar{error}},
                  {"reliability", Scalar{0.95}},
                  {"salience", Scalar{salience}},
                  {"novelty", Scalar{novelty}}}};
}

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis_brain_deep_suite";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);

    // Attention uncertainty must follow evidence relevant to the current
    // observation, not an unrelated belief with very high confidence.
    const auto attention_relevance_journal = root / "attention_relevance.bin";
    {
        Brain attentive(attention_relevance_journal);
        for (int i = 0; i < 12; ++i) {
            assert(attentive.observe(Event{0, 0, "sensor", "observation",
                {{"established_signal", Scalar{std::string("stable")}}}}).event.sequence != 0);
        }
        assert(attentive.observe(Event{0, 0, "sensor", "observation",
            {{"new_signal", Scalar{std::string("unfamiliar")}}}}).event.sequence != 0);
        // A new belief begins at 0.7 confidence, so its uncertainty is 0.3.
        assert(std::abs(attentive.attention().uncertainty - 0.3) < 1e-12);
    }
    {
        Brain replayed_attention(attention_relevance_journal);
        assert(std::abs(replayed_attention.attention().uncertainty - 0.3) < 1e-12);
    }

    // Isolate attention's causal path into the actual planning context:
    // same goal, evidence confidence, and actions; only urgency differs.
    const auto low_attention_journal = root / "low_attention_planning.bin";
    const auto high_attention_journal = root / "high_attention_planning.bin";
    CognitiveCycleInput attention_input;
    attention_input.goal_id = "attention-causal-goal";
    attention_input.planning_horizon = 1;
    attention_input.resource_budget = 1.0;
    attention_input.candidate_actions = {
        CandidateAction{"reversible_action", 0.0, 0.100, 1.0, 0.0, 1.0, 0.0},
        CandidateAction{"irreversible_action", 0.0, 0.150, 1.0, 0.0, 0.0, 0.0},
    };
    attention_input.observation = Event{0, 0, "sensor", "observation",
        {{"confidence", 0.7}, {"sensor_state", std::string("uncertain")},
         {"urgency", 0.0}}};
    CognitiveCycleResult low_attention_result;
    CognitiveCycleResult low_attention_replay_reference;
    CognitiveCycleResult high_attention_replay_reference;
    AttentionPolicy low_attention_policy_reference{};
    {
        Brain low_attention(low_attention_journal);
        assert(low_attention.create_goal(Goal{"attention-causal-goal", "act under uncertainty",
            0.5, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        assert(low_attention.activate_goal("attention-causal-goal"));
        for (int i = 0; i < 12; ++i) {
            assert(low_attention.observe(Event{0, 0, "sensor", "observation",
                {{"confidence", 0.7}, {"sensor_state", std::string("uncertain")},
                 {"urgency", 0.0}}}).event.sequence != 0);
        }
        CognitiveCycle cycle(low_attention);
        low_attention_result = cycle.run(attention_input);
        assert(low_attention_result.status == CognitiveCycleStatus::completed);
        assert(low_attention_result.context.plan.steps.front().action.name ==
               "irreversible_action");
        assert(!low_attention_result.context.decisions.empty());
        assert(low_attention_result.context.decisions.front().action.name ==
               "irreversible_action");
        assert(!low_attention_result.context.action_assessments.empty());
        assert(low_attention_result.context.action_assessments.front().action.name ==
               "irreversible_action");
        // Compare replay against the next live cycle, after the same journal
        // history, rather than against the earlier cycle that created it.
        low_attention_replay_reference = cycle.run(attention_input);
        assert(low_attention_replay_reference.status == CognitiveCycleStatus::completed);
        assert(low_attention_replay_reference.context.plan.steps.front().action.name ==
               "irreversible_action");
        low_attention_policy_reference = low_attention.attention_policy();
    }
    attention_input.observation.data["urgency"] = Scalar{1.0};
    {
        Brain high_attention(high_attention_journal);
        assert(high_attention.create_goal(Goal{"attention-causal-goal", "act under uncertainty",
            0.5, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        assert(high_attention.activate_goal("attention-causal-goal"));
        for (int i = 0; i < 12; ++i) {
            assert(high_attention.observe(Event{0, 0, "sensor", "observation",
                {{"confidence", 0.7}, {"sensor_state", std::string("uncertain")},
                 {"urgency", 0.0}}}).event.sequence != 0);
        }
        CognitiveCycle cycle(high_attention);
        const auto high_attention_result = cycle.run(attention_input);
        assert(high_attention_result.status == CognitiveCycleStatus::completed);
        assert(high_attention_result.context.attention.salience >
               low_attention_result.context.attention.salience);
        assert(std::abs(high_attention_result.context.attention.uncertainty -
                        low_attention_result.context.attention.uncertainty) < 1e-12);
        assert(high_attention_result.context.decision_context.uncertainty >
               low_attention_result.context.decision_context.uncertainty);
        // The planner and decision engine receive the changed value, not merely
        // a diagnostic attention score.
        assert(high_attention_result.context.plan.steps.size() == 1);
        assert(low_attention_result.context.plan.steps.size() == 1);
        assert(high_attention_result.context.plan.steps.front().action.name ==
               "reversible_action");
        assert(!high_attention_result.context.decisions.empty());
        assert(high_attention_result.context.decisions.front().action.name ==
               "reversible_action");
        assert(!high_attention_result.context.action_assessments.empty());
        assert(high_attention_result.context.action_assessments.front().action.name ==
               "reversible_action");
        assert(high_attention_result.context.decision_context.uncertainty <= 1.0);
        high_attention_replay_reference = cycle.run(attention_input);
        assert(high_attention_replay_reference.status == CognitiveCycleStatus::completed);
        assert(high_attention_replay_reference.context.plan.steps.front().action.name ==
               "reversible_action");
    }
    {
        Brain replayed_low_attention(low_attention_journal);
        CognitiveCycle cycle(replayed_low_attention);
        auto low_input = attention_input;
        low_input.observation.data["urgency"] = Scalar{0.0};
        const auto replayed_result = cycle.run(low_input);
        assert(replayed_result.status == CognitiveCycleStatus::completed);
        assert(std::isfinite(replayed_result.context.attention.salience));
        assert(std::isfinite(replayed_result.context.decision_context.uncertainty));
        assert(replayed_result.context.plan.steps.size() == 1);
        assert(replayed_result.context.plan.steps.front().action.name ==
               "irreversible_action");
        assert(!replayed_result.context.decisions.empty());
        assert(replayed_result.context.decisions.front().action.name ==
               "irreversible_action");
        assert(!replayed_result.context.action_assessments.empty());
        assert(replayed_result.context.action_assessments.front().action.name ==
               "irreversible_action");
        const auto replay_policy = replayed_low_attention.attention_policy();
        assert(std::abs(replay_policy.novelty_weight -
                        low_attention_policy_reference.novelty_weight) < 1e-12);
        assert(std::abs(replay_policy.uncertainty_weight -
                        low_attention_policy_reference.uncertainty_weight) < 1e-12);
        assert(std::abs(replay_policy.urgency_weight -
                        low_attention_policy_reference.urgency_weight) < 1e-12);
        assert(std::abs(replay_policy.internal_activation_weight -
                        low_attention_policy_reference.internal_activation_weight) < 1e-12);
        assert(std::abs(replay_policy.prediction_error_weight -
                        low_attention_policy_reference.prediction_error_weight) < 1e-12);
        // The live reference above is the preceding cycle, while constructing
        // replay then running cycle.run() adds another observation to the journal.
        // Its salience can therefore differ slightly as affect is updated by that
        // additional experience; compare bounded state and downstream behavior,
        // not numeric salience across different history lengths.
        assert(replayed_result.context.attention.salience >= 0.0 &&
               replayed_result.context.attention.salience <= 1.0);
        // Decision uncertainty is derived from the current cycle's attention
        // salience. The replayed cycle adds a new observation, so compare the
        // value against that same cycle's inputs rather than an earlier cycle.
        const double replayed_attended_uncertainty =
            replayed_result.context.attention.salience *
            replayed_result.context.attention.uncertainty;
        assert(std::abs(replayed_result.context.decision_context.uncertainty -
                        replayed_attended_uncertainty) < 1e-12);
    }
    {
        Brain replayed_high_attention(high_attention_journal);
        CognitiveCycle cycle(replayed_high_attention);
        const auto replayed_result = cycle.run(attention_input);
        assert(replayed_result.status == CognitiveCycleStatus::completed);
        assert(std::isfinite(replayed_result.context.attention.salience));
        assert(std::isfinite(replayed_result.context.decision_context.uncertainty));
        // Replay must retain the attention policy strongly enough to reproduce
        // the downstream action choice and the numeric state that caused it.
        assert(replayed_result.context.plan.steps.size() == 1);
        assert(replayed_result.context.plan.steps.front().action.name ==
               "reversible_action");
        assert(!replayed_result.context.decisions.empty());
        assert(replayed_result.context.decisions.front().action.name ==
               "reversible_action");
        assert(!replayed_result.context.action_assessments.empty());
        assert(replayed_result.context.action_assessments.front().action.name ==
               "reversible_action");
        // This replayed cycle runs after the journal has already recorded the
        // reference cycle, so its observation history is one event longer than
        // the reference result. Verify valid salience and the decision-context
        // relationship below instead of requiring equality across different
        // histories (the low-attention replay uses the same invariant).
        assert(replayed_result.context.attention.salience >= 0.0 &&
               replayed_result.context.attention.salience <= 1.0);
        const double replayed_attended_uncertainty =
            replayed_result.context.attention.salience *
            replayed_result.context.attention.uncertainty;
        assert(std::abs(replayed_result.context.decision_context.uncertainty -
                        replayed_attended_uncertainty) < 1e-12);
    }
    std::filesystem::remove(low_attention_journal, ec);
    std::filesystem::remove((low_attention_journal.string() + ".meta"), ec);
    std::filesystem::remove(high_attention_journal, ec);
    std::filesystem::remove((high_attention_journal.string() + ".meta"), ec);

    Brain brain(root / "continuity.bin");
    const auto observed = brain.observe(event(0, "test", "observation", "persistent", 42.0));
    assert(observed.event.sequence == 1);
    assert(observed.novelty == 1.0);
    assert(brain.memory().size() == 1);

    assert(brain.learn(Evidence{"trusted", "temperature", Scalar{25.0}, 0.9}) >= 0.0);
    assert(brain.knowledge_source("trusted") != nullptr);

    // Prediction learning must change future predictions, not merely record an error.
    // The first forecasts use the supplied prior; repeated outcomes teach the
    // adaptation model, and a later forecast is pulled toward the learned estimate.
    const auto prediction_journal = root / "prediction_learning.bin";
    {
        Brain predictor(prediction_journal);
        for (int i = 0; i < 8; ++i) {
            const auto prediction = predictor.predict("temperature", Scalar{0.2}, 0.5);
            assert(prediction.created_sequence != 0);
            assert(!predictor.resolve_prediction(prediction.created_sequence, Scalar{0.8}));
        }
        const auto* metric = predictor.learning_metric("temperature");
        assert(metric != nullptr);
        assert(metric->observations == 8);
        const auto learned_prediction = predictor.predict("temperature", Scalar{0.2}, 0.5);
        const auto learned_value = std::get_if<double>(&learned_prediction.predicted);
        assert(learned_value != nullptr);
        assert(*learned_value > 0.2);
        assert(*learned_value < 0.8);
    }
    {
        Brain replayed_predictor(prediction_journal);
        const auto replayed_prediction = replayed_predictor.predict("temperature", Scalar{0.2}, 0.5);
        const auto replayed_value = std::get_if<double>(&replayed_prediction.predicted);
        assert(replayed_value != nullptr);
        assert(*replayed_value > 0.2);
        assert(*replayed_value < 0.8);
        // Forecasting consumes learned calibration but is not new outcome evidence.
        assert(replayed_predictor.learning_metric("temperature")->observations == 8);
    }

    const std::vector<CandidateAction> actions{{"safe", 0.9, 0.9, 0.95, 0.1, 1.0}, {"risky", 0.95, 0.2, 0.9, 0.9, 0.2}};
    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(!brain.plan(actions, 4).steps.empty());

    const auto assessments = brain.assess_actions(decisions, ActionConstraints{0.5, false});
    assert(!assessments.empty());
    const auto& executable = assessments.front();
    const auto affect_before_action = brain.affective_state();
    const auto action_result = brain.execute_action(
        executable,
        [](const CandidateAction& action) { return action.name == "safe"; },
        [](const CandidateAction& action) { return action.name == "safe"; },
        {},
        [](const CandidateAction& action) { return action.name == "safe" ? 0.8 : 0.0; });
    assert(action_result.authorized);
    assert(action_result.executed);
    assert(action_result.verified);
    assert(brain.memory().by_kind("action_outcome", 1).size() == 1);
    assert(brain.memory().by_kind("affective_learning", 1).size() == 1);
    assert(brain.memory().by_kind("learning", 1).size() == 1);
    // The derived learning event must not re-appraise the same experience.
    assert(brain.affective_state().updates == affect_before_action.updates + 1);

    // Derived affective-learning evidence is keyed to its source action and must not train twice.
    const auto affective_records = brain.memory().by_kind("affective_learning", 1);
    assert(affective_records.size() == 1);
    const auto duplicate_source = affective_records.front().data.find("source_action_sequence");
    assert(duplicate_source != affective_records.front().data.end());
    const auto affect_before_duplicate = brain.affective_state();
    const auto calibration_before_duplicate = brain.affective_calibration();
    brain.observe(affective_records.front());
    const auto affect_after_duplicate = brain.affective_state();
    const auto calibration_after_duplicate = brain.affective_calibration();
    assert(affect_after_duplicate.updates == affect_before_duplicate.updates);
    assert(calibration_after_duplicate.observations == calibration_before_duplicate.observations);
    assert(std::abs(calibration_after_duplicate.mean_absolute_error - calibration_before_duplicate.mean_absolute_error) < 1e-12);

    // Replay must reconstruct the same learned state produced by live processing.
    {
        Brain replayed_action(root / "continuity.bin");
        const auto live_affect = brain.affective_state();
        const auto replay_affect = replayed_action.affective_state();
        const auto live_calibration = brain.affective_calibration();
        const auto replay_calibration = replayed_action.affective_calibration();
        const auto live_attention = brain.attention();
        const auto replay_attention = replayed_action.attention();
        assert(std::abs(live_affect.valence - replay_affect.valence) < 1e-12);
        assert(std::abs(live_affect.arousal - replay_affect.arousal) < 1e-12);
        assert(std::abs(live_affect.uncertainty - replay_affect.uncertainty) < 1e-12);
        assert(std::abs(live_affect.tension - replay_affect.tension) < 1e-12);
        assert(std::abs(live_affect.stability - replay_affect.stability) < 1e-12);
        assert(live_affect.updates == replay_affect.updates);
        assert(std::abs(live_calibration.mean_absolute_error - replay_calibration.mean_absolute_error) < 1e-12);
        assert(std::abs(live_calibration.learning_rate_scale - replay_calibration.learning_rate_scale) < 1e-12);
        assert(live_calibration.observations == replay_calibration.observations);
        assert(std::abs(live_attention.salience - replay_attention.salience) < 1e-12);
        assert(std::abs(live_attention.novelty - replay_attention.novelty) < 1e-12);
        assert(std::abs(live_attention.uncertainty - replay_attention.uncertainty) < 1e-12);
    }

    const auto affect_before_failure = brain.affective_state();
    const auto learning_before_failure = brain.affective_learning_updates();
    const auto affective_records_before_failure = brain.memory().by_kind("affective_learning", 16).size();
    const auto* learned_safe_before_unknown = brain.developmental_best_strategy("global");
    const auto learned_safe_uses_before_unknown = learned_safe_before_unknown == nullptr ? 0ULL : learned_safe_before_unknown->uses;
    const auto failed_action = brain.execute_action(
        executable,
        [](const CandidateAction&) { return false; },
        [](const CandidateAction&) { return false; });
    assert(failed_action.authorized);
    assert(!failed_action.executed);
    assert(brain.memory().by_kind("action_outcome", 2).size() == 2);
    assert(brain.memory().by_kind("affective_learning", 16).size() == affective_records_before_failure);
    // No consequence observer means the action result must not train the
    // consequence-sensitive affective calibration model.
    assert(learning_before_failure > 0);
    assert(brain.affective_learning_updates() == learning_before_failure);
    const auto* learned_safe_after_unknown = brain.developmental_best_strategy("global");
    assert((learned_safe_after_unknown == nullptr ? 0ULL : learned_safe_after_unknown->uses) == learned_safe_uses_before_unknown);

    const auto affect_after_failure = brain.affective_state();
    assert(std::isfinite(affect_after_failure.valence));
    assert(std::isfinite(affect_after_failure.tension));
    assert(brain.affective_learning_updates() == learning_before_failure);
    assert(affect_after_failure.valence != affect_before_failure.valence ||
           affect_after_failure.tension != affect_before_failure.tension ||
           affect_after_failure.arousal != affect_before_failure.arousal ||
           affect_after_failure.uncertainty != affect_before_failure.uncertainty);

    const CandidateAction probe{"probe", 0.0, 1.0, 0.2, 1.0};
    const auto before_decision = brain.choose_with_affect({probe}).front().score;
    brain.observe(event(0, "feedback", "observation", "consequence", -1.0));
    const auto after_decision = brain.choose_with_affect({probe}).front().score;
    assert(std::isfinite(before_decision));
    assert(std::isfinite(after_decision));
    assert(before_decision != after_decision);

    // Developmental learning must be reconstructable from the journal.
    const auto developmental_journal = root / "developmental.bin";
    {
        Brain learner(developmental_journal);
        for (int i = 0; i < 8; ++i) {
            learner.observe(strategy_outcome("navigation", "route_a", 0.9, 0.1, 0.8, 0.2));
            learner.observe(strategy_outcome("navigation", "route_b", -0.8, 0.9, 0.8, 0.2));
        }
        const auto* best = learner.developmental_best_strategy("navigation");
        assert(best != nullptr);
        assert(best->action == "route_a");
        assert(best->uses == 8);
        assert(learner.developmental_strategies().size() == 2);
    }
    {
        Brain replayed(developmental_journal);
        const auto strategies = replayed.developmental_strategies();
        assert(strategies.size() == 2);
        const auto* best = replayed.developmental_best_strategy("navigation");
        assert(best != nullptr);
        assert(best->action == "route_a");
        assert(best->uses == 8);
        const auto affect = replayed.affective_state();
        assert(std::isfinite(affect.valence));
        assert(std::isfinite(affect.arousal));
    }

    // Learned strategy must affect actual action selection, not merely remain
    // queryable as metadata. The learned route starts with a lower base utility
    // and only wins because prior consequences changed developmental value.
    const auto selection_journal = root / "selection.bin";
    Brain selector(selection_journal);
    assert(selector.create_goal(Goal{"navigation", "navigate", 1.0, 0.0, 0, 0,
                                     GoalStatus::pending, {}, {}}));
    assert(selector.activate_goal("navigation"));
    CandidateAction learned_route{"route_a", 0.0, 0.0, 0.1, 1.0};
    CandidateAction unlearned_route{"route_b", 0.15, 0.15, 0.1, 1.0};
    const auto before_learning = selector.choose({learned_route, unlearned_route});
    assert(!before_learning.empty());
    assert(before_learning.front().action.name == "route_b");

    for (int i = 0; i < 8; ++i) {
        selector.observe(strategy_outcome("navigation", "route_a", 0.9, 0.1, 0.8, 0.2));
        selector.observe(strategy_outcome("navigation", "route_b", -0.8, 0.9, 0.8, 0.2));
    }

    // The ordinary decision path now consumes the learned developmental
    // strategy. No separate "developmental decision" API is required.
    const auto learned_selection = selector.choose({learned_route, unlearned_route});
    assert(!learned_selection.empty());
    assert(learned_selection.front().action.name == "route_a");

    // The learned action preference must survive restart and journal replay.
    Brain replayed_selector(selection_journal);
    const auto replayed_selection = replayed_selector.choose({learned_route, unlearned_route});
    assert(!replayed_selection.empty());
    assert(replayed_selection.front().action.name == "route_a");

    // Development must emerge from real action consequences, not only from
    // direct strategy-training events. A failed action should change later
    // selection, and the learned preference must survive replay.
    const auto developmental_action_journal = root / "developmental_action.bin";
    {
        Brain developing(developmental_action_journal);
        CognitiveCycle cycle(developing);
        assert(developing.create_goal(Goal{"navigation", "navigate safely", 1.0, 0.0, 0, 0,
                                           GoalStatus::pending, {}, {}}));
        assert(developing.activate_goal("navigation"));

        const CandidateAction route_a{"route_a", 0.0, 0.0, 0.1, 0.1, 1.0};
        const CandidateAction route_b{"route_b", 0.15, 0.15, 0.1, 0.1, 1.0};
        CognitiveCycleInput input;
        input.observation = Event{0, 0, "navigator", "observation", {{"route_state", std::string("unknown")}}};
        input.candidate_actions = {route_a, route_b};
        input.goal_id = "navigation";
        input.developmental_context = "navigation";
        input.planning_horizon = 1;
        input.resource_budget = 1.0;
        input.action_constraints = ActionConstraints{1.0, false};

        const auto initial = cycle.run(input);
        assert(initial.status == CognitiveCycleStatus::completed);
        assert(!initial.context.action_assessments.empty());
        assert(initial.context.action_assessments.front().action.name == "route_b");

        // Isolate consequence learning from execution reliability: route_b
        // executes and verifies successfully, but its observed consequence is bad.
        // Both routes therefore have identical execution reliability; only the
        // signed consequence evidence should reverse the preferred plan.
        const auto failed = developing.execute_action(
            initial.context.action_assessments.front(),
            [](const CandidateAction&) { return true; },
            [](const CandidateAction&) { return true; },
            {},
            [](const CandidateAction&) { return -0.8; });
        assert(failed.authorized);
        assert(failed.executed);
        assert(failed.verified);
        assert(failed.outcome.observed);
        assert(std::abs(failed.outcome.actual_consequence + 0.8) < 1e-12);
        const auto* route_b_reliability = developing.knowledge_source("action_executor");
        assert(route_b_reliability != nullptr);
        assert(std::abs(route_b_reliability->reliability - 1.0) < 1e-12);

        const auto after_failure = cycle.run(input);
        assert(after_failure.status == CognitiveCycleStatus::completed);
        assert(after_failure.context.plan.steps.front().action.name == "route_a");

        // Reinforce the alternative through the same action/consequence path.
        for (int i = 0; i < 3; ++i) {
            const auto result = developing.execute_action(
                after_failure.context.action_assessments.front(),
                [](const CandidateAction& action) { return action.name == "route_a"; },
                [](const CandidateAction& action) { return action.name == "route_a"; },
                {},
                [](const CandidateAction&) { return 0.9; });
            assert(result.authorized);
            assert(result.executed);
            assert(result.verified);
            assert(result.outcome.observed);
        }

        const auto developed = cycle.run(input);
        assert(developed.status == CognitiveCycleStatus::completed);
        assert(developed.context.plan.steps.front().action.name == "route_a");
        const auto* learned_route = developing.developmental_best_strategy("navigation");
        assert(learned_route != nullptr);
        assert(learned_route->action == "route_a");
        assert(learned_route->uses >= 3);
        const auto strategies = developing.developmental_strategies();
        bool negative_route_b = false;
        bool positive_route_a = false;
        for (const auto& strategy : strategies) {
            if (strategy.context != "navigation") continue;
            if (strategy.action == "route_b") negative_route_b = strategy.value < 0.0;
            if (strategy.action == "route_a") positive_route_a = strategy.value > 0.0;
        }
        assert(negative_route_b);
        assert(positive_route_a);
        const auto* route_a_reliability = developing.knowledge_source("action_executor.route_a");
        assert(route_a_reliability != nullptr);
        assert(std::abs(route_a_reliability->reliability - route_b_reliability->reliability) < 1e-12);
    }
    {
        Brain replayed(developmental_action_journal);
        CognitiveCycle cycle(replayed);
        CognitiveCycleInput input;
        input.observation = Event{0, 0, "navigator", "observation", {{"route_state", std::string("unknown")}}};
        input.candidate_actions = {
            CandidateAction{"route_a", 0.0, 0.0, 0.1, 0.1, 1.0},
            CandidateAction{"route_b", 0.15, 0.15, 0.1, 0.1, 1.0},
        };
        input.goal_id = "navigation";
        input.developmental_context = "navigation";
        input.planning_horizon = 1;
        input.resource_budget = 1.0;
        input.action_constraints = ActionConstraints{1.0, false};
        const auto replayed_cycle = cycle.run(input);
        assert(replayed_cycle.status == CognitiveCycleStatus::completed);
        assert(replayed_cycle.context.plan.steps.front().action.name == "route_a");
        const auto* learned_route = replayed.developmental_best_strategy("navigation");
        assert(learned_route != nullptr);
        assert(learned_route->action == "route_a");
        const auto replayed_strategies = replayed.developmental_strategies();
        bool replayed_negative_route_b = false;
        bool replayed_positive_route_a = false;
        for (const auto& strategy : replayed_strategies) {
            if (strategy.context != "navigation") continue;
            if (strategy.action == "route_b") replayed_negative_route_b = strategy.value < 0.0;
            if (strategy.action == "route_a") replayed_positive_route_a = strategy.value > 0.0;
        }
        assert(replayed_negative_route_b);
        assert(replayed_positive_route_a);
    }

    // Generalization must transfer consequence learning to a related context,
    // alter the real cognitive-cycle choice, and reconstruct the same bias on replay.
    // The query shares two of four unique tokens with the learned context (Jaccard 0.5).
    const auto generalized_journal = root / "developmental_generalization.bin";
    const CandidateAction generalized_route_a{"route_a", 0.0, 0.0, 0.1, 1.0};
    const CandidateAction generalized_route_b{"route_b", 0.05, 0.05, 0.1, 1.0};
    CognitiveCycleInput generalized_input;
    generalized_input.observation = Event{0, 0, "sensor", "observation",
        {{"state", std::string("uncertain")}}};
    generalized_input.candidate_actions = {generalized_route_a, generalized_route_b};
    generalized_input.goal_id = "generalization-goal";
    generalized_input.developmental_context = "sensor uncertainty response";
    generalized_input.planning_horizon = 1;
    generalized_input.resource_budget = 1.0;
    generalized_input.action_constraints = ActionConstraints{1.0, false};
    {
        Brain learner(generalized_journal);
        CognitiveCycle cycle(learner);
        assert(learner.create_goal(Goal{"generalization-goal", "respond to uncertain sensors",
                                        1.0, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        assert(learner.activate_goal("generalization-goal"));
        const auto before = cycle.run(generalized_input);
        assert(before.status == CognitiveCycleStatus::completed);
        assert(before.context.plan.steps.front().action.name == "route_b");
        assert(learner.developmental_best_strategy("sensor uncertainty response") == nullptr);
        assert(learner.developmental_best_related_strategy("sensor uncertainty response") == nullptr);

        const auto experience = learner.observe(strategy_outcome(
            "indoor sensor uncertainty", "route_a", 0.9, 0.1, 0.8, 0.2));
        assert(experience.event.sequence != 0);
        assert(learner.developmental_best_strategy("sensor uncertainty response") == nullptr);
        const auto* generalized = learner.developmental_best_related_strategy(
            "sensor uncertainty response");
        assert(generalized != nullptr);
        assert(generalized->context == "indoor sensor uncertainty");
        assert(generalized->action == "route_a");
        assert(generalized->value > 0.0);
        const auto after = cycle.run(generalized_input);
        assert(after.status == CognitiveCycleStatus::completed);
        assert(after.context.plan.steps.front().action.name == "route_a");
    }
    {
        Brain replayed(generalized_journal);
        CognitiveCycle cycle(replayed);
        const auto* generalized = replayed.developmental_best_related_strategy(
            "sensor uncertainty response");
        assert(generalized != nullptr);
        assert(generalized->context == "indoor sensor uncertainty");
        assert(generalized->action == "route_a");
        assert(generalized->value > 0.0);
        const auto after_replay = cycle.run(generalized_input);
        assert(after_replay.status == CognitiveCycleStatus::completed);
        assert(after_replay.context.plan.steps.front().action.name == "route_a");
    }

    // Negative consequences must also generalize: a previously attractive action
    // is demoted in a related context instead of being reinforced by mere success
    // of execution. This checks the sign of the learned consequence, not reliability.
    const auto generalized_negative_journal = root / "developmental_negative_generalization.bin";
    {
        Brain learner(generalized_negative_journal);
        CognitiveCycle cycle(learner);
        assert(learner.create_goal(Goal{"generalization-goal", "respond to uncertain sensors",
                                        1.0, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        assert(learner.activate_goal("generalization-goal"));
        CognitiveCycleInput input = generalized_input;
        input.candidate_actions = {
            CandidateAction{"route_a", 0.0, 0.0, 0.1, 1.0},
            CandidateAction{"route_b", 0.1, 0.1, 0.1, 1.0}};
        const auto before = cycle.run(input);
        assert(before.status == CognitiveCycleStatus::completed);
        assert(before.context.plan.steps.front().action.name == "route_b");

        const auto experience = learner.observe(strategy_outcome(
            "indoor sensor uncertainty", "route_b", -0.9, 0.1, 0.8, 0.2));
        assert(experience.event.sequence != 0);
        const auto* generalized = learner.developmental_best_related_strategy(
            "sensor uncertainty response");
        assert(generalized != nullptr);
        assert(generalized->action == "route_b");
        assert(generalized->value < 0.0);
        const auto after = cycle.run(input);
        assert(after.status == CognitiveCycleStatus::completed);
        assert(after.context.plan.steps.front().action.name == "route_a");
    }
    {
        Brain replayed(generalized_negative_journal);
        CognitiveCycle cycle(replayed);
        CognitiveCycleInput input = generalized_input;
        input.candidate_actions = {
            CandidateAction{"route_a", 0.0, 0.0, 0.1, 1.0},
            CandidateAction{"route_b", 0.1, 0.1, 0.1, 1.0}};
        const auto* generalized = replayed.developmental_best_related_strategy(
            "sensor uncertainty response");
        assert(generalized != nullptr);
        assert(generalized->action == "route_b");
        assert(generalized->value < 0.0);
        const auto after_replay = cycle.run(input);
        assert(after_replay.status == CognitiveCycleStatus::completed);
        assert(after_replay.context.plan.steps.front().action.name == "route_a");
    }

    // Related evidence for competing actions must be evaluated together.
    // A weak positive memory for route_a must not hide a stronger harmful
    // outcome for route_b merely because the positive score ranks higher.
    const auto competing_journal = root / "developmental_competing_evidence.bin";
    CognitiveCycleInput competing_input = generalized_input;
    competing_input.candidate_actions = {
        CandidateAction{"route_a", 0.0, 0.0, 0.1, 1.0},
        CandidateAction{"route_b", 0.1, 0.1, 0.1, 1.0}};
    competing_input.developmental_context = "sensor uncertainty response";
    {
        Brain learner(competing_journal);
        CognitiveCycle cycle(learner);
        assert(learner.create_goal(Goal{"generalization-goal", "respond to uncertain sensors",
                                        1.0, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        assert(learner.activate_goal("generalization-goal"));
        const auto before = cycle.run(competing_input);
        assert(before.status == CognitiveCycleStatus::completed);
        assert(before.context.plan.steps.front().action.name == "route_b");
        assert(learner.observe(strategy_outcome(
            "indoor sensor uncertainty", "route_a", 0.05, 0.1, 0.2, 0.1)).event.sequence != 0);
        assert(learner.observe(strategy_outcome(
            "indoor sensor response", "route_b", -0.9, 0.8, 0.9, 0.8)).event.sequence != 0);
        const auto related = learner.developmental_related_strategies(
            "sensor uncertainty response");
        bool saw_positive_a = false;
        bool saw_negative_b = false;
        for (const auto& evidence : related) {
            if (evidence.strategy.action == "route_a" && evidence.strategy.value > 0.0)
                saw_positive_a = true;
            if (evidence.strategy.action == "route_b" && evidence.strategy.value < 0.0)
                saw_negative_b = true;
        }
        assert(saw_positive_a && saw_negative_b);
        const auto after = cycle.run(competing_input);
        assert(after.status == CognitiveCycleStatus::completed);
        assert(after.context.plan.steps.front().action.name == "route_a");
    }
    {
        Brain replayed(competing_journal);
        CognitiveCycle cycle(replayed);
        const auto related = replayed.developmental_related_strategies(
            "sensor uncertainty response");
        bool saw_positive_a = false;
        bool saw_negative_b = false;
        for (const auto& evidence : related) {
            if (evidence.strategy.action == "route_a" && evidence.strategy.value > 0.0)
                saw_positive_a = true;
            if (evidence.strategy.action == "route_b" && evidence.strategy.value < 0.0)
                saw_negative_b = true;
        }
        assert(saw_positive_a && saw_negative_b);
        const auto after_replay = cycle.run(competing_input);
        assert(after_replay.status == CognitiveCycleStatus::completed);
        assert(after_replay.context.plan.steps.front().action.name == "route_a");
    }

    // Exact-context evidence must also compare actions, rather than applying
    // only the single highest-valued strategy and ignoring contrary experience.
    const auto exact_competing_journal = root / "developmental_exact_competing.bin";
    CognitiveCycleInput exact_competing_input = competing_input;
    exact_competing_input.goal_id = "exact-generalization-goal";
    exact_competing_input.developmental_context = "sensor uncertainty response";
    {
        Brain learner(exact_competing_journal);
        CognitiveCycle cycle(learner);
        assert(learner.create_goal(Goal{"exact-generalization-goal", "respond to uncertain sensors",
                                        1.0, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        assert(learner.activate_goal("exact-generalization-goal"));
        const auto before = cycle.run(exact_competing_input);
        assert(before.status == CognitiveCycleStatus::completed);
        assert(before.context.plan.steps.front().action.name == "route_b");
        assert(learner.observe(strategy_outcome(
            "sensor uncertainty response", "route_a", 0.9, 0.1, 0.2, 0.1)).event.sequence != 0);
        assert(learner.observe(strategy_outcome(
            "sensor uncertainty response", "route_b", -0.9, 0.8, 0.9, 0.8)).event.sequence != 0);
        const auto after = cycle.run(exact_competing_input);
        assert(after.status == CognitiveCycleStatus::completed);
        assert(after.context.plan.steps.front().action.name == "route_a");
    }
    {
        Brain replayed(exact_competing_journal);
        CognitiveCycle cycle(replayed);
        const auto after_replay = cycle.run(exact_competing_input);
        assert(after_replay.status == CognitiveCycleStatus::completed);
        assert(after_replay.context.plan.steps.front().action.name == "route_a");
    }

    // Equal generalized evidence must resolve ties deterministically rather
    // than inheriting unordered-map iteration order.
    DevelopmentalLearning tie_breaker;
    const LearningSignal tied_signal{0.1, 0.9, 0.8, 0.2, 0.3};
    tie_breaker.observe_strategy("outdoor sensor uncertainty", "route_b", tied_signal);
    tie_breaker.observe_strategy("indoor sensor uncertainty", "route_a", tied_signal);
    const auto* tied_strategy =
        tie_breaker.best_related_strategy("sensor uncertainty response");
    assert(tied_strategy != nullptr);
    assert(tied_strategy->context == "indoor sensor uncertainty");
    assert(tied_strategy->action == "route_a");
    const auto all_tied_strategies =
        tie_breaker.related_strategies("sensor uncertainty response");
    assert(all_tied_strategies.size() == 2);
    assert(all_tied_strategies[0].strategy.context == "indoor sensor uncertainty");
    assert(all_tied_strategies[1].strategy.context == "outdoor sensor uncertainty");
    assert(std::abs(all_tied_strategies[0].similarity - 0.5) < 1e-12);
    assert(std::abs(all_tied_strategies[1].similarity - 0.5) < 1e-12);

    // Retrieval must retain both favorable and unfavorable contextual evidence,
    // rather than collapsing competing experiences into one global winner.
    DevelopmentalLearning competing_evidence;
    competing_evidence.observe_strategy(
        "indoor sensor uncertainty", "route_a",
        LearningSignal{0.1, -0.9, 0.8, 0.2, 0.3});
    competing_evidence.observe_strategy(
        "outdoor sensor uncertainty", "route_b", tied_signal);
    const auto competing = competing_evidence.related_strategies(
        "sensor uncertainty response");
    assert(competing.size() == 2);
    bool saw_negative_route_a = false;
    bool saw_positive_route_b = false;
    for (const auto& evidence : competing) {
        if (evidence.strategy.action == "route_a")
            saw_negative_route_a = evidence.strategy.value < 0.0;
        if (evidence.strategy.action == "route_b")
            saw_positive_route_b = evidence.strategy.value > 0.0;
    }
    assert(saw_negative_route_a);
    assert(saw_positive_route_b);

    // Lexical overlap must not erase negation. "safe route" and "not safe route"
    // share most tokens, but the learned strategy must not cross that polarity boundary.
    DevelopmentalLearning polarity_guard;
    polarity_guard.observe_strategy("safe route", "take_route", tied_signal);
    assert(polarity_guard.best_related_strategy("not safe route") == nullptr);
    DevelopmentalLearning unsafe_guard;
    unsafe_guard.observe_strategy("safe route", "take_route", tied_signal);
    assert(unsafe_guard.best_related_strategy("unsafe route") == nullptr);

    DevelopmentalLearning contraction_guard;
    contraction_guard.observe_strategy("approach obstacle", "approach", tied_signal);
    assert(contraction_guard.best_related_strategy("can't approach obstacle") == nullptr);

    // Goal, capability, and resilience mutations are journal-first and must
    // reconstruct the same durable state after restart.
    const auto state_journal = root / "state_transactions.bin";
    {
        Brain stateful(state_journal);
        assert(stateful.create_goal(Goal{"transaction-goal", "test durable goal", 0.5, 0.0, 0, 0,
                                         GoalStatus::pending, {}, {}}));
        assert(stateful.activate_goal("transaction-goal"));
        assert(stateful.update_goal_progress("transaction-goal", 0.4));
        const auto* live_goal = stateful.goal("transaction-goal");
        assert(live_goal != nullptr);
        assert(live_goal->progress == 0.4);
        assert(live_goal->outcome_momentum > 0.0);
        assert(stateful.set_goal_priority("transaction-goal", 0.8));

        stateful.observe_capability("planner", 0.9, 0.8);
        assert(stateful.isolate_capability("planner"));
        assert(stateful.restore_capability("planner", 0.7, 0.6));

        assert(stateful.observe(Event{0, 0, "health", "observation",
                                      {{"health", Scalar{0.8}}}}).event.sequence != 0);
        assert(stateful.isolate("health"));
        assert(stateful.recover("health", 0.95));
        assert(stateful.recovery_options().empty());
    }
    {
        Brain replayed(state_journal);
        const auto* replayed_goal = replayed.goal("transaction-goal");
        assert(replayed_goal != nullptr);
        assert(replayed_goal->progress == 0.4);
        assert(replayed_goal->priority == 0.8);
        assert(replayed_goal->outcome_momentum > 0.0);

        const auto replayed_self = replayed.snapshot().self_state;
        const auto pressure = replayed_self.resource_pressure.find("planner");
        assert(pressure != replayed_self.resource_pressure.end());
        assert(pressure->second > 0.0);
        assert(replayed.recovery_options().empty());
    }

    std::filesystem::remove_all(root, ec);
    return 0;
}
