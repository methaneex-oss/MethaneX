#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_brain_action_consequence_integration.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);

    Brain brain(journal);

    ActionAssessment assessment;
    assessment.action = CandidateAction{
        "calibrate",
        0.8,
        0.8,
        0.1,
        1.0,
        0.1,
        0.8,
        0.0,
        DecisionOutcome::act,
        {}};
    assessment.disposition = ActionDisposition::execute;
    assessment.permitted = true;
    assessment.confidence = 0.9;

    bool executed = false;
    const auto result = brain.execute_action(
        assessment,
        [&](const CandidateAction&) { executed = true; return true; },
        [&](const CandidateAction&) { return executed; },
        {},
        [](const CandidateAction&) { return -0.2; });

    assert(result.authorized);
    assert(result.executed);
    assert(result.verified);
    assert(result.outcome.observed);
    assert(std::abs(result.action.expected_consequence - 0.8) < 1e-9);
    assert(std::abs(result.outcome.actual_consequence + 0.2) < 1e-9);
    assert(std::abs(result.outcome.consequence_error + 1.0) < 1e-9);

    bool saw_action_outcome = false;
    for (const auto& event : brain.memory().all()) {
        if (event.kind != "action_outcome") continue;
        saw_action_outcome = true;
        assert(std::get<std::string>(event.data.at("action")) == "calibrate");
        assert(std::abs(std::get<double>(event.data.at("expected_consequence")) - 0.8) < 1e-9);
        assert(std::abs(std::get<double>(event.data.at("actual_consequence")) + 0.2) < 1e-9);
        assert(std::abs(std::get<double>(event.data.at("consequence_error")) + 1.0) < 1e-9);
    }
    assert(saw_action_outcome);
    assert(brain.affective_learning_updates() > 0);

    Brain restored(journal);
    assert(restored.affective_learning_updates() > 0);
    bool restored_action_outcome = false;
    for (const auto& event : restored.memory().all()) {
        if (event.kind == "action_outcome") {
            restored_action_outcome = true;
            break;
        }
    }
    assert(restored_action_outcome);

    std::filesystem::remove(journal, ec);
    return 0;
}
