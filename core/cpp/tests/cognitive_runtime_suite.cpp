#include "jarvis/core/cognitive_runtime.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <string>
#include <thread>

using namespace jarvis::core;

namespace {
CognitiveCycleInput make_input(const std::string& goal_id, int value) {
    CognitiveCycleInput input;
    input.observation = Event{0, 0, "runtime", "observation", {{"value", value}}};
    input.candidate_actions = {
        CandidateAction{"continue", 1.0, 0.9, 0.1, 1.0},
        CandidateAction{"inspect", 0.6, 0.5, 0.2, 1.0},
    };
    input.goal_id = goal_id;
    input.planning_horizon = 2;
    input.memory_limit = 4;
    input.reasoning_steps = 4;
    return input;
}
}

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_runtime_suite.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

    Brain brain(journal);
    Goal goal;
    goal.id = "runtime-goal";
    goal.description = "Process runtime observations";
    goal.priority = 1.0;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    CognitiveRuntimeConfig config;
    config.input_capacity = 64;
    config.result_capacity = 64;
    config.drain_on_stop = true;

    CognitiveRuntime runtime(brain, config);
    assert(!runtime.running());
    assert(runtime.start());
    assert(runtime.running());
    assert(!runtime.start());

    auto high = make_input(goal.id, 100);
    auto low = make_input(goal.id, 1);
    auto medium = make_input(goal.id, 50);
    assert(runtime.submit(low, 1.0));
    assert(runtime.submit(high, 10.0));
    assert(runtime.submit(medium, 5.0));

    int completed = 0;
    bool saw_high = false;
    for (int attempt = 0; attempt < 200 && completed < 3; ++attempt) {
        while (const auto result = runtime.poll_result()) {
            assert(result->status == CognitiveCycleStatus::completed);
            assert(result->context.selected_goal.id == goal.id);
            assert(!result->context.decisions.empty());
            if (result->context.observation.event.data.at("value") == 100) {
                saw_high = completed == 0;
            }
            ++completed;
        }
        if (completed < 3) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }

    assert(completed == 3);
    assert(saw_high);
    assert(runtime.pending_inputs() == 0);

    const auto metrics = runtime.metrics();
    assert(metrics.accepted == 3);
    assert(metrics.rejected == 0);
    assert(metrics.processed == 3);
    assert(metrics.dropped_results == 0);

    assert(!runtime.submit(make_input(goal.id, 999), 100.0));
    assert(runtime.metrics().rejected == 1);

    runtime.stop();
    assert(!runtime.running());
    assert(!runtime.submit(make_input(goal.id, 1000), 100.0));
    assert(runtime.metrics().rejected == 2);

    std::filesystem::remove(journal, ec);
    return 0;
}
