#include "jarvis/core/association_model.hpp"
#include "jarvis/core/brain.hpp"
#include "jarvis/core/causal_model.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>

using namespace jarvis::core;

int main() {
    AssociationModel associations;
    const std::vector<Belief> before{
        {"temperature", 20.0, 0.9, 1, 1},
        {"fan", false, 0.9, 1, 1},
    };
    const std::vector<Belief> after{
        {"temperature", 30.0, 0.95, 2, 2},
        {"fan", true, 0.9, 2, 2},
    };
    associations.observe(before, after, 2);
    const auto related = associations.related("temperature", 0.5);
    assert(!related.empty());
    assert(related.front().observations == 1);
    assert(related.front().strength >= 0.5);

    // Generalization is structural, not hard-coded: temperature -> fan and
    // fan -> power imply a weak contextual path temperature -> power, but do
    // not manufacture a direct temperature/power association.
    const std::vector<Belief> before_power{
        {"fan", false, 0.9, 2, 2},
        {"power", 100.0, 0.9, 2, 2},
    };
    const std::vector<Belief> after_power{
        {"fan", true, 0.9, 3, 3},
        {"power", 120.0, 0.9, 3, 3},
    };
    associations.observe(before_power, after_power, 3);
    const auto contextual = associations.contextual("temperature", 2, 0.20);
    assert(!contextual.empty());
    bool found_power = false;
    for (const auto& inference : contextual) {
        if (inference.key == "power") {
            found_power = true;
            assert(inference.hops == 2);
            assert(inference.strength < related.front().strength);
        }
    }
    assert(found_power);

    CausalModel causal;
    causal.observe_transition(before, after);
    // One experience creates a hypothesis but does not authorize prediction.
    const auto first = causal.simulate({Belief{"temperature", 30.0, 0.95, 2, 2}}, 1);
    assert(first.depth == 1);
    assert(first.predictions.empty());

    // Repeated experience strengthens the same hypothesis enough to predict.
    causal.observe_transition(before, after);
    const auto one_step = causal.simulate({Belief{"temperature", 30.0, 0.95, 2, 2}}, 1);
    assert(!one_step.predictions.empty());
    assert(one_step.confidence >= 0.5);

    const auto bounded = causal.simulate({Belief{"temperature", 30.0, 0.95, 2, 2}}, 100);
    assert(bounded.depth == 8);

    const auto path = std::filesystem::temp_directory_path() / "jarvis_phase5_association.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(std::filesystem::path(path.string() + ".meta"), ec);

    Brain brain(path);
    brain.observe(Event{0, 1, "sensor", "observation", {{"temperature", 20.0}, {"fan", false}}});
    brain.observe(Event{0, 2, "sensor", "observation", {{"temperature", 30.0}, {"fan", true}}});
    brain.observe(Event{0, 3, "sensor", "observation", {{"temperature", 30.0}, {"fan", false}, {"power", 120.0}}});
    assert(!brain.associations().empty());
    assert(!brain.associated_with("temperature").empty());
    assert(!brain.causal_links().empty());

    const auto brain_contextual = brain.contextual_associations("temperature", 2, 0.20);
    bool brain_found_power = false;
    for (const auto& inference : brain_contextual) {
        if (inference.key == "power") {
            brain_found_power = true;
            assert(inference.hops == 2);
        }
    }
    assert(brain_found_power);

    const auto simulated = brain.simulate({Belief{"temperature", 30.0, 0.95, 2, 2}}, 2);
    assert(simulated.depth == 2);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(std::filesystem::path(path.string() + ".meta"), ec);
    return 0;
}
