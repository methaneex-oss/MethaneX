#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_affective_goal_outcome.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    assert(brain.affective_learning_updates() == 0);

    assert(brain.create_goal(Goal{"g1", "learn", 0.8, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
    assert(brain.activate_goal("g1"));
    assert(brain.update_goal_progress("g1", 0.5));
    const auto before = brain.affective_state();
    assert(brain.complete_goal("g1"));

    const auto after = brain.affective_state();
    assert(after.updates > before.updates);
    assert(brain.affective_learning_updates() >= 2);
    assert(after.valence >= before.valence);

    Brain restored(path);
    const auto replayed = restored.affective_state();
    assert(replayed.updates == after.updates);
    assert(replayed.valence == after.valence);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "affective_goal_outcome_suite: PASS\n";
    return 0;
}
