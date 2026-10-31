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
    // Reflection must account for unresolved counter-evidence even when the
    // current value itself was learned with high confidence.
    ReflectionModel reflection_model;
    const auto trusted_reflection = reflection_model.evaluate(
        {Belief{"stable-fact", true, 0.95, 3, 1, false}}, {}, 0.0, 1.0, 0);
    const auto disputed_reflection = reflection_model.evaluate(
        {Belief{"disputed-fact", true, 0.95, 3, 1, true}}, {}, 0.0, 1.0, 0);
    assert(disputed_reflection.uncertainty > trusted_reflection.uncertainty);
    assert(disputed_reflection.uncertainty == 1.0);

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
        // Consequence-aware execution adds forecasts beyond the two explicit
        // developmental predictions; ensure the original records remain present.
        assert(snapshot.predictions.size() >= 2);
        for (const auto& prediction : snapshot.predictions) assert(prediction.resolved);
        const auto restored_associations = restored.developmental_associations();
        // Resolved action-consequence forecasts also contribute associations;
        // do not assume the total remains fixed as integrated learning expands.
        assert(!restored_associations.empty());
        for (const auto& association : restored_associations)
            assert(std::isfinite(association.strength));

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
        episodic_brain.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
            {{"action", std::string("episodically-good")},
             {"context", std::string("episodic-only-context")},
             {"observed", true},
             {"actual_consequence", 1.0},
             {"consequence_error", 0.0},
             {"reliability", 0.1},
             {"evidence_reliability", 1.0},
             {"salience", 1.0}}});
        episodic_brain.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
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
        episodic_brain.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
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
            experienced.import_legacy_memory_event(Event{0, 0, "environment", "observation",
                {{"new_sensor_schema", std::string("unrelated-sensor-state")},
                 {"salience", 0.9}}});
        }
        experienced.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
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
            experienced.import_legacy_memory_event(Event{0, 0, "executor", "action_attempt",
                {{"action", std::string("sensor-adaptation-action")},
                 {"salience", 1.0}}});
        }
        // Legacy outcome records may omit context entirely. They are useful
        // for broad action recall but must never masquerade as exact local
        // evidence when the current context is known.
        experienced.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
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
            experienced.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
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
        isolated.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
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

    // Execution success without a consequence observer is capability
    // evidence, not positive task-utility evidence. Operational failures may
    // still teach a negative strategy-reliability signal.
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
        assert(reliable == strategies.end());
        assert(uncertain != strategies.end());
        assert(uncertain->value < 0.0);
        assert(uncertain->uses == 4);
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

        // A malformed observed flag must be rejected rather than silently
        // interpreted as "no consequence observed" and learned as execution
        // reliability evidence.
        const auto malformed_observed = guarded.observe(Event{
            0, 0, "malformed-test", "action_outcome",
            {{"action", std::string("malformed-observation-action")},
             {"context", std::string("critical repair")},
             {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
             {"observed", std::string("true")},
             {"reliability", 1.0}}});
        assert(malformed_observed.event.sequence == 0);
        assert(guarded.developmental_strategies().empty());
        assert(guarded.self_model().capability("malformed-observation-action") == nullptr);

        // An outcome with no context identity must not update affect or learning
        // state before the action-specific replay handler rejects it.
        const auto missing_context = guarded.observe(Event{
            0, 0, "malformed-test", "action_outcome",
            {{"action", std::string("missing-context-action")},
             {"observed", true},
             {"actual_consequence", 1.0},
             {"consequence_error", 0.0},
             {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
             {"reliability", 1.0}}});
        assert(missing_context.event.sequence == 0);
        assert(guarded.developmental_strategies().empty());
        assert(guarded.self_model().capability("missing-context-action") == nullptr);

        // Confidence is consumed by memory consolidation, so non-finite values
        // must be rejected before append rather than poisoning stored rankings.
        const auto malformed_confidence = guarded.observe(Event{
            0, 0, "malformed-test", "action_outcome",
            {{"action", std::string("malformed-confidence-action")},
             {"context", std::string("critical repair")},
             {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
             {"observed", false},
             {"reliability", 1.0},
             {"confidence", std::nan("")}}});
        assert(malformed_confidence.event.sequence == 0);
        assert(guarded.developmental_strategies().empty());
        assert(guarded.self_model().capability("malformed-confidence-action") == nullptr);
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
        assert(before_numeric_learning.context.representation.modality == Modality::sensor);
        assert(!before_numeric_learning.context.representation.nodes.empty());
        assert(std::any_of(before_numeric_learning.context.representation.nodes.begin(),
                           before_numeric_learning.context.representation.nodes.end(),
            [](const SemanticNode& node) { return node.label == "temperature"; }));
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

    // Malformed persisted appraisal evidence must be rejected before it
    // consumes the action's exactly-once learning key or updates calibration.
    const auto affective_learning_path =
        std::filesystem::temp_directory_path() / "jarvis_invalid_affective_learning.bin";
    std::filesystem::remove(affective_learning_path, ec);
    std::filesystem::remove(affective_learning_path.string() + ".meta", ec);
    {
        Brain affective_learning_brain(affective_learning_path);
        const auto updates_before = affective_learning_brain.affective_learning_updates();
        const auto events_before = affective_learning_brain.memory().all().size();
        const auto rejected = affective_learning_brain.observe(
            Event{0, 0, "affective-learning-test", "affective_learning",
                {{"source_action_sequence", std::int64_t{7}},
                 {"expected_consequence", 0.0},
                 {"actual_consequence", 1.0},
                 {"consequence_error", 1.0},
                 {"utility", 1.0},
                 {"prediction_error", 1.0},
                 {"novelty", 0.2},
                 {"salience", 0.8},
                 {"uncertainty", 0.1},
                 {"confidence", std::nan("")}}});
        assert(rejected.event.sequence == 0);
        assert(affective_learning_brain.memory().all().size() == events_before);
        assert(affective_learning_brain.affective_learning_updates() == updates_before);

        // Structurally valid appraisal data must still be rejected when its
        // source sequence does not identify a persisted observed action outcome.
        const auto orphaned = affective_learning_brain.observe(
            Event{0, 0, "affective-learning-test", "affective_learning",
                {{"source_action_sequence", std::int64_t{7}},
                 {"expected_consequence", 0.0},
                 {"actual_consequence", 1.0},
                 {"consequence_error", 1.0},
                 {"utility", 1.0},
                 {"prediction_error", 1.0},
                 {"novelty", 0.2},
                 {"salience", 0.8},
                 {"uncertainty", 0.1},
                 {"confidence", 0.9}}});
        assert(orphaned.event.sequence == 0);
        assert(affective_learning_brain.memory().all().size() == events_before);
        assert(affective_learning_brain.affective_learning_updates() == updates_before);
    }
    std::filesystem::remove(affective_learning_path, ec);
    std::filesystem::remove(affective_learning_path.string() + ".meta", ec);

    {
        Brain affective_learning_brain(affective_learning_path);
        const auto updates_before = affective_learning_brain.affective_learning_updates();
        const auto events_before = affective_learning_brain.memory().all().size();
        const auto rejected = affective_learning_brain.observe(
            Event{0, 0, "affective-learning-test", "affective_learning",
                {{"source_action_sequence", std::int64_t{8}},
                 {"expected_consequence", 0.0},
                 {"actual_consequence", 1.0},
                 {"consequence_error", 1.0},
                 {"utility", 1.0},
                 {"prediction_error", 1.2},
                 {"novelty", 0.2},
                 {"salience", 0.8},
                 {"uncertainty", 0.1},
                 {"confidence", 0.9}}});
        assert(rejected.event.sequence == 0);
        assert(affective_learning_brain.memory().all().size() == events_before);
        assert(affective_learning_brain.affective_learning_updates() == updates_before);
    }

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

    // Contradictory observations must remain disputed while evidence is
    // balanced, then become usable again when repeated reliable evidence
    // supports one value. The same resolution must be reconstructed on replay.
    const auto contradiction_path =
        std::filesystem::temp_directory_path() / "jarvis_fact_contradiction_resolution.bin";
    std::filesystem::remove(contradiction_path, ec);
    std::filesystem::remove(contradiction_path.string() + ".meta", ec);
    const auto verify_resolved_fact = [](const Brain& candidate) {
        const auto fact = candidate.world().query(
            "contradiction-resolution-test", "door-state");
        assert(fact.has_value());
        assert(fact->value == Scalar{std::string("closed")});
        assert(!fact->disputed);
        assert(candidate.world().disputed_facts().empty());
        const auto beliefs = candidate.beliefs();
        const auto belief = std::find_if(
            beliefs.begin(), beliefs.end(),
            [](const Belief& item) { return item.key == "door-state"; });
        assert(belief != beliefs.end());
        assert(belief->value == Scalar{std::string("closed")});
        assert(!belief->disputed);
    };
    {
        Brain contradiction_brain(contradiction_path);
        const auto open = contradiction_brain.observe(Event{
            0, 1, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("open")}, {"confidence", 0.9}}});
        assert(open.event.sequence != 0);
        const auto closed = contradiction_brain.observe(Event{
            0, 2, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("closed")}, {"confidence", 0.9}}});
        assert(closed.event.sequence != 0);
        const auto contested = contradiction_brain.world().query(
            "contradiction-resolution-test", "door-state");
        assert(contested.has_value());
        assert(contested->disputed);
        assert(!contradiction_brain.world().disputed_facts().empty());

        const auto corroboration = contradiction_brain.observe(Event{
            0, 3, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("closed")}, {"confidence", 0.95}}});
        assert(corroboration.event.sequence != 0);
        verify_resolved_fact(contradiction_brain);

        const auto verify_resolved_relation = [](const Brain& candidate) {
            const auto relations = candidate.world().relations_from("door");
            assert(relations.size() == 1);
            assert(relations.front().type == "opens_into");
            assert(relations.front().to == "room-b");
            assert(!relations.front().disputed);
            assert(candidate.world().disputed_relations().empty());
        };
        const auto room_a = contradiction_brain.observe(Event{
            0, 4, "contradiction-resolution-test", "observation",
            {{"subject", std::string("door")},
             {"predicate", std::string("opens_into")},
             {"object", std::string("room-a")}}});
        assert(room_a.event.sequence != 0);
        const auto room_b = contradiction_brain.observe(Event{
            0, 5, "contradiction-resolution-test", "observation",
            {{"subject", std::string("door")},
             {"predicate", std::string("opens_into")},
             {"object", std::string("room-b")}}});
        assert(room_b.event.sequence != 0);
        assert(contradiction_brain.world().disputed_relations().size() == 2);
        const auto room_b_corroboration = contradiction_brain.observe(Event{
            0, 6, "contradiction-resolution-test", "observation",
            {{"subject", std::string("door")},
             {"predicate", std::string("opens_into")},
             {"object", std::string("room-b")},
             {"confidence", 0.8}}});
        assert(room_b_corroboration.event.sequence != 0);
        verify_resolved_relation(contradiction_brain);

        // A strong value learned before a contradiction must not settle the
        // new conflict by relying only on its old observations. It needs fresh
        // corroboration after the competing value has appeared.
        const auto new_fact_conflict = contradiction_brain.observe(Event{
            0, 7, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("open")}, {"confidence", 0.9}}});
        assert(new_fact_conflict.event.sequence != 0);
        const auto still_contested_fact = contradiction_brain.world().query(
            "contradiction-resolution-test", "door-state");
        assert(still_contested_fact.has_value());
        assert(still_contested_fact->disputed);
        const auto fresh_fact_corroboration = contradiction_brain.observe(Event{
            0, 8, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("closed")}, {"confidence", 0.99}}});
        assert(fresh_fact_corroboration.event.sequence != 0);
        verify_resolved_fact(contradiction_brain);

        // Repeating the challenger once is not enough when accumulated support
        // still favors the prior value. The Brain belief must remain disputed
        // until the leading value is observed again after this new conflict.
        const auto second_fact_conflict = contradiction_brain.observe(Event{
            0, 9, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("open")}, {"confidence", 0.9}}});
        assert(second_fact_conflict.event.sequence != 0);
        const auto repeated_challenger = contradiction_brain.observe(Event{
            0, 10, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("open")}, {"confidence", 0.9}}});
        assert(repeated_challenger.event.sequence != 0);
        const auto still_disputed_fact = contradiction_brain.world().query(
            "contradiction-resolution-test", "door-state");
        assert(still_disputed_fact.has_value());
        assert(still_disputed_fact->disputed);
        const auto current_beliefs = contradiction_brain.beliefs();
        const auto current_door_belief = std::find_if(
            current_beliefs.begin(), current_beliefs.end(),
            [](const Belief& item) { return item.key == "door-state"; });
        assert(current_door_belief != current_beliefs.end());
        assert(current_door_belief->disputed);
        const auto final_fact_corroboration = contradiction_brain.observe(Event{
            0, 11, "contradiction-resolution-test", "observation",
            {{"door-state", std::string("closed")}, {"confidence", 0.99}}});
        assert(final_fact_corroboration.event.sequence != 0);
        verify_resolved_fact(contradiction_brain);

        const auto new_relation_conflict = contradiction_brain.observe(Event{
            0, 9, "contradiction-resolution-test", "observation",
            {{"subject", std::string("door")},
             {"predicate", std::string("opens_into")},
             {"object", std::string("room-a")}}});
        assert(new_relation_conflict.event.sequence != 0);
        assert(contradiction_brain.world().disputed_relations().size() == 2);
        const auto fresh_relation_corroboration = contradiction_brain.observe(Event{
            0, 10, "contradiction-resolution-test", "observation",
            {{"subject", std::string("door")},
             {"predicate", std::string("opens_into")},
             {"object", std::string("room-b")},
             {"confidence", 0.9}}});
        assert(fresh_relation_corroboration.event.sequence != 0);
        verify_resolved_relation(contradiction_brain);
    }
    {
        Brain contradiction_replay(contradiction_path);
        verify_resolved_fact(contradiction_replay);
        const auto relations = contradiction_replay.world().relations_from("door");
        assert(relations.size() == 1);
        assert(relations.front().type == "opens_into");
        assert(relations.front().to == "room-b");
        assert(!relations.front().disputed);
        assert(contradiction_replay.world().disputed_relations().empty());
    }
    std::filesystem::remove(contradiction_path, ec);
    std::filesystem::remove(contradiction_path.string() + ".meta", ec);

    // Observation evidence quality must reach belief/world learning, while
    // appraisal metadata must not be learned as if it were part of the world.
    const auto evidence_quality_path =
        std::filesystem::temp_directory_path() / "jarvis_observation_evidence_quality.bin";
    std::filesystem::remove(evidence_quality_path, ec);
    std::filesystem::remove(evidence_quality_path.string() + ".meta", ec);
    {
        Brain evidence_quality(evidence_quality_path);
        const auto observed = evidence_quality.observe(Event{
            0, 1, "sensor-quality", "observation",
            {{"reading", 42.0},
             {"evidence_reliability", 0.2},
             {"reliability", 0.9},
             {"confidence", 0.8},
             {"world_step", std::int64_t{3}}}});
        assert(observed.event.sequence != 0);
        const auto fact = evidence_quality.world().query("sensor-quality", "reading");
        assert(fact.has_value());
        assert(std::abs(fact->confidence - 0.2) < 1e-12);
        assert(!evidence_quality.world().query(
            "sensor-quality", "evidence_reliability").has_value());
        assert(!evidence_quality.world().query("sensor-quality", "reliability").has_value());
        assert(!evidence_quality.world().query("sensor-quality", "confidence").has_value());
        assert(!evidence_quality.world().query("sensor-quality", "world_step").has_value());
        const auto beliefs = evidence_quality.beliefs();
        const auto reading = std::find_if(
            beliefs.begin(), beliefs.end(),
            [](const Belief& item) { return item.key == "reading"; });
        assert(reading != beliefs.end());
        assert(std::abs(reading->confidence - 0.2) < 1e-12);
    }
    {
        Brain evidence_quality_replay(evidence_quality_path);
        const auto fact = evidence_quality_replay.world().query("sensor-quality", "reading");
        assert(fact.has_value());
        assert(std::abs(fact->confidence - 0.2) < 1e-12);
        assert(!evidence_quality_replay.world().query(
            "sensor-quality", "evidence_reliability").has_value());
    }
    std::filesystem::remove(evidence_quality_path, ec);
    std::filesystem::remove(evidence_quality_path.string() + ".meta", ec);

    // Cross-source consistency: a clean observation from one source must not
    // erase another source's unresolved contradiction. Replay and source-order
    // permutations must reconstruct the same global dispute state.
    const auto cross_source_path =
        std::filesystem::temp_directory_path() / "jarvis_cross_source_conflict.bin";
    std::filesystem::remove(cross_source_path, ec);
    std::filesystem::remove(cross_source_path.string() + ".meta", ec);
    const auto assert_global_dispute = [](const Brain& candidate, bool expected) {
        const auto beliefs = candidate.beliefs();
        const auto belief = std::find_if(
            beliefs.begin(), beliefs.end(),
            [](const Belief& item) { return item.key == "shared-fact"; });
        assert(belief != beliefs.end());
        assert(belief->disputed == expected);
    };
    {
        Brain cross_source(cross_source_path);
        assert(cross_source.observe(Event{0, 1, "source-a", "observation",
            {{"shared-fact", std::string("X")}, {"evidence_reliability", 0.8}}}).event.sequence != 0);
        assert(cross_source.observe(Event{0, 2, "source-a", "observation",
            {{"shared-fact", std::string("Y")}, {"evidence_reliability", 0.8}}}).event.sequence != 0);
        const auto source_a_fact = cross_source.world().query("source-a", "shared-fact");
        assert(source_a_fact.has_value() && source_a_fact->disputed);
        assert_global_dispute(cross_source, true);

        assert(cross_source.observe(Event{0, 3, "source-b", "observation",
            {{"shared-fact", std::string("Y")}, {"evidence_reliability", 0.8}}}).event.sequence != 0);
        // Source B's clean Y must not hide source A's unresolved X/Y conflict.
        assert_global_dispute(cross_source, true);

        assert(cross_source.observe(Event{0, 4, "source-a", "observation",
            {{"shared-fact", std::string("Y")}, {"evidence_reliability", 0.9}}}).event.sequence != 0);
        assert_global_dispute(cross_source, false);
    }
    {
        Brain cross_source_replay(cross_source_path);
        assert_global_dispute(cross_source_replay, false);
        const auto a = cross_source_replay.world().query("source-a", "shared-fact");
        const auto b = cross_source_replay.world().query("source-b", "shared-fact");
        assert(a.has_value() && !a->disputed && a->value == Scalar{std::string("Y")});
        assert(b.has_value() && !b->disputed && b->value == Scalar{std::string("Y")});
    }
    std::filesystem::remove(cross_source_path, ec);
    std::filesystem::remove(cross_source_path.string() + ".meta", ec);

    const auto reverse_cross_source_path =
        std::filesystem::temp_directory_path() / "jarvis_cross_source_conflict_reverse.bin";
    std::filesystem::remove(reverse_cross_source_path, ec);
    std::filesystem::remove(reverse_cross_source_path.string() + ".meta", ec);
    {
        Brain reverse_cross_source(reverse_cross_source_path);
        assert(reverse_cross_source.observe(Event{0, 1, "source-b", "observation",
            {{"shared-fact", std::string("Y")}, {"evidence_reliability", 0.8}}}).event.sequence != 0);
        assert(reverse_cross_source.observe(Event{0, 2, "source-a", "observation",
            {{"shared-fact", std::string("X")}, {"evidence_reliability", 0.8}}}).event.sequence != 0);
        assert(reverse_cross_source.observe(Event{0, 3, "source-a", "observation",
            {{"shared-fact", std::string("Y")}, {"evidence_reliability", 0.8}}}).event.sequence != 0);
        assert_global_dispute(reverse_cross_source, true);
        const auto a = reverse_cross_source.world().query("source-a", "shared-fact");
        assert(a.has_value() && a->disputed);
        assert(reverse_cross_source.observe(Event{0, 4, "source-a", "observation",
            {{"shared-fact", std::string("Y")}, {"evidence_reliability", 0.9}}}).event.sequence != 0);
        assert_global_dispute(reverse_cross_source, false);
    }
    {
        Brain reverse_cross_source_replay(reverse_cross_source_path);
        assert_global_dispute(reverse_cross_source_replay, false);
        const auto a = reverse_cross_source_replay.world().query("source-a", "shared-fact");
        const auto b = reverse_cross_source_replay.world().query("source-b", "shared-fact");
        assert(a.has_value() && !a->disputed && a->value == Scalar{std::string("Y")});
        assert(b.has_value() && !b->disputed && b->value == Scalar{std::string("Y")});
    }
    std::filesystem::remove(reverse_cross_source_path, ec);
    std::filesystem::remove(reverse_cross_source_path.string() + ".meta", ec);

    // Three-way alternatives: ties must remain contested, and unequal
    // reliability must accumulate without allowing pre-conflict evidence alone
    // to settle a newly introduced alternative.
    const auto multi_value_path =
        std::filesystem::temp_directory_path() / "jarvis_three_way_fact_conflict.bin";
    std::filesystem::remove(multi_value_path, ec);
    std::filesystem::remove(multi_value_path.string() + ".meta", ec);
    {
        Brain multi_value(multi_value_path);
        const auto observe_value = [&](const char* value, double reliability) {
            return multi_value.observe(Event{0, 0, "multi-value-source", "observation",
                {{"multi-value", std::string(value)},
                 {"evidence_reliability", reliability}}});
        };
        assert(observe_value("alpha", 0.8).event.sequence != 0);
        assert(observe_value("beta", 0.8).event.sequence != 0);
        assert(observe_value("gamma", 0.8).event.sequence != 0);
        auto contested = multi_value.world().query("multi-value-source", "multi-value");
        assert(contested.has_value() && contested->disputed);
        const auto disputed_values = multi_value.world().disputed_facts();
        assert(disputed_values.size() == 3);
        assert(std::all_of(disputed_values.begin(), disputed_values.end(),
            [](const Fact& fact) {
                return fact.subject == "multi-value-source" &&
                       fact.predicate == "multi-value" && fact.disputed;
            }));
        const auto contains_value = [&](const char* expected) {
            return std::any_of(disputed_values.begin(), disputed_values.end(),
                [&](const Fact& fact) {
                    return fact.value == Scalar{std::string(expected)};
                });
        };
        assert(contains_value("alpha"));
        assert(contains_value("beta"));
        assert(contains_value("gamma"));

        // A low-reliability repeat cannot settle the three-way tie.
        assert(observe_value("gamma", 0.0).event.sequence != 0);
        contested = multi_value.world().query("multi-value-source", "multi-value");
        assert(contested.has_value() && contested->disputed);
        assert(observe_value("gamma", 0.7).event.sequence != 0);
        contested = multi_value.world().query("multi-value-source", "multi-value");
        assert(contested.has_value() && contested->disputed);
        // Equal reliability is a tie, not a resolution.
        assert(observe_value("gamma", 0.8).event.sequence != 0);
        contested = multi_value.world().query("multi-value-source", "multi-value");
        assert(contested.has_value() && contested->disputed);

        // Strictly stronger fresh evidence after the conflict can resolve it.
        assert(observe_value("gamma", 0.9).event.sequence != 0);
        const auto resolved = multi_value.world().query(
            "multi-value-source", "multi-value");
        assert(resolved.has_value() && !resolved->disputed);
        assert(resolved->value == Scalar{std::string("gamma")});
        assert(multi_value.world().disputed_facts().empty());
    }
    {
        Brain multi_value_replay(multi_value_path);
        const auto resolved = multi_value_replay.world().query(
            "multi-value-source", "multi-value");
        assert(resolved.has_value() && !resolved->disputed);
        assert(resolved->value == Scalar{std::string("gamma")});
        assert(multi_value_replay.world().disputed_facts().empty());
    }
    std::filesystem::remove(multi_value_path, ec);
    std::filesystem::remove(multi_value_path.string() + ".meta", ec);

    const auto multi_relation_path =
        std::filesystem::temp_directory_path() / "jarvis_three_way_relation_conflict.bin";
    std::filesystem::remove(multi_relation_path, ec);
    std::filesystem::remove(multi_relation_path.string() + ".meta", ec);
    {
        Brain multi_relation(multi_relation_path);
        const auto observe_destination = [&](const char* destination, double reliability) {
            return multi_relation.observe(Event{0, 0, "relation-source", "observation",
                {{"subject", std::string("gateway")},
                 {"predicate", std::string("connects_to")},
                 {"object", std::string(destination)},
                 {"evidence_reliability", reliability}}});
        };
        assert(observe_destination("node-a", 0.8).event.sequence != 0);
        assert(observe_destination("node-b", 0.8).event.sequence != 0);
        assert(observe_destination("node-c", 0.8).event.sequence != 0);
        auto relations = multi_relation.world().relations_from("gateway");
        assert(relations.size() == 3);
        assert(std::all_of(relations.begin(), relations.end(),
            [](const Relation& relation) { return relation.disputed; }));

        assert(observe_destination("node-c", 0.2).event.sequence != 0);
        relations = multi_relation.world().relations_from("gateway");
        assert(relations.size() == 3);
        assert(std::all_of(relations.begin(), relations.end(),
            [](const Relation& relation) { return relation.disputed; }));
        assert(observe_destination("node-c", 0.7).event.sequence != 0);
        relations = multi_relation.world().relations_from("gateway");
        assert(relations.size() == 3);
        assert(std::all_of(relations.begin(), relations.end(),
            [](const Relation& relation) { return relation.disputed; }));
        assert(observe_destination("node-c", 0.8).event.sequence != 0);
        relations = multi_relation.world().relations_from("gateway");
        assert(relations.size() == 3);
        assert(std::all_of(relations.begin(), relations.end(),
            [](const Relation& relation) { return relation.disputed; }));

        assert(observe_destination("node-c", 0.9).event.sequence != 0);
        relations = multi_relation.world().relations_from("gateway");
        assert(relations.size() == 1);
        assert(relations.front().to == "node-c");
        assert(!relations.front().disputed);
        assert(multi_relation.world().disputed_relations().empty());
    }
    {
        Brain multi_relation_replay(multi_relation_path);
        const auto relations = multi_relation_replay.world().relations_from("gateway");
        assert(relations.size() == 1);
        assert(relations.front().to == "node-c");
        assert(!relations.front().disputed);
        assert(multi_relation_replay.world().disputed_relations().empty());
    }
    std::filesystem::remove(multi_relation_path, ec);
    std::filesystem::remove(multi_relation_path.string() + ".meta", ec);

    // Repeated reversals require a fresh, strictly stronger observation after
    // each new conflict; a source cannot settle a tie by repeating an equal value.
    const auto reversal_path =
        std::filesystem::temp_directory_path() / "jarvis_repeated_conflict_reversal.bin";
    std::filesystem::remove(reversal_path, ec);
    {
        Brain reversal(reversal_path);
        const auto observe_reversal = [&](const char* value, double reliability) {
            return reversal.observe(Event{0, 0, "reversal-source", "observation",
                {{"reversible-state", std::string(value)},
                 {"evidence_reliability", reliability}}});
        };
        assert(observe_reversal("alpha", 0.8).event.sequence != 0);
        assert(observe_reversal("beta", 0.9).event.sequence != 0);
        auto contested = reversal.world().query("reversal-source", "reversible-state");
        assert(contested.has_value() && contested->disputed);
        assert(observe_reversal("beta", 0.95).event.sequence != 0);
        auto resolved = reversal.world().query("reversal-source", "reversible-state");
        assert(resolved.has_value() && !resolved->disputed);
        assert(resolved->value == Scalar{std::string("beta")});

        assert(observe_reversal("alpha", 0.9).event.sequence != 0);
        contested = reversal.world().query("reversal-source", "reversible-state");
        assert(contested.has_value() && contested->disputed);
        assert(observe_reversal("alpha", 0.99).event.sequence != 0);
        resolved = reversal.world().query("reversal-source", "reversible-state");
        assert(resolved.has_value() && !resolved->disputed);
        assert(resolved->value == Scalar{std::string("alpha")});
    }
    {
        Brain reversal_replay(reversal_path);
        const auto resolved = reversal_replay.world().query(
            "reversal-source", "reversible-state");
        assert(resolved.has_value() && !resolved->disputed);
        assert(resolved->value == Scalar{std::string("alpha")});
    }
    std::filesystem::remove(reversal_path, ec);
    std::filesystem::remove(reversal_path.string() + ".meta", ec);

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
        precedence_brain.import_legacy_memory_event(Event{0, 0, "legacy-journal", "action_outcome",
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

    // Knowledge assessment must be driven by factual experience, survive
    // journal replay, and distinguish repeated observations from independent
    // corroboration. Corroboration is not treated as proof or safety approval.
    const auto knowledge_path =
        std::filesystem::temp_directory_path() / "jarvis_knowledge_assessment.bin";
    std::filesystem::remove(knowledge_path, ec);
    std::filesystem::remove(knowledge_path.string() + ".meta", ec);
    const KnowledgeProvenanceVerifier knowledge_origin_verifier =
        [](const KnowledgeProvenanceRequest& request) {
            return request.key == "surface-risk" &&
                request.attestation == "origin:" + request.source + ":" +
                    request.provenance_id;
        };
    {
        Brain knowledge_brain(knowledge_path, {}, {}, knowledge_origin_verifier);
        assert(knowledge_brain.observe(Event{0, 1, "source-A", "observation",
            {{"surface-risk", std::string("hazardous")},
             {"provenance_id", std::string("origin-A")},
             {"provenance_attestation", std::string("origin:source-A:origin-A")}}}).event.sequence != 0);
        assert(knowledge_brain.observe(Event{0, 2, "source-A", "observation",
            {{"surface-risk", std::string("hazardous")},
             {"provenance_id", std::string("origin-A")},
             {"provenance_attestation", std::string("origin:source-A:origin-A")}}}).event.sequence != 0);
        auto assessment = knowledge_brain.knowledge_assessment("surface-risk");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::provisional);
        assert(assessment->supporting_sources == 1);
        assert(assessment->supporting_origins == 1);

        assert(knowledge_brain.observe(Event{0, 3, "source-B", "observation",
            {{"surface-risk", std::string("hazardous")},
             {"provenance_id", std::string("origin-B")},
             {"provenance_attestation", std::string("origin:source-B:origin-B")}}}).event.sequence != 0);
        assessment = knowledge_brain.knowledge_assessment("surface-risk");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::corroborated);
        assert(assessment->supporting_sources == 2);
        assert(assessment->supporting_origins == 2);

        assert(knowledge_brain.observe(Event{0, 4, "source-C", "observation",
            {{"surface-risk", std::string("safe")},
             {"provenance_id", std::string("origin-C")},
             {"provenance_attestation", std::string("origin:source-C:origin-C")}}}).event.sequence != 0);
        assessment = knowledge_brain.knowledge_assessment("surface-risk");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::disputed);
        assert(assessment->supporting_origins == 2);
        assert(assessment->conflicting_sources == 1);
        assert(assessment->conflicting_origins == 1);
    }
    {
        Brain knowledge_replay(knowledge_path, {}, {}, knowledge_origin_verifier);
        const auto assessment = knowledge_replay.knowledge_assessment("surface-risk");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::disputed);
        assert(assessment->supporting_sources == 2);
        assert(assessment->supporting_origins == 2);
        assert(assessment->conflicting_sources == 1);
        assert(assessment->conflicting_origins == 1);
    }
    std::filesystem::remove(knowledge_path, ec);
    std::filesystem::remove(knowledge_path.string() + ".meta", ec);

    // Three independent sources can sustain three competing values. Resolving
    // one source-local dispute must not erase a separate source's disagreement,
    // and an unresolved three-way dispute must survive a fresh process.
    const auto three_source_path =
        std::filesystem::temp_directory_path() / "jarvis_three_source_conflict.bin";
    std::filesystem::remove(three_source_path, ec);
    std::filesystem::remove(three_source_path.string() + ".meta", ec);
    const auto observe_value = [](Brain& candidate, const std::string& source,
                                  const std::string& value,
                                  double reliability = 0.9) {
        return candidate.observe(Event{0, 0, source, "observation",
            {{"shared-state", value}, {"evidence_reliability", reliability}}});
    };
    const auto assert_three_source_dispute = [](const Brain& candidate, bool expected) {
        const auto beliefs = candidate.beliefs();
        const auto belief = std::find_if(beliefs.begin(), beliefs.end(),
            [](const Belief& item) { return item.key == "shared-state"; });
        assert(belief != beliefs.end());
        assert(belief->disputed == expected);
    };
    {
        Brain three_source(three_source_path);
        assert(observe_value(three_source, "sensor-A", "alpha").event.sequence != 0);
        assert(observe_value(three_source, "sensor-A", "beta").event.sequence != 0);
        assert(observe_value(three_source, "sensor-B", "beta").event.sequence != 0);
        assert(observe_value(three_source, "sensor-C", "gamma").event.sequence != 0);
        assert(three_source.world().disputed_facts().size() >= 2);
        assert_three_source_dispute(three_source, true);
    }
    {
        Brain unresolved_replay(three_source_path);
        assert_three_source_dispute(unresolved_replay, true);
        assert(unresolved_replay.world().disputed_facts().size() >= 2);
        // Fresh corroboration resolves sensor A's alpha/beta dispute, but
        // sensor C's independent gamma claim still keeps the global belief open.
        assert(observe_value(unresolved_replay, "sensor-A", "beta", 0.95).event.sequence != 0);
        assert_three_source_dispute(unresolved_replay, true);
        assert(unresolved_replay.world().disputed_facts().empty());
        // A first beta observation from sensor C introduces a new conflict;
        // it must not be mistaken for post-conflict corroboration.
        assert(observe_value(unresolved_replay, "sensor-C", "beta").event.sequence != 0);
        assert_three_source_dispute(unresolved_replay, true);
        assert(!unresolved_replay.world().disputed_facts().empty());
        // A second beta observation is fresh corroboration after gamma/beta
        // became contested, so sensor C can now resolve its own conflict.
        assert(observe_value(unresolved_replay, "sensor-C", "beta", 0.95).event.sequence != 0);
        assert_three_source_dispute(unresolved_replay, false);
        assert(unresolved_replay.world().disputed_facts().empty());
    }
    {
        Brain resolved_replay(three_source_path);
        assert_three_source_dispute(resolved_replay, false);
        assert(resolved_replay.world().disputed_facts().empty());
    }
    std::filesystem::remove(three_source_path, ec);
    std::filesystem::remove(three_source_path.string() + ".meta", ec);

    // Repetition from one source is not independent corroboration. Twenty
    // weak reassertions cannot erase a stronger competing fact.
    const auto repeated_fact_path = std::filesystem::temp_directory_path() /
                                    "jarvis_repeated_weak_fact_evidence.bin";
    std::filesystem::remove(repeated_fact_path, ec);
    {
        Brain repeated_fact(repeated_fact_path);
        assert(repeated_fact.observe(Event{0, 0, "sensor-repeated", "observation",
            {{"shared-state", Scalar{std::string("stable")}},
             {"evidence_reliability", Scalar{0.9}}}}).event.sequence != 0);
        assert(repeated_fact.observe(Event{0, 0, "sensor-repeated", "observation",
            {{"shared-state", Scalar{std::string("unstable")}},
             {"evidence_reliability", Scalar{0.8}}}}).event.sequence != 0);
        for (int i = 0; i < 20; ++i) {
            assert(repeated_fact.observe(Event{0, 0, "sensor-repeated", "observation",
                {{"shared-state", Scalar{std::string("unstable")}},
                 {"evidence_reliability", Scalar{0.2}}}}).event.sequence != 0);
        }
        const auto fact = repeated_fact.world().query("sensor-repeated", "shared-state");
        assert(fact.has_value());
        assert(fact->disputed);
        assert(!repeated_fact.world().disputed_facts().empty());
    }
    {
        Brain repeated_fact_replay(repeated_fact_path);
        const auto fact = repeated_fact_replay.world().query(
            "sensor-repeated", "shared-state");
        assert(fact.has_value());
        assert(fact->disputed);
        assert(!repeated_fact_replay.world().disputed_facts().empty());
    }
    std::filesystem::remove(repeated_fact_path, ec);
    std::filesystem::remove(repeated_fact_path.string() + ".meta", ec);

    // Relation alternatives obey the same non-independence rule.
    const auto repeated_relation_path = std::filesystem::temp_directory_path() /
                                        "jarvis_repeated_weak_relation_evidence.bin";
    std::filesystem::remove(repeated_relation_path, ec);
    {
        Brain repeated_relation(repeated_relation_path);
        assert(repeated_relation.observe(Event{0, 0, "relation-sensor", "observation",
            {{"subject", Scalar{std::string("bridge")}},
             {"predicate", Scalar{std::string("leads_to")}},
             {"object", Scalar{std::string("room-a")}},
             {"evidence_reliability", Scalar{0.9}}}}).event.sequence != 0);
        assert(repeated_relation.observe(Event{0, 0, "relation-sensor", "observation",
            {{"subject", Scalar{std::string("bridge")}},
             {"predicate", Scalar{std::string("leads_to")}},
             {"object", Scalar{std::string("room-b")}},
             {"evidence_reliability", Scalar{0.8}}}}).event.sequence != 0);
        for (int i = 0; i < 20; ++i) {
            assert(repeated_relation.observe(Event{0, 0, "relation-sensor", "observation",
                {{"subject", Scalar{std::string("bridge")}},
                 {"predicate", Scalar{std::string("leads_to")}},
                 {"object", Scalar{std::string("room-b")}},
                 {"evidence_reliability", Scalar{0.2}}}}).event.sequence != 0);
        }
        assert(repeated_relation.world().disputed_relations().size() == 2);
    }
    {
        Brain repeated_relation_replay(repeated_relation_path);
        assert(repeated_relation_replay.world().disputed_relations().size() == 2);
    }
    std::filesystem::remove(repeated_relation_path, ec);
    std::filesystem::remove(repeated_relation_path.string() + ".meta", ec);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "developmental brain integration suite passed\n";
    return 0;
}
