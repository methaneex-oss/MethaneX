#include "jarvis/core/brain.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_digest.hpp"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
std::string evaluator_path;
std::string baseline_artifact_path;
std::string candidate_artifact_path;

void write_artifacts(const EvolutionExperiment& experiment) {
    { std::ofstream out(baseline_artifact_path); out << std::setprecision(17) << experiment.proposal.current; }
    { std::ofstream out(candidate_artifact_path); out << std::setprecision(17) << experiment.proposal.proposed; }
}
void attest_isolated(EvolutionExperiment& experiment) {
    write_artifacts(experiment);
    ProcessIsolationBackend backend;
    IsolatedEvaluationProcedure procedure{
        IsolatedCommand{evaluator_path, {"--trusted-test-evaluator"}, ""},
        "memory-learning-local-evaluator-v1", "held-out-linear-regression-v1",
        baseline_artifact_path, candidate_artifact_path, detail::sha256_file(evaluator_path)};
    const auto outcome = EvolutionExperimentRunner::run_isolated_evaluation(
        experiment, backend, procedure, 4, 4, 0.5);
    if (outcome != ExperimentOutcome::Improved)
        std::cerr << "integration failure: local candidate evaluation was not improved\n";
}
bool check(bool condition, const char* message) {
    if (!condition) std::cerr << "integration failure: " << message << '\n';
    return condition;
}

