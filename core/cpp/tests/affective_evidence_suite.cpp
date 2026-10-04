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
    brain.observe(Event{0, 0, "sensor", "prediction_outcome", {
        {"key", std::string("temperature")}, {"error", 0.1}, {"novelty", 0.8},
        {"salience", 0.9}, {"confidence", 0.8}, {"utility", 0.9}}});
    brain.observe(Event{0, 0, "sensor", "action_outcome", {
        {"action", std::string("probe")}, {"context", std::string("temperature")},
        {"reliability", 0.2}, {"novelty", 0.7}, {"salience", 0.8}, {"utility", -0.9}}});

    // A low-explicit-salience experience with strong internal activation must
    // still acquire consolidation evidence through generic affective signals.
    const auto activated = brain.observe(Event{0, 0, "sensor", "observation", {
        {"outcome", Scalar{-1.0}}, {"prediction_error", Scalar{1.0}},
        {"novelty", Scalar{1.0}}, {"salience", Scalar{0.0}}, {"confidence", Scalar{0.0}}}});
    const auto ranked = brain.memory().salient(16);
    bool found_activated = false;
    double activated_salience = 0.0;
    for (const auto& record : ranked) {
        if (record.event.sequence == activated.event.sequence) {
            found_activated = true;
            activated_salience = record.salience;
            break;
        }
    }
    assert(found_activated);
    assert(activated_salience > 0.0);

    const auto affect = brain.affective_state();
    const auto appraisal = brain.affective_appraisal();
    assert(affect.updates >= 3);
    assert(affect.valence < 0.5);
    assert(appraisal.outcome_weight >= 0.0 && appraisal.outcome_weight <= 2.0);

    const auto actions = std::vector<CandidateAction>{{"observe", 0.5}, {"act", 0.6}};
    const auto decisions = brain.choose_with_affect(actions);
    assert(decisions.size() == actions.size());

    Brain restored(path);
    const auto restored_affect = restored.affective_state();
    assert(restored_affect.updates == affect.updates);
    assert(std::abs(restored_affect.valence - affect.valence) < 1e-9);
    const auto restored_ranked = restored.memory().salient(16);
    bool restored_activated = false;
    for (const auto& record : restored_ranked) {
        if (record.event.sequence == activated.event.sequence) {
            restored_activated = true;
            assert(std::abs(record.salience - activated_salience) < 1e-12);
            break;
        }
    }
    assert(restored_activated);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "affective_evidence_suite: PASS\n";
    return 0;
}
