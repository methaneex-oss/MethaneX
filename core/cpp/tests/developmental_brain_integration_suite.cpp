#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

static double score_for(const std::vector<Decision>& decisions, const std::string& action) {
    for (const auto& decision : decisions) {
        if (decision.action.name == action) return decision.score;
    }
    return -1.0e9;
}

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_developmental_brain_integration.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    {
        Brain brain(path);
        const auto first = brain.predict("temperature", 20.0, 0.8);
        const auto second = brain.predict("temperature", 30.0, 0.9);
        assert(first.created_sequence != 0);
        assert(second.created_sequence != 0);
        assert(first.created_sequence != second.created_sequence);
        assert(brain.resolve_prediction(first.created_sequence, 20.0));

        const auto snapshot = brain.snapshot();
        assert(snapshot.predictions.size() == 2);
        std::size_t resolved = 0;
        for (const auto& prediction : snapshot.predictions) if (prediction.resolved) ++resolved;
        assert(resolved == 1);
        assert(brain.developmental_associations().size() == 1);
        assert(std::isfinite(brain.developmental_associations().front().strength));
        assert(!brain.resolve_prediction(first.created_sequence, 20.0));
        assert(brain.resolve_prediction(second.created_sequence, 30.0));

        Goal goal{"developmental-context", "learn a useful action strategy", 0.9, 0.0,
                  0, 0, GoalStatus::pending, {}, {}};
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        const std::vector<CandidateAction> actions{
            {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
            {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
        };

        const auto before = brain.choose_with_developmental_learning(actions);
        const double before_learned = score_for(before, "learned-action");
        const double before_other = score_for(before, "other-action");

        for (int i = 0; i < 5; ++i) {
            const ActionAssessment assessment{
                actions[0], ActionDisposition::execute, true, 0.9, "developmental"};
            const auto result = brain.execute_action(
                assessment,
                [](const CandidateAction&) { return true; },
                [](const CandidateAction&) { return true; },
                {},
                [](const CandidateAction&) { return 1.0; });
            assert(result.verified);
        }

        for (int i = 0; i < 5; ++i) {
            const ActionAssessment assessment{
                actions[1], ActionDisposition::execute, true, 0.9, "developmental"};
            const auto result = brain.execute_action(
                assessment,
                [](const CandidateAction&) { return false; },
                [](const CandidateAction&) { return false; });
            assert(!result.executed);
        }

        const auto learned = brain.developmental_best_strategy(goal.id);
        assert(learned != nullptr);
        assert(learned->action == "learned-action");
        assert(learned->confidence > 0.0);
        assert(learned->uses >= 5);

        const auto after = brain.choose_with_developmental_learning(actions);
        const double after_learned = score_for(after, "learned-action");
        const double after_other = score_for(after, "other-action");
        assert(after_learned > before_learned);
        assert(after_learned > after_other);
        assert(after_other <= before_other);
    }

    {
        Brain restored(path);
        const auto snapshot = restored.snapshot();
        assert(snapshot.predictions.size() == 2);
        for (const auto& prediction : snapshot.predictions) assert(prediction.resolved);
        assert(restored.developmental_associations().size() == 1);

        const auto learned = restored.developmental_best_strategy("developmental-context");
        assert(learned != nullptr);
        assert(learned->action == "learned-action");
        assert(learned->uses >= 5);

        const std::vector<CandidateAction> actions{
            {"learned-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
            {"other-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5, 0.0, 0.0},
        };
        const auto restored_decisions = restored.choose_with_developmental_learning(actions);
        assert(score_for(restored_decisions, "learned-action") >
               score_for(restored_decisions, "other-action"));
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "developmental brain integration suite passed
";
    return 0;
}
