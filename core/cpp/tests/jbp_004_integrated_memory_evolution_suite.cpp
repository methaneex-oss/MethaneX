#include "jarvis/core/cognitive_cycle.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

using namespace jarvis::core;

namespace {
bool require(bool condition, const std::string& message) {
    if (!condition) std::cerr << "JBP-004 status=FAIL check=" << message << '\n';
    return condition;
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
        [consequence](const CandidateAction&) { return consequence; });
    if (!result.authorized || !result.executed || !result.verified ||
        !result.outcome.observed ||
        std::abs(result.outcome.actual_consequence - consequence) > 1e-12) {
        throw std::runtime_error("action consequence did not complete end-to-end");
    }
}

CognitiveCycleInput make_input(const std::string& context) {
    CognitiveCycleInput input;
    input.goal_id = "jbp-004-integrated-goal";
    input.developmental_context = context;
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    input.observation = Event{0, 1, "jbp-004", "observation",
                              {{"environment", context}}};
    CandidateAction preferred;
    preferred.name = "route-good";
    preferred.utility = 0.5;
    preferred.expected_value = 0.5;
    preferred.confidence = 0.5;
    preferred.risk = 0.1;
    CandidateAction alternate = preferred;
    alternate.name = "route-bad";
    input.candidate_actions = {preferred, alternate};
    return input;
}

std::string selected_action(Brain& brain, const std::string& context) {
    const auto result = CognitiveCycle(brain).run(make_input(context));
    if (result.status != CognitiveCycleStatus::completed ||
        result.context.plan.steps.empty()) {
        throw std::runtime_error("cognitive cycle did not produce a decision");
    }
    return result.context.plan.steps.front().action.name;
}

double strategy_value(const Brain& brain, const std::string& context,
                      const std::string& action) {
    for (const auto& strategy : brain.developmental_strategies()) {
        if (strategy.context == context && strategy.action == action) return strategy.value;
    }
    return 0.0;
}

bool train(const std::filesystem::path& journal) {
    std::error_code ec;
    if (std::filesystem::exists(journal) ||
        std::filesystem::exists(journal.string() + ".meta")) {
        std::cerr << "JBP-004 status=REFUSED_OVERWRITE\n";
        return false;
    }

    Brain brain(journal);
    Goal goal;
    goal.id = "jbp-004-integrated-goal";
    goal.description = "Learn context-specific consequences and preserve safe adaptation";
    goal.priority = 1.0;
    if (!require(brain.create_goal(goal), "goal_create") ||
        !require(brain.activate_goal(goal.id), "goal_activate")) return false;

    const std::string clear = "navigation/clear";
    const std::string storm = "navigation/storm";
    // Acquire different action/outcome relationships from observed consequences.
    for (int i = 0; i < 10; ++i) {
        record_outcome(brain, clear, "route-good", 1.0);
        record_outcome(brain, clear, "route-bad", -1.0);
        record_outcome(brain, storm, "route-good", -1.0);
        record_outcome(brain, storm, "route-bad", 1.0);
    }
    if (!require(selected_action(brain, clear) == "route-good", "clear_acquisition_changes_decision") ||
        !require(selected_action(brain, storm) == "route-bad", "storm_acquisition_changes_decision")) return false;

    // Reverse only storm. Clear is a held control for interference/catastrophic forgetting.
    for (int i = 0; i < 18; ++i) {
        record_outcome(brain, storm, "route-good", 1.0);
        record_outcome(brain, storm, "route-bad", -1.0);
    }
    if (!require(selected_action(brain, clear) == "route-good", "clear_control_survives_reversal") ||
        !require(selected_action(brain, storm) == "route-good", "storm_reversal_changes_decision")) return false;

    // Explicit prediction error must become durable feedback and a learning update.
    const auto prediction = brain.predict("environment.temperature", Scalar{23.0}, 0.8);
    const auto feedback = brain.resolve_prediction_feedback(
        prediction.created_sequence, Scalar{22.0}, -0.5);
    if (!require(feedback == PredictionFeedbackStatus::resolved_with_error,
                 "prediction_feedback_resolves_with_error")) return false;

    // Feed actual learned utility into evolution fitness observations. Evolution
    // is evaluated and adopted through the guarded experiment lifecycle, not by
    // directly changing a parameter.
    if (!require(brain.register_evolution_parameter("planner.bias", 0.3),
                 "evolution_parameter_registered")) return false;
    const double learned_utility = strategy_value(brain, clear, "route-good");
    brain.observe_evolution_fitness("planner.bias", learned_utility);
    brain.observe_evolution_fitness("planner.bias", learned_utility);
    const auto proposals = brain.evolution_options();
    const auto proposal_it = std::find_if(
        proposals.begin(), proposals.end(),
        [](const EvolutionProposal& proposal) { return proposal.key == "planner.bias"; });
    if (!require(proposal_it != proposals.end(), "fitness_produces_evolution_proposal")) return false;

    EvolutionExperiment experiment{
        "jbp-004-planner-bias", *proposal_it, 0.70, 0.90, 0.01, 0.95,
        ExperimentOutcome::Improved, true};
    if (!require(brain.record_evolution_evaluation(experiment), "evolution_evaluation_recorded") ||
        !require(brain.adopt_evolution_experiment(experiment), "evolution_candidate_adopted")) return false;

    // Leave the canary deliberately pending so the next OS process must restore
    // both the adoption record and its accumulated evidence before deciding.
    const auto canary_one = brain.observe_evolution_canary(
        "planner.bias", "jbp-004-planner-bias", {0.90, 0.89});
    const auto canary_two = brain.observe_evolution_canary(
        "planner.bias", "jbp-004-planner-bias", {0.90, 0.88});
    if (!require(!canary_one.sufficient_evidence && !canary_two.sufficient_evidence,
                 "canary_remains_pending_until_sufficient_evidence")) return false;

    if (!require(brain.memory().by_kind("action_outcome").size() == 76,
                 "all_action_outcomes_recorded") ||
        !require(brain.affective_learning_updates() > 0, "outcomes_reach_affective_learning") ||
        !require(brain.learning_metric("environment.temperature") != nullptr,
                 "prediction_error_reaches_learning_metric")) return false;

    std::cout << "JBP-004 stage=train status=PASS outcomes=76 contexts=2 reversal=1"
              << " prediction_feedback=resolved evolution=adopted canary=pending\n";
    return true;
}

