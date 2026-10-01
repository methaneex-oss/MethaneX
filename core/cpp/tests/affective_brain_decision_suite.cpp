#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_affective_brain_decision.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    CandidateAction reversible{"reversible", 0.3, 0.2, 0.2, 1.0, 0.1, 0.1, 0.4};
    CandidateAction irreversible{"irreversible", 0.3, 0.2, 0.2, 0.1, 0.1, 0.1, 0.4};
    const std::vector<CandidateAction> actions{reversible, irreversible};

    const auto neutral = brain.choose_with_affect(actions);
    assert(neutral.size() == 2);

    brain.observe(Event{0, 0, "test", "observation", {{"novelty", 1.0}, {"salience", 1.0}, {"uncertainty", 1.0}}});
    brain.execute_action(
        ActionAssessment{reversible, 0.0, true, {}},
        [](const CandidateAction&) { return false; },
        [](const CandidateAction&) { return false; });

    const auto affected = brain.choose_with_affect(actions);
    assert(affected.size() == 2);
    assert(affected.front().action.name == "reversible");

    Brain restored(path);
    const auto replayed = restored.choose_with_affect(actions);
    assert(replayed.size() == 2);
    assert(replayed.front().action.name == affected.front().action.name);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "affective_brain_decision_suite: PASS\n";
    return 0;
}
