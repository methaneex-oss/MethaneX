#include "jarvis/core/brain.hpp"
#include "jarvis/core/cognitive_cycle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

static double score_for(const std::vector<Decision>& decisions, const std::string& action) {
    for (const auto& decision : decisions) {
        if (decision.action.name == action) return decision.score;
    }
    return -1.0e9;
}

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_developmental_brain_integration.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    {
        Brain brain(path);
        const auto first = brain.predict("temperature", 20.0, 0.8);
        const auto second = brain.predict("temperature", 30.0, 0.9);
        assert(first.created_sequence != 0);
        assert(second.created_sequence != 0);
        assert(first.created_sequence != second.created_sequence);
        assert(brain.resolve_prediction(first.created_sequence, 20.0));

        const auto snapshot = brain.snapshot();
        assert(snapshot.predictions.size() == 2);
        std::size_t resolved = 0;
        for (const auto& prediction : snapshot.predictions) if (prediction.resolved) ++resolved;
        assert(resolved == 1);
        assert(brain.developmental_associations().size() == 1);
        assert(std::isfinite(brain.developmental_associations().front().strength));
        assert(!brain.resolve_prediction(first.created_sequence, 20.0));
        assert(brain.resolve_prediction(second.created_sequence, 30.0));

        Goal goal{"developmental-context", "learn a useful action strategy", 0.9, 0.0,
                  0, 0, GoalStatus::pending, {}, {}};
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        const std::vector<CandidateAction> actions{
            {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
            {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
        };

        const auto before = brain.choose_with_developmental_learning(actions);
        const double before_learned = score_for(before, "learned-action");
        const double before_other = score_for(before, "other-action");

        const auto before_related = brain.choose_with_developmental_learning(
            actions, "developmental-context/variant");
        const double before_related_learned = score_for(before_related, "learned-action");
        const double before_related_other = score_for(before_related, "other-action");
        assert(std::abs(before_related_learned - before_related_other) < 1e-9);

        for (int i = 0; i < 5; ++i) {
            const ActionAssessment assessment{
                actions[0], ActionDisposition::execute, true, 0.9, "developmental"};
            const auto result = brain.execute_action(
                assessment,
                [](const CandidateAction&) { return true; },
                [](const CandidateAction&) { return true; },
                {},
                [](const CandidateAction&) { return 1.0; });
            assert(result.verified);
        }

        for (int i = 0; i < 5; ++i) {
            const ActionAssessment assessment{
                actions[1], ActionDisposition::execute, true, 0.9, "developmental"};
            const auto result = brain.execute_action(
                assessment,
                [](const CandidateAction&) { return false; },
                [](const CandidateAction&) { return false; });
            assert(!result.executed);
        }

        // Observed execution results update capability performance, not just
        // strategy preference. This estimate is reconstructed from the journal.
        const auto* failed_capability = brain.self_model().capability("other-action");
        const auto* successful_capability = brain.self_model().capability("learned-action");
        assert(failed_capability != nullptr);
        assert(successful_capability != nullptr);
        assert(failed_capability->performance < successful_capability->performance);
        assert(failed_capability->availability == 1.0);

        // Failed execution/verification is negative evidence about strategy
        // reliability even when no consequence observer is configured. It must
        // be learned without pretending that a real-world consequence was seen.
        const auto strategies_after_execution = brain.developmental_strategies();
        const auto failed_strategy = std::find_if(
            strategies_after_execution.begin(), strategies_after_execution.end(),
            [&](const LearnedStrategy& strategy) {
                return strategy.context == goal.id &&
                       strategy.action == "other-action";
            });
        assert(failed_strategy != strategies_after_execution.end());
        assert(failed_strategy->value < 0.0);
        assert(failed_strategy->uses >= 5);

        const auto learned = brain.developmental_best_strategy(goal.id);
        assert(learned != nullptr);
        assert(learned->action == "learned-action");
        assert(learned->confidence > 0.0);
        assert(learned->uses >= 5);

        const auto after = brain.choose_with_developmental_learning(actions);
        const double after_learned = score_for(after, "learned-action");
        const double after_other = score_for(after, "other-action");
        assert(after_learned > before_learned);
        assert(after_learned > after_other);
        // Outcomes legitimately change global affect, so unrelated actions
        // may receive a shared score shift. The strategy-learning effect is
        // isolated by checking that the learned action improves more.
        assert((after_learned - before_learned) >
               (after_other - before_other));

        // Novel but structurally related context: the exact learned context
        // does not match, so the change must come from similarity-based
        // developmental generalization.
        const auto after_related = brain.choose_with_developmental_learning(
            actions, "developmental-context/variant");
        const double after_related_learned = score_for(after_related, "learned-action");
        const double after_related_other = score_for(after_related, "other-action");
        assert(after_related_learned > before_related_learned);
        assert(after_related_learned > after_related_other);
        assert((after_related_learned - before_related_learned) >
               (after_related_other - before_related_other));

        // The normal CognitiveCycle path must consume the same learned change
        // before planning, rather than requiring callers to use a special
        // developmental decision API.
        Goal related_goal{"developmental-context-novel", "handle a related novel situation", 0.9, 0.0,
                           0, 0, GoalStatus::pending, {}, {}};
        assert(brain.create_goal(related_goal));
        assert(brain.activate_goal(related_goal.id));
        CognitiveCycle cycle(brain);
        CognitiveCycleInput cycle_input;
        cycle_input.observation = Event{0, 0, "environment", "observation",
                                        {{"situation", std::string("related-variant")}}};
        cycle_input.candidate_actions = actions;
        cycle_input.goal_id = related_goal.id;
        cycle_input.developmental_context = "developmental-context/variant";
        cycle_input.planning_horizon = 1;
        const auto cycle_result = cycle.run(cycle_input);
        assert(cycle_result.status == CognitiveCycleStatus::completed);
        assert(score_for(cycle_result.context.decisions, "learned-action") >
               score_for(cycle_result.context.decisions, "other-action"));

        // A featureless observation must not sever continuity: the cycle should
        // recover salient prior episodes when attribute-based recall has no query.
        auto featureless_input = cycle_input;
        featureless_input.observation =
            Event{0, 0, "environment", "observation", {}};
        featureless_input.memory_limit = 8;
        const auto featureless_result = cycle.run(featureless_input);
        assert(featureless_result.status == CognitiveCycleStatus::completed);
        assert(!featureless_result.context.memories.empty());
        assert(std::any_of(featureless_result.context.memories.begin(),
                           featureless_result.context.memories.end(),
                           [](const MemoryRecord& memory) {
                               return memory.event.kind == "action_outcome";
                           }));

    }

    {
        Brain restored(path);
        const auto* restored_failed_capability = restored.self_model().capability("other-action");
        assert(restored_failed_capability != nullptr);
        assert(restored_failed_capability->performance < 1.0);
        assert(restored_failed_capability->availability == 1.0);
        const auto restored_strategies = restored.developmental_strategies();
        const auto restored_failed_strategy = std::find_if(
            restored_strategies.begin(), restored_strategies.end(),
            [](const LearnedStrategy& strategy) {
                return strategy.context == "developmental-context" &&
                       strategy.action == "other-action";
            });
        assert(restored_failed_strategy != restored_strategies.end());
        assert(restored_failed_strategy->value < 0.0);
        assert(restored_failed_strategy->uses >= 5);

        const auto snapshot = restored.snapshot();
        assert(snapshot.predictions.size() == 2);
        for (const auto& prediction : snapshot.predictions) assert(prediction.resolved);
        assert(restored.developmental_associations().size() == 1);

        const auto learned = restored.developmental_best_strategy("developmental-context");
        assert(learned != nullptr);
        assert(learned->action == "learned-action");
        assert(learned->uses >= 5);

        const std::vector<CandidateAction> actions{
            {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
            {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
        };
        const auto restored_decisions = restored.choose_with_developmental_learning(actions);
        assert(score_for(restored_decisions, "learned-action") >
               score_for(restored_decisions, "other-action"));

        const auto restored_related = restored.choose_with_developmental_learning(
            actions, "developmental-context/variant");
        assert(score_for(restored_related, "learned-action") >
               score_for(restored_related, "other-action"));

        Goal restored_related_goal{"developmental-context-restored",
                                  "handle the same related novel situation after restart",
                                  0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        assert(restored.create_goal(restored_related_goal));
        assert(restored.activate_goal(restored_related_goal.id));
        CognitiveCycle restored_cycle(restored);
        CognitiveCycleInput restored_input;
        restored_input.observation = Event{0, 0, "environment", "observation",
                                           {{"situation", std::string("related-variant")}}};
        restored_input.candidate_actions = actions;
        restored_input.goal_id = restored_related_goal.id;
        restored_input.developmental_context = "developmental-context/variant";
        restored_input.planning_horizon = 1;
        const auto restored_cycle_result = restored_cycle.run(restored_input);
        assert(restored_cycle_result.status == CognitiveCycleStatus::completed);
        assert(score_for(restored_cycle_result.context.decisions, "learned-action") >
               score_for(restored_cycle_result.context.decisions, "other-action"));
    }

    // Episodic outcomes are a bounded decision fallback when no learned
    // strategy exists (for example, imported/legacy journals). Directly append
    // traces to memory so this test isolates episodic retrieval from Brain's
    // normal outcome handler and proves memories themselves affect action choice.
    const auto episodic_path =
        std::filesystem::temp_directory_path() / "jarvis_episodic_decision_fallback.bin";
    std::filesystem::remove(episodic_path, ec);
    std::filesystem::remove(episodic_path.string() + ".meta", ec);
    {
        Brain episodic_brain(episodic_path);
        Goal episodic_goal{"episodic-fallback-goal", "use prior episodic outcomes",
                           0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        assert(episodic_brain.create_goal(episodic_goal));
        assert(episodic_brain.activate_goal(episodic_goal.id));
        episodic_brain.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("episodically-good")},
             {"context", std::string("episodic-only-context")},
             {"observed", true},
             {"actual_consequence", 1.0},
             {"consequence_error", 0.0},
             {"reliability", 0.1},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        episodic_brain.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("episodically-bad")},
             {"context", std::string("episodic-only-context")},
             {"observed", true},
             {"actual_consequence", -1.0},
             {"consequence_error", 1.0},
             {"reliability", 1.0},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        // A recorded but unobserved consequence is not reward evidence and must
        // not make an action look successful merely because a value was stored.
        episodic_brain.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("episodically-unobserved")},
             {"context", std::string("episodic-only-context")},
             {"observed", false},
             {"actual_consequence", 1.0},
             {"consequence_error", 0.0},
             {"reliability", 1.0},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        const std::vector<CandidateAction> episodic_actions{
            {"episodically-good", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
            {"episodically-bad", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
            {"episodically-unobserved", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
        };
        CognitiveCycle episodic_cycle(episodic_brain);
        CognitiveCycleInput episodic_input;
        episodic_input.observation = Event{0, 0, "environment", "observation", {}};
        episodic_input.candidate_actions = episodic_actions;
        episodic_input.goal_id = episodic_goal.id;
        episodic_input.developmental_context = "episodic-only-context";
        episodic_input.memory_limit = 16;
        const auto episodic_result = episodic_cycle.run(episodic_input);
        assert(episodic_result.status == CognitiveCycleStatus::completed);
        assert(std::any_of(episodic_result.context.memories.begin(),
                           episodic_result.context.memories.end(),
                           [](const MemoryRecord& memory) {
                               return memory.event.kind == "action_outcome";
                           }));
        assert(score_for(episodic_result.context.decisions, "episodically-good") >
               score_for(episodic_result.context.decisions, "episodically-bad"));
        assert(score_for(episodic_result.context.decisions, "episodically-good") >
               score_for(episodic_result.context.decisions, "episodically-unobserved"));
        // The positive episode deliberately has low legacy executor reliability
        // but explicit evidence_reliability=1.0. Its score above the negative
        // episode proves consequence confidence is not erased by executor reliability.
    }

    // Featureful observations can still miss episode attributes when sensor
    // schemas change. Salient episodic recall must then alter the same action's
    // score relative to an otherwise identical brain without that experience.
    const auto featureful_memory_path =
        std::filesystem::temp_directory_path() / "jarvis_featureful_episodic_recall.bin";
    const auto featureful_baseline_path =
        std::filesystem::temp_directory_path() / "jarvis_featureful_episodic_baseline.bin";
    std::filesystem::remove(featureful_memory_path, ec);
    std::filesystem::remove(featureful_memory_path.string() + ".meta", ec);
    std::filesystem::remove(featureful_baseline_path, ec);
    std::filesystem::remove(featureful_baseline_path.string() + ".meta", ec);
    const CandidateAction featureful_action{
        "sensor-adaptation-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5,
        DecisionOutcome::act, 0.0};
    const Event featureful_observation{
        0, 0, "environment", "observation",
        {{"new_sensor_schema", std::string("temperature-v2")}}};
    double score_with_episode = -1.0e9;
    {
        Brain experienced(featureful_memory_path);
        Goal goal{"featureful-episodic-goal", "use experience across sensor schemas",
                  0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        assert(experienced.create_goal(goal));
        assert(experienced.activate_goal(goal.id));
        // Fill the generic observation-recall top-1 with unrelated memories
        // that share the current sensor key. A nonempty generic result must not
        // suppress candidate-specific retrieval of the older action outcome.
        for (int i = 0; i < 3; ++i) {
            experienced.memory().append(Event{0, 0, "environment", "observation",
                {{"new_sensor_schema", std::string("unrelated-sensor-state")},
                 {"salience", 0.9}}});
        }
        experienced.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("sensor-adaptation-action")},
             {"context", std::string("featureful-episodic-context")},
             {"observed", true},
             {"actual_consequence", 1.0},
             {"consequence_error", 0.0},
             {"reliability", 1.0},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        // Same-action non-outcome records are newer and salient. A plain
        // top-1 action recall would return one of them, then discard it after
        // ranking and miss the older outcome. Kind filtering must happen first.
        for (int i = 0; i < 3; ++i) {
            experienced.memory().append(Event{0, 0, "executor", "action_attempt",
                {{"action", std::string("sensor-adaptation-action")},
                 {"salience", 1.0}}});
        }
        // Legacy outcome records may omit context entirely. They are useful
        // for broad action recall but must never masquerade as exact local
        // evidence when the current context is known.
        experienced.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("sensor-adaptation-action")},
             {"observed", true},
             {"actual_consequence", -1.0},
             {"consequence_error", 1.0},
             {"reliability", 1.0},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        // Recent outcomes for the same action in unrelated contexts must not
        // evict the older outcome that matches this developmental situation.
        for (int i = 0; i < 3; ++i) {
            experienced.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
                {{"action", std::string("sensor-adaptation-action")},
                 {"context", std::string("unrelated-developmental-context")},
                 {"observed", true},
                 {"actual_consequence", -1.0},
                 {"consequence_error", 1.0},
                 {"reliability", 1.0},
                 {"evidence_reliability", 1.0},
                 {"salience", 1.0}}});
        }
        const auto targeted_outcomes = experienced.memory().recall_ranked(
            {{"action", Scalar{std::string("sensor-adaptation-action")}}},
            1, "action_outcome");
        assert(targeted_outcomes.size() == 1);
        assert(targeted_outcomes.front().event.kind == "action_outcome");
        assert(targeted_outcomes.front().event.data.at("context") ==
               Scalar{std::string("unrelated-developmental-context")});
        const auto contextual_outcomes = experienced.memory().recall_ranked(
            {{"action", Scalar{std::string("sensor-adaptation-action")}},
             {"context", Scalar{std::string("featureful-episodic-context")}}},
            1, "action_outcome", true);
        assert(contextual_outcomes.size() == 1);
        assert(contextual_outcomes.front().event.data.at("context") ==
               Scalar{std::string("featureful-episodic-context")});
        CognitiveCycle cycle(experienced);
        CognitiveCycleInput input;
        input.observation = featureful_observation;
        input.candidate_actions = {featureful_action};
        input.goal_id = goal.id;
        input.developmental_context = "featureful-episodic-context";
        input.memory_limit = 1;
        const auto result = cycle.run(input);
        assert(result.status == CognitiveCycleStatus::completed);
        assert(std::any_of(result.context.memories.begin(), result.context.memories.end(),
                           [](const MemoryRecord& memory) {
                               const auto context = memory.event.data.find("context");
                               const auto actual = memory.event.data.find("actual_consequence");
                               const auto* consequence = actual == memory.event.data.end()
                                   ? nullptr : std::get_if<double>(&actual->second);
                               return memory.event.kind == "action_outcome" &&
                                      context != memory.event.data.end() &&
                                      context->second == Scalar{std::string("featureful-episodic-context")} &&
                                      consequence != nullptr && *consequence > 0.0;
                           }));
        score_with_episode = score_for(result.context.decisions, featureful_action.name);
        assert(score_with_episode > -1.0e8);
    }
    {
        Brain inexperienced(featureful_baseline_path);
        Goal goal{"featureful-episodic-goal", "use experience across sensor schemas",
                  0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        assert(inexperienced.create_goal(goal));
        assert(inexperienced.activate_goal(goal.id));
        CognitiveCycle cycle(inexperienced);
        CognitiveCycleInput input;
        input.observation = featureful_observation;
        input.candidate_actions = {featureful_action};
        input.goal_id = goal.id;
        input.developmental_context = "featureful-episodic-context";
        input.memory_limit = 8;
        const auto result = cycle.run(input);
        assert(result.status == CognitiveCycleStatus::completed);
        const double score_without_episode =
            score_for(result.context.decisions, featureful_action.name);
        assert(score_without_episode > -1.0e8);
        assert(score_with_episode > score_without_episode);
    }

    // A contextless legacy outcome must not penalize an action in a known,
    // unrelated developmental context. Compare identical candidates across
    // otherwise equivalent brains, rather than assuming different action names
    // receive identical baseline scores.
    const auto contextless_isolation_path =
        std::filesystem::temp_directory_path() / "jarvis_contextless_episode_isolation.bin";
    const auto contextless_baseline_path =
        std::filesystem::temp_directory_path() / "jarvis_contextless_episode_baseline.bin";
    std::filesystem::remove(contextless_isolation_path, ec);
    std::filesystem::remove(contextless_isolation_path.string() + ".meta", ec);
    std::filesystem::remove(contextless_baseline_path, ec);
    std::filesystem::remove(contextless_baseline_path.string() + ".meta", ec);
    const std::vector<CandidateAction> isolation_actions{
        {"contextless-negative-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5},
        {"neutral-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5},
    };
    double contextless_action_score = -1.0e9;
    {
        Brain isolated(contextless_isolation_path);
        Goal goal{"contextless-isolation-goal", "avoid cross-context memory leakage",
                  0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        assert(isolated.create_goal(goal));
        assert(isolated.activate_goal(goal.id));
        isolated.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("contextless-negative-action")},
             {"observed", true},
             {"actual_consequence", -1.0},
             {"reliability", 1.0},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        CognitiveCycle cycle(isolated);
        CognitiveCycleInput input;
        input.observation = Event{0, 0, "environment", "observation", {}};
        input.candidate_actions = isolation_actions;
        input.goal_id = goal.id;
        input.developmental_context = "known-but-unrelated-context";
        input.memory_limit = 8;
        const auto result = cycle.run(input);
        assert(result.status == CognitiveCycleStatus::completed);
        contextless_action_score =
            score_for(result.context.decisions, "contextless-negative-action");
        assert(contextless_action_score > -1.0e8);
    }
    {
        Brain baseline(contextless_baseline_path);
        Goal goal{"contextless-isolation-goal", "avoid cross-context memory leakage",
                  0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        assert(baseline.create_goal(goal));
        assert(baseline.activate_goal(goal.id));
        CognitiveCycle cycle(baseline);
        CognitiveCycleInput input;
        input.observation = Event{0, 0, "environment", "observation", {}};
        input.candidate_actions = isolation_actions;
        input.goal_id = goal.id;
        input.developmental_context = "known-but-unrelated-context";
        input.memory_limit = 8;
        const auto result = cycle.run(input);
        assert(result.status == CognitiveCycleStatus::completed);
        const double baseline_action_score =
            score_for(result.context.decisions, "contextless-negative-action");
        assert(std::abs(contextless_action_score - baseline_action_score) < 1e-9);
    }
    std::filesystem::remove(contextless_isolation_path, ec);
    std::filesystem::remove(contextless_isolation_path.string() + ".meta", ec);
    std::filesystem::remove(contextless_baseline_path, ec);
    std::filesystem::remove(contextless_baseline_path.string() + ".meta", ec);

    // The ordinary Brain decision APIs must generalize learned behavior too;
    // generalization is not restricted to CognitiveCycle or an opt-in API.
    const auto generalization_path =
        std::filesystem::temp_directory_path() / "jarvis_developmental_standard_decision.bin";
    std::filesystem::remove(generalization_path, ec);
    std::filesystem::remove(generalization_path.string() + ".meta", ec);
    const std::vector<CandidateAction> generalization_actions{
        {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
        {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
    };
    {
        Brain generalized(generalization_path);
        for (int i = 0; i < 5; ++i) {
            generalized.observe(Event{0, 0, "environment", "action_outcome",
                {{"action", std::string("learned-action")},
                 {"context", std::string("navigation route")},
                 {"observed", true},
                 {"expected_consequence", 1.0},
                 {"actual_consequence", 1.0},
                 {"consequence_error", 0.0},
                 {"reliability", 1.0},
                 {"salience", 0.8},
                 {"novelty", 0.2}}});
        }
        Goal related_goal{"navigation-route-variant",
                          "navigate using a related route", 0.9, 0.0,
                          0, 0, GoalStatus::pending, {}, {}};
        assert(generalized.create_goal(related_goal));
        assert(generalized.activate_goal(related_goal.id));

        const auto standard_decisions = generalized.choose(generalization_actions);
        assert(score_for(standard_decisions, "learned-action") >
               score_for(standard_decisions, "other-action"));
        const auto affective_decisions =
            generalized.choose_with_affect(generalization_actions);
        assert(score_for(affective_decisions, "learned-action") >
               score_for(affective_decisions, "other-action"));
    }
    {
        Brain restored_generalized(generalization_path);
        const auto standard_decisions =
            restored_generalized.choose(generalization_actions);
        assert(score_for(standard_decisions, "learned-action") >
               score_for(standard_decisions, "other-action"));
        const auto affective_decisions =
            restored_generalized.choose_with_affect(generalization_actions);
        assert(score_for(affective_decisions, "learned-action") >
               score_for(affective_decisions, "other-action"));
    }
    std::filesystem::remove(generalization_path, ec);
    std::filesystem::remove(generalization_path.string() + ".meta", ec);

    // Strategy learning must recover when later evidence contradicts earlier failures.
    // This exercises the real execution -> outcome journal -> learner -> replay path.
    const auto recovery_path =
        std::filesystem::temp_directory_path() / "jarvis_developmental_recovery.bin";
    std::filesystem::remove(recovery_path, ec);
    std::filesystem::remove(recovery_path.string() + ".meta", ec);
    double failed_strategy_value = 0.0;
    {
        Brain recovering(recovery_path);
        Goal recovery_goal{"recovery-context", "learn from changed outcomes", 0.9, 0.0,
                           0, 0, GoalStatus::pending, {}, {}};
        assert(recovering.create_goal(recovery_goal));
        assert(recovering.activate_goal(recovery_goal.id));
        const CandidateAction recoverable{
            "recoverable-action", 0.5, 0.5, 0.9, 0.1, 1.0, 0.0, 0.5};
        const ActionAssessment assessment{
            recoverable, ActionDisposition::execute, true, 0.9,
            "recovery learning test", recovery_goal.id};

        for (int i = 0; i < 5; ++i) {
            const auto failed = recovering.execute_action(
                assessment,
                [](const CandidateAction&) { return false; },
                [](const CandidateAction&) { return false; });
            assert(failed.status == ActionExecutionStatus::failed);
        }
        const auto* failed_strategy =
            recovering.developmental_best_strategy(recovery_goal.id);
        assert(failed_strategy != nullptr);
        assert(failed_strategy->action == "recoverable-action");
        assert(failed_strategy->value < 0.0);
        failed_strategy_value = failed_strategy->value;

        for (int i = 0; i < 5; ++i) {
            const auto recovered = recovering.execute_action(
                assessment,
                [](const CandidateAction&) { return true; },
                [](const CandidateAction&) { return true; },
                {},
                [](const CandidateAction&) { return 1.0; });
            assert(recovered.status == ActionExecutionStatus::verified);
            assert(recovered.outcome.observed);
            assert(recovered.outcome.actual_consequence == 1.0);
        }
        const auto* recovered_strategy =
            recovering.developmental_best_strategy(recovery_goal.id);
        assert(recovered_strategy != nullptr);
        assert(recovered_strategy->action == "recoverable-action");
        assert(recovered_strategy->uses == 10);
        assert(recovered_strategy->value > failed_strategy_value);
        assert(recovered_strategy->value > 0.0);
    }
    {
        Brain recovered_after_restart(recovery_path);
        const auto* recovered_strategy =
            recovered_after_restart.developmental_best_strategy("recovery-context");
        assert(recovered_strategy != nullptr);
        assert(recovered_strategy->action == "recoverable-action");
        assert(recovered_strategy->uses == 10);
        assert(recovered_strategy->value > 0.0);
        assert(recovered_strategy->value > failed_strategy_value);
    }
    std::filesystem::remove(recovery_path, ec);
    std::filesystem::remove(recovery_path.string() + ".meta", ec);

    // The Brain event path must preserve consequence reliability when it
    // updates developmental strategies. Weakly supported success is not
    // equivalent to a directly verified success.
    const auto reliability_path =
        std::filesystem::temp_directory_path() / "jarvis_developmental_reliability.bin";
    std::filesystem::remove(reliability_path, ec);
    std::filesystem::remove(reliability_path.string() + ".meta", ec);
    {
        Brain reliability_brain(reliability_path);
        for (int i = 0; i < 4; ++i) {
            assert(reliability_brain.observe(Event{0, 0, "reliability-test", "action_outcome",
                {{"action", std::string("high-confidence-action")},
                 {"context", std::string("same context")},
                 {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
                 {"observed", true},
                 {"expected_consequence", 1.0},
                 {"actual_consequence", 1.0},
                 {"consequence_error", 0.0},
                 {"reliability", 1.0},
                 {"salience", 0.8},
                 {"novelty", 0.2}}}).event.sequence != 0);
            assert(reliability_brain.observe(Event{0, 0, "reliability-test", "action_outcome",
                {{"action", std::string("low-confidence-action")},
                 {"context", std::string("same context")},
                 {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
                 {"observed", true},
                 {"expected_consequence", 1.0},
                 {"actual_consequence", 1.0},
                 {"consequence_error", 0.0},
                 {"reliability", 0.1},
                 {"salience", 0.8},
                 {"novelty", 0.2}}}).event.sequence != 0);
        }
        const auto strategies = reliability_brain.developmental_strategies();
        const auto high_strategy = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) { return strategy.action == "high-confidence-action"; });
        const auto low_strategy = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) { return strategy.action == "low-confidence-action"; });
        assert(high_strategy != strategies.end());
        assert(low_strategy != strategies.end());
        // Both actions have the same observed positive outcome. Reliability
        // changes confidence and therefore effective influence, not the
        // observed outcome's valence or raw target value.
        assert(std::abs(high_strategy->value - low_strategy->value) < 1e-9);
        assert(high_strategy->confidence > low_strategy->confidence);
        assert(high_strategy->value * high_strategy->confidence >
               low_strategy->value * low_strategy->confidence);
    }
    std::filesystem::remove(reliability_path, ec);
    std::filesystem::remove(reliability_path.string() + ".meta", ec);

    // Execution-only feedback has no observed world consequence, but its
    // reliability must still limit how strongly capability evidence changes
    // developmental strategy values.
    const auto execution_path =
        std::filesystem::temp_directory_path() / "jarvis_execution_reliability.bin";
    std::filesystem::remove(execution_path, ec);
    std::filesystem::remove(execution_path.string() + ".meta", ec);
    {
        Brain execution_brain(execution_path);
        for (int i = 0; i < 4; ++i) {
            assert(execution_brain.observe(Event{0, 0, "execution-reliability-test", "action_outcome",
                {{"action", std::string("reliable-execution")},
                 {"context", std::string("execution context")},
                 {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
                 {"observed", false},
                 {"reliability", 1.0},
                 {"salience", 0.5},
                 {"novelty", 0.1}}}).event.sequence != 0);
            assert(execution_brain.observe(Event{0, 0, "execution-reliability-test", "action_outcome",
                {{"action", std::string("uncertain-execution")},
                 {"context", std::string("execution context")},
                 {"status", static_cast<std::int64_t>(ActionExecutionStatus::failed)},
                 {"observed", false},
                 {"reliability", 0.1},
                 {"salience", 0.5},
                 {"novelty", 0.1}}}).event.sequence != 0);
        }
        const auto strategies = execution_brain.developmental_strategies();
        const auto reliable = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) { return strategy.action == "reliable-execution"; });
        const auto uncertain = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) { return strategy.action == "uncertain-execution"; });
        assert(reliable != strategies.end());
        assert(uncertain != strategies.end());
        assert(reliable->value > uncertain->value);
        assert(reliable->confidence > uncertain->confidence);
    }
    std::filesystem::remove(execution_path, ec);
    std::filesystem::remove(execution_path.string() + ".meta", ec);

    // Malformed execution metadata must not become a learned experience.
    // Unknown enum values cannot masquerade as verified actions.
    const auto malformed_path =
        std::filesystem::temp_directory_path() / "jarvis_developmental_malformed_outcome.bin";
    std::filesystem::remove(malformed_path, ec);
    std::filesystem::remove(malformed_path.string() + ".meta", ec);
    {
        Brain guarded(malformed_path);
        const auto rejected = guarded.observe(Event{0, 0, "malformed-test", "action_outcome",
            {{"action", std::string("untrusted-action")},
             {"context", std::string("critical repair")},
             {"status", static_cast<std::int64_t>(999)},
             {"observed", false},
             {"reliability", 1.0}}});
        assert(rejected.event.sequence == 0);
        assert(guarded.developmental_strategies().empty());
        assert(guarded.self_model().capability("untrusted-action") == nullptr);
    }
    {
        Brain restored_guarded(malformed_path);
        assert(restored_guarded.developmental_strategies().empty());
        assert(restored_guarded.self_model().capability("untrusted-action") == nullptr);
    }
    std::filesystem::remove(malformed_path, ec);
    std::filesystem::remove(malformed_path.string() + ".meta", ec);

    // Inferred numeric context must complete the full perception -> strategy
    // learning -> later decision loop and survive journal replay.
    const auto numeric_path =
        std::filesystem::temp_directory_path() / "jarvis_numeric_context_learning.bin";
    std::filesystem::remove(numeric_path, ec);
    std::filesystem::remove(numeric_path.string() + ".meta", ec);
    const std::vector<CandidateAction> numeric_actions{
        {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5},
        {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5},
    };
    {
        Brain numeric_brain(numeric_path);
        Goal numeric_goal{"numeric-sensor-goal",
                          "learn from numeric sensor consequences", 0.9, 0.0,
                          0, 0, GoalStatus::pending, {}, {}};
        assert(numeric_brain.create_goal(numeric_goal));
        assert(numeric_brain.activate_goal(numeric_goal.id));
        CognitiveCycle numeric_cycle(numeric_brain);
        CognitiveCycleInput numeric_input;
        numeric_input.observation =
            Event{0, 0, "sensor", "observation", {{"temperature", 42.0}}};
        numeric_input.candidate_actions = numeric_actions;
        numeric_input.goal_id = numeric_goal.id;
        numeric_input.planning_horizon = 1;
        numeric_input.resource_budget = 10.0;

        const auto before_numeric_learning = numeric_cycle.run(numeric_input);
        assert(before_numeric_learning.status == CognitiveCycleStatus::completed);
        const auto learned_assessment = std::find_if(
            before_numeric_learning.context.action_assessments.begin(),
            before_numeric_learning.context.action_assessments.end(),
            [](const ActionAssessment& assessment) {
                return assessment.action.name == "learned-action";
            });
        assert(learned_assessment !=
               before_numeric_learning.context.action_assessments.end());
        const std::string inferred_context = learned_assessment->developmental_context;
        assert(inferred_context.find("temperature") != std::string::npos);
        assert(inferred_context.find("scale") != std::string::npos);

        for (int i = 0; i < 5; ++i) {
            const auto outcome = numeric_brain.execute_action(
                *learned_assessment,
                [](const CandidateAction&) { return true; },
                [](const CandidateAction&) { return true; },
                {},
                [](const CandidateAction&) { return 1.0; });
            assert(outcome.verified);
        }

        const auto after_numeric_learning = numeric_cycle.run(numeric_input);
        assert(after_numeric_learning.status == CognitiveCycleStatus::completed);
        assert(score_for(after_numeric_learning.context.decisions, "learned-action") >
               score_for(after_numeric_learning.context.decisions, "other-action"));

        // A nearby numeric state has a different exact context, but can reuse
        // the learned strategy through bounded feature similarity.
        numeric_input.observation =
            Event{0, 0, "sensor", "observation", {{"temperature", 80.0}}};
        const auto related_numeric_result = numeric_cycle.run(numeric_input);
        assert(related_numeric_result.status == CognitiveCycleStatus::completed);
        assert(score_for(related_numeric_result.context.decisions, "learned-action") >
               score_for(related_numeric_result.context.decisions, "other-action"));
    }
    {
        Brain restored_numeric(numeric_path);
        CognitiveCycle restored_numeric_cycle(restored_numeric);
        CognitiveCycleInput restored_input;
        restored_input.observation =
            Event{0, 0, "sensor", "observation", {{"temperature", 42.0}}};
        restored_input.candidate_actions = numeric_actions;
        restored_input.goal_id = "numeric-sensor-goal";
        restored_input.planning_horizon = 1;
        restored_input.resource_budget = 10.0;
        const auto restored_result = restored_numeric_cycle.run(restored_input);
        assert(restored_result.status == CognitiveCycleStatus::completed);
        assert(score_for(restored_result.context.decisions, "learned-action") >
               score_for(restored_result.context.decisions, "other-action"));
    }
    std::filesystem::remove(numeric_path, ec);
    std::filesystem::remove(numeric_path.string() + ".meta", ec);

    // Memory confidence must follow evidence quality, not action execution
    // reliability. A reliably observed failed attempt remains useful evidence.
    const auto evidence_confidence_path =
        std::filesystem::temp_directory_path() / "jarvis_evidence_confidence.bin";
    std::filesystem::remove(evidence_confidence_path, ec);
    std::filesystem::remove(evidence_confidence_path.string() + ".meta", ec);
    std::uint64_t failed_action_sequence = 0;
    {
        Brain evidence_confidence_brain(evidence_confidence_path);
        const auto observation = evidence_confidence_brain.observe(
            Event{0, 0, "confidence-integration-test", "action_outcome",
                {{"action", std::string("failed-but-observed")},
                 {"context", std::string("sensor-repair")},
                 {"status", static_cast<std::int64_t>(ActionExecutionStatus::failed)},
                 {"observed", false},
                 {"reliability", 0.1},
                 {"evidence_reliability", 0.9},
                 {"salience", 0.8},
                 {"novelty", 0.3}}});
        assert(observation.event.sequence != 0);
        failed_action_sequence = observation.event.sequence;
        const auto records = evidence_confidence_brain.memory().recall_ranked(
            {{"action", Scalar{std::string("failed-but-observed")}}}, 8);
        const auto record = std::find_if(records.begin(), records.end(),
            [failed_action_sequence](const MemoryRecord& item) {
                return item.event.sequence == failed_action_sequence;
            });
        assert(record != records.end());
        assert(record->confidence > 0.85);
    }
    {
        Brain restored_evidence_confidence(evidence_confidence_path);
        const auto records = restored_evidence_confidence.memory().recall_ranked(
            {{"action", Scalar{std::string("failed-but-observed")}}}, 8);
        const auto record = std::find_if(records.begin(), records.end(),
            [failed_action_sequence](const MemoryRecord& item) {
                return item.event.sequence == failed_action_sequence;
            });
        assert(record != records.end());
        assert(record->confidence > 0.85);
    }
    std::filesystem::remove(evidence_confidence_path, ec);
    std::filesystem::remove(evidence_confidence_path.string() + ".meta", ec);

    // Generic evidence must enter the same coordinated experience pathway:
    // durable evidence -> knowledge/affective processing -> memory consolidation.
    const auto evidence_path =
        std::filesystem::temp_directory_path() / "jarvis_generic_evidence_consolidation.bin";
    std::filesystem::remove(evidence_path, ec);
    std::filesystem::remove(evidence_path.string() + ".meta", ec);
    std::uint64_t learning_sequence = 0;
    {
        Brain evidence_brain(evidence_path);
        const double accepted = evidence_brain.learn(
            Evidence{"generic-evidence-test", "observed-state", Scalar{std::string("stable")}, 0.9});
        assert(accepted > 0.0);
        const auto fact = evidence_brain.world().query(
            "generic-evidence-test", "observed-state");
        assert(fact.has_value());
        assert(fact->value == Scalar{std::string("stable")});
        // Appraisal and confidence metadata must not become world knowledge.
        assert(!evidence_brain.world().query(
            "generic-evidence-test", "novelty").has_value());
        assert(!evidence_brain.world().query(
            "generic-evidence-test", "salience").has_value());
        assert(!evidence_brain.world().query(
            "generic-evidence-test", "reliability").has_value());
        const auto learning_events = evidence_brain.memory().by_kind("learning");
        assert(!learning_events.empty());
        const auto learned_event = std::find_if(
            learning_events.begin(), learning_events.end(),
            [](const Event& event) {
                return event.source == "generic-evidence-test" &&
                       event.data.contains("novelty") &&
                       event.data.contains("salience");
            });
        assert(learned_event != learning_events.end());
        learning_sequence = learned_event->sequence;
        const auto records = evidence_brain.memory().recall_ranked(
            {{"evidence_key", Scalar{std::string("observed-state")}},
             {"evidence_value", Scalar{std::string("stable")}}}, 8);
        const auto consolidated = std::find_if(
            records.begin(), records.end(),
            [learning_sequence](const MemoryRecord& record) {
                return record.event.sequence == learning_sequence;
            });
        assert(consolidated != records.end());
        assert(consolidated->consolidation > 0.0);
        assert(evidence_brain.affective_learning_updates() > 0);
    }
    {
        Brain restored_evidence(evidence_path);
        const auto events = restored_evidence.memory().by_kind("learning");
        assert(std::any_of(events.begin(), events.end(),
            [learning_sequence](const Event& event) {
                return event.sequence == learning_sequence &&
                       event.data.contains("novelty") &&
                       event.data.contains("salience");
            }));
        const auto restored_fact = restored_evidence.world().query(
            "generic-evidence-test", "observed-state");
        assert(restored_fact.has_value());
        assert(restored_fact->value == Scalar{std::string("stable")});
        assert(!restored_evidence.world().query(
            "generic-evidence-test", "novelty").has_value());
        assert(!restored_evidence.world().query(
            "generic-evidence-test", "salience").has_value());
        const auto records = restored_evidence.memory().recall_ranked(
            {{"evidence_key", Scalar{std::string("observed-state")}},
             {"evidence_value", Scalar{std::string("stable")}}}, 8);
        const auto consolidated = std::find_if(
            records.begin(), records.end(),
            [learning_sequence](const MemoryRecord& record) {
                return record.event.sequence == learning_sequence;
            });
        assert(consolidated != records.end());
        assert(consolidated->consolidation > 0.0);
    }
    std::filesystem::remove(evidence_path, ec);
    std::filesystem::remove(evidence_path.string() + ".meta", ec);

    // Strategy evidence and episodic fallback must remain coordinated without
    // contaminating the restart/replay fixture above. Seed one durable positive
    // strategy, then add a conflicting in-memory episode after Brain has replayed
    // the journal; the existing generalized strategy must remain authoritative.
    const auto precedence_path =
        std::filesystem::temp_directory_path() / "jarvis_episodic_strategy_precedence.bin";
    std::filesystem::remove(precedence_path, ec);
    std::filesystem::remove(precedence_path.string() + ".meta", ec);
    {
        Memory seed_memory(256, precedence_path);
        seed_memory.append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("learned-action")},
             {"context", std::string("developmental-context")},
             {"status", std::int64_t(3)},
             {"observed", true},
             {"actual_consequence", 1.0},
             {"consequence_error", 0.0},
             {"reliability", 1.0},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
    }
    {
        Brain precedence_brain(precedence_path);
        const auto strategies = precedence_brain.developmental_strategies();
        assert(std::any_of(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) {
                return strategy.context == "developmental-context" &&
                       strategy.action == "learned-action" &&
                       strategy.value > 0.0;
            }));
        Goal precedence_goal{"episodic-precedence-goal", "preserve learned strategy",
                             0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        assert(precedence_brain.create_goal(precedence_goal));
        assert(precedence_brain.activate_goal(precedence_goal.id));
        precedence_brain.memory().append(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("learned-action")},
             {"context", std::string("developmental-context/variant")},
             {"observed", true},
             {"actual_consequence", -1.0},
             {"consequence_error", 1.0},
             {"reliability", 1.0},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        const std::vector<CandidateAction> precedence_actions{
            {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
            {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, DecisionOutcome::act, 0.0},
        };
        CognitiveCycle precedence_cycle(precedence_brain);
        CognitiveCycleInput precedence_input;
        precedence_input.observation = Event{0, 0, "environment", "observation", {}};
        precedence_input.candidate_actions = precedence_actions;
        precedence_input.goal_id = precedence_goal.id;
        precedence_input.developmental_context = "developmental-context/variant";
        precedence_input.memory_limit = 16;
        const auto precedence_result = precedence_cycle.run(precedence_input);
        assert(precedence_result.status == CognitiveCycleStatus::completed);
        assert(score_for(precedence_result.context.decisions, "learned-action") >
               score_for(precedence_result.context.decisions, "other-action"));
    }
    std::filesystem::remove(precedence_path, ec);
    std::filesystem::remove(precedence_path.string() + ".meta", ec);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "developmental brain integration suite passed\n";
    return 0;
}