double score_for(const std::vector<Decision>& decisions, const std::string& action) {
    for (const auto& decision : decisions) {
        if (decision.action.name == action) return decision.score;
    }
    return -1.0e9;
}
} // namespace

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--trusted-test-evaluator") {
        if (argc != 14 || std::string(argv[2]) != "--jarvis-evaluate-v1") return 21;
        std::ifstream artifact(argv[9]);
        std::string coefficient_text;
        if (!artifact || !(artifact >> coefficient_text)) return 22;
        const double coefficient = std::stod(coefficient_text);
        if (std::abs(coefficient - std::stod(argv[6])) > 1e-12) return 23;
        double squared_error = 0.0;
        for (double input = 1.0; input <= 4.0; input += 1.0) {
            const double error = coefficient * input - 0.8 * input;
            squared_error += error * error;
        }
        const double fitness = 1.0 / (1.0 + squared_error / 4.0);
        std::cout << "JARVIS_EVAL_V1\t" << argv[3] << "\t" << argv[4] << "\t"
                  << argv[5] << "\t" << argv[6] << "\t" << argv[7] << "\t"
                  << argv[8] << "\t" << argv[10] << "\t" << argv[11] << "\t"
                  << argv[12] << "\t" << argv[13] << "\t" << fitness;
        return 0;
    }
    evaluator_path = std::filesystem::absolute(argv[0]).string();
    const auto temp = std::filesystem::temp_directory_path();
    baseline_artifact_path = (temp / "jarvis_memory_learning_baseline.txt").string();
    candidate_artifact_path = (temp / "jarvis_memory_learning_candidate.txt").string();
    const auto path = std::filesystem::temp_directory_path() /
                      "jarvis_memory_learning_evolution_integration.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    double adopted_value = 0.0;
    std::size_t expected_outcomes = 0;
    {
        Brain brain(path);
        if (!check(brain.register_evolution_parameter("planner.weight", 0.4),
                   "register evolution parameter")) return 1;

        // Prediction error enters the ordinary learning path and updates the
        // same registered parameter's evidence statistics.
        const auto prediction = brain.predict("planner.weight", Scalar{0.4}, 0.9);
        if (!check(prediction.created_sequence != 0, "prediction was recorded")) return 1;
        const auto learning = brain.learn_from_prediction("planner.weight", Scalar{0.6}, 0.8);
        if (!check(learning.adaptation.observations == 1, "prediction feedback updated learning")) return 1;
        const auto* parameter_after_learning = brain.evolution_parameter("planner.weight");
        if (!check(parameter_after_learning != nullptr &&
                   parameter_after_learning->observations == 1,
                   "learning feedback reached evolution parameter statistics")) return 1;

        // Run actual action/consequence interactions in a separate context.
        // These outcomes must create learned strategies, not hard-coded rules.
        Goal goal{"integrated-learning-context", "choose the more reliable action",
                  0.9, 0.0, 0, 0, GoalStatus::pending, {}, {}};
        if (!check(brain.create_goal(goal) && brain.activate_goal(goal.id),
                   "activate strategy-learning context")) return 1;

        const std::vector<CandidateAction> actions{
            {"stable-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5,
             DecisionOutcome::act, 0.0},
            {"unreliable-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5,
             DecisionOutcome::act, 0.0},
        };
        for (int i = 0; i < 6; ++i) {
            const ActionAssessment assessment{
                actions[0], ActionDisposition::execute, true, 0.9, "integration"};
            const auto result = brain.execute_action(
                assessment,
                [](const CandidateAction&) { return true; },
                [](const CandidateAction&) { return true; },
                {},
                [](const CandidateAction&) { return 1.0; });
            if (!check(result.verified, "successful action was verified")) return 1;
        }
        for (int i = 0; i < 6; ++i) {
            const ActionAssessment assessment{
                actions[1], ActionDisposition::execute, true, 0.9, "integration"};
            const auto result = brain.execute_action(
                assessment,
                [](const CandidateAction&) { return false; },
                [](const CandidateAction&) { return false; });
            if (!check(!result.executed, "failed action was not reported as executed")) return 1;
        }
        expected_outcomes = 12;

        const auto strategies = brain.developmental_strategies();
        const auto stable = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) {
                return strategy.context == "integrated-learning-context" &&
                       strategy.action == "stable-action";
            });
        const auto unreliable = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) {
                return strategy.context == "integrated-learning-context" &&
                       strategy.action == "unreliable-action";
            });
        if (!check(stable != strategies.end() && stable->value > 0.0,
                   "positive consequence produced positive strategy evidence")) return 1;
        if (!check(unreliable != strategies.end() && unreliable->value < 0.0,
                   "failed execution produced negative strategy evidence")) return 1;

        const auto decisions = brain.choose_with_developmental_learning(
            actions, "integrated-learning-context");
        if (!check(score_for(decisions, "stable-action") >
                   score_for(decisions, "unreliable-action"),
                   "learned strategy changed the subsequent decision")) return 1;

        // Evolution must consume accumulated evidence and persist its evaluated
        // candidate/adoption in the same journal as the learned experience.
        brain.observe_evolution_fitness("planner.weight", 0.9);
        brain.observe_evolution_fitness("planner.weight", 0.9);
        const auto proposals = brain.evolution_options();
        const auto proposal = std::find_if(proposals.begin(), proposals.end(),
            [](const EvolutionProposal& candidate) {
                return candidate.key == "planner.weight";
            });
        if (!check(proposal != proposals.end(), "learning evidence produced an evolution proposal")) return 1;

        EvolutionExperiment experiment{
            "integrated-learning-evolution-1", *proposal,
            0.70, 0.90, 0.01, 0.95, ExperimentOutcome::Improved, true};
        attest_isolated(experiment);
        if (!check(brain.record_evolution_evaluation(experiment),
                   "evolution evaluation was journaled")) return 1;
        if (!check(brain.adopt_evolution_experiment(experiment),
                   "validated evolution candidate was adopted")) return 1;
        const auto* adopted = brain.evolution_parameter("planner.weight");
        if (!check(adopted != nullptr && adopted->value == proposal->proposed,
                   "adoption changed the registered parameter")) return 1;
        adopted_value = proposal->proposed;

        const auto before_restart = brain.snapshot();
        if (!check(!before_restart.predictions.empty() &&
                   std::any_of(before_restart.predictions.begin(), before_restart.predictions.end(),
                       [](const Prediction& item) { return item.key == "planner.weight" && item.resolved; }),
                   "prediction resolution is present before restart")) return 1;
        if (!check(brain.memory().by_kind("action_outcome").size() >= expected_outcomes,
                   "action outcomes are persisted as memory events")) return 1;
    }

    // A new Brain instance forces journal replay; no live object state is reused.
    {
        Brain restored(path);
        const auto* parameter = restored.evolution_parameter("planner.weight");
        if (!check(parameter != nullptr && parameter->value == adopted_value,
                   "adopted evolution parameter survived journal replay")) return 1;
        if (!check(parameter->observations >= 3,
                   "learning and fitness observations survived journal replay")) return 1;

        const auto strategies = restored.developmental_strategies();
        const auto stable = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) {
                return strategy.context == "integrated-learning-context" &&
                       strategy.action == "stable-action";
            });
        const auto unreliable = std::find_if(strategies.begin(), strategies.end(),
            [](const LearnedStrategy& strategy) {
                return strategy.context == "integrated-learning-context" &&
                       strategy.action == "unreliable-action";
            });
        if (!check(stable != strategies.end() && stable->value > 0.0 && stable->uses >= 6,
                   "positive strategy survived restart")) return 1;
        if (!check(unreliable != strategies.end() && unreliable->value < 0.0 &&
                   unreliable->uses >= 6,
                   "negative counter-evidence survived restart")) return 1;

        const std::vector<CandidateAction> actions{
            {"stable-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5,
             DecisionOutcome::act, 0.0},
            {"unreliable-action", 0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5,
             DecisionOutcome::act, 0.0},
        };
        const auto decisions = restored.choose_with_developmental_learning(
            actions, "integrated-learning-context");
        if (!check(score_for(decisions, "stable-action") >
                   score_for(decisions, "unreliable-action"),
                   "restored learning still changes decision selection")) return 1;

        const auto history = restored.evolution_history();
        if (!check(std::any_of(history.begin(), history.end(),
                   [](const EvolutionHistoryRecord& record) {
                       return record.experiment_id == "integrated-learning-evolution-1" &&
                              record.action == EvolutionRecordAction::Adopted;
                   }),
                   "evolution adoption history survived restart")) return 1;
        const auto snapshot = restored.snapshot();
        if (!check(std::any_of(snapshot.predictions.begin(), snapshot.predictions.end(),
                   [](const Prediction& item) {
                       return item.key == "planner.weight" && item.resolved;
                   }),
                   "resolved prediction survived restart")) return 1;
        if (!check(restored.memory().by_kind("action_outcome").size() >= expected_outcomes,
                   "experience journal survived restart")) return 1;
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::filesystem::remove(baseline_artifact_path, ec);
    std::filesystem::remove(candidate_artifact_path, ec);
    std::cout << "memory-learning-evolution persistence integration passed\n";
    return 0;
}
