#include "jarvis/core/experience_memory.hpp"

#include <cassert>
#include <cstdint>
#include <string>

using namespace jarvis::core;

int main() {
    ExperienceMemory memory;

    Prediction first{"temperature", Scalar{30.0}, 0.7, 101, false, 0.0};
    Prediction second{"temperature", Scalar{32.0}, 0.8, 108, false, 0.0};

    assert(memory.record_prediction(first));
    assert(memory.record_prediction(second));
    assert(memory.size() == 2);

    const auto experiences = memory.for_key("temperature");
    assert(experiences.size() == 2);
    assert(experiences[0]->sequence == 101);
    assert(experiences[1]->sequence == 108);

    // Resolving one experience must not mutate or erase the other.
    assert(memory.resolve(101, Scalar{31.0}, 1.0));
    assert(memory.get(101)->resolved);
    assert(!memory.get(108)->resolved);
    assert(memory.latest_unresolved("temperature")->sequence == 108);

    // A second semantic experience can be resolved independently.
    assert(memory.resolve(108, Scalar{33.0}, 1.0));
    assert(memory.latest_unresolved("temperature") == nullptr);

    return 0;
}
