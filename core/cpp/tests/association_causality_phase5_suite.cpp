#include "jarvis/core/association_model.hpp"
#include "jarvis/core/brain.hpp"
#include "jarvis/core/causal_model.hpp"

#include <algorithm>

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
    brain.observe(Event{0, 3, "sensor", "observation", {{"temperature", 30.0}, {"fan", false}, {"power", 140.0}}});
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

    // Concept formation is derived from repeated shared context. The test does
    // not name a semantic category; it only verifies that the graph discovers
    // two experiences with the same contextual structure.
    AssociationModel concept_model;
    const std::vector<Belief> concept_before{
        {"alpha", false, 0.9, 1, 10},
        {"beta", false, 0.9, 1, 10},
        {"context_one", false, 0.9, 1, 10},
        {"context_two", false, 0.9, 1, 10},
    };
    concept_model.observe(
        concept_before,
        {{"alpha", true, 0.9, 2, 11},
         {"beta", false, 0.9, 2, 11},
         {"context_one", true, 0.9, 2, 11},
         {"context_two", true, 0.9, 2, 11}},
        11);
    concept_model.observe(
        {{"alpha", true, 0.9, 2, 11},
         {"beta", false, 0.9, 2, 11},
         {"context_one", true, 0.9, 2, 11},
         {"context_two", true, 0.9, 2, 11}},
        {{"alpha", true, 0.9, 3, 12},
         {"beta", true, 0.9, 3, 12},
         {"context_one", false, 0.9, 3, 12},
         {"context_two", false, 0.9, 3, 12}},
        12);
    // A later experience is deliberately an exception: alpha and beta remain
    // stable while their learned contexts change. The first exception weakens
    // coherence without erasing the hypothesis immediately.
    concept_model.observe(
        {{"alpha", true, 0.9, 3, 12},
         {"beta", true, 0.9, 3, 12},
         {"context_one", false, 0.9, 3, 12},
         {"context_two", false, 0.9, 3, 12}},
        {{"alpha", true, 0.9, 4, 13},
         {"beta", true, 0.9, 4, 13},
         {"context_one", true, 0.9, 4, 13},
         {"context_two", true, 0.9, 4, 13}},
        13);

    const auto weakened_concepts = concept_model.concept_candidates(0.5, 2);
    double weakened_coherence = 0.0;
    for (const auto& concept : weakened_concepts) {
        const auto has_alpha = std::find(concept.members.begin(), concept.members.end(), "alpha") != concept.members.end();
        const auto has_beta = std::find(concept.members.begin(), concept.members.end(), "beta") != concept.members.end();
        if (has_alpha && has_beta) weakened_coherence = concept.coherence;
    }
    assert(weakened_coherence > 0.0);
    assert(weakened_coherence < 1.0);

    // Repeated counter-evidence eventually removes the hypothesis from the
    // trusted-strength view rather than forcing the old abstraction to survive.
    for (std::uint64_t sequence = 14; sequence <= 20; ++sequence) {
        concept_model.observe(
            {{"alpha", true, 0.9, sequence - 1, sequence - 1},
             {"beta", true, 0.9, sequence - 1, sequence - 1},
             {"context_one", false, 0.9, sequence - 1, sequence - 1},
             {"context_two", false, 0.9, sequence - 1, sequence - 1}},
            {{"alpha", true, 0.9, sequence, sequence},
             {"beta", true, 0.9, sequence, sequence},
             {"context_one", true, 0.9, sequence, sequence},
             {"context_two", true, 0.9, sequence, sequence}},
            sequence);
    }
    const auto revised_concepts = concept_model.concept_candidates(0.5, 2);
    for (const auto& concept : revised_concepts) {
        const auto has_alpha = std::find(concept.members.begin(), concept.members.end(), "alpha") != concept.members.end();
        const auto has_beta = std::find(concept.members.begin(), concept.members.end(), "beta") != concept.members.end();
        assert(!(has_alpha && has_beta));
    }

    const auto simulated = brain.simulate({Belief{"temperature", 30.0, 0.95, 2, 2}}, 2);
    assert(simulated.depth == 2);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(std::filesystem::path(path.string() + ".meta"), ec);
    return 0;
}
