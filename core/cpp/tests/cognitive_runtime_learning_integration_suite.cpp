#include "jarvis/core/cognitive_runtime.hpp"

#include <algorithm>
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

CognitiveCycleInput make_input(const std::string& goal_id, std::int64_t observation,
                               const std::string& developmental_context = "runtime-learning-context") {
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
    input.developmental_context = developmental_context;
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
    bool environment_regime_changed = false;
    config.action_adapter.observe_consequence = [&](const CandidateAction& action)
        -> std::optional<double> {
        if (!environment_regime_changed)
            return action.name == "calibrate" ? -0.8 : 0.8;
        return action.name == "calibrate" ? 0.8 : -0.8;
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

    // Verify this runtime experience reached multiple mechanisms, not only the
    // strategy table: the action-consequence prediction is resolved, its
    // prediction-error metric records evidence, affective learning was updated,
    // and episodic memory contains the authoritative outcome with its context.
    const auto& first_execution = first->context.action_execution_results.front();
    assert(first_execution.consequence_prediction_sequence.has_value());
    assert(!first_execution.consequence_prediction_key.empty());
    const auto first_prediction_snapshot = brain.snapshot().predictions;
    const auto resolved_consequence_prediction = std::find_if(
        first_prediction_snapshot.begin(), first_prediction_snapshot.end(),
        [&](const Prediction& prediction) {
            return prediction.created_sequence ==
                   *first_execution.consequence_prediction_sequence;
        });
    assert(resolved_consequence_prediction != first_prediction_snapshot.end());
    assert(resolved_consequence_prediction->resolved);
    const auto* consequence_metric =
        brain.learning_metric(first_execution.consequence_prediction_key);
    assert(consequence_metric != nullptr);
    assert(consequence_metric->observations > 0);
    assert(brain.affective_learning_updates() > 0);
    bool persisted_outcome_memory = false;
    for (const auto& event : brain.memory().all()) {
        if (event.kind != "action_outcome") continue;
        const auto action = event.data.find("action");
        const auto context = event.data.find("context");
        const auto actual = event.data.find("actual_consequence");
        if (action == event.data.end() || context == event.data.end() ||
            actual == event.data.end()) continue;
        const auto* action_name = std::get_if<std::string>(&action->second);
        const auto* context_name = std::get_if<std::string>(&context->second);
        const auto* actual_value = std::get_if<double>(&actual->second);
        if (action_name != nullptr && context_name != nullptr &&
            actual_value != nullptr && *action_name == "calibrate" &&
            *context_name == "runtime-learning-context" &&
            *actual_value == -0.8) {
            persisted_outcome_memory = true;
            break;
        }
    }
    assert(persisted_outcome_memory);

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

    // Context-isolation control: a preference learned in one context must not
    // blindly transfer to a semantically unrelated context. Both candidates
    // have equal initial scores, so the unrelated context starts from the
    // planner's ordinary deterministic tie-break rather than the learned
    // preference for "wait" in runtime-learning-context.
    assert(runtime.submit(make_input(goal.id, 200, "orchard-irrigation-context")));
    const auto unrelated = wait_for_result(runtime);
    assert(unrelated.has_value());
    assert(unrelated->status == CognitiveCycleStatus::completed);
    assert(unrelated->context.plan.steps.size() == 1);
    assert(unrelated->context.plan.steps.front().action.name == "calibrate");
    assert(unrelated->context.action_execution_results.size() == 1);
    assert(unrelated->context.action_execution_results.front().action.name == "calibrate");
    assert(unrelated->context.action_execution_results.front().outcome.observed);
    assert(wait_for_feedback(runtime, 3));

    const auto original_context_strategy =
        brain.developmental_best_strategy("runtime-learning-context");
    assert(original_context_strategy != nullptr);
    assert(original_context_strategy->action == "wait");
    assert(original_context_strategy->value > 0.0);
    const auto unrelated_context_strategy =
        brain.developmental_best_strategy("orchard-irrigation-context");
    assert(unrelated_context_strategy != nullptr);
    assert(unrelated_context_strategy->action == "calibrate");
    assert(unrelated_context_strategy->value < 0.0);

    // Regime-change test: the environment now contradicts the old experience.
    // The runtime must collect new observed consequences and eventually revise
    // its choice, rather than freezing the first learned preference.
    environment_regime_changed = true;
    bool reversed = false;
    std::uint64_t expected_feedback = 3;
    for (std::int64_t observation = 3; observation < 43; ++observation) {
        assert(runtime.submit(make_input(goal.id, observation)));
        const auto result = wait_for_result(runtime);
        assert(result.has_value());
        assert(result->status == CognitiveCycleStatus::completed);
        assert(result->context.plan.steps.size() == 1);
        assert(result->context.action_execution_results.size() == 1);
        const auto& execution = result->context.action_execution_results.front();
        assert(execution.outcome.observed);
        ++expected_feedback;
        assert(wait_for_feedback(runtime, expected_feedback));
        if (result->context.plan.steps.front().action.name == "calibrate") {
            assert(execution.outcome.actual_consequence == 0.8);
            reversed = true;
            break;
        }
        assert(result->context.plan.steps.front().action.name == "wait");
        assert(execution.outcome.actual_consequence == -0.8);
    }
    assert(reversed);

    runtime.stop();
    assert(!runtime.running());

    Brain restored(journal);
    const auto* restored_strategy =
        restored.developmental_best_strategy("runtime-learning-context");
    assert(restored_strategy != nullptr);
    assert(restored_strategy->action == "calibrate");
    assert(restored_strategy->value > 0.0);
    assert(restored_strategy->uses >= 2);

    // Persistence must affect a real decision after restart, not merely expose
    // a stored strategy through an inspection API.
    {
        std::vector<std::string> restored_executions;
        CognitiveRuntimeConfig restored_config;
        restored_config.result_capacity = 4;
        restored_config.feedback_capacity = 4;
        restored_config.drain_on_stop = true;
        restored_config.action_adapter.authorization.maximum_risk = 1.0;
        restored_config.action_adapter.execute = [&](const CandidateAction& action) {
            restored_executions.push_back(action.name);
            return true;
        };
        restored_config.action_adapter.verify = [](const CandidateAction&) { return true; };
        restored_config.action_adapter.observe_consequence =
            [](const CandidateAction& action) -> std::optional<double> {
                return action.name == "calibrate" ? 0.8 : -0.8;
            };
        CognitiveRuntime restored_runtime(restored, restored_config);
        assert(restored_runtime.start());
        assert(restored_runtime.submit(make_input(goal.id, 100)));
        const auto restored_decision = wait_for_result(restored_runtime);
        assert(restored_decision.has_value());
        assert(restored_decision->status == CognitiveCycleStatus::completed);
        assert(restored_decision->context.plan.steps.size() == 1);
        assert(restored_decision->context.plan.steps.front().action.name == "calibrate");
        assert(restored_executions.size() == 1);
        assert(restored_executions.front() == "calibrate");
        restored_runtime.stop();
    }

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

        CognitiveRuntimeConfig control_config;
        control_config.result_capacity = 8;
        control_config.feedback_capacity = 8;
        control_config.drain_on_stop = true;
        control_config.action_adapter.authorization.maximum_risk = 1.0;
        // No executor and no consequence observer: this control run cannot
        // produce either operational or real-world outcome evidence.
        CognitiveRuntime control_runtime(control_brain, control_config);
        assert(control_runtime.start());
        assert(control_runtime.submit(make_input(control_goal.id, 1)));
        const auto control_first = wait_for_result(control_runtime);
        assert(control_first.has_value());
        assert(control_first->status == CognitiveCycleStatus::completed);
        assert(control_first->context.plan.steps.front().action.name == "calibrate");
        assert(control_first->context.action_execution_results.size() == 1);
        assert(control_first->context.action_execution_results.front().status ==
               ActionExecutionStatus::rejected);
        assert(control_first->context.action_execution_results.front().reason ==
               "action_adapter_unavailable");
        assert(control_brain.developmental_best_strategy("runtime-learning-context") == nullptr);

        assert(control_runtime.submit(make_input(control_goal.id, 2)));
        const auto control_second = wait_for_result(control_runtime);
        assert(control_second.has_value());
        assert(control_second->status == CognitiveCycleStatus::completed);
        assert(control_second->context.plan.steps.front().action.name == "calibrate");
        assert(control_second->context.action_execution_results.size() == 1);
        assert(control_second->context.action_execution_results.front().status ==
               ActionExecutionStatus::rejected);
        assert(control_brain.developmental_best_strategy("runtime-learning-context") == nullptr);
        control_runtime.stop();
    }
    std::filesystem::remove(control_journal, ec);
    std::filesystem::remove(control_journal.string() + ".meta", ec);

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
