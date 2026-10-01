#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_affective_evidence.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    brain.observe(Event{0, 0, "sensor", "arbitrary_experience", {
        {"novelty", 0.8}, {"salience", 0.9}, {"uncertainty", 0.2},
        {"confidence", 0.8}, {"outcome", 0.9}, {"utility", 0.9}}});
    brain.observe(Event{0, 0, "sensor", "another_experience", {
        {"novelty", 0.7}, {"salience", 0.8}, {"uncertainty", 0.9},
        {"confidence", 0.2}, {"outcome", -0.9}, {"utility", -0.9}}});

    const auto affect = brain.affective_state();
    const auto appraisal = brain.affective_appraisal();
    assert(affect.updates >= 2);
    assert(affect.valence < 0.5);
    assert(appraisal.outcome_weight >= 0.0 && appraisal.outcome_weight <= 2.0);

    const auto actions = std::vector<CandidateAction>{{"observe", 0.5}, {"act", 0.6}};
    const auto decisions = brain.choose_with_affect(actions);
    assert(decisions.size() == actions.size());

    Brain restored(path);
    const auto restored_affect = restored.affective_state();
    assert(restored_affect.updates == affect.updates);
    assert(std::abs(restored_affect.valence - affect.valence) < 1e-9);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "affective_evidence_suite: PASS\n";
    return 0;
}
