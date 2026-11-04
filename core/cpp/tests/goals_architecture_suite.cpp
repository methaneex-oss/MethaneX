#include "jarvis/core/brain.hpp"
#include "jarvis/core/goals.hpp"
#include "jarvis/core/intent.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <limits>
#include <string>

using namespace jarvis::core;

int main() {
    GoalModel goals;

    assert(goals.create(Goal{"foundation", "Complete foundation", 0.5, 0.0, 1, 0,
                             GoalStatus::pending, {}, {"deep"}}));
    assert(goals.create(Goal{"deep", "Build deeper cognition", 0.9, 0.0, 2, 20,
                             GoalStatus::pending, {"foundation"}, {}}));
    assert(!goals.create(Goal{"deep", "duplicate", 0.1, 0.0, 3, 0,
                              GoalStatus::pending, {}, {}}));

    assert(!goals.activate("deep"));
    assert(goals.activate("foundation"));
    assert(goals.update_progress("foundation", 0.4));
    const double reinforced_priority = goals.get("foundation")->priority;
    assert(reinforced_priority > 0.5);
    assert(goals.update_progress("foundation", 0.1));
    assert(goals.get("foundation")->priority < reinforced_priority);
    assert(goals.update_progress("foundation", 1.0));
    assert(goals.get("foundation")->status == GoalStatus::completed);
    assert(goals.activate("deep"));
    assert(goals.set_priority("deep", 0.8));
    assert(goals.update_progress("deep", 0.5));
    assert(goals.get("deep")->status == GoalStatus::active);
    assert(!goals.update_progress("deep", std::numeric_limits<double>::quiet_NaN()));
    assert(goals.complete("deep"));
    assert(goals.get("deep")->status == GoalStatus::completed);
    assert(!goals.abandon("deep"));
    assert(goals.eligible(10).empty());
    assert(goals.all().size() == 2);

    IntentModel intent_model;
    Goal positive{"positive", "Learn from progress", 0.6, 0.2, 0, 0,
                   GoalStatus::active, {}, {}};
    Goal negative{"negative", "Learn from regression", 0.6, 0.2, 0, 0,
                   GoalStatus::active, {}, {}};
    positive.outcome_momentum = 0.8;
    negative.outcome_momentum = -0.8;
    const auto learned_positive = intent_model.select({positive, negative}, 0.0, 0.1, 1);
    assert(learned_positive.id == "positive");
    negative.outcome_momentum = 0.8;
    positive.outcome_momentum = -0.8;
    const auto learned_negative = intent_model.select({positive, negative}, 0.0, 0.1, 1);
    assert(learned_negative.id == "negative");

    // Brain must reject every non-finite goal input before journaling. Model-level
    // rejection after append is too late: it leaves an invalid durable event.
    std::error_code invalid_goal_ec;
    const auto invalid_goal_journal =
        std::filesystem::temp_directory_path() / "jarvis_invalid_goal_input_test.bin";
    std::filesystem::remove(invalid_goal_journal, invalid_goal_ec);
    std::filesystem::remove(invalid_goal_journal.string() + ".meta", invalid_goal_ec);
    const double non_finite_values[] = {
        std::numeric_limits<double>::quiet_NaN(),
        std::numeric_limits<double>::infinity(),
        -std::numeric_limits<double>::infinity(),
    };
    {
        Brain invalid_goal_brain(invalid_goal_journal);
        const auto events_before = invalid_goal_brain.memory().all().size();
        for (std::size_t i = 0; i < 3; ++i) {
            const std::string priority_id = "invalid-priority-" + std::to_string(i);
            Goal invalid_priority{priority_id, "Reject non-finite priority",
                                  non_finite_values[i], 0.0, 0, 0,
                                  GoalStatus::pending, {}, {}};
            assert(!invalid_goal_brain.create_goal(invalid_priority));
            assert(invalid_goal_brain.goal(priority_id) == nullptr);
            assert(invalid_goal_brain.memory().all().size() == events_before);

            const std::string progress_id = "invalid-progress-" + std::to_string(i);
            Goal invalid_progress{progress_id, "Reject non-finite progress",
                                  0.5, non_finite_values[i], 0, 0,
                                  GoalStatus::pending, {}, {}};
            assert(!invalid_goal_brain.create_goal(invalid_progress));
            assert(invalid_goal_brain.goal(progress_id) == nullptr);
            assert(invalid_goal_brain.memory().all().size() == events_before);
        }
        assert(invalid_goal_brain.memory().all().empty());
    }
    {
        Brain restored_invalid_goal_brain(invalid_goal_journal);
        assert(restored_invalid_goal_brain.memory().all().empty());
        for (std::size_t i = 0; i < 3; ++i) {
            assert(restored_invalid_goal_brain.goal(
                "invalid-priority-" + std::to_string(i)) == nullptr);
            assert(restored_invalid_goal_brain.goal(
                "invalid-progress-" + std::to_string(i)) == nullptr);
        }
    }
    std::filesystem::remove(invalid_goal_journal, invalid_goal_ec);
    std::filesystem::remove(invalid_goal_journal.string() + ".meta", invalid_goal_ec);

    // Failure-inject the second append in goal completion by placing the
    // journal cursor at UINT64_MAX-1. The progress evidence is durable, but
    // the separate completion event cannot be appended. This is an explicitly
    // partial transition: the API reports failure and replay must preserve the
    // pre-completion goal state rather than inventing completion.
    std::error_code partial_completion_ec;
    const auto partial_completion_journal =
        std::filesystem::temp_directory_path() / "jarvis_partial_goal_completion_test.bin";
    std::filesystem::remove(partial_completion_journal, partial_completion_ec);
    std::filesystem::remove(partial_completion_journal.string() + ".meta", partial_completion_ec);
    const auto max_sequence = std::numeric_limits<std::uint64_t>::max();
    {
        Memory seed(256, partial_completion_journal);
        Event initial_goal{max_sequence - 2, 0, "brain", "goal_create",
            {{"id", std::string("partial-completion-goal")},
             {"description", std::string("Goal used to test partial completion persistence")},
             {"priority", 0.5},
             {"progress", 0.25},
             {"status", static_cast<std::int64_t>(GoalStatus::active)},
             {"deadline_cycle", std::int64_t{0}}}};
        assert(seed.append(initial_goal) == max_sequence - 2);
    }
    {
        Brain partial_completion(partial_completion_journal);
        const auto* before = partial_completion.goal("partial-completion-goal");
        assert(before != nullptr && before->status == GoalStatus::active);
        assert(before->progress == 0.25);
        const GoalOutcomeEvidence evidence{
            "partial-completion-goal", 0.25, 1.0, 0.75, true, 0.9, 77};
        assert(!partial_completion.assimilate_goal_outcome(evidence));
        const auto events = partial_completion.memory().all();
        assert(events.size() == 2);
        assert(events.back().sequence == max_sequence - 1);
        assert(events.back().kind == "goal_progress");
        const auto* after = partial_completion.goal("partial-completion-goal");
        assert(after != nullptr && after->status == GoalStatus::active);
        assert(after->progress == 0.25);
    }
    {
        Brain restored_partial_completion(partial_completion_journal);
        const auto events = restored_partial_completion.memory().all();
        assert(events.size() == 2);
        assert(events.back().kind == "goal_progress");
        const auto* restored_goal =
            restored_partial_completion.goal("partial-completion-goal");
        assert(restored_goal != nullptr && restored_goal->status == GoalStatus::active);
        assert(restored_goal->progress == 0.25);
    }
    std::filesystem::remove(partial_completion_journal, partial_completion_ec);
    std::filesystem::remove(partial_completion_journal.string() + ".meta", partial_completion_ec);

    const auto journal = std::filesystem::temp_directory_path() / "jarvis_goal_integration_test.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

    double child_priority_after_learning = 0.0;
    {
        Brain brain(journal);
        assert(brain.create_goal(Goal{"root", "Establish a root goal", 0.6, 0.0, 0, 0,
                                      GoalStatus::pending, {}, {"child"}}));
        assert(brain.create_goal(Goal{"child", "Complete a dependent goal", 0.9, 0.0, 0, 0,
                                      GoalStatus::pending, {"root"}, {}}));
        assert(brain.goals().size() == 2);
        assert(brain.eligible_goals().size() == 1);
        assert(brain.eligible_goals().front().id == "root");
        assert(!brain.activate_goal("child"));
        assert(brain.activate_goal("root"));
        assert(brain.update_goal_progress("root", 0.8));
        assert(brain.complete_goal("root"));
        assert(brain.activate_goal("child"));
        const double initial_child_priority = brain.goal("child")->priority;
        assert(brain.update_goal_progress("child", 0.5));
        child_priority_after_learning = brain.goal("child")->priority;
        assert(child_priority_after_learning > initial_child_priority);
        assert(brain.goal("child")->outcome_momentum > 0.0);
        assert(brain.goal("child")->status == GoalStatus::active);
    }

    {
        Brain restored(journal);
        assert(restored.goals().size() == 2);
        assert(restored.goal("root")->status == GoalStatus::completed);
        assert(restored.goal("child")->status == GoalStatus::active);
        assert(std::abs(restored.goal("child")->progress - 0.5) < 1e-12);
        assert(std::abs(restored.goal("child")->priority - child_priority_after_learning) < 1e-12);
        assert(std::abs(restored.goal("child")->outcome_momentum - 0.1) < 1e-12);
        const auto eligible = restored.eligible_goals();
        assert(eligible.size() == 1);
        assert(eligible.front().id == "child");
    }

    std::filesystem::remove(journal, ec);
    return 0;
}
