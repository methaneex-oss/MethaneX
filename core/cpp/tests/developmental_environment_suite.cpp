#include "jarvis/core/developmental_environment.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

using namespace jarvis::core;

int main() {
    DevelopmentalEnvironment world(
        "reach_destination", "navigation/route-selection",
        {{"route_condition", std::string("clear")}},
        [](const std::string& action, const Attributes& state)
            -> std::optional<DevelopmentalTransition> {
            const auto condition = std::get<std::string>(state.at("route_condition"));
            const bool good_route = action == "good-route";
            const bool works = condition == "flooded" ? !good_route : good_route;
            if (action != "good-route" && action != "bad-route") return std::nullopt;
            return DevelopmentalTransition{works ? 1.0 : -1.0, std::nullopt};
        });

    const Event first_observation = world.observe();
    assert(first_observation.kind == "observation");
    assert(first_observation.source == "developmental_environment");
    assert(std::get<std::string>(first_observation.data.at("task")) == "reach_destination");
    assert(std::get<std::string>(first_observation.data.at("route_condition")) == "clear");

    const auto outage = world.step("good-route", false);
    assert(!outage.executed);
    assert(!outage.observed);
    assert(!outage.consequence);

    const auto success = world.step("good-route");
    assert(success.executed && success.observed);
    assert(success.consequence && *success.consequence == 1.0);

    const auto failure = world.step("bad-route");
    assert(failure.observed && failure.consequence && *failure.consequence == -1.0);

    // Change the world's rules, not the brain's answer: the same action now
    // produces a different consequence and the observation exposes the change.
    world.set_context("navigation/route-variant");
    world.set_state({{"route_condition", std::string("flooded")}});
    const Event changed_observation = world.observe();
    assert(std::get<std::string>(changed_observation.data.at("context")) ==
           "navigation/route-variant");
    assert(std::get<std::string>(changed_observation.data.at("route_condition")) == "flooded");

    const auto contradiction = world.step("good-route");
    assert(contradiction.observed && contradiction.consequence);
    assert(*contradiction.consequence == -1.0);
    const auto revised = world.step("bad-route");
    assert(revised.observed && revised.consequence && *revised.consequence == 1.0);

    // An action unknown to this world's transition model gives no fabricated
    // reward or punishment: the brain must represent the outcome as unknown.
    const auto unknown = world.step("unmodeled-action");
    assert(unknown.executed);
    assert(!unknown.observed);
    assert(!unknown.consequence);
    assert(world.step_count() == 6);

    std::cout << "[world] observations=2 steps=" << world.step_count()
              << " outage=unobserved contradiction=observed\n";
    return 0;
}
