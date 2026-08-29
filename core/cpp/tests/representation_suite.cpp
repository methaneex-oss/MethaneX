#include "jarvis/core/representation.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    RepresentationEngine engine;
    Event event{42, 123, "voice", "command", {{"intent", std::string{"weather"}}, {"urgent", true}}};
    const auto representation = engine.normalize(event);

    assert(representation.sequence == 42);
    assert(representation.modality == Modality::speech);
    assert(representation.nodes.size() == 2);
    assert(representation.confidence > 0.0 && representation.confidence <= 1.0);
    assert(engine.validate(representation));

    Event empty{43, 124, "unknown", "", {}};
    const auto unknown = engine.normalize(empty);
    assert(unknown.modality == Modality::unknown);
    assert(unknown.nodes.empty());
    assert(unknown.confidence == 0.0);
    assert(engine.validate(unknown));

    auto invalid = representation;
    invalid.confidence = 2.0;
    assert(!engine.validate(invalid));

    return 0;
}
