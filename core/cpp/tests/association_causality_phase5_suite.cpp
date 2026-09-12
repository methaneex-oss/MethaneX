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

    CausalModel causal;
    causal.observe_transition(before, after);
    const auto one_step = causal.simulate({Belief{"temperature", 30.0, 0.95, 2, 2}}, 1);
    assert(one_step.depth == 1);
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
    assert(!brain.associations().empty());
    assert(!brain.associated_with("temperature").empty());
    assert(!brain.causal_links().empty());

    const auto simulated = brain.simulate({Belief{"temperature", 30.0, 0.95, 2, 2}}, 2);
    assert(simulated.depth == 2);
    assert(!simulated.predictions.empty());

    std::filesystem::remove(path, ec);
    std::filesystem::remove(std::filesystem::path(path.string() + ".meta"), ec);
    return 0;
}
