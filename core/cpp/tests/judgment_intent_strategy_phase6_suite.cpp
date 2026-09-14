#include "jarvis/core/brain.hpp"
#include "jarvis/core/intent.hpp"
#include "jarvis/core/strategy.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_phase6_judgment_test.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

    Brain brain(journal);
    assert(brain.create_goal(Goal{"observe", "Maintain situational awareness", 0.35, 0.0, 0, 0,
                                 GoalStatus::pending, {}, {}}));
    assert(brain.create_goal(Goal{"critical", "Protect critical state", 0.95, 0.0, 0, 20,
                                 GoalStatus::pending, {}, {}}));
    assert(brain.activate_goal("observe"));
    assert(brain.activate_goal("critical"));

    const auto observation = brain.observe(Event{0, 0, "sensor", "observation", {{"temperature", 80.0}}});
    assert(observation.event.sequence > 0);

    const auto selected = brain.intent();
    assert(selected.id == "critical");
    assert(selected.priority > 0.9);
    assert(selected.confidence >= 0.0 && selected.confidence <= 1.0);
    assert(selected.urgency > 0.0);

    const auto strategy = brain.strategy();
    assert(strategy.intent.id == "critical");
    assert(strategy.planning.goal_priority > 0.9);
    assert(strategy.planning.deadline_pressure >= selected.urgency);
    assert(strategy.attention >= 0.0 && strategy.attention <= 1.0);

    const std::vector<CandidateAction> actions{
        CandidateAction{"protect", 0.2, 0.4, 0.1, 1.0, 0.1, 0.0, 0.9, DecisionOutcome::act},
        CandidateAction{"ignore", 0.3, 0.3, 0.1, 1.0, 0.1, 0.0, 0.1, DecisionOutcome::defer}
    };
    const auto decisions = brain.choose(actions);
    assert(decisions.size() == 2);
    assert(std::isfinite(decisions.front().score));
    assert(decisions.front().action.name == "protect");

    std::filesystem::remove(journal, ec);
    return 0;
}
