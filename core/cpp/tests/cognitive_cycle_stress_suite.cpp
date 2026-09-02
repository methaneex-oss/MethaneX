#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cstdint>
#include <filesystem>
#include <string>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_cycle_stress.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

    Brain brain(journal);
    CognitiveCycle cycle(brain);

    Goal goal;
    goal.id = "continuous-operation";
    goal.description = "Process the incoming stream";
    goal.priority = 1.0;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    constexpr std::int64_t iterations = 256;
    for (std::int64_t i = 0; i < iterations; ++i) {
        CognitiveCycleInput input;
        input.observation = Event{0, 0, "stress", "observation", {{"sequence", i}, {"state", std::string("active")}}};
        input.candidate_actions = {
            CandidateAction{"continue", 1.0, 1.0, 0.0, 1.0},
            CandidateAction{"inspect", 0.5, 0.5, 0.1, 1.0},
        };
        input.goal_id = goal.id;
        input.planning_horizon = 2;
        input.memory_limit = 8;
        input.reasoning_steps = 8;

        const auto result = cycle.run(input);
        assert(result.status == CognitiveCycleStatus::completed);
        assert(result.context.selected_goal.id == goal.id);
        assert(!result.context.plan.steps.empty());
        assert(!result.context.decisions.empty());
    }

    assert(brain.state().events_seen >= static_cast<std::uint64_t>(iterations));
    assert(brain.memory().size() >= static_cast<std::size_t>(iterations));

    std::filesystem::remove(journal, ec);
    return 0;
}
