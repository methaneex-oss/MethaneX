#include "jarvis/core/world_state.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    WorldState world;

    Event first{1, 100, "sensor", "observation", {{"temperature", 25.0}}};
    world.apply(first);
    auto current = world.snapshot();
    assert(current.sequence == 1);
    assert(current.timestamp_ns == 100);
    assert(!current.facts.empty());

    world.observe(Fact{"room", "temperature", 25.0, 0.9, 1});
    world.relate(Relation{"room", "contains", "sensor", 0.8});
    current = world.snapshot();
    assert(current.facts.size() >= 2);

    const auto history = world.history();
    assert(history.size() == 1);
    assert(history.front().source == "sensor");

    const auto historical = world.at(1);
    assert(historical.has_value());
    assert(historical->sequence == 1);

    assert(!world.at(0).has_value());
    world.clear();
    assert(world.history().empty());
    assert(world.snapshot().facts.empty());
    return 0;
}
