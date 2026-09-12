#include "jarvis/core/brain.hpp"
#include "jarvis/core/world_model.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>

using namespace jarvis::core;

int main() {
    {
        WorldModel world;
        world.observe(Fact{"room", "temperature", 20.0, 0.9, 1, 1, 1, false});
        world.observe(Fact{"room", "temperature", 25.0, 0.4, 1, 2, 2, false});

        const auto current = world.query("room", "temperature");
        assert(current.has_value());
        assert(std::get<double>(current->value) == 20.0);
        assert(current->disputed);
        assert(world.disputed_facts().size() == 2);

        world.relate(Relation{"room", "contains", "sensor-a", 0.9, 3, false});
        world.relate(Relation{"room", "contains", "sensor-b", 0.7, 4, false});
        assert(world.relations_from("room").size() == 2);
        assert(world.disputed_relations().size() == 2);

        world.clear();
        assert(world.facts().empty());
        assert(world.disputed_facts().empty());
        assert(world.disputed_relations().empty());
    }

    const auto path = std::filesystem::temp_directory_path() / "jarvis_phase4_self_state.bin";
    const auto metadata = std::filesystem::path(path.string() + ".meta");
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(metadata, ec);

    Brain brain(path);
    brain.observe(Event{0, 1, "sensor", "observation", {{"temperature", 20.0}}});
    assert(brain.world().query("sensor", "temperature").has_value());

    assert(brain.create_goal(Goal{"g1", "stabilize", 0.8, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
    assert(brain.activate_goal("g1"));
    brain.observe_capability("reasoning", 0.5, 0.8);

    const auto snapshot = brain.snapshot();
    assert(snapshot.self_state.active_goals.size() == 1);
    assert(snapshot.self_state.active_goals.front().id == "g1");
    assert(snapshot.self_state.resource_pressure.count("reasoning") == 1);
    assert(snapshot.self_state.resource_pressure.at("reasoning") > 0.0);
    assert(snapshot.self_state.health.reasoning < 1.0);
    assert(snapshot.self_state.health.execution < 1.0);
    assert(snapshot.self_state.workload > 0.0);

    const auto restored = Brain(path).snapshot();
    assert(restored.self_state.active_goals.size() == 1);
    assert(restored.self_state.active_goals.front().id == "g1");
    assert(restored.self_state.resource_pressure.count("reasoning") == 1);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(metadata, ec);
    return 0;
}
