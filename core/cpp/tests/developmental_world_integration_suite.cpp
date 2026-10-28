#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/developmental_world.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <thread>

using namespace jarvis::core;

namespace {
CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        if (auto result = runtime.poll_result()) return *result;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(false && "timed out waiting for world-integrated cognitive cycle");
    return {};
}

CognitiveCycleInput make_input(const Goal& goal, const DevelopmentalWorld& world) {
    CognitiveCycleInput input;
    input.observation = world.observe().event;
    for (const auto& name : world.available_actions())
        input.candidate_actions.push_back(CandidateAction{name, 2.0, 0.5, 0.9, 0.1});
    input.goal_id = goal.id;
    input.developmental_context = world.config().context;
    input.planning_horizon = 1;
    input.memory_limit = 8;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.action_constraints = ActionConstraints{1.0, false};
    return input;
}
} // namespace

int main() {
    const auto journal = std::filesystem::temp_directory_path() /
                         "jarvis_developmental_world_integration.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    DevelopmentalWorldConfig world_config;
    world_config.task = "reach_destination";
    world_config.context = "navigation/clear";
    world_config.initial_state = {
        {"route_condition", std::string("clear")},
        {"weather", std::string("clear")},
        {"destination_reached", false},
    };
    world_config.initial_resources = 20.0;
    world_config.random_seed = 20261024;
    world_config.max_steps = 50;
    DevelopmentalWorld world(world_config);

    assert(world.add_action(DevelopmentalWorldAction{
        "route-north", 1.0, {},
        [](const Attributes& state, std::mt19937_64&) -> std::optional<DevelopmentalWorldTransition> {
            const bool flooded = std::get<std::string>(state.at("route_condition")) == "flooded";
            return DevelopmentalWorldTransition{
                flooded ? -1.0 : 1.0,
                {{"last_route", std::string("north")}},
                {flooded ? "north_route_blocked" : "north_route_traversed"}, false};
        }}));
    assert(world.add_action(DevelopmentalWorldAction{
        "route-south", 1.0, {},
        [](const Attributes& state, std::mt19937_64&) -> std::optional<DevelopmentalWorldTransition> {
            const bool flooded = std::get<std::string>(state.at("route_condition")) == "flooded";
            return DevelopmentalWorldTransition{
                flooded ? 1.0 : -1.0,
                {{"last_route", std::string("south")}},
                {flooded ? "south_route_traversed" : "south_route_longer"}, false};
        }}));

    std::optional<DevelopmentalWorldStep> last_world_step;
    CognitiveRuntimeConfig runtime_config;
    runtime_config.input_capacity = 8;
    runtime_config.result_capacity = 8;
    runtime_config.feedback_capacity = 16;
    runtime_config.drain_on_stop = true;
    runtime_config.action_adapter.authorization.maximum_risk = 1.0;
    runtime_config.action_adapter.execute = [&](const CandidateAction& action) {
        const auto available = world.available_actions();
        return std::find(available.begin(), available.end(), action.name) != available.end();
    };
    runtime_config.action_adapter.verify = [](const CandidateAction&) { return true; };
    runtime_config.action_adapter.observe_consequence = [&](const CandidateAction& action) {
        last_world_step = world.step(action.name);
        return last_world_step->consequence;
    };

    {
        Brain brain(journal);
        Goal goal;
        goal.id = "world-navigation-goal";
        goal.description = "Reach the destination while learning route consequences";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        CognitiveRuntime runtime(brain, runtime_config);
        assert(runtime.start());

        // Run the same agent against a changing world. The world controls
        // observations, action availability, resource use, and consequences;
        // the brain controls which candidate is selected.
        for (int episode = 0; episode < 12; ++episode) {
            const bool flooded = episode >= 6;
            world.set_context(flooded ? "navigation/flooded" : "navigation/clear");
            world.reset_episode(Attributes{
                {"route_condition", std::string(flooded ? "flooded" : "clear")},
                {"weather", std::string(flooded ? "rain" : "clear")},
                {"destination_reached", false},
            });
            last_world_step.reset();

            const auto input = make_input(goal, world);
            assert(input.candidate_actions.size() == 2);
            assert(runtime.submit(input, 1.0));
            const auto result = await_result(runtime);
            assert(result.status == CognitiveCycleStatus::completed);
            assert(!result.context.plan.steps.empty());
            assert(result.context.action_execution_results.size() == 1);
            const auto& execution = result.context.action_execution_results.front();
            const auto& selected = result.context.plan.steps.front().action.name;
            assert(execution.action.name == selected);
            assert(last_world_step.has_value());
            assert(last_world_step->executed);
            assert(last_world_step->observed);
            assert(last_world_step->consequence.has_value());
            assert(execution.outcome.observed);
            assert(execution.outcome.actual_consequence == *last_world_step->consequence);
            assert(world.step_count() == 1);
            assert(world.resources_remaining() == 19.0);
            assert(std::get<std::string>(result.context.observation.event.data.at("route_condition")) ==
                   (flooded ? "flooded" : "clear"));

            // The world changes which route is useful halfway through the run.
            // Verify the runtime's actual choice adapts from observed outcomes,
            // rather than merely recording outcomes and surviving a restart.
            if (!flooded && episode > 0) {
                assert(selected == "route-north");
                const auto* clear_strategy =
                    brain.developmental_best_strategy("navigation/clear");
                assert(clear_strategy != nullptr);
                assert(clear_strategy->action == "route-north");
                assert(clear_strategy->value > 0.0);
            } else if (flooded && episode == 6) {
                // New context has no prior strategy: first trial exposes the
                // formerly good route's now-negative consequence.
                assert(selected == "route-north");
                const auto* flooded_strategy =
                    brain.developmental_best_strategy("navigation/flooded");
                assert(flooded_strategy != nullptr);
                assert(flooded_strategy->action == "route-north");
                assert(flooded_strategy->value < 0.0);
            } else if (flooded && episode > 6) {
                assert(selected == "route-south");
                const auto* flooded_strategy =
                    brain.developmental_best_strategy("navigation/flooded");
                assert(flooded_strategy != nullptr);
                assert(flooded_strategy->action == "route-south");
                assert(flooded_strategy->value > 0.0);
            }

            std::cout << "[world-trial] episode=" << episode
                      << " context=" << world.config().context
                      << " selected=" << selected
                      << " consequence=" << *last_world_step->consequence << '\n';
        }
        runtime.stop();

        assert(runtime.metrics().processed == 12);
        assert(runtime.metrics().action_succeeded == 12);
        assert(!brain.memory().by_kind("action_outcome").empty());
        assert(!brain.memory().by_kind("observation").empty());
    }

    // The learned journal can be reopened independently of the environment's
    // episode state. The environment resets; the brain's persisted experience
    // remains available to influence later decisions.
    {
        Brain restored(journal);
        assert(restored.goal("world-navigation-goal") != nullptr);
        assert(!restored.memory().by_kind("action_outcome").empty());
        assert(!restored.developmental_strategies().empty());
    }

    std::cout << "[world-integration] episodes=12 action_consequences=12 "
                 "persistent_experience=verified\n";
    return 0;
}
