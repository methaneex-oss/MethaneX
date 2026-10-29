#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <random>
#include <string>
#include <system_error>

using namespace jarvis::core;

namespace {
constexpr const char* goal_id = "dlt-003-mapping-generalization-goal";
constexpr const char* primary_context = "task/primary";
constexpr const char* secondary_context = "task/secondary";
constexpr const char* related_context = "task/related";

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
        [consequence](const CandidateAction&) { return consequence; });

    assert(result.authorized);
    assert(result.executed);
    assert(result.verified);
    assert(result.outcome.observed);
    assert(result.outcome.actual_consequence == consequence);
}

CognitiveCycleInput make_input(const std::string& context) {
    CognitiveCycleInput input;
    input.goal_id = goal_id;
    input.developmental_context = context;
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    input.observation = Event{0, 1, "dlt-003", "observation",
                              {{"task-context", context}}};

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

std::string selected_action(Brain& brain, const std::string& context) {
    const auto result = CognitiveCycle(brain).run(make_input(context));
    assert(result.status == CognitiveCycleStatus::completed);
    assert(!result.context.plan.steps.empty());
    return result.context.plan.steps.front().action.name;
}

double strategy_value(const Brain& brain, const std::string& context,
                      const std::string& action) {
    for (const auto& strategy : brain.developmental_strategies())
        if (strategy.context == context && strategy.action == action)
            return strategy.value;
    return 0.0;
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

void run_seed(std::uint64_t seed) {
    const auto journal = std::filesystem::temp_directory_path() /
        ("jarvis_dlt_003_" + std::to_string(seed) + ".bin");
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    // The environment chooses which arbitrary action label succeeds for this
    // seed. This oracle is test-only; neither the mapping nor the expected
    // action is passed into Brain as a prescribed answer.
    std::mt19937_64 mapping_random(seed);
    std::bernoulli_distribution choose_route_one_for_primary(0.5);
    const std::string primary_positive = choose_route_one_for_primary(mapping_random)
        ? "route-one" : "route-two";
    const std::string secondary_positive =
        primary_positive == "route-one" ? "route-two" : "route-one";

    {
        Brain brain(journal);
        Goal goal;
        goal.id = goal_id;
        goal.description = "Learn arbitrary action consequences and revise from new evidence";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        // Same two actions, but the environment independently assigns the
        // successful action in each context. Only observed consequences teach.
        train_pair(brain, primary_context, primary_positive, 6);
        train_pair(brain, secondary_context, secondary_positive, 6);
        train_pair(brain, related_context, primary_positive, 6);

        assert(selected_action(brain, primary_context) == primary_positive);
        assert(selected_action(brain, secondary_context) == secondary_positive);
        assert(selected_action(brain, related_context) == primary_positive);

        // Reverse only the primary task. The learned behavior must change there
        // without erasing the other context-specific action/outcome mappings.
        train_pair(brain, primary_context, secondary_positive, 12);
        assert(selected_action(brain, primary_context) == secondary_positive);
        assert(selected_action(brain, secondary_context) == secondary_positive);
        assert(selected_action(brain, related_context) == primary_positive);

        assert(strategy_value(brain, primary_context, primary_positive) < 0.0);
        assert(strategy_value(brain, primary_context, secondary_positive) > 0.0);
        assert(strategy_value(brain, secondary_context, secondary_positive) > 0.0);
        assert(strategy_value(brain, related_context, primary_positive) > 0.0);
        assert(brain.memory().by_kind("action_outcome").size() == 96);
    }

    // A fresh Brain instance must reproduce actual decisions, not merely expose
    // stored values. The test also catches accidental dependence on old process
    // state and uses the same held-out seed mapping after journal restoration.
    {
        Brain restored(journal);
        assert(restored.goal(goal_id) != nullptr);
        assert(selected_action(restored, primary_context) == secondary_positive);
        assert(selected_action(restored, secondary_context) == secondary_positive);
        assert(selected_action(restored, related_context) == primary_positive);
        assert(restored.memory().by_kind("action_outcome").size() == 96);
    }

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    std::cout << "[DLT-003] seed=" << seed
              << " primary_initial=" << primary_positive
              << " primary_after_reversal=" << secondary_positive
              << " secondary_preserved=" << secondary_positive
              << " related_preserved=" << primary_positive
              << " persistence=verified\n";
}
} // namespace

int main() {
    // These seeds produce different environment mappings. Running both prevents
    // the acceptance criterion from being tied to a single action label.
    run_seed(7);
    run_seed(19);
    std::cout << "[DLT-003] status=PASS seeds=2 randomized_action_mappings=true\n";
    return 0;
}
