#include "jarvis/core/goals.hpp"

#include <cassert>
#include <cmath>
#include <limits>

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

    const auto eligible = goals.eligible(10);
    assert(eligible.empty());
    assert(goals.all().size() == 2);
    return 0;
}
