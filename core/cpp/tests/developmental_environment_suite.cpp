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
    assert(std::get<std::string>(outage.state_before.at("route_condition")) == "clear");
    assert(std::get<std::string>(outage.state_after.at("route_condition")) == "clear");

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

    // Exercise a state-changing action, not only externally injected changes.
    // A measured neutral consequence (0.0) is still observed evidence; an
    // unsupported action remains unknown and must not be conflated with neutral.
    DevelopmentalEnvironment stateful_world(
        "operate_gate", "facility/access",
        {{"gate_status", std::string("closed")}},
        [](const std::string& action, const Attributes& state)
            -> std::optional<DevelopmentalTransition> {
            if (action == "open-gate") {
                return DevelopmentalTransition{
                    0.0, Attributes{{"gate_status", std::string("open")}}};
            }
            if (action == "cross-gate") {
                const bool open = std::get<std::string>(state.at("gate_status")) == "open";
                return DevelopmentalTransition{open ? 1.0 : -1.0, std::nullopt};
            }
            return std::nullopt;
        });

    const auto neutral_but_observed = stateful_world.step("open-gate");
    assert(neutral_but_observed.executed);
    assert(neutral_but_observed.observed);
    assert(neutral_but_observed.consequence && *neutral_but_observed.consequence == 0.0);
    assert(std::get<std::string>(neutral_but_observed.state_before.at("gate_status")) == "closed");
    assert(std::get<std::string>(neutral_but_observed.state_after.at("gate_status")) == "open");
    assert(std::get<std::string>(stateful_world.observe().data.at("gate_status")) == "open");

    const auto state_dependent_success = stateful_world.step("cross-gate");
    assert(state_dependent_success.observed && state_dependent_success.consequence);
    assert(*state_dependent_success.consequence == 1.0);
    const auto unknown_after_state_change = stateful_world.step("unknown-gate-action");
    assert(unknown_after_state_change.executed);
    assert(!unknown_after_state_change.observed);
    assert(!unknown_after_state_change.consequence);
    assert(std::get<std::string>(unknown_after_state_change.state_before.at("gate_status")) == "open");
    assert(std::get<std::string>(unknown_after_state_change.state_after.at("gate_status")) == "open");

    std::cout << "[world] observations=2 steps=" << world.step_count()
              << " outage=unobserved contradiction=observed\n";
    return 0;
}
