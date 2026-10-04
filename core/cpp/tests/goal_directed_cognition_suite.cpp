#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
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
        intent.priority, intent.progress, intent.urgency,
        intent.uncertainty, 1.0, intent.urgency
    };
    const auto plan = brain.plan(actions, 2, context);
    assert(!plan.steps.empty());
    assert(plan.steps.front().action.name == "safe_protect");

    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(decisions.front().action.name == "safe_protect");

    // Goal progress is now derived from outcome evidence rather than being only
    // an externally assigned field.
    GoalOutcomeEvidence progress{"protect", 0.0, 0.5, 0.0, false, 0.9, 0};
    assert(brain.assimilate_goal_outcome(progress));
    const auto progressed = brain.goal("protect");
    assert(progressed != nullptr);
    assert(std::abs(progressed->progress - 0.5) < 1e-12);

    // A negative outcome must move the goal backward rather than being treated as
    // an action failure with no cognitive consequence.
    GoalOutcomeEvidence regression{"protect", 0.5, 0.25, 0.0, false, 0.8, 0};
    assert(brain.assimilate_goal_outcome(regression));
    assert(std::abs(brain.goal("protect")->progress - 0.25) < 1e-12);

    // Completion is a state transition and must survive restart.
    GoalOutcomeEvidence completion{"protect", 0.25, 1.0, 0.0, true, 0.95, 0};
    assert(brain.assimilate_goal_outcome(completion));
    assert(brain.goal("protect")->status == GoalStatus::completed);

    const auto before_restart = brain.snapshot();
    assert(!before_restart.goals.empty());

    Brain restarted(journal);
    const auto restored = restarted.goal("protect");
    assert(restored != nullptr);
    assert(restored->status == GoalStatus::completed);
    assert(std::abs(restored->progress - 1.0) < 1e-12);
    assert(restarted.intent().id.empty());

    std::filesystem::remove(journal, ec);
    return 0;
}
