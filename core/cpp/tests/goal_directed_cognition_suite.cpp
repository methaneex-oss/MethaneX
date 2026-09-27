#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_goal_directed_cognition.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

    Brain brain(journal);
    assert(brain.create_goal(Goal{"observe", "learn the environment", 0.35, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
    assert(brain.create_goal(Goal{"protect", "protect the active system", 0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
    assert(brain.activate_goal("protect"));

    const auto intent = brain.intent();
    assert(intent.id == "protect");
    assert(intent.priority >= 0.9);
    assert(intent.progress == 0.0);
    assert(intent.confidence >= 0.0 && intent.confidence <= 1.0);

    const std::vector<CandidateAction> actions{
        CandidateAction{"safe_protect", 0.8, 0.9, 0.1, 1.0, 0.1, 0.05, 0.8},
        CandidateAction{"dangerous_protect", 1.0, 1.0, 0.9, 0.2, 0.2, 0.8, 0.8}
    };
    const auto context = PlanningContext{
        intent.priority,
        intent.progress,
        intent.urgency,
        intent.uncertainty,
        1.0,
        intent.urgency
    };
    const auto plan = brain.plan(actions, 2, context);
    assert(!plan.steps.empty());
    assert(plan.steps.front().action.name == "safe_protect");

    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(decisions.front().action.name == "safe_protect");

    assert(brain.update_goal_progress("protect", 0.5));
    const auto progressed = brain.goal("protect");
    assert(progressed != nullptr);
    assert(progressed->progress == 0.5);

    const auto before_restart = brain.snapshot();
    assert(!before_restart.goals.empty());

    Brain restarted(journal);
    const auto restored_intent = restarted.intent();
    assert(restored_intent.id == "protect");
    assert(restored_intent.progress == 0.5);

    std::filesystem::remove(journal, ec);
    return 0;
}
