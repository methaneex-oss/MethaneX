#include "jarvis/core/cognitive_runtime.hpp"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>

using namespace jarvis::core;

namespace {
CognitiveCycleInput make_input(const std::string& goal_id, std::int64_t value) {
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

    constexpr int submitted = 32;
    for (int i = 0; i < submitted; ++i) {
        assert(runtime.submit(make_input(goal.id, i), static_cast<double>(i)));
    }

    int completed = 0;
    for (int attempt = 0; attempt < 200 && completed < submitted; ++attempt) {
        while (const auto result = runtime.poll_result()) {
            assert(result->status == CognitiveCycleStatus::completed);
            assert(result->context.selected_goal.id == goal.id);
            assert(!result->context.decisions.empty());
            ++completed;
        }
        if (completed < submitted) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }

    assert(completed == submitted);
    assert(runtime.pending_inputs() == 0);

    const auto metrics = runtime.metrics();
    assert(metrics.accepted == submitted);
    assert(metrics.rejected == 0);
    assert(metrics.processed == submitted);
    assert(metrics.dropped_results == 0);

    runtime.stop();
    assert(!runtime.running());
    assert(!runtime.submit(make_input(goal.id, 1000), 100.0));
    assert(runtime.metrics().rejected == 1);

    std::filesystem::remove(journal, ec);
    return 0;
}
