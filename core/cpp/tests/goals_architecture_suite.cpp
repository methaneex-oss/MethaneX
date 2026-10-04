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
