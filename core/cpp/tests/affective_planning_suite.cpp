#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <string>
#include <vector>

using namespace jarvis::core;

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis-affective-planning-suite";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root);

    const std::vector<CandidateAction> actions{
        {"safe", 0.45, 0.45, 0.10, 1.0},
        {"risky", 0.45, 0.90, 0.85, 0.0},
    };

    Brain calm(root / "calm.bin");
    Goal calm_goal{"goal", "complete objective", 0.80, 0.10, 0, 0, GoalStatus::active};
    assert(calm.create_goal(calm_goal));
    const auto calm_plan = calm.plan_with_affect(actions, 1);
    assert(calm_plan.steps.size() == 1);

    Brain activated(root / "activated.bin");
    Goal activated_goal{"goal", "complete objective", 0.80, 0.10, 0, 0, GoalStatus::active};
    assert(activated.create_goal(activated_goal));
    activated.observe(Event{
        0, 0, "experience", "observation",
        {{"outcome", Scalar{-1.0}},
         {"prediction_error", Scalar{1.0}},
         {"novelty", Scalar{1.0}},
         {"salience", Scalar{1.0}},
         {"confidence", Scalar{0.0}}}});
    const auto state = activated.affective_state();
    assert(state.tension > 0.0);
    assert(state.arousal > 0.0);

    const auto activated_plan = activated.plan_with_affect(actions, 1);
    assert(activated_plan.steps.size() == 1);
    assert(activated_plan.steps.front().action.name == "safe");

    IntentModel intent_model;
    const std::vector<Goal> goals{activated_goal};
    const auto neutral_intent = intent_model.select_with_affect(
        goals, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1);
    const auto affected_intent = intent_model.select_with_affect(
        goals, 0.0, 0.0,
        state.valence, state.arousal, state.uncertainty,
        state.tension, state.stability, 1);
    assert(neutral_intent.id == affected_intent.id);
    assert(neutral_intent.priority != affected_intent.priority ||
           neutral_intent.uncertainty != affected_intent.uncertainty);
    assert(affected_intent.uncertainty >= neutral_intent.uncertainty);

    // PlanStep exposes expected_score, not a raw score. The affective planning
    // pathway must alter that actual planning quantity.
    assert(std::abs(calm_plan.steps.front().expected_score -
                    activated_plan.steps.front().expected_score) > 1e-12);
    assert(std::isfinite(calm_plan.steps.front().expected_score));
    assert(std::isfinite(activated_plan.steps.front().expected_score));

    const auto explicit_context = PlanningContext{
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        -1.0, 1.0, 1.0, 1.0, 0.0};
    Planner planner;
    const auto explicit_plan = planner.build(actions, 1, explicit_context);
    assert(explicit_plan.steps.front().action.name == "safe");
    assert(std::isfinite(explicit_plan.steps.front().expected_score));

    std::filesystem::remove_all(root);
    return 0;
}
