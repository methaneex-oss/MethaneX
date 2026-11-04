#include "jarvis/core/cognitive_cycle.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
constexpr const char* goal_id = "memory-learning-evolution-integration";
constexpr const char* clear_context = "navigation/clear";
constexpr const char* storm_context = "navigation/storm";

void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

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

    require(result.authorized && result.executed && result.verified,
            "controlled action failed to execute and verify");
    require(result.outcome.observed,
            "environment consequence was not observed");
    require(std::abs(result.outcome.actual_consequence - consequence) < 1e-12,
            "recorded consequence differs from environment consequence");
}

CognitiveCycleInput make_input(const std::string& context) {
    CognitiveCycleInput input;
    input.goal_id = goal_id;
    input.developmental_context = context;
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    input.observation = Event{0, 1, "integration-environment", "observation",
                              {{"environment", context}}};

    CandidateAction route_a;
    route_a.name = "route-a";
    route_a.utility = 0.5;
    route_a.expected_value = 0.5;
    route_a.confidence = 0.5;
    route_a.risk = 0.1;

    CandidateAction route_b = route_a;
    route_b.name = "route-b";
    input.candidate_actions = {route_a, route_b};
    return input;
}

std::string selected_action(Brain& brain, const std::string& context) {
    const auto result = CognitiveCycle(brain).run(make_input(context));
    require(result.status == CognitiveCycleStatus::completed,
            "cognitive cycle did not complete for context: " + context);
    require(!result.context.plan.steps.empty(),
            "cognitive cycle produced no action for context: " + context);
    return result.context.plan.steps.front().action.name;
}

void require_context_recall(const Brain& brain, const std::string& context,
                           const std::string& action) {
    const auto recalled = brain.memory().recall_ranked(
        {{"context", std::string(context)}, {"action", std::string(action)}},
        5, "action_outcome", true);
    require(!recalled.empty(),
            "memory could not retrieve the relevant action experience");
    for (const auto& record : recalled) {
        const auto context_it = record.event.data.find("context");
        const auto action_it = record.event.data.find("action");
        require(context_it != record.event.data.end() &&
                    std::get_if<std::string>(&context_it->second) != nullptr &&
                    std::get<std::string>(context_it->second) == context,
                "memory retrieval leaked an unrelated context");
        require(action_it != record.event.data.end() &&
                    std::get_if<std::string>(&action_it->second) != nullptr &&
                    std::get<std::string>(action_it->second) == action,
                "memory retrieval returned the wrong action");
    }
}

double strategy_value(const Brain& brain, const std::string& context,
                      const std::string& action) {
    for (const auto& strategy : brain.developmental_strategies()) {
        if (strategy.context == context && strategy.action == action)
            return strategy.value;
    }
    throw std::runtime_error("missing learned strategy: " + context + " / " + action);
}

void train_evolution_from_feedback(Brain& brain, const std::string& key,
                                   double predicted, double actual,
                                   double fitness, int repetitions) {
    for (int i = 0; i < repetitions; ++i) {
        brain.predict(key, Scalar{predicted}, 0.8);
        const auto cycle = brain.learn_from_prediction(key, Scalar{actual}, fitness);
        require(cycle.adaptation.observations > 0,
                "prediction outcome did not update adaptation for " + key);
    }
}

void require_evolved(const Brain& brain, const std::string& key,
                     double baseline, bool should_increase) {
    const auto* parameter = brain.evolution_parameter(key);
    require(parameter != nullptr, "evolution parameter missing after replay: " + key);
    require(parameter->observations >= 12,
            "evolution fitness observations were not retained: " + key);
    if (should_increase) {
        require(parameter->value > baseline,
                "positive feedback did not evolve parameter upward: " + key);
    } else {
        require(parameter->value < baseline,
                "negative feedback did not evolve parameter downward: " + key);
    }
}
} // namespace

