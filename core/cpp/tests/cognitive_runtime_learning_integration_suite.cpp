#include "jarvis/core/cognitive_runtime.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <optional>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

namespace {
std::optional<CognitiveCycleResult> wait_for_result(CognitiveRuntime& runtime,
                                                    int attempts = 500) {
    for (int attempt = 0; attempt < attempts; ++attempt) {
        if (auto result = runtime.poll_result(); result.has_value()) return result;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    return std::nullopt;
}

bool wait_for_feedback(CognitiveRuntime& runtime, std::uint64_t expected,
                       int attempts = 500) {
    for (int attempt = 0; attempt < attempts; ++attempt) {
        if (runtime.metrics().feedback_processed >= expected) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    return runtime.metrics().feedback_processed >= expected;
}

CognitiveCycleInput make_input(const std::string& goal_id, std::int64_t observation) {
    CognitiveCycleInput input;
    input.observation = Event{0, 0, "runtime-learning-world", "observation",
                              {{"state", observation}}};
    CandidateAction calibrate;
    calibrate.name = "calibrate";
    calibrate.utility = 0.8;
    calibrate.expected_value = 0.8;
    calibrate.confidence = 0.9;
    calibrate.risk = 0.1;
    calibrate.reversibility = 1.0;
    calibrate.expected_consequence = 0.8;

    CandidateAction wait;
    wait.name = "wait";
    wait.utility = 0.8;
    wait.expected_value = 0.8;
    wait.confidence = 0.9;
    wait.risk = 0.1;
    wait.reversibility = 1.0;
    wait.expected_consequence = 0.8;

    input.candidate_actions = {calibrate, wait};
    input.goal_id = goal_id;
    input.developmental_context = "runtime-learning-context";
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    return input;
}
} // namespace

int main() {
    const auto journal = std::filesystem::temp_directory_path() /
                         "jarvis_runtime_experience_choice_loop.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    Brain brain(journal);
    Goal goal;
    goal.id = "runtime-learning-goal";
    goal.description = "Learn which action has better observed consequences";
    goal.priority = 0.8;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    std::vector<std::string> executed_actions;
    CognitiveRuntimeConfig config;
    config.result_capacity = 8;
    config.feedback_capacity = 8;
    config.drain_on_stop = true;
    config.action_adapter.authorization.maximum_risk = 1.0;
    config.action_adapter.execute = [&](const CandidateAction& action) {
        executed_actions.push_back(action.name);
        return true;
    };
    config.action_adapter.verify = [](const CandidateAction&) { return true; };
    config.action_adapter.observe_consequence = [](const CandidateAction& action)
        -> std::optional<double> {
        return action.name == "calibrate" ? -0.8 : 0.8;
    };

    CognitiveRuntime runtime(brain, config);
    assert(runtime.start());

    assert(runtime.submit(make_input(goal.id, 1)));
    const auto first = wait_for_result(runtime);
    assert(first.has_value());
    assert(first->status == CognitiveCycleStatus::completed);
    assert(first->context.plan.steps.size() == 1);
    assert(first->context.plan.steps.front().action.name == "calibrate");
    assert(first->context.action_execution_results.size() == 1);
    assert(first->context.action_execution_results.front().action.name == "calibrate");
    assert(executed_actions.size() == 1);
    assert(executed_actions.front() == "calibrate");
    assert(first->context.action_execution_results.front().outcome.observed);
    assert(first->context.action_execution_results.front().outcome.actual_consequence == -0.8);
    assert(wait_for_feedback(runtime, 1));

    const auto learned = brain.developmental_best_strategy("runtime-learning-context");
    assert(learned != nullptr);
    assert(learned->action == "calibrate");
    assert(learned->value < 0.0);
    assert(learned->uses > 0);

    // The same candidate set must be reconsidered after the observed outcome.
    assert(runtime.submit(make_input(goal.id, 2)));
    const auto second = wait_for_result(runtime);
    assert(second.has_value());
    assert(second->status == CognitiveCycleStatus::completed);
    assert(second->context.plan.steps.size() == 1);
    assert(second->context.plan.steps.front().action.name == "wait");
    assert(second->context.action_execution_results.size() == 1);
    assert(second->context.action_execution_results.front().action.name == "wait");
    assert(executed_actions.size() == 2);
    assert(executed_actions[1] == "wait");
    assert(wait_for_feedback(runtime, 2));

    runtime.stop();
    assert(!runtime.running());

    Brain restored(journal);
    const auto* restored_strategy =
        restored.developmental_best_strategy("runtime-learning-context");
    assert(restored_strategy != nullptr);
    assert(restored_strategy->action == "wait");
    assert(restored_strategy->value > 0.0);
    assert(restored_strategy->uses >= 2);

    // No-feedback control: successful execution alone must not be mistaken for
    // a beneficial consequence. Without an observation, the same alternatives
    // should not acquire a consequence-driven preference.
    const auto control_journal = std::filesystem::temp_directory_path() /
                                 "jarvis_runtime_no_feedback_control.bin";
    std::filesystem::remove(control_journal, ec);
    std::filesystem::remove(control_journal.string() + ".meta", ec);
    {
        Brain control_brain(control_journal);
        Goal control_goal;
        control_goal.id = "runtime-no-feedback-goal";
        control_goal.description = "Do not infer outcomes without observation";
        control_goal.priority = 0.8;
        assert(control_brain.create_goal(control_goal));
        assert(control_brain.activate_goal(control_goal.id));

        std::vector<std::string> control_executed;
        CognitiveRuntimeConfig control_config;
        control_config.result_capacity = 8;
        control_config.feedback_capacity = 8;
        control_config.drain_on_stop = true;
        control_config.action_adapter.authorization.maximum_risk = 1.0;
        control_config.action_adapter.execute = [&](const CandidateAction& action) {
            control_executed.push_back(action.name);
            return true;
        };
        control_config.action_adapter.verify = [](const CandidateAction&) { return true; };
        // Deliberately leave observe_consequence unset: no observed outcome exists.
        CognitiveRuntime control_runtime(control_brain, control_config);
        assert(control_runtime.start());
        assert(control_runtime.submit(make_input(control_goal.id, 1)));
        const auto control_first = wait_for_result(control_runtime);
        assert(control_first.has_value());
        assert(control_first->status == CognitiveCycleStatus::completed);
        assert(control_first->context.plan.steps.front().action.name == "calibrate");
        assert(control_first->context.action_execution_results.size() == 1);
        assert(!control_first->context.action_execution_results.front().outcome.observed);
        assert(control_executed == std::vector<std::string>{"calibrate"});
        assert(wait_for_feedback(control_runtime, 1));
        assert(control_brain.developmental_best_strategy("runtime-learning-context") == nullptr);

        assert(control_runtime.submit(make_input(control_goal.id, 2)));
        const auto control_second = wait_for_result(control_runtime);
        assert(control_second.has_value());
        assert(control_second->status == CognitiveCycleStatus::completed);
        assert(control_second->context.plan.steps.front().action.name == "calibrate");
        assert(control_executed == (std::vector<std::string>{"calibrate", "calibrate"}));
        control_runtime.stop();
    }
    std::filesystem::remove(control_journal, ec);
    std::filesystem::remove(control_journal.string() + ".meta", ec);

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
