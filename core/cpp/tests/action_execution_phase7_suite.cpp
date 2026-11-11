#include "jarvis/core/brain.hpp"
#include "jarvis/core/action_execution.hpp"

#include <cassert>
#include <filesystem>

using namespace jarvis::core;

int main() {
    ActionAssessment permitted;
    permitted.action = CandidateAction{"protect", 0.9, 0.9, 0.1, 1.0, 0.1, 0.0, 0.9, DecisionOutcome::act};
    permitted.disposition = ActionDisposition::execute;
    permitted.permitted = true;

    bool executed = false;
    bool rolled_back = false;
    const auto verified = ActionExecutor{}.run(ActionExecutionRequest{
        permitted,
        [&](const CandidateAction&) { executed = true; return true; },
        [&](const CandidateAction&) { return executed; },
        [&](const CandidateAction&) { rolled_back = true; return true; }});
    assert(verified.status == ActionExecutionStatus::verified);
    assert(verified.authorized && verified.executed && verified.verified);
    assert(!rolled_back);

    bool failing_execution = false;
    const auto failed = ActionExecutor{}.run(ActionExecutionRequest{
        permitted,
        [&](const CandidateAction&) { failing_execution = true; return false; },
        [&](const CandidateAction&) { return true; },
        {}});
    assert(failing_execution);
    assert(failed.status == ActionExecutionStatus::failed);
    assert(!failed.executed);

    const auto rejected = ActionExecutor{}.run(ActionExecutionRequest{
        ActionAssessment{permitted.action, ActionDisposition::reject, false, 0.1, "risk_limit"},
        [&](const CandidateAction&) { return true; },
        [&](const CandidateAction&) { return true; },
        {}});
    assert(rejected.status == ActionExecutionStatus::rejected);
    assert(!rejected.authorized);

    bool verify_failed = false;
    bool rollback_called = false;
    const auto rollback = ActionExecutor{}.run(ActionExecutionRequest{
        permitted,
        [&](const CandidateAction&) { return true; },
        [&](const CandidateAction&) { verify_failed = true; return false; },
        [&](const CandidateAction&) { rollback_called = true; return true; }});
    assert(verify_failed && rollback_called);
    assert(rollback.status == ActionExecutionStatus::rolled_back);
    assert(rollback.executed && rollback.rolled_back && !rollback.verified);

    const auto journal = std::filesystem::temp_directory_path() / "jarvis_phase7_action_test.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    Brain brain(journal);
    assert(brain.create_goal(Goal{"goal-alpha", "protect the system", 0.8, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
    assert(brain.activate_goal("goal-alpha"));
    const auto result = brain.execute_action(
        permitted,
        [](const CandidateAction&) { return true; },
        [](const CandidateAction&) { return true; });
    assert(result.status == ActionExecutionStatus::verified);
    const auto learned = brain.beliefs();
    bool saw_action_feedback = false;
    for (const auto& belief : learned) {
        if (belief.key == "action.protect") {
            saw_action_feedback = true;
            assert(std::get<std::string>(belief.value) == "verified");
        }
    }
    assert(saw_action_feedback);
    const auto strategies = brain.developmental_strategies();
    assert(strategies.size() == 1);
    assert(strategies.front().context == "goal-alpha");
    assert(strategies.front().action == "protect");
    assert(strategies.front().value > 0.0);
    const auto* best = brain.developmental_best_strategy("goal-alpha");
    assert(best != nullptr && best->action == "protect");
    Brain restored(journal);
    const auto restored_strategies = restored.developmental_strategies();
    assert(restored_strategies.size() == 1);
    assert(restored_strategies.front().context == "goal-alpha");
    assert(restored_strategies.front().action == "protect");
    std::filesystem::remove(journal, ec);
    return 0;
}
