#include "jarvis/core/cognitive_runtime.hpp"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

namespace {
CognitiveCycleInput training_input(const std::string& goal_id, std::int64_t episode) {
    CognitiveCycleInput input;
    input.observation = Event{0, 0, "training_environment", "observation",
                              {{"episode", episode},
                               {"task", std::string("reach_destination")}}};
    // The environment offers both actions. It does not choose for the brain.
    input.candidate_actions = {
        CandidateAction{"bad-route", 0.5, 0.5, 0.9, 0.1},
        CandidateAction{"good-route", 0.5, 0.5, 0.9, 0.1},
    };
    input.goal_id = goal_id;
    input.developmental_context = "navigation/route-selection";
    input.planning_horizon = 1;
    input.memory_limit = 8;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.action_constraints = ActionConstraints{1.0, false};
    return input;
}

CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int attempt = 0; attempt < 500; ++attempt) {
        if (auto result = runtime.poll_result()) return *result;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(false && "timed out waiting for a developmental training episode");
    return {};
}
} // namespace

int main() {
    const auto journal = std::filesystem::temp_directory_path() /
                        "jarvis_developmental_training_environment.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    std::vector<std::string> executed_actions;
    CognitiveRuntimeConfig config;
    config.input_capacity = 32;
    config.result_capacity = 32;
    config.feedback_capacity = 32;
    config.drain_on_stop = true;
    config.action_adapter.authorization.maximum_risk = 1.0;
    // Episode zero simulates a total executor outage. Even if the plan contains
    // multiple actions, none can produce a real-world consequence in that episode.
    std::int64_t current_episode = -1;
    config.action_adapter.execute = [&](const CandidateAction& action) {
        executed_actions.push_back(action.name);
        if (current_episode == 0) return false;
        return true;
    };
    config.action_adapter.verify = [](const CandidateAction&) { return true; };
    config.action_adapter.observe_consequence = [](const CandidateAction& action) {
        // Deterministic world physics: the brain must discover which route works
        // by acting and observing consequences, not by receiving the answer.
        return action.name == "good-route" ? 1.0 : -1.0;
    };

    std::vector<std::string> episode_actions;
    {
        Brain brain(journal);
        Goal goal;
        goal.id = "training-navigation-goal";
        goal.description = "Reach the destination with positive consequences";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        CognitiveRuntime runtime(brain, config);
        assert(runtime.start());

        constexpr std::int64_t episode_count = 8;
        for (std::int64_t episode = 0; episode < episode_count; ++episode) {
            current_episode = episode;
            auto input = training_input(goal.id, episode);
            // A system-wide executor outage is infrastructure evidence, not
            // evidence that the selected route is intrinsically bad. Keep that
            // episode in its own context so it cannot poison route learning.
            if (episode == 0) {
                input.developmental_context = "infrastructure/executor-outage";
            }
            assert(runtime.submit(input, 1.0));
            const auto result = await_result(runtime);
            assert(result.status == CognitiveCycleStatus::completed);
            assert(!result.context.plan.steps.empty());
            episode_actions.push_back(result.context.plan.steps.front().action.name);

            if (episode == 0) {
                assert(runtime.running());
                bool observed_executor_failure = false;
                for (const auto& execution : result.context.action_execution_results) {
                    if (execution.status == ActionExecutionStatus::failed) {
                        observed_executor_failure = true;
                        break;
                    }
                }
                assert(observed_executor_failure);
                // Every execution failed before a consequence could be observed.
                // The failure may inform the outage context, but must not create
                // a route preference in the navigation context.
                assert(!result.context.action_execution_results.empty());
                for (const auto& execution : result.context.action_execution_results) {
                    assert(execution.status == ActionExecutionStatus::failed);
                    assert(!execution.outcome.observed);
                }
                const auto* outage_strategy =
                    brain.developmental_best_strategy("infrastructure/executor-outage");
                assert(outage_strategy != nullptr);
                assert(outage_strategy->value < 0.0);
                for (const auto& strategy : brain.developmental_strategies()) {
                    assert(strategy.context != "navigation/route-selection");
                }
            }
        }
        runtime.stop();

        // These are behavioral acceptance criteria, not just checks that
        // events were stored: the same brain must change its later choice.
        assert(episode_actions.front() == "bad-route");
        assert(episode_actions.back() == "good-route");
        assert(runtime.metrics().processed == episode_count);
        assert(runtime.metrics().action_succeeded > 0);

        const auto strategies = brain.developmental_strategies();
        bool learned_good_route = false;
        for (const auto& strategy : strategies) {
            if (strategy.context == "navigation/route-selection" &&
                strategy.action == "good-route" && strategy.value > 0.0 &&
                strategy.uses > 0) {
                learned_good_route = true;
                break;
            }
        }
        assert(learned_good_route);
        assert(!brain.memory().by_kind("action_outcome").empty());
    }

    // The second phase starts a fresh Brain from the same persistent journal.
    // It must retain the strategy and select the useful route without relearning.
    {
        Brain restored(journal);
        Goal goal;
        goal.id = "training-navigation-goal";
        goal.description = "Reach the destination with positive consequences";
        goal.priority = 1.0;
        assert(restored.goal(goal.id) != nullptr);

        CognitiveCycleInput probe = training_input(goal.id, 100);
        const auto decision = CognitiveCycle(restored).run(probe);
        assert(decision.status == CognitiveCycleStatus::completed);
        assert(!decision.context.plan.steps.empty());
        assert(decision.context.plan.steps.front().action.name == "good-route");
        assert(restored.developmental_best_strategy("navigation/route-selection") != nullptr);

        // Generalization acceptance: after restart, experience learned in the
        // original context must improve choice in a related but unseen context.
        CognitiveCycleInput related_probe = training_input(goal.id, 101);
        related_probe.developmental_context = "navigation/route-variant";
        const auto generalized = CognitiveCycle(restored).run(related_probe);
        assert(generalized.status == CognitiveCycleStatus::completed);
        assert(!generalized.context.plan.steps.empty());
        assert(generalized.context.plan.steps.front().action.name == "good-route");

        // Transfer must remain bounded: navigation experience must not dictate
        // a choice in an unrelated task where the candidates are otherwise tied.
        CognitiveCycleInput unrelated_probe = training_input(goal.id, 102);
        unrelated_probe.developmental_context = "orbital/cooking";
        const auto unrelated = CognitiveCycle(restored).run(unrelated_probe);
        assert(unrelated.status == CognitiveCycleStatus::completed);
        assert(!unrelated.context.plan.steps.empty());
        assert(unrelated.context.plan.steps.front().action.name == "bad-route");
    }

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
