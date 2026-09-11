#include "jarvis/core/self_model.hpp"

#include <cassert>
#include <cmath>

using namespace jarvis::core;

int main() {
    SelfModel model;
    assert(model.health().overall == 1.0);

    model.observe_capability("reasoning", 0.8, 0.5);
    model.observe_capability("memory", 1.0, 0.9);

    const auto health = model.health();
    assert(std::abs(health.availability - 0.9) < 1e-12);
    assert(std::abs(health.performance - 0.7) < 1e-12);
    assert(std::abs(health.overall - 0.63) < 1e-12);

    assert(model.isolate("reasoning"));
    const auto degraded = model.health();
    assert(degraded.overall < health.overall);

    assert(model.restore("reasoning", 1.0, 1.0));
    const auto restored = model.health();
    assert(restored.overall > degraded.overall);
    return 0;
}
