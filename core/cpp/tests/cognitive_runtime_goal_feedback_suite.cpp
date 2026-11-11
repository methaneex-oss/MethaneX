#include "jarvis/core/cognitive_runtime.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <thread>

using namespace jarvis::core;

static bool wait_feedback(CognitiveRuntime& runtime, std::uint64_t target) {
    for (int i = 0; i < 300; ++i) {
        if (runtime.metrics().feedback_processed >= target) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    return false;
}

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_runtime_goal_feedback.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    Brain brain(journal);
    Goal goal{"runtime-goal", "reach observed state", 1.0, 0.0, 0, 0, GoalStatus::pending, {}, {}};
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    CognitiveRuntimeConfig config;
    config.feedback_capacity = 16;
    CognitiveRuntime runtime(brain, config);
    assert(runtime.start());

    assert(runtime.submit_feedback(CognitiveFeedback{
        "", Scalar{1.0}, std::nullopt, goal.id, 0.4, 0.8}));
    assert(wait_feedback(runtime, 1));
    const auto progressed = brain.goal(goal.id);
    assert(progressed != nullptr);
    assert(progressed->progress == 0.4);
    assert(progressed->status == GoalStatus::active);

    assert(runtime.submit_feedback(CognitiveFeedback{
        "", Scalar{1.0}, std::nullopt, goal.id, 1.0, 0.95}));
    assert(wait_feedback(runtime, 2));
    const auto completed = brain.goal(goal.id);
    assert(completed != nullptr);
    assert(completed->progress == 1.0);
    assert(completed->status == GoalStatus::completed);
    assert(brain.memory().by_kind("goal_progress", 2).size() == 2);
    assert(brain.memory().by_kind("goal_complete", 1).size() == 1);

    assert(!runtime.submit_feedback(CognitiveFeedback{"", Scalar{0.0}, std::nullopt, goal.id, 0.5, 0.5}));
    runtime.stop();

    Brain restored(journal);
    const auto restored_goal = restored.goal(goal.id);
    assert(restored_goal != nullptr);
    assert(restored_goal->status == GoalStatus::completed);
    assert(restored_goal->progress == 1.0);

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