int main() {
    try {
        const auto journal = std::filesystem::temp_directory_path() /
                             "jarvis_memory_learning_evolution_integration.bin";
        std::error_code ec;
        std::filesystem::remove(journal, ec);
        std::filesystem::remove(journal.string() + ".meta", ec);

        double positive_baseline = 0.1;
        double negative_baseline = 0.5;
        std::size_t expected_action_outcomes = 24;
        std::size_t expected_prediction_outcomes = 84;

        {
            Brain brain(journal);
            Goal goal;
            goal.id = goal_id;
            goal.description =
                "Acquire context-sensitive behavior and revise it from consequences";
            goal.priority = 0.9;
            require(brain.create_goal(goal), "could not create integration goal");
            require(brain.activate_goal(goal.id), "could not activate integration goal");

            // SIMPLE: acquire two different context-specific action preferences
            // exclusively from observed action consequences.
            for (int repetition = 0; repetition < 6; ++repetition) {
                record_experience(brain, clear_context, "route-a", 1.0);
                record_experience(brain, clear_context, "route-b", -1.0);
                record_experience(brain, storm_context, "route-a", -1.0);
                record_experience(brain, storm_context, "route-b", 1.0);
            }
            require(selected_action(brain, clear_context) == "route-a",
                    "acquisition failed in unchanged clear context");
            require(selected_action(brain, storm_context) == "route-b",
                    "acquisition failed in storm context");

            // HARD: reverse only the storm relationship. Interleaving clear
            // experiences checks that learning remains context-local.
            for (int repetition = 0; repetition < 12; ++repetition) {
                record_experience(brain, storm_context, "route-a", 1.0);
                record_experience(brain, storm_context, "route-b", -1.0);
                if (repetition % 3 == 0) {
                    record_experience(brain, clear_context, "route-a", 1.0);
                    record_experience(brain, clear_context, "route-b", -1.0);
                    expected_action_outcomes += 2;
                }
            }
            expected_action_outcomes += 24;

            require(selected_action(brain, clear_context) == "route-a",
                    "reversal damaged the unchanged clear context");
            require(selected_action(brain, storm_context) == "route-a",
                    "storm-context behavior did not adapt after reversal");
            require(strategy_value(brain, clear_context, "route-a") > 0.0,
                    "clear-context positive strategy was not retained");
            require(strategy_value(brain, storm_context, "route-a") > 0.0,
                    "storm-context revised strategy was not learned");
            require(strategy_value(brain, storm_context, "route-b") < 0.0,
                    "storm-context harmful strategy was not revised");
            require_context_recall(brain, storm_context, "route-a");
            require_context_recall(brain, clear_context, "route-a");

            // VERY HARD: prediction feedback drives adaptation and evolution
            // through the Brain API, not direct calls to EvolutionModel.
            require(brain.register_evolution_parameter("planner.positive-feedback", positive_baseline),
                    "could not register positive evolution parameter");
            require(brain.register_evolution_parameter("planner.negative-feedback", negative_baseline),
                    "could not register negative evolution parameter");
            train_evolution_from_feedback(
                brain, "planner.positive-feedback", 0.1, 0.7, 0.9, 14);
            train_evolution_from_feedback(
                brain, "planner.negative-feedback", 0.9, 0.1, -0.9, 14);
            require_evolved(brain, "planner.positive-feedback", positive_baseline, true);
            require_evolved(brain, "planner.negative-feedback", negative_baseline, false);

            require(brain.memory().by_kind("action_outcome").size() ==
                        expected_action_outcomes,
                    "action outcome journal count does not match generated experience");
            require(brain.memory().by_kind("prediction_outcome").size() ==
                        expected_prediction_outcomes,
                    "prediction feedback was not durably recorded");
            require(brain.learning_metric("planner.positive-feedback") != nullptr,
                    "prediction error did not reach the adaptation metric");
            require(brain.memory().by_kind("evolution_fitness").size() == 28,
                    "prediction feedback did not reach the evolution fitness journal");
        }

        // COMPLEX: destruction and reconstruction force the journal to be the
        // source of truth. No in-memory learner or evolution object survives.
        {
            Brain restored(journal);
            require(restored.goal(goal_id) != nullptr,
                    "goal was not restored from the journal");
            require(restored.memory().by_kind("action_outcome").size() ==
                        expected_action_outcomes,
                    "action consequences did not survive restart");
            require(restored.memory().by_kind("prediction_outcome").size() ==
                        expected_prediction_outcomes,
                    "prediction outcomes did not survive restart");
            require(restored.memory().by_kind("evolution_fitness").size() == 28,
                    "evolution fitness history did not survive restart");

            require(strategy_value(restored, clear_context, "route-a") > 0.0,
                    "clear-context learning was lost after restart");
            require(strategy_value(restored, storm_context, "route-a") > 0.0,
                    "revised storm strategy was lost after restart");
            require(strategy_value(restored, storm_context, "route-b") < 0.0,
                    "storm-context negative evidence was lost after restart");
            require_context_recall(restored, storm_context, "route-a");
            require_context_recall(restored, clear_context, "route-a");
            require(selected_action(restored, clear_context) == "route-a",
                    "restored brain no longer selects the learned clear action");
            require(selected_action(restored, storm_context) == "route-a",
                    "restored brain no longer selects the adapted storm action");

            require_evolved(restored, "planner.positive-feedback", positive_baseline, true);
            require_evolved(restored, "planner.negative-feedback", negative_baseline, false);
            require(restored.learning_metric("planner.positive-feedback") != nullptr,
                    "adaptation state was not reconstructed from prediction history");
            require(restored.learning_metric("planner.negative-feedback") != nullptr,
                    "negative adaptation state was not reconstructed from prediction history");

            std::cout << "[BRAIN-MLEI] PASS"
                      << " action_outcomes=" << expected_action_outcomes
                      << " prediction_outcomes=" << expected_prediction_outcomes
                      << " evolution_fitness=28"
                      << " reversal=adapted"
                      << " unchanged_context=preserved"
                      << " restart=restored_behavior_and_evolution\n";
        }

        std::filesystem::remove(journal, ec);
        std::filesystem::remove(journal.string() + ".meta", ec);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "[BRAIN-MLEI] FAIL: " << error.what() << '\n';
        return 1;
    }
}
