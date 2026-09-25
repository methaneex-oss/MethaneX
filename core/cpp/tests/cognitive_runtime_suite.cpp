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

bool wait_for_results(CognitiveRuntime& runtime, int expected, int attempts = 300) {
    int completed = 0;
    for (int attempt = 0; attempt < attempts && completed < expected; ++attempt) {
        while (runtime.poll_result().has_value()) ++completed;
        if (completed < expected) std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    return completed == expected;
}

} // namespace

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_runtime_suite.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    Brain brain(journal);
    Goal goal;
    goal.id = "runtime-goal";
    goal.description = "Process runtime observations";
    goal.priority = 1.0;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    int executed = 0;
    int verified = 0;
    CognitiveRuntimeConfig config;
    config.input_capacity = 64;
    config.result_capacity = 64;
    config.feedback_capacity = 64;
    config.drain_on_stop = true;
    config.action_adapter.authorization.granted_permissions = {};
    config.action_adapter.authorization.maximum_risk = 1.0;
    config.action_adapter.execute = [&](const CandidateAction&) {
        ++executed;
        return true;
    };
    config.action_adapter.verify = [&](const CandidateAction&) {
        ++verified;
        return true;
    };

    CognitiveRuntime runtime(brain, config);
    assert(!runtime.running());
    assert(runtime.start());
    assert(runtime.running());
    assert(!runtime.start());

    assert(runtime.submit(make_input(goal.id, 1), 1.0));
    std::optional<CognitiveCycleResult> action_result;
    for (int attempt = 0; attempt < 300 && !action_result.has_value(); ++attempt) {
        while (const auto result = runtime.poll_result()) {
            if (result->status == CognitiveCycleStatus::completed) {
                action_result = *result;
                break;
            }
        }
        if (!action_result.has_value()) std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    assert(action_result.has_value());
    assert(!action_result->context.action_assessments.empty());
    assert(action_result->context.action_execution_results.size() == 1);
    assert(action_result->context.action_execution_results.front().status == ActionExecutionStatus::verified);
    assert(action_result->context.action_execution_results.front().authorized);
    assert(action_result->context.action_execution_results.front().executed);
    assert(action_result->context.action_execution_results.front().verified);
    assert(executed == 1);
    assert(verified == 1);

    for (int attempt = 0; attempt < 300 && runtime.pending_feedback() != 0; ++attempt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(runtime.pending_feedback() == 0);
    assert(runtime.metrics().feedback_processed >= 1);
    assert(runtime.workspace().action_execution_results.size() == 1);

    // Authorization is a hard boundary: an assessed action must never reach the
    // execution callback when the authorization context denies its risk.
    int bypass_attempts = 0;
    CognitiveRuntimeConfig denied_config;
    denied_config.result_capacity = 8;
    denied_config.feedback_capacity = 8;
    denied_config.action_adapter.authorization.maximum_risk = 0.0;
    denied_config.action_adapter.execute = [&](const CandidateAction&) {
        ++bypass_attempts;
        return true;
    };
    denied_config.action_adapter.verify = [](const CandidateAction&) { return true; };

    CognitiveRuntime denied_runtime(brain, denied_config);
    assert(denied_runtime.start());
    assert(denied_runtime.submit(make_input(goal.id, 2)));

    std::optional<CognitiveCycleResult> denied_result;
    for (int attempt = 0; attempt < 300 && !denied_result.has_value(); ++attempt) {
        if (const auto result = denied_runtime.poll_result()) denied_result = *result;
        if (!denied_result.has_value()) std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(denied_result.has_value());
    assert(denied_result->context.action_execution_results.size() == 1);
    assert(denied_result->context.action_execution_results.front().status == ActionExecutionStatus::rejected);
    assert(!denied_result->context.action_execution_results.front().authorized);
    assert(bypass_attempts == 0);
    denied_runtime.stop();

    // Execution failure is observable but non-fatal to the cognitive worker.
    CognitiveRuntimeConfig failing_config;
    failing_config.result_capacity = 8;
    failing_config.feedback_capacity = 8;
    failing_config.action_adapter.authorization.maximum_risk = 1.0;
    failing_config.action_adapter.execute = [](const CandidateAction&) { return false; };
    failing_config.action_adapter.verify = [](const CandidateAction&) { return true; };

    CognitiveRuntime failing_runtime(brain, failing_config);
    assert(failing_runtime.start());
    assert(failing_runtime.submit(make_input(goal.id, 3)));

    std::optional<CognitiveCycleResult> failed_result;
    for (int attempt = 0; attempt < 300 && !failed_result.has_value(); ++attempt) {
        if (const auto result = failing_runtime.poll_result()) failed_result = *result;
        if (!failed_result.has_value()) std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(failed_result.has_value());
    assert(failed_result->status == CognitiveCycleStatus::completed);
    assert(failed_result->context.action_execution_results.size() == 1);
    assert(failed_result->context.action_execution_results.front().status == ActionExecutionStatus::failed);
    assert(failing_runtime.running());
    assert(failing_runtime.submit(make_input(goal.id, 4)));
    assert(wait_for_results(failing_runtime, 1));
    failing_runtime.stop();

    // Feedback is processed before subsequent queued cognition and invalid
    // feedback cannot terminate or mutate the worker.
    const auto prediction = brain.predict("runtime.prediction", 0.75, 0.9);
    assert(!prediction.key.empty());
    assert(runtime.submit_feedback(CognitiveFeedback{
        prediction.key,
        0.75,
        Evidence{"runtime", "runtime.prediction.outcome", 0.75, 0.9},
    }));
    assert(runtime.submit(make_input(goal.id, 5), 1.0));
    assert(runtime.submit_feedback(CognitiveFeedback{} ) == false);

    for (int attempt = 0; attempt < 300 && runtime.pending_feedback() != 0; ++attempt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(runtime.pending_feedback() == 0);
    assert(runtime.running());

    bool resolved = false;
    for (const auto& current : brain.snapshot().predictions) {
        if (current.key == prediction.key) {
            resolved = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(resolved);
    assert(runtime.metrics().feedback_rejected == 1);

    runtime.stop();
    assert(!runtime.running());
    assert(!runtime.submit(make_input(goal.id, 1000), 100.0));
    assert(runtime.metrics().rejected == 1);

    Brain restored(journal);
    bool persisted = false;
    for (const auto& current : restored.snapshot().predictions) {
        if (current.key == prediction.key) {
            persisted = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(persisted);
    const auto* action_knowledge = restored.knowledge_source("action_executor");
    assert(action_knowledge != nullptr);
    assert(action_knowledge->observations >= 1);

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
