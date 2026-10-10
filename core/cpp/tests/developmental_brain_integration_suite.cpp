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
            {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
            {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
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
        assert(after_other <= before_other);

        // Novel but structurally related context: the exact learned context
        // does not match, so the change must come from similarity-based
        // developmental generalization.
        const auto after_related = brain.choose_with_developmental_learning(
            actions, "developmental-context/variant");
        const double after_related_learned = score_for(after_related, "learned-action");
        const double after_related_other = score_for(after_related, "other-action");
        assert(after_related_learned > before_related_learned);
        assert(after_related_learned > after_related_other);
        assert(after_related_other <= before_related_other);

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
    }

    {
        Brain restored(path);
        const auto snapshot = restored.snapshot();
        assert(snapshot.predictions.size() == 2);
        for (const auto& prediction : snapshot.predictions) assert(prediction.resolved);
        assert(restored.developmental_associations().size() == 1);

        const auto learned = restored.developmental_best_strategy("developmental-context");
        assert(learned != nullptr);
        assert(learned->action == "learned-action");
        assert(learned->uses >= 5);

        const std::vector<CandidateAction> actions{
            {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
            {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
        };
        const auto restored_decisions = restored.choose_with_developmental_learning(actions);
        assert(score_for(restored_decisions, "learned-action") >
               score_for(restored_decisions, "other-action"));

        const restored_related = restored.choose_with_developmental_learning(
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

    // The ordinary Brain decision APIs must generalize learned behavior too;
    // generalization is not restricted to CognitiveCycle or an opt-in API.
    const auto generalization_path =
        std::filesystem::temp_directory_path() / "jarvis_developmental_standard_decision.bin";
    std::filesystem::remove(generalization_path, ec);
    std::filesystem::remove(generalization_path.string() + ".meta", ec);
    const std::vector<CandidateAction> generalization_actions{
        {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
        {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
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

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "developmental brain integration suite passed\n";
    return 0;
}
