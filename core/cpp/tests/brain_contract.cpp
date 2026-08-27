#include "jarvis/core/brain.hpp"

#include <cassert>
#include <string>

using namespace jarvis::core;

int main() {
    Brain brain;

    Event event{0, 0, "test", "observation", {{"health", Scalar{0.9}}, {"mode", Scalar{std::string("nominal")}}}};
    const auto observation = brain.observe(event);
    assert(observation.novelty >= 0.0 && observation.novelty <= 1.0);

    const auto beliefs = brain.beliefs();
    assert(!beliefs.empty());

    const auto prediction = brain.predict("test.value", Scalar{0.9}, 0.8);
    assert(prediction.key == "test.value");
    assert(brain.resolve_prediction("test.value", Scalar{0.9}));

    const auto reflection = brain.reflect();
    assert(reflection.prediction_accuracy >= 0.0 && reflection.prediction_accuracy <= 1.0);
    assert(reflection.coherence >= 0.0 && reflection.coherence <= 1.0);

    const auto state = brain.state();
    assert(state.events_seen >= 1);
    assert(state.cycle >= 1);
    return 0;
}
