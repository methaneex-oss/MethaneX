#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_affective_goal_outcome.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    {
        Brain brain(path);
        assert(brain.affective_learning_updates() == 0);

        assert(brain.create_goal(Goal{"g1", "learn", 0.8, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        assert(brain.activate_goal("g1"));

        const auto before = brain.affective_state();
        const auto before_appraisal = brain.affective_appraisal();

        GoalOutcomeEvidence evidence;
        evidence.goal_id = "g1";
        evidence.progress_after = 0.5;
        evidence.confidence = 0.8;
        assert(brain.assimilate_goal_outcome_with_affect(evidence));

        const auto after = brain.affective_state();
        const auto appraisal = brain.affective_appraisal();
        assert(after.updates > before.updates);
        assert(brain.affective_learning_updates() > 0);
        assert(std::isfinite(after.valence));
        assert(std::isfinite(after.arousal));
        assert(appraisal.outcome_weight >= 0.0 && appraisal.outcome_weight <= 2.0);
        assert(appraisal.error_weight >= 0.0 && appraisal.error_weight <= 2.0);
        assert(appraisal.outcome_weight != before_appraisal.outcome_weight ||
               appraisal.error_weight != before_appraisal.error_weight);

        Brain restored(path);
        const auto replayed = restored.affective_state();
        const auto replayed_appraisal = restored.affective_appraisal();
        assert(restored.affective_learning_updates() == brain.affective_learning_updates());
        assert(std::abs(replayed.valence - after.valence) < 1e-9);
        assert(std::abs(replayed.arousal - after.arousal) < 1e-9);
        assert(std::abs(replayed_appraisal.outcome_weight - appraisal.outcome_weight) < 1e-9);
        assert(std::abs(replayed_appraisal.error_weight - appraisal.error_weight) < 1e-9);
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "affective_goal_outcome_suite: PASS\n";
    return 0;
}
