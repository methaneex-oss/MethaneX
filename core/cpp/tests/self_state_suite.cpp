#include "jarvis/core/self_state.hpp"

#include <cassert>
#include <cmath>
#include <string>
#include <vector>

using namespace jarvis::core;

int main() {
    SelfStateModel model;
    const auto initial = model.snapshot();
    assert(initial.revision == 0);
    assert(initial.cycle == 0);
    assert(initial.events_seen == 0);
    assert(initial.workload == 0.0);
    assert(initial.uncertainty == 0.0);

    model.set_activity("observing");
    model.set_workload(2.0);
    model.set_uncertainty(-1.0);
    model.set_health(CognitiveHealth{-1.0, 2.0, 0.4, 3.0});
    model.set_goals({GoalState{"g1", 0.8, true}});
    model.set_resource_pressure("cpu", 2.0);
    model.synchronize_cycle(7, 11);

    const auto state = model.snapshot();
    assert(state.revision > initial.revision);
    assert(state.cycle == 7);
    assert(state.events_seen == 11);
    assert(state.activity == "observing");
    assert(state.workload == 1.0);
    assert(state.uncertainty == 0.0);
    assert(state.health.overall == 0.0);
    assert(state.health.memory == 1.0);
    assert(state.health.reasoning == 0.4);
    assert(state.health.execution == 1.0);
    assert(state.active_goals.size() == 1);
    assert(state.active_goals.front().id == "g1");
    assert(state.resource_pressure.at("cpu") == 1.0);

    const auto stable_revision = state.revision;
    model.set_activity("observing");
    model.set_workload(1.0);
    model.set_uncertainty(0.0);
    model.set_health(state.health);
    model.set_goals(state.active_goals);
    model.set_resource_pressure("cpu", 1.0);
    model.synchronize_cycle(7, 11);
    assert(model.snapshot().revision == stable_revision);

    model.set_resource_pressure("", 0.5);
    assert(model.snapshot().resource_pressure.find("") == model.snapshot().resource_pressure.end());

    return 0;
}
