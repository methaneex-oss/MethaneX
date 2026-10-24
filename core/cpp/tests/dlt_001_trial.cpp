#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/developmental_world.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

namespace {
CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        if (auto result = runtime.poll_result()) return *result;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(false && "DLT-001 timed out waiting for a cognitive cycle");
    return {};
}

CognitiveCycleInput make_input(const Goal& goal, const DevelopmentalWorld& world) {
    CognitiveCycleInput input;
    input.observation = world.observe().event;
    for (const auto& action : world.available_actions())
        input.candidate_actions.push_back(CandidateAction{action, 2.5, 0.5, 0.9, 0.1});
    input.goal_id = goal.id;
    input.developmental_context = world.config().context;
    input.planning_horizon = 1;
    input.memory_limit = 8;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.action_constraints = ActionConstraints{1.0, false};
    return input;
}

bool selected_action_is(const CognitiveCycleResult& result, const std::string& expected) {
    return !result.context.plan.steps.empty() &&
           result.context.plan.steps.front().action.name == expected;
}
} // namespace

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_dlt_001.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    DevelopmentalWorldConfig world_config;
    world_config.task = "reach_destination";
    world_config.context = "navigation/route-selection";
    world_config.initial_state = {
        {"route_condition", std::string("clear")},
        {"bridge_status", std::string("open")},
        {"visibility", std::string("clear")},
    };
    world_config.initial_resources = 100.0;
    world_config.random_seed = 20261024;
    world_config.max_steps = 4;
    DevelopmentalWorld world(world_config);

    // The world defines action consequences; it does not tell the brain which
    // route is correct. The same action has different consequences when the
    // actual world condition changes.
    for (const auto& action_name : {std::string("bad-route"), std::string("good-route")}) {
        assert(world.add_action(DevelopmentalWorldAction{
            action_name, 1.0, {},
            [action_name](const Attributes& state, std::mt19937_64&)
                -> std::optional<DevelopmentalWorldTransition> {
                const auto condition = std::get<std::string>(state.at("route_condition"));
                const bool original_route_works = action_name == "good-route";
                const bool route_works = condition == "flooded"
                    ? !original_route_works : original_route_works;
                return DevelopmentalWorldTransition{
                    route_works ? 1.0 : -1.0,
                    {{"last_route", action_name}},
                    {route_works ? "destination_progress" : "route_setback"},
                    false};
            }}));
    }

    std::int64_t current_episode = -1;
    std::vector<std::string> initial_context_actions;
    std::vector<std::string> variant_actions;
    std::uint64_t observed_consequences = 0;
    std::uint64_t positive_consequences = 0;
    std::uint64_t negative_consequences = 0;
    std::optional<DevelopmentalWorldStep> last_world_step;

    CognitiveRuntimeConfig runtime_config;
    runtime_config.input_capacity = 8;
    runtime_config.result_capacity = 8;
    runtime_config.feedback_capacity = 16;
    runtime_config.drain_on_stop = true;
    runtime_config.action_adapter.authorization.maximum_risk = 1.0;
    runtime_config.action_adapter.execute = [&](const CandidateAction& action) {
        const auto available = world.available_actions();
        const bool offered = std::find(available.begin(), available.end(), action.name) != available.end();
        if (!offered) return false;

        // Episode zero is a deliberate executor outage control. It must not
        // be mistaken for a route consequence or teach a route preference.
        if (current_episode == 0) {
            last_world_step = world.step(action.name, false);
            return false;
        }
        return true;
    };
    runtime_config.action_adapter.verify = [](const CandidateAction&) { return true; };
    runtime_config.action_adapter.observe_consequence = [&](const CandidateAction& action) {
        last_world_step = world.step(action.name);
        if (last_world_step->consequence) {
            ++observed_consequences;
            if (*last_world_step->consequence > 0.0) ++positive_consequences;
            if (*last_world_step->consequence < 0.0) ++negative_consequences;
        }
        return last_world_step->consequence;
    };

    {
        Brain brain(journal);
        Goal goal;
        goal.id = "dlt-001-navigation-goal";
        goal.description = "Reach the destination using experience about route consequences";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        CognitiveRuntime runtime(brain, runtime_config);
        assert(runtime.start());

        constexpr std::int64_t initial_episode_count = 8;
        constexpr std::int64_t reversal_episode_count = 24;

        // Phase A: repeated experience in the original environment. The first
        // episode tests execution failure; subsequent episodes provide genuine
        // observed action consequences that can update the brain's strategy.
        for (std::int64_t episode = 0; episode < initial_episode_count; ++episode) {
            current_episode = episode;
            world.set_context(episode == 0 ? "infrastructure/executor-outage"
                                           : "navigation/route-selection");
            world.reset_episode(Attributes{
                {"route_condition", std::string("clear")},
                {"bridge_status", std::string("open")},
                {"visibility", std::string("clear")},
            }, 100.0);
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
            assert(std::get<std::string>(result.context.observation.event.data.at("route_condition")) == "clear");
            initial_context_actions.push_back(selected);

            if (episode == 0) {
                assert(execution.status == ActionExecutionStatus::failed);
                assert(!execution.outcome.observed);
                assert(last_world_step.has_value());
                assert(!last_world_step->executed && !last_world_step->consequence);
                const auto* outage = brain.developmental_best_strategy("infrastructure/executor-outage");
                assert(outage != nullptr && outage->value < 0.0);
                for (const auto& strategy : brain.developmental_strategies())
                    assert(strategy.context != "navigation/route-selection");
            } else {
                assert(execution.outcome.observed);
                assert(last_world_step && last_world_step->executed && last_world_step->observed);
                assert(last_world_step->consequence.has_value());
            }
        }

        // Phase B: the world changes the relationship between action and
        // outcome. The previously useful route is now harmful. The brain gets
        // observations and real consequences, not a prescribed action label.
        for (std::int64_t offset = 0; offset < reversal_episode_count; ++offset) {
            current_episode = initial_episode_count + offset;
            world.set_context("navigation/route-variant");
            world.reset_episode(Attributes{
                {"route_condition", std::string("flooded")},
                {"bridge_status", std::string("closed")},
                {"visibility", std::string("poor")},
            }, 100.0);
            last_world_step.reset();

            const auto input = make_input(goal, world);
            assert(input.candidate_actions.size() == 2);
            assert(runtime.submit(input, 1.0));
            const auto result = await_result(runtime);
            assert(result.status == CognitiveCycleStatus::completed);
            assert(!result.context.plan.steps.empty());
            assert(result.context.action_execution_results.size() == 1);
            const auto& execution = result.context.action_execution_results.front();
            assert(execution.action.name == result.context.plan.steps.front().action.name);
            assert(execution.outcome.observed);
            assert(last_world_step && last_world_step->executed && last_world_step->observed);
            assert(last_world_step->consequence.has_value());
            assert(std::get<std::string>(result.context.observation.event.data.at("route_condition")) == "flooded");
            variant_actions.push_back(execution.action.name);
        }

        runtime.stop();
        assert(runtime.metrics().processed ==
               static_cast<std::uint64_t>(initial_episode_count + reversal_episode_count));
        assert(runtime.metrics().action_failed >= 1);
        assert(observed_consequences == static_cast<std::uint64_t>(
                   (initial_episode_count - 1) + reversal_episode_count));
        assert(positive_consequences > 0 && negative_consequences > 0);

        // These criteria require actual choice changes, not merely memory growth.
        assert(initial_context_actions.front() == "bad-route");
        assert(initial_context_actions.back() == "good-route");
        assert(variant_actions.front() == "good-route");
        assert(variant_actions.back() == "bad-route");

        bool original_good_route_positive = false;
        bool variant_good_route_negative = false;
        bool variant_bad_route_positive = false;
        for (const auto& strategy : brain.developmental_strategies()) {
            if (strategy.context == "navigation/route-selection" &&
                strategy.action == "good-route" && strategy.value > 0.0 && strategy.uses > 0)
                original_good_route_positive = true;
            if (strategy.context == "navigation/route-variant" &&
                strategy.action == "good-route" && strategy.value < 0.0 && strategy.uses > 0)
                variant_good_route_negative = true;
            if (strategy.context == "navigation/route-variant" &&
                strategy.action == "bad-route" && strategy.value > 0.0 && strategy.uses > 0)
                variant_bad_route_positive = true;
        }
        assert(original_good_route_positive);
        assert(variant_good_route_negative);
        assert(variant_bad_route_positive);
        assert(!brain.memory().by_kind("observation").empty());
        assert(!brain.memory().by_kind("action_outcome").empty());

        std::cout << "[DLT-001] phase=experience episodes=" << runtime.metrics().processed
                  << " observed_consequences=" << observed_consequences
                  << " positive=" << positive_consequences
                  << " negative=" << negative_consequences << '\n';
        std::cout << "[DLT-001] phase=behavioral_change initial_first="
                  << initial_context_actions.front()
                  << " initial_last=" << initial_context_actions.back()
                  << " variant_first=" << variant_actions.front()
                  << " variant_last=" << variant_actions.back() << '\n';
    }

    // Restart test: world state resets independently, while the brain's
    // persistent journal retains the original strategy and the learned
    // context-specific exception. Probe without executing an action, so the
    // test itself does not add a fresh training consequence.
    {
        Brain restored(journal);
        Goal goal;
        goal.id = "dlt-001-navigation-goal";
        goal.description = "Reach the destination using experience about route consequences";
        goal.priority = 1.0;
        assert(restored.goal(goal.id) != nullptr);

        world.set_context("navigation/route-selection");
        world.reset_episode(Attributes{
            {"route_condition", std::string("clear")},
            {"bridge_status", std::string("open")},
            {"visibility", std::string("clear")},
        }, 100.0);
        const auto original_probe = CognitiveCycle(restored).run(make_input(goal, world));
        assert(original_probe.status == CognitiveCycleStatus::completed);
        assert(selected_action_is(original_probe, "good-route"));

        world.set_context("navigation/route-variant");
        world.reset_episode(Attributes{
            {"route_condition", std::string("flooded")},
            {"bridge_status", std::string("closed")},
            {"visibility", std::string("poor")},
        }, 100.0);
        const auto variant_probe = CognitiveCycle(restored).run(make_input(goal, world));
        assert(variant_probe.status == CognitiveCycleStatus::completed);
        assert(selected_action_is(variant_probe, "bad-route"));

        world.set_context("navigation/route-selection alternate");
        world.reset_episode(Attributes{
            {"route_condition", std::string("clear")},
            {"bridge_status", std::string("open")},
            {"visibility", std::string("clear")},
        }, 100.0);
        auto related_input = make_input(goal, world);
        related_input.developmental_context = "navigation/route-selection alternate";
        const auto generalized_probe = CognitiveCycle(restored).run(related_input);
        assert(generalized_probe.status == CognitiveCycleStatus::completed);
        assert(selected_action_is(generalized_probe, "good-route"));

        auto unrelated_input = make_input(goal, world);
        unrelated_input.developmental_context = "orbital/cooking";
        unrelated_input.candidate_actions = {
            CandidateAction{"unrelated-first", 0.5, 0.5, 0.9, 0.1},
            CandidateAction{"unrelated-second", 0.5, 0.5, 0.9, 0.1},
        };
        const auto unrelated_probe = CognitiveCycle(restored).run(unrelated_input);
        assert(unrelated_probe.status == CognitiveCycleStatus::completed);
        assert(selected_action_is(unrelated_probe, "unrelated-first"));

        assert(!restored.memory().by_kind("action_outcome").empty());
        assert(!restored.developmental_strategies().empty());
        std::cout << "[DLT-001] phase=persistence original=good-route variant=bad-route"
                     " related=good-route unrelated=unrelated-first"
                  << " restored_memories=" << restored.memory().all().size() << '\n';
    }

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    std::cout << "[DLT-001] status=PASS\n";
    return 0;
}
