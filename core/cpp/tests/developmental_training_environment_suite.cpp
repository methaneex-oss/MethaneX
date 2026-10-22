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
    config.action_adapter.execute = [&](const CandidateAction& action) {
        executed_actions.push_back(action.name);
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
            assert(runtime.submit(training_input(goal.id, episode), 1.0));
            const auto result = await_result(runtime);
            assert(result.status == CognitiveCycleStatus::completed);
            assert(!result.context.plan.steps.empty());
            episode_actions.push_back(result.context.plan.steps.front().action.name);
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
    }

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
