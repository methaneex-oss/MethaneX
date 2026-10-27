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
    config.feedback_capacity = 64;
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

    // Establish a causal pattern through the same persistent brain so the next
    // runtime cycle produces an actual prediction that can be fed back.
    brain.observe(Event{0, 0, "sensor", "observation",
                         {{"temperature", 20.0}, {"fan", false}}});
    brain.observe(Event{0, 0, "sensor", "observation",
                         {{"temperature", 30.0}, {"fan", true}}});

    assert(runtime.submit(make_input(goal.id, 101), 101.0));

    std::optional<CognitiveCycleResult> prediction_result;
    for (int attempt = 0; attempt < 200 && !prediction_result.has_value(); ++attempt) {
        while (const auto result = runtime.poll_result()) {
            assert(result->status == CognitiveCycleStatus::completed);
            if (!result->context.predictions.empty()) {
                prediction_result = *result;
                break;
            }
        }
        if (!prediction_result.has_value()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }

    assert(prediction_result.has_value());
    const auto& prediction = prediction_result->context.predictions.front();
    assert(!prediction.key.empty());
    assert(!prediction.resolved);

    assert(runtime.submit_feedback(CognitiveFeedback{
        prediction.key,
        prediction.predicted,
        Evidence{"runtime", "prediction-feedback", prediction.predicted, 0.9},
    }));

    for (int attempt = 0; attempt < 200 && runtime.pending_feedback() != 0; ++attempt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    assert(runtime.pending_feedback() == 0);
    assert(runtime.metrics().feedback_accepted == 1);
    assert(runtime.metrics().feedback_processed == 1);

    bool resolved = false;
    for (const auto& current : brain.snapshot().predictions) {
        if (current.key == prediction.key) {
            resolved = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(resolved);

    const auto metrics = runtime.metrics();
    assert(metrics.accepted == submitted + 1);
    assert(metrics.rejected == 0);
    assert(metrics.processed == submitted + 1);
    assert(metrics.dropped_results == 0);
    assert(metrics.feedback_rejected == 0);

    runtime.stop();
    assert(!runtime.running());
    assert(!runtime.submit(make_input(goal.id, 1000), 100.0));
    assert(!runtime.submit_feedback(CognitiveFeedback{}));
    assert(runtime.metrics().rejected == 1);
    assert(runtime.metrics().feedback_rejected == 1);

    Brain restored(journal);
    bool persisted = false;
    for (const auto& current : restored.snapshot().predictions) {
        if (current.key == prediction.key) {
            persisted = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(persisted);

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
