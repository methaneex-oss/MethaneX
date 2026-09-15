#include "jarvis/core/cognitive_runtime.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <thread>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_workspace_runtime_suite.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);

    Brain brain(path);
    CognitiveRuntime runtime(brain, CognitiveRuntimeConfig{8, 8, true});
    assert(runtime.start());

    CognitiveCycleInput input;
    input.observation = Event{0, 1, "test", "workspace", {{"value", 1.0}}};
    input.planning_horizon = 1;
    input.memory_limit = 4;
    input.reasoning_steps = 4;
    assert(runtime.submit(std::move(input), 1.0));

    for (int i = 0; i < 100 && runtime.pending_results() == 0; ++i)
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

    const auto result = runtime.poll_result();
    assert(result.has_value());
    const auto workspace = runtime.workspace();
    assert(workspace.observation.has_value());
    assert(workspace.observation->event.type == "workspace");
    assert(workspace.cycle == brain.state().cycle);

    runtime.stop();
    std::filesystem::remove(path, ec);
    return 0;
}
