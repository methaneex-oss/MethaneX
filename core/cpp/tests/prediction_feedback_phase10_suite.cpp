#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <filesystem>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_phase10_prediction_feedback.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    Goal goal;
    goal.id = "stabilize";
    goal.description = "Stabilize the observed system";
    goal.priority = 1.0;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    brain.observe(Event{0, 1, "sensor", "observation", {{"temperature", 20.0}, {"fan", false}}});
    brain.observe(Event{0, 2, "sensor", "observation", {{"temperature", 30.0}, {"fan", true}}});

    CognitiveCycle cycle(brain);
    CognitiveCycleInput input;
    input.observation = Event{0, 3, "sensor", "observation", {{"temperature", 30.0}, {"fan", true}}};
    input.goal_id = goal.id;
    input.planning_horizon = 1;
    input.candidate_actions = {
        CandidateAction{"stabilize", 0.9, 0.8, 0.1, 1.0, 1.0, 0.0, 0.8},
    };
    input.resource_budget = 2.0;

    const auto result = cycle.run(input);
    assert(result.status == CognitiveCycleStatus::completed);
    assert(!result.context.causal_links.empty());
    assert(!result.context.predictions.empty());

    const auto& prediction = result.context.predictions.front();
    assert(!prediction.key.empty());
    assert(prediction.created_sequence != 0);
    assert(!prediction.resolved);
    assert(prediction.confidence >= 0.0 && prediction.confidence <= 1.0);

    const auto feedback = cycle.process_outcome(prediction.key, prediction.predicted);
    assert(feedback.prediction_resolved);

    const auto predictions = brain.snapshot().predictions;
    bool resolved = false;
    for (const auto& current : predictions) {
        if (current.key == prediction.key) {
            resolved = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(resolved);

    Brain restored(path);
    bool persisted = false;
    for (const auto& current : restored.snapshot().predictions) {
        if (current.key == prediction.key) {
            persisted = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(persisted);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
