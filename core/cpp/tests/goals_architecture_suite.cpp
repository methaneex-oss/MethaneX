#include "jarvis/core/brain.hpp"
#include "jarvis/core/goals.hpp"

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

    const auto journal = std::filesystem::temp_directory_path() / "jarvis_goal_integration_test.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

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
        assert(brain.complete_goal("root"));
        assert(brain.activate_goal("child"));
        assert(brain.update_goal_progress("child", 0.5));
        assert(brain.goal("child")->status == GoalStatus::active);
    }

    {
        Brain restored(journal);
        assert(restored.goals().size() == 2);
        assert(restored.goal("root")->status == GoalStatus::completed);
        assert(restored.goal("child")->status == GoalStatus::active);
        assert(std::abs(restored.goal("child")->progress - 0.5) < 1e-12);
        const auto eligible = restored.eligible_goals();
        assert(eligible.size() == 1);
        assert(eligible.front().id == "child");
    }

    std::filesystem::remove(journal, ec);
    return 0;
}
