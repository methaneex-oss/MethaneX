#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
constexpr const char* goal_id = "dlt-002-persistence-goal";

void record_experience(Brain& brain, const std::string& context,
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
    assert(std::abs(result.outcome.actual_consequence - consequence) < 1e-12);
}

CognitiveCycleInput make_input(const std::string& context) {
    CognitiveCycleInput input;
    input.goal_id = goal_id;
    input.developmental_context = context;
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    input.observation = Event{0, 1, "dlt-002", "observation",
                              {{"environment", context}}};

    CandidateAction good;
    good.name = "good-route";
    good.utility = 0.5;
    good.expected_value = 0.5;
    good.confidence = 0.5;
    good.risk = 0.1;

    CandidateAction bad = good;
    bad.name = "bad-route";
    input.candidate_actions = {good, bad};
    return input;
}

double strategy_value(const Brain& brain, const std::string& context,
                      const std::string& action, std::uint64_t* uses = nullptr) {
    for (const auto& strategy : brain.developmental_strategies()) {
        if (strategy.context == context && strategy.action == action) {
            if (uses) *uses = strategy.uses;
            return strategy.value;
        }
    }
    if (uses) *uses = 0;
    return 0.0;
}
} // namespace

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: jarvis_dlt_002_persistence <train|verify> <journal-path>\n";
        return 64;
    }
    const std::string mode = argv[1];
    const std::filesystem::path journal = argv[2];

    if (mode == "train") {
        std::error_code ec;
        std::filesystem::remove(journal, ec);
        std::filesystem::remove(journal.string() + ".meta", ec);

        Brain brain(journal);
        Goal goal;
        goal.id = goal_id;
        goal.description = "Choose actions using context-sensitive accumulated experience";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        // Train through observed consequences only. The same actions have
        // opposing outcomes in two contexts; no route choice is prescribed.
        for (int repetition = 0; repetition < 6; ++repetition) {
            record_experience(brain, "navigation/clear", "good-route", 1.0);
            record_experience(brain, "navigation/clear", "bad-route", -1.0);
            record_experience(brain, "navigation/flooded", "good-route", -1.0);
            record_experience(brain, "navigation/flooded", "bad-route", 1.0);
        }

        assert(strategy_value(brain, "navigation/clear", "good-route") > 0.0);
        assert(strategy_value(brain, "navigation/clear", "bad-route") < 0.0);
        assert(strategy_value(brain, "navigation/flooded", "good-route") < 0.0);
        assert(strategy_value(brain, "navigation/flooded", "bad-route") > 0.0);
        assert(!brain.memory().by_kind("action_outcome").empty());

        std::cout << "[DLT-002] TRAINED outcomes="
                  << brain.memory().by_kind("action_outcome").size()
                  << " journal=" << journal.string() << '\n';
        return 0;
    }

    if (mode == "verify") {
        // This executable is invoked in a second OS process by the workflow.
        // Constructing Brain here proves the learned state is restored from
        // the on-disk journal, rather than retained in the trainer's memory.
        Brain restored(journal);
        assert(restored.goal(goal_id) != nullptr);
        assert(!restored.memory().by_kind("action_outcome").empty());

        std::uint64_t clear_good_uses = 0;
        std::uint64_t flooded_bad_uses = 0;
        assert(strategy_value(restored, "navigation/clear", "good-route",
                              &clear_good_uses) > 0.0);
        assert(strategy_value(restored, "navigation/clear", "bad-route") < 0.0);
        assert(strategy_value(restored, "navigation/flooded", "good-route") < 0.0);
        assert(strategy_value(restored, "navigation/flooded", "bad-route",
                              &flooded_bad_uses) > 0.0);
        assert(clear_good_uses > 0 && flooded_bad_uses > 0);

        const auto clear = CognitiveCycle(restored).run(make_input("navigation/clear"));
        assert(clear.status == CognitiveCycleStatus::completed);
        assert(!clear.context.plan.steps.empty());
        assert(clear.context.plan.steps.front().action.name == "good-route");

        const auto flooded = CognitiveCycle(restored).run(make_input("navigation/flooded"));
        assert(flooded.status == CognitiveCycleStatus::completed);
        assert(!flooded.context.plan.steps.empty());
        assert(flooded.context.plan.steps.front().action.name == "bad-route");

        std::cout << "[DLT-002] PASS process_restart=verified "
                  << "clear_choice=good-route flooded_choice=bad-route "
                  << "restored_outcomes="
                  << restored.memory().by_kind("action_outcome").size() << '\n';

        std::error_code ec;
        std::filesystem::remove(journal, ec);
        std::filesystem::remove(journal.string() + ".meta", ec);
        return 0;
    }

    std::cerr << "unknown mode: " << mode << '\n';
    return 64;
}
