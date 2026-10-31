#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cstdint>
#include <filesystem>
#include <string>
#include <system_error>

using namespace jarvis::core;

namespace {
constexpr const char* goal_id = "dlt-004-feature-composition-goal";

CognitiveCycleInput make_input(const std::string& bridge,
                               const std::string& visibility,
                               const std::string& surface) {
    CognitiveCycleInput input;
    input.goal_id = goal_id;
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    // Deliberately leave developmental_context empty. CognitiveCycle must
    // infer the feature representation from the observation itself.
    input.observation = Event{
        0, 1, "sensor", "observation",
        {{"bridge_status", bridge}, {"visibility", visibility},
         {"surface_condition", surface},
         {"task", std::string("navigation")},
         {"context", std::string("navigation/phase-label-that-must-not-leak")},
         {"world_episode", std::int64_t{17}},
         {"world_terminal", false}}};

    CandidateAction first;
    first.name = "route-one";
    first.utility = 0.5;
    first.expected_value = 0.5;
    first.confidence = 0.5;
    first.risk = 0.1;
    CandidateAction second = first;
    second.name = "route-two";
    input.candidate_actions = {first, second};
    return input;
}

std::string inferred_context(Brain& brain, const std::string& bridge,
                             const std::string& visibility,
                             const std::string& surface) {
    const auto result = CognitiveCycle(brain).run(
        make_input(bridge, visibility, surface));
    assert(result.status == CognitiveCycleStatus::completed);
    assert(!result.context.action_assessments.empty());
    const auto& context = result.context.action_assessments.front().developmental_context;
    assert(context.find("/features/bridge_status/surface_condition/visibility/values/") != std::string::npos);
    assert(context.find("/values/") != std::string::npos);
    assert(context.find("phase-label-that-must-not-leak") == std::string::npos);
    assert(context.find("world_episode") == std::string::npos);
    return context;
}

void record_outcome(Brain& brain, const std::string& context,
                    const std::string& action, double consequence) {
    ActionAssessment assessment;
    assessment.action.name = action;
    assessment.action.expected_consequence = 0.0;
    assessment.disposition = ActionDisposition::execute;
    assessment.permitted = true;
    assessment.confidence = 0.9;
    assessment.developmental_context = context;

    const auto result = brain.execute_action(
        assessment,
        [](const CandidateAction&) { return true; },
        [](const CandidateAction&) { return true; },
        {},
        [consequence](const CandidateAction&) {
            return std::optional<double>{consequence};
        });
    assert(result.authorized && result.executed && result.verified);
    assert(result.outcome.observed);
    assert(result.outcome.actual_consequence == consequence);
}

void train_pair(Brain& brain, const std::string& context,
                const std::string& positive_action, int repetitions) {
    const std::string negative_action =
        positive_action == "route-one" ? "route-two" : "route-one";
    for (int i = 0; i < repetitions; ++i) {
        record_outcome(brain, context, positive_action, 1.0);
        record_outcome(brain, context, negative_action, -1.0);
    }
}

std::string selected_action(Brain& brain, const std::string& bridge,
                            const std::string& visibility,
                            const std::string& surface) {
    const auto result = CognitiveCycle(brain).run(
        make_input(bridge, visibility, surface));
    assert(result.status == CognitiveCycleStatus::completed);
    assert(!result.context.plan.steps.empty());
    return result.context.plan.steps.front().action.name;
}

void run_seed(std::uint64_t seed) {
    const auto journal = std::filesystem::temp_directory_path() /
        ("jarvis_dlt_004_" + std::to_string(seed) + ".bin");
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    // The environment varies the successful action label by seed. The brain
    // receives only bridge and visibility features, never this oracle.
    const std::string clear_action = seed % 2U == 0U ? "route-two" : "route-one";
    const std::string poor_action =
        clear_action == "route-one" ? "route-two" : "route-one";

    {
        Brain brain(journal);
        Goal goal;
        goal.id = goal_id;
        goal.description = "Choose routes by learning independently useful environmental features";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        const auto open_clear_flat =
            inferred_context(brain, "open", "clear", "flat");
        const auto open_clear_rough =
            inferred_context(brain, "open", "clear", "rough");
        const auto closed_clear_rough =
            inferred_context(brain, "closed", "clear", "rough");
        const auto closed_poor_flat =
            inferred_context(brain, "closed", "poor", "flat");
        const auto closed_poor_rough =
            inferred_context(brain, "closed", "poor", "rough");

        // The open/poor/rough combination is deliberately withheld. Every
        // feature value used in the probe has been observed in multiple
        // distinct contexts, so repeated samples of one combination cannot
        // masquerade as independent support.
        train_pair(brain, open_clear_flat, clear_action, 8);
        train_pair(brain, open_clear_rough, clear_action, 8);
        train_pair(brain, closed_clear_rough, clear_action, 8);
        train_pair(brain, closed_poor_flat, poor_action, 8);
        train_pair(brain, closed_poor_rough, poor_action, 8);

        const auto held_out =
            inferred_context(brain, "open", "poor", "rough");
        const auto route_one =
            brain.developmental_feature_strategy_estimate(held_out, "route-one");
        const auto route_two =
            brain.developmental_feature_strategy_estimate(held_out, "route-two");
        assert(route_one.matched_features == 3);
        assert(route_two.matched_features == 3);
        assert(route_one.confidence >= 0.5);
        assert(route_two.confidence >= 0.5);
        assert((poor_action == "route-one" ? route_one.value : route_two.value) >
               (poor_action == "route-one" ? route_two.value : route_one.value));
        assert(selected_action(brain, "open", "poor", "rough") == poor_action);
        assert(brain.memory().by_kind("action_outcome").size() == 80);
    }

    // Feature weights are reconstructed from the same durable experiences;
    // restart must preserve the held-out decision, not just the stored table.
    {
        Brain restored(journal);
        assert(restored.goal(goal_id) != nullptr);
        assert(selected_action(restored, "open", "poor", "rough") == poor_action);
        const auto held_out = inferred_context(restored, "open", "poor", "rough");
        const auto estimate =
            restored.developmental_feature_strategy_estimate(held_out, poor_action);
        assert(estimate.confidence >= 0.5);
        assert(estimate.value > 0.0);
        assert(restored.memory().by_kind("action_outcome").size() == 80);
    }

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
}
} // namespace

int main() {
    // A single observation must not be treated as sufficient support for
    // compositional transfer, even when both feature values are present.
    DevelopmentalLearning sparse;
    const std::string sparse_context =
        "observation/observation/source/sensor/features/bridge_status/visibility/values/open/clear";
    sparse.observe_strategy(
        sparse_context, "route-one",
        LearningSignal{1.0, 1.0, 0.0, 0.0, 0.0, 1.0});
    const auto sparse_estimate =
        sparse.feature_strategy_estimate(sparse_context, "route-one");
    assert(sparse_estimate.matched_features == 2);
    assert(sparse_estimate.confidence < 0.5);

    run_seed(7);
    run_seed(8);
    return 0;
}
