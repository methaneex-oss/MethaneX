#include "jarvis/core/developmental_world.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

using namespace jarvis::core;

int main() {
    DevelopmentalWorldConfig config;
    config.task = "learn_resourceful_navigation";
    config.context = "forest/day";
    config.initial_state = {
        {"location", std::string("camp")},
        {"bridge", std::string("closed")},
        {"weather", std::string("clear")},
        {"hidden_route_quality", std::string("safe")},
    };
    config.initial_resources = 5.0;
    config.random_seed = 41;
    config.max_steps = 12;
    config.observation_filter = [](const Attributes& state) {
        Attributes visible = state;
        visible.erase("hidden_route_quality");
        return visible;
    };

    DevelopmentalWorld world(config);
    assert(world.add_action(DevelopmentalWorldAction{
        "inspect-bridge", 0.5,
        [](const Attributes& state) {
            return std::get<std::string>(state.at("location")) == "camp";
        },
        [](const Attributes& state, std::mt19937_64&) -> std::optional<DevelopmentalWorldTransition> {
            const auto bridge = std::get<std::string>(state.at("bridge"));
            return DevelopmentalWorldTransition{
                0.0, {{"bridge_inspected", true}},
                {"inspection_complete", bridge}, false};
        }}));

    assert(world.add_action(DevelopmentalWorldAction{
        "cross-bridge", 1.0,
        [](const Attributes& state) {
            return std::get<std::string>(state.at("bridge")) == "open";
        },
        [](const Attributes& state, std::mt19937_64&) -> std::optional<DevelopmentalWorldTransition> {
            const bool safe = std::get<std::string>(state.at("hidden_route_quality")) == "safe";
            return DevelopmentalWorldTransition{
                safe ? 1.0 : -1.0,
                {{"location", std::string("other-bank")}},
                {safe ? "crossing_safe" : "crossing_dangerous"}, true};
        }}));

    assert(world.add_action(DevelopmentalWorldAction{
        "open-bridge", 1.0, {},
        [](const Attributes&, std::mt19937_64&) -> std::optional<DevelopmentalWorldTransition> {
            return DevelopmentalWorldTransition{
                0.0, {{"bridge", std::string("open")}}, {"bridge_opened"}, false};
        }}));

    // Observation includes the public world state but does not leak hidden facts.
    auto observation = world.observe();
    assert(observation.event.source == "developmental_world");
    assert(observation.event.data.contains("location"));
    assert(!observation.event.data.contains("hidden_route_quality"));
    assert(std::get<std::string>(observation.event.data.at("context")) == "forest/day");
    assert(std::get<double>(observation.event.data.at("resources_remaining")) == 5.0);

    const auto initial_actions = world.available_actions();
    assert(initial_actions.size() == 2);
    assert(initial_actions[0] == "inspect-bridge");
    assert(initial_actions[1] == "open-bridge");

    // A failed external executor must not mutate the world or fabricate reward.
    const auto outage = world.step("open-bridge", false);
    assert(!outage.executed && !outage.observed && !outage.consequence);
    assert(outage.reason == "execution_failed");
    assert(std::get<std::string>(world.true_state().at("bridge")) == "closed");

    // Unknown actions are not silently rewarded or punished.
    const auto unknown = world.step("invented-action");
    assert(!unknown.executed && !unknown.observed && !unknown.consequence);
    assert(unknown.reason == "unknown_action");

    const auto inspection = world.step("inspect-bridge");
    assert(inspection.executed && inspection.observed);
    assert(inspection.consequence && *inspection.consequence == 0.0);
    assert(inspection.resources_after == 4.5);
    assert(std::get<bool>(world.true_state().at("bridge_inspected")));
    assert(inspection.events.size() == 2);

    // State changes alter which actions are available and what follows.
    const auto opened = world.step("open-bridge");
    assert(opened.observed && opened.consequence && *opened.consequence == 0.0);
    assert(std::get<std::string>(opened.state_before.at("bridge")) == "closed");
    assert(std::get<std::string>(opened.state_after.at("bridge")) == "open");
    assert(world.available_actions().size() == 2);

    const auto crossed = world.step("cross-bridge");
    assert(crossed.executed && crossed.observed);
    assert(crossed.consequence && *crossed.consequence == 1.0);
    assert(crossed.terminal);
    assert(world.terminal());
    assert(world.available_actions().empty());

    const auto after_terminal = world.step("inspect-bridge");
    assert(!after_terminal.executed && !after_terminal.observed);
    assert(after_terminal.reason == "world_terminal");

    // New episodes reset world state and resources while preserving the world
    // definition and the seeded random stream for reproducible experiments.
    world.reset_episode();
    assert(world.episode() == 1);
    assert(world.step_count() == 0);
    assert(!world.terminal());
    assert(world.resources_remaining() == 5.0);
    assert(std::get<std::string>(world.true_state().at("location")) == "camp");
    assert(std::get<std::string>(world.true_state().at("bridge")) == "closed");

    // Insufficient resources and unavailable actions produce no fabricated
    // outcome. The agent must distinguish "could not execute" from failure.
    DevelopmentalWorldConfig low_resource_config = config;
    low_resource_config.initial_resources = 0.25;
    DevelopmentalWorld low_resource_world(low_resource_config);
    assert(low_resource_world.add_action(DevelopmentalWorldAction{
        "expensive-action", 1.0, {},
        [](const Attributes&, std::mt19937_64&) -> std::optional<DevelopmentalWorldTransition> {
            return DevelopmentalWorldTransition{1.0, {}, {}, false};
        }}));
    assert(low_resource_world.available_actions().empty());
    const auto insufficient = low_resource_world.step("expensive-action");
    assert(!insufficient.executed && !insufficient.observed && !insufficient.consequence);
    assert(insufficient.reason == "insufficient_resources");
    assert(low_resource_world.resources_remaining() == 0.25);

    std::cout << "[developmental-world] observations=verified state_transitions=verified "
                 "partial_observation=verified resources=verified reset=verified\n";
    return 0;
}