bool verify(const std::filesystem::path& journal) {
    if (!std::filesystem::exists(journal)) {
        std::cerr << "JBP-004 status=FAIL reason=journal_missing\n";
        return false;
    }
    {
        Brain restored(journal);
        const std::string clear = "navigation/clear";
        const std::string storm = "navigation/storm";
        if (!require(restored.memory().by_kind("action_outcome").size() == 76,
                     "restart_restores_all_outcomes") ||
            !require(strategy_value(restored, clear, "route-good") > 0.0,
                     "restart_restores_clear_strategy") ||
            !require(strategy_value(restored, storm, "route-good") > 0.0,
                     "restart_restores_reversed_storm_strategy") ||
            !require(selected_action(restored, clear) == "route-good",
                     "restored_clear_strategy_drives_decision") ||
            !require(selected_action(restored, storm) == "route-good",
                     "restored_storm_strategy_drives_decision")) return false;

        const auto snapshot = restored.snapshot();
        bool resolved_temperature = false;
        for (const auto& prediction : snapshot.predictions) {
            if (prediction.key == "environment.temperature") {
                resolved_temperature = prediction.resolved;
                break;
            }
        }
        if (!require(resolved_temperature, "resolved_prediction_survives_restart") ||
            !require(restored.learning_metric("environment.temperature") != nullptr,
                     "prediction_learning_metric_survives_restart") ||
            !require(restored.affective_learning_updates() > 0,
                     "affective_updates_survive_restart")) return false;

        const auto* parameter = restored.evolution_parameter("planner.bias");
        if (!require(parameter != nullptr && parameter->value != parameter->baseline,
                     "adopted_evolution_value_survives_restart")) return false;
        const auto canary = restored.observe_evolution_canary(
            "planner.bias", "jbp-004-planner-bias", {0.90, 0.80});
        if (!require(canary.sufficient_evidence && canary.rollback,
                     "restored_canary_evidence_triggers_rollback")) return false;
        const auto* rolled_back = restored.evolution_parameter("planner.bias");
        if (!require(rolled_back != nullptr && rolled_back->value == rolled_back->baseline,
                     "canary_rollback_restores_baseline") ||
            !require(!restored.evolution_history().empty() &&
                     restored.evolution_history().back().action == EvolutionRecordAction::RolledBack,
                     "rollback_is_recorded_in_history")) return false;

        // Memory must support content-based recall, not only retain event counts.
        const auto recalled = restored.memory().recall_ranked(
            {{"action", std::string("route-good")},
             {"context", clear}}, 3, "action_outcome", true);
        if (!require(!recalled.empty(), "contextual_outcome_recall_after_restart") ||
            !require(recalled.front().event.data.contains("context") &&
                     std::get<std::string>(recalled.front().event.data.at("context")) == clear,
                     "recall_keeps_context_identity")) return false;
    }

    // Re-open after the rollback to prove the lifecycle transition itself is durable.
    Brain after_rollback(journal);
    const auto* final_parameter = after_rollback.evolution_parameter("planner.bias");
    if (!require(final_parameter != nullptr && final_parameter->value == final_parameter->baseline,
                 "rollback_survives_second_restore") ||
        !require(!after_rollback.evolution_history().empty() &&
                 after_rollback.evolution_history().back().action == EvolutionRecordAction::RolledBack,
                 "rollback_history_survives_second_restore")) return false;

    std::cout << "JBP-004 stage=verify status=PASS fresh_process=true"
              << " decision_recall=true prediction_replay=true evolution_rollback=true\n";
    return true;
}
} // namespace

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: jarvis_jbp_004_integrated_memory_evolution_suite train|verify <journal-path>\n";
        return 64;
    }
    const std::string mode = argv[1];
    const std::filesystem::path journal = argv[2];
    try {
        if (mode == "train") return train(journal) ? 0 : 1;
        if (mode == "verify") return verify(journal) ? 0 : 1;
        std::cerr << "mode must be train or verify\n";
        return 64;
    } catch (const std::exception& error) {
        std::cerr << "JBP-004 status=FAIL reason=" << error.what() << '\n';
        return 1;
    }
}
