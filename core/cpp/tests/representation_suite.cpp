#include "jarvis/core/representation.hpp"

#include <algorithm>

#include <cassert>
#include <cmath>
#include <limits>

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
    const auto repeated = engine.normalize(event);
    assert(repeated.nodes.size() == representation.nodes.size());
    for (const auto& node : representation.nodes) {
        const auto match = std::find_if(repeated.nodes.begin(), repeated.nodes.end(),
            [&](const SemanticNode& candidate) { return candidate.label == node.label; });
        assert(match != repeated.nodes.end());
        assert(match->id == node.id);
    }

    Event explicit_confidence{44, 125, "sensor", "observation",
                              {{"temperature", 18.0}, {"confidence", 0.2},
                               {"novelty", 0.8}, {"salience", 0.6},
                               {"world_step", std::int64_t{12}}}};
    const auto grounded = engine.normalize(explicit_confidence);
    assert(std::abs(grounded.confidence - 0.2) < 1e-12);
    assert(grounded.nodes.size() == 1);
    assert(grounded.nodes.front().label == "temperature");
    assert(std::abs(grounded.nodes.front().confidence - 0.2) < 1e-12);
    assert(std::get<double>(grounded.metadata.at("novelty")) == 0.8);
    assert(std::get<double>(grounded.metadata.at("salience")) == 0.6);
    assert(std::get<std::int64_t>(grounded.metadata.at("world_step")) == 12);

    Event empty{43, 124, "unknown", "", {}};
    const auto unknown = engine.normalize(empty);
    assert(unknown.modality == Modality::unknown);
    assert(unknown.nodes.empty());
    assert(unknown.confidence == 0.0);
    assert(engine.validate(unknown));

    auto invalid = representation;
    invalid.confidence = 2.0;
    assert(!engine.validate(invalid));

    invalid = representation;
    invalid.confidence = std::numeric_limits<double>::quiet_NaN();
    assert(!engine.validate(invalid));

    if (!representation.nodes.empty()) {
        invalid = representation;
        invalid.nodes.front().confidence = std::numeric_limits<double>::infinity();
        assert(!engine.validate(invalid));
    }

    return 0;
}
