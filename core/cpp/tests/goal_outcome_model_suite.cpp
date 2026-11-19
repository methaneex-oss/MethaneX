#include "jarvis/core/cognitive_goal_outcome.hpp"

#include <cassert>
#include <cmath>

using namespace jarvis::core;

int main() {
    GoalOutcomeEvidence first{"goal-alpha", 0.0, 0.4, 0.0, false, 0.8, 1};
    first.normalize();
    assert(std::abs(first.delta - 0.4) < 1e-12);
    assert(!first.completed);

    GoalProgressModel model{};
    model.observe(first);
    assert(model.goal_id == "goal-alpha");
    assert(std::abs(model.progress - 0.4) < 1e-12);
    assert(model.positive_outcomes == 1);
    assert(std::abs(model.confidence - 0.8) < 1e-12);

    GoalOutcomeEvidence second{"goal-alpha", 0.4, 0.25, 0.0, false, 0.6, 2};
    second.normalize();
    model.observe(second);
    assert(second.delta < 0.0);
    assert(model.negative_outcomes == 1);
    assert(std::abs(model.progress - 0.25) < 1e-12);
    assert(std::abs(model.confidence - 0.7) < 1e-12);

    GoalOutcomeEvidence completed{"goal-alpha", 0.25, 1.0, 0.0, false, 0.95, 3};
    completed.normalize();
    assert(completed.completed);
    model.observe(completed);
    assert(model.completed_outcomes == 1);
    assert(std::abs(model.progress - 1.0) < 1e-12);

    GoalOutcomeEvidence unrelated{"goal-beta", 0.0, 1.0, 0.0, false, 1.0, 4};
    unrelated.normalize();
    model.observe(unrelated);
    assert(model.goal_id == "goal-alpha");
    assert(model.completed_outcomes == 1);

    return 0;
}
