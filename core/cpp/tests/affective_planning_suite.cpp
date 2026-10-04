#include "jarvis/core/brain.hpp"

#include <cassert>
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
    const auto calm_plan = calm.plan_with_affect(actions, 1);
    assert(calm_plan.steps.size() == 1);

    Brain activated(root / "activated.bin");
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

    // The same world/action evidence is evaluated differently because the
    // internal affective state changes appraisal weighting, not because an
    // emotion-specific action rule was installed.
    const auto explicit_context = PlanningContext{
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        -1.0, 1.0, 1.0, 1.0, 0.0};
    Planner planner;
    const auto explicit_plan = planner.build(actions, 1, explicit_context);
    assert(explicit_plan.steps.front().action.name == "safe");

    std::filesystem::remove_all(root);
    return 0;
}
