#include "jarvis/core/brain.hpp"
#include "jarvis/core/evolution_safety.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_experiment_coordinator.hpp"
#include "jarvis/core/evolution_candidate_generator.hpp"
#include "jarvis/core/evolution_digest.hpp"
#include "jarvis/core/process_isolation.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace jarvis::core;

namespace {
std::string evaluator_path;
std::string baseline_artifact_path;
std::string candidate_artifact_path;
EvolutionSafetyPolicy test_policy;
void write_artifacts(const EvolutionExperiment& experiment) {
    { std::ofstream out(baseline_artifact_path); out << std::setprecision(17) << experiment.proposal.current; }
    { std::ofstream out(candidate_artifact_path); out << std::setprecision(17) << experiment.proposal.proposed; }
}
void attest_isolated(EvolutionExperiment& experiment) {
    write_artifacts(experiment);
    ProcessIsolationBackend backend;
    IsolatedEvaluationProcedure procedure{
        IsolatedCommand{evaluator_path, {"--trusted-test-evaluator"}, ""},
        "brain-suite-local-evaluator-v1", "linear-fitness-v1",
        baseline_artifact_path, candidate_artifact_path, detail::sha256_file(evaluator_path)};
    const auto outcome = EvolutionExperimentRunner::run_isolated_evaluation(
        experiment, backend, procedure, 4, 4, 0.5);
    assert(outcome == ExperimentOutcome::Improved);
}
} // namespace

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--trusted-test-evaluator") {
        if (argc != 14 || std::string(argv[2]) != "--jarvis-evaluate-v1") return 21;
        std::ifstream artifact(argv[9]);
        std::string coefficient_text;
        if (!artifact || !(artifact >> coefficient_text)) return 22;
        const double coefficient = std::stod(coefficient_text);
        const double evaluated_value = std::stod(argv[6]);
        if (std::abs(coefficient - evaluated_value) > 1e-12) return 23;
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
    test_policy.trusted_evaluator_digest = detail::sha256_file(evaluator_path);
    const auto temp = std::filesystem::temp_directory_path();
    baseline_artifact_path = (temp / "jarvis_brain_baseline_artifact.txt").string();
    candidate_artifact_path = (temp / "jarvis_brain_candidate_artifact.txt").string();
    const std::filesystem::path path = "evolution_brain_integration_test.bin";
    std::error_code ec;
    // A persisted legacy adoption event without experiment evidence must
    // not bypass the evaluation gate when a Brain reconstructs from disk.
    const std::filesystem::path legacy_path = "evolution_legacy_adoption_test.bin";
    std::filesystem::remove(legacy_path, ec);
    std::filesystem::remove(legacy_path.string() + ".meta", ec);
    {
        Brain source(legacy_path, test_policy);
        assert(source.register_evolution_parameter("legacy.replay", 0.25));
    }
    {
        Memory journal(256, legacy_path);
        Event legacy_adoption{
            0, 1, "legacy-test", "evolution_adopt",
            {{"key", std::string("legacy.replay")},
             {"current", 0.25},
             {"proposed", 0.95},
             {"expected_gain", 0.70},
             {"confidence", 0.99}}};
        assert(journal.append(legacy_adoption) != 0);
    }
    {
        Brain restarted_legacy(legacy_path, test_policy);
        const auto* parameter = restarted_legacy.evolution_parameter("legacy.replay");
        assert(parameter != nullptr);
        assert(parameter->value == parameter->baseline);
    }
    std::filesystem::remove(legacy_path, ec);
    std::filesystem::remove(legacy_path.string() + ".meta", ec);

    // An experiment ID does not make an adoption event valid: replay must
    // require a preceding, matching evaluation record.
    const std::filesystem::path missing_evaluation_path = "evolution_missing_evaluation_test.bin";
    std::filesystem::remove(missing_evaluation_path, ec);
    std::filesystem::remove(missing_evaluation_path.string() + ".meta", ec);
    {
        Brain source(missing_evaluation_path, test_policy);
        assert(source.register_evolution_parameter("replay.no-evaluation", 0.25));
    }
    {
        Memory journal(256, missing_evaluation_path);
        Event adoption_without_evaluation{
            0, 2, "forged-test", "evolution_adopt",
            {{"key", std::string("replay.no-evaluation")},
             {"current", 0.25}, {"proposed", 0.95},
             {"expected_gain", 0.70}, {"proposal_confidence", 0.99},
             {"confidence", 0.99}, {"minimum_improvement", 0.05},
             {"baseline", 0.70}, {"candidate", 0.95},
             {"outcome", static_cast<std::int64_t>(ExperimentOutcome::Improved)},
             {"isolated", true}, {"experiment_id", std::string("forged-no-evaluation")}}};
        assert(journal.append(adoption_without_evaluation) != 0);
    }
    {
        Brain restarted(missing_evaluation_path, test_policy);
        const auto* parameter = restarted.evolution_parameter("replay.no-evaluation");
        assert(parameter != nullptr && parameter->value == parameter->baseline);
    }
    std::filesystem::remove(missing_evaluation_path, ec);
    std::filesystem::remove(missing_evaluation_path.string() + ".meta", ec);

    // A forged "Improved" label cannot override equal measured fitness.
    const std::filesystem::path inconsistent_evaluation_path = "evolution_inconsistent_evaluation_test.bin";
    std::filesystem::remove(inconsistent_evaluation_path, ec);
    std::filesystem::remove(inconsistent_evaluation_path.string() + ".meta", ec);
    {
        Brain source(inconsistent_evaluation_path, test_policy);
        assert(source.register_evolution_parameter("replay.equal-fitness", 0.25));
    }
    {
        Memory journal(256, inconsistent_evaluation_path);
        Event forged_evaluation{
            0, 2, "forged-test", "evolution_evaluated",
            {{"experiment_id", std::string("forged-equal-fitness")},
             {"key", std::string("replay.equal-fitness")},
             {"current", 0.25}, {"proposed", 0.35},
             {"expected_gain", 0.10}, {"proposal_confidence", 0.99},
             {"baseline", 0.80}, {"candidate", 0.80},
             {"minimum_improvement", 0.05}, {"confidence", 0.99},
             {"outcome", static_cast<std::int64_t>(ExperimentOutcome::Improved)},
             {"isolated", true}}};
        assert(journal.append(forged_evaluation) != 0);
        Event adoption_after_forged_evaluation{
            0, 3, "forged-test", "evolution_adopt",
            {{"experiment_id", std::string("forged-equal-fitness")},
             {"key", std::string("replay.equal-fitness")},
             {"current", 0.25}, {"proposed", 0.35},
             {"expected_gain", 0.10}, {"proposal_confidence", 0.99},
             {"baseline", 0.80}, {"candidate", 0.80},
             {"minimum_improvement", 0.05}, {"confidence", 0.99},
             {"outcome", static_cast<std::int64_t>(ExperimentOutcome::Improved)},
             {"isolated", true}}};
        assert(journal.append(adoption_after_forged_evaluation) != 0);
    }
    {
        Brain restarted(inconsistent_evaluation_path, test_policy);
        const auto* parameter = restarted.evolution_parameter("replay.equal-fitness");
        assert(parameter != nullptr && parameter->value == parameter->baseline);
    }
    std::filesystem::remove(inconsistent_evaluation_path, ec);
    std::filesystem::remove(inconsistent_evaluation_path.string() + ".meta", ec);

    // An unversioned legacy rollback must not undo a newer adoption during
    // journal replay: it does not identify the experiment it belongs to.
    const std::filesystem::path legacy_rollback_path = "evolution_legacy_rollback_test.bin";
    std::filesystem::remove(legacy_rollback_path, ec);
    std::filesystem::remove(legacy_rollback_path.string() + ".meta", ec);
    {
        Brain source(legacy_rollback_path, test_policy);
        assert(source.register_evolution_parameter("legacy.rollback", 0.25));
        EvolutionExperiment valid_adoption{
            "legacy-rollback-protection-1",
            EvolutionProposal{"legacy.rollback", 0.25, 0.35, 0.1, 0.90},
            0.70, 0.85, 0.01, 0.90, ExperimentOutcome::Improved, true};
        attest_isolated(valid_adoption);
        assert(source.record_evolution_evaluation(valid_adoption));
        assert(source.adopt_evolution_experiment(valid_adoption));
        const auto* adopted = source.evolution_parameter("legacy.rollback");
        assert(adopted != nullptr && adopted->value == 0.35);
    }
    {
        Memory journal(256, legacy_rollback_path);
        Event legacy_rollback{
            0, 0, "legacy-test", "evolution_rollback",
            {{"key", std::string("legacy.rollback")}}};
        assert(journal.append(legacy_rollback) != 0);
    }
    {
        Brain restarted_legacy(legacy_rollback_path, test_policy);
        const auto* parameter = restarted_legacy.evolution_parameter("legacy.rollback");
        assert(parameter != nullptr);
        assert(parameter->value == 0.35);
        const auto history = restarted_legacy.evolution_history();
        assert(std::any_of(history.begin(), history.end(), [](const EvolutionHistoryRecord& record) {
            return record.experiment_id == "legacy-rollback-protection-1" &&
                   record.action == EvolutionRecordAction::Adopted;
        }));
    }
    std::filesystem::remove(legacy_rollback_path, ec);
    std::filesystem::remove(legacy_rollback_path.string() + ".meta", ec);

    // A valid evaluation followed by an adoption event that changes the
    // proposed parameter must be rejected during replay.
    const std::filesystem::path mismatched_replay_path = "evolution_mismatched_replay_test.bin";
    std::filesystem::remove(mismatched_replay_path, ec);
    std::filesystem::remove(mismatched_replay_path.string() + ".meta", ec);
    EvolutionExperiment valid_replay_evidence;
    {
        Brain source(mismatched_replay_path, test_policy);
        assert(source.register_evolution_parameter("replay.mismatched-proposal", 0.3));
        valid_replay_evidence = EvolutionExperiment{
            "mismatched-replay-1",
            EvolutionProposal{"replay.mismatched-proposal", 0.3, 0.4, 0.1, 0.8},
            0.0, 0.0, 0.01, 0.0, ExperimentOutcome::Pending, false};
        ProcessIsolationBackend backend;
        IsolatedEvaluationProcedure procedure{
            IsolatedCommand{evaluator_path, {"--trusted-test-evaluator"}, ""},
            "brain-suite-local-evaluator-v1", "artifact-score-v1",
            baseline_artifact_path, candidate_artifact_path, detail::sha256_file(evaluator_path)};
        write_artifacts(valid_replay_evidence);
        const auto batch = EvolutionExperimentCoordinator::run_isolated(
            valid_replay_evidence, backend, procedure, EvolutionTrialConfig{});
        assert(batch.executed && valid_replay_evidence.has_valid_evaluation_evidence());
        assert(source.record_evolution_evaluation(valid_replay_evidence));
    }
    {
        Memory journal(256, mismatched_replay_path);
        const auto& e = valid_replay_evidence;
        Event mismatched_adoption{
            0, 2, "forged-test", "evolution_adopt",
            {{"experiment_id", e.id}, {"key", e.proposal.key},
             {"current", e.proposal.current}, {"proposed", 0.45},
             {"expected_gain", e.proposal.expected_gain},
             {"proposal_confidence", e.proposal.confidence},
             {"outcome", static_cast<std::int64_t>(e.outcome)},
             {"baseline", e.baseline_fitness}, {"candidate", e.candidate_fitness},
             {"confidence", e.confidence}, {"minimum_improvement", e.minimum_improvement},
             {"isolated", true}, {"evaluation_procedure_id", e.evaluation_procedure_id},
             {"evaluation_config_id", e.evaluation_config_id},
             {"baseline_artifact_digest", e.baseline_artifact_digest},
             {"candidate_artifact_digest", e.candidate_artifact_digest},
             {"evaluator_artifact_digest", e.evaluator_artifact_digest},
             {"baseline_trial_count", static_cast<std::int64_t>(e.baseline_trial_count)},
             {"candidate_trial_count", static_cast<std::int64_t>(e.candidate_trial_count)},
             {"evaluation_evidence_digest", e.evaluation_evidence_digest}}};
        assert(journal.append(mismatched_adoption) != 0);
    }
    {
        Brain restored(mismatched_replay_path, test_policy);
        const auto* parameter = restored.evolution_parameter("replay.mismatched-proposal");
        assert(parameter != nullptr && parameter->value == parameter->baseline);
    }
    std::filesystem::remove(mismatched_replay_path, ec);
    std::filesystem::remove(mismatched_replay_path.string() + ".meta", ec);

    // Full default-policy lifecycle through the isolated coordinator, durable
    // evaluation/adoption events, and a fresh Brain reconstructed from journal.
    const std::filesystem::path lifecycle_path = "evolution_isolated_lifecycle_test.bin";
    std::filesystem::remove(lifecycle_path, ec);
    std::filesystem::remove(lifecycle_path.string() + ".meta", ec);
    {
        Brain source(lifecycle_path, test_policy);
        assert(source.register_evolution_parameter("coordinator.lifecycle", 0.3));
        const EvolutionOpportunity opportunity{
            "coordinator-lifecycle-opportunity", "test-evidence", 0.9, 0.9, 0.3, 0.4, 4, 1, 4};
        EvolutionCandidateGenerator generator = [](const EvolutionOpportunity&) {
            return std::vector<EvolutionProposal>{
                EvolutionProposal{"coordinator.lifecycle", 0.3, 0.4, 0.1, 0.8}};
        };
        const auto generated = EvolutionCandidateValidator::validate(generator(opportunity));
        assert(generated.size() == 1);
        EvolutionExperiment experiment{
            "coordinator-lifecycle-1", generated.front(),
            0.0, 0.0, 0.01, 0.0, ExperimentOutcome::Pending, false};
        ProcessIsolationBackend backend;
        IsolatedEvaluationProcedure procedure{
            IsolatedCommand{evaluator_path, {"--trusted-test-evaluator"}, ""},
            "brain-suite-local-evaluator-v1", "artifact-score-v1",
            baseline_artifact_path, candidate_artifact_path, detail::sha256_file(evaluator_path)};
        write_artifacts(experiment);
        const auto batch = EvolutionExperimentCoordinator::run_isolated(
            experiment, backend, procedure, EvolutionTrialConfig{});
        assert(batch.executed && batch.outcome == ExperimentOutcome::Improved);
        assert(experiment.has_valid_evaluation_evidence());
        assert(source.record_evolution_evaluation(experiment));
        assert(source.adopt_evolution_experiment(experiment));
    }
    {
        Brain restored(lifecycle_path, test_policy);
        const auto* parameter = restored.evolution_parameter("coordinator.lifecycle");
        assert(parameter != nullptr && std::abs(parameter->value - 0.4) < 1e-12);
        const auto history = restored.evolution_history();
        assert(std::any_of(history.begin(), history.end(), [](const auto& record) {
            return record.experiment_id == "coordinator-lifecycle-1" &&
                   record.action == EvolutionRecordAction::Adopted;
        }));
        EvolutionSafetyPolicy wrong_trust = test_policy;
        wrong_trust.trusted_evaluator_digest = "untrusted-evaluator-digest";
        Brain untrusted_restored(lifecycle_path, wrong_trust);
        const auto* untrusted_parameter = untrusted_restored.evolution_parameter("coordinator.lifecycle");
        assert(untrusted_parameter != nullptr);
        assert(untrusted_parameter->value == untrusted_parameter->baseline);
    }
    std::filesystem::remove(lifecycle_path, ec);
    std::filesystem::remove(lifecycle_path.string() + ".meta", ec);
    std::filesystem::remove(baseline_artifact_path, ec);
    std::filesystem::remove(candidate_artifact_path, ec);
    std::filesystem::remove(path, ec);

    {
        Brain brain(path, test_policy);
        assert(brain.register_evolution_parameter("planner.weight", 0.4));
        assert(!brain.register_evolution_parameter("planner.weight", 0.4));
        brain.predict("planner.weight", Scalar{0.4}, 0.9);
        const auto learning_cycle = brain.learn_from_prediction("planner.weight", Scalar{0.6}, 0.8);
        assert(learning_cycle.adaptation.observations == 1);
        const auto* after_prediction = brain.evolution_parameter("planner.weight");
        assert(after_prediction != nullptr);
        assert(after_prediction->observations == 1);
        brain.observe_evolution_fitness("planner.weight", 0.9);
        brain.observe_evolution_fitness("planner.weight", 0.9);
        const auto* after_fitness = brain.evolution_parameter("planner.weight");
        assert(after_fitness != nullptr);
        assert(after_fitness->observations == 3);
        const auto proposals = brain.evolution_options();
        assert(!proposals.empty());

        EvolutionExperiment experiment{
            "brain-evolution-1", proposals.front(), 0.70, 0.90, 0.01, 0.95,
            ExperimentOutcome::Improved, true};
        attest_isolated(experiment);
        assert(brain.record_evolution_evaluation(experiment));
        const auto evaluated_history = brain.evolution_history();
        assert(evaluated_history.size() == 1);
        assert(evaluated_history.front().action == EvolutionRecordAction::Evaluated);
        assert(brain.adopt_evolution_experiment(experiment));
        const auto live_history = brain.evolution_history();
        assert(live_history.size() == 2);
        assert(live_history.front().action == EvolutionRecordAction::Evaluated);
        assert(live_history.back().experiment_id == "brain-evolution-1");
        assert(live_history.back().action == EvolutionRecordAction::Adopted);

        assert(brain.register_evolution_parameter("manual.rollback", 0.25));
        EvolutionExperiment manual_rollback{
            "manual-rollback-1",
            EvolutionProposal{"manual.rollback", 0.25, 0.35, 0.1, 0.90},
            0.70, 0.85, 0.01, 0.90, ExperimentOutcome::Improved, true};
        attest_isolated(manual_rollback);
        assert(brain.record_evolution_evaluation(manual_rollback));
        assert(brain.adopt_evolution_experiment(manual_rollback));
        const auto* adopted_manual = brain.evolution_parameter("manual.rollback");
        assert(adopted_manual != nullptr && adopted_manual->value == 0.35);
        assert(brain.rollback_evolution("manual.rollback"));
        const auto* rolled_manual = brain.evolution_parameter("manual.rollback");
        assert(rolled_manual != nullptr && rolled_manual->value == rolled_manual->baseline);
        const auto manual_history = brain.evolution_history();
        assert(manual_history.size() == 5);
        assert(manual_history.back().experiment_id == "manual-rollback-1");
        assert(manual_history.back().action == EvolutionRecordAction::RolledBack);

        assert(brain.register_evolution_parameter("direct.rollback", 0.2));
        brain.observe_evolution_fitness("direct.rollback", 0.9);
        brain.observe_evolution_fitness("direct.rollback", 0.9);
        const auto direct_proposals = brain.evolution_options();
        const auto direct_it = std::find_if(
            direct_proposals.begin(), direct_proposals.end(),
            [](const EvolutionProposal& proposal) { return proposal.key == "direct.rollback"; });
        assert(direct_it != direct_proposals.end());
        // A proposal without a recorded candidate-vs-baseline experiment
        // must not mutate the parameter through the legacy convenience API.
        const auto* before_direct_adoption = brain.evolution_parameter("direct.rollback");
        assert(before_direct_adoption != nullptr);
        const double direct_baseline = before_direct_adoption->baseline;
        assert(!brain.adopt_evolution(*direct_it));
        assert(brain.register_evolution_parameter("safety.missing-evaluation", 0.2));
        EvolutionExperiment missing_evaluation{
            "safety-missing-evaluation",
            EvolutionProposal{"safety.missing-evaluation", 0.2, 0.3, 0.1, 0.99},
            0.70, 0.82, 0.01, 0.99, ExperimentOutcome::Improved, true};
        attest_isolated(missing_evaluation);
        assert(!brain.adopt_evolution_experiment(missing_evaluation));
        const auto* unchanged_missing = brain.evolution_parameter("safety.missing-evaluation");
        assert(unchanged_missing != nullptr && unchanged_missing->value == 0.2);
        // An experiment cannot be adopted merely because the caller labels it
        // Improved; the outcome must be recomputed against its threshold.
        assert(brain.register_evolution_parameter("safety.equal-fitness", 0.2));
        EvolutionExperiment equal_fitness{
            "safety-equal-fitness", EvolutionProposal{"safety.equal-fitness", 0.2, 0.3, 0.1, 0.99},
            0.70, 0.70, 0.01, 0.99, ExperimentOutcome::Improved, true};
        attest_isolated(equal_fitness);
        equal_fitness.candidate_fitness = equal_fitness.baseline_fitness;
        equal_fitness.outcome = ExperimentOutcome::Improved;
        EvolutionSafetyPolicy non_isolation_policy;
        non_isolation_policy.require_isolation = false;
        assert(!EvolutionSafetyGate::approve(equal_fitness, non_isolation_policy));
        assert(!brain.record_evolution_evaluation(equal_fitness));
        assert(!brain.adopt_evolution_experiment(equal_fitness));

        assert(brain.register_evolution_parameter("safety.subthreshold", 0.2));
        EvolutionExperiment subthreshold{
            "safety-subthreshold", EvolutionProposal{"safety.subthreshold", 0.2, 0.3, 0.1, 0.99},
            0.70, 0.74, 0.05, 0.99, ExperimentOutcome::Improved, true};
        attest_isolated(subthreshold);
        subthreshold.candidate_fitness = subthreshold.baseline_fitness + 0.01;
        subthreshold.outcome = ExperimentOutcome::Improved;
        assert(!EvolutionSafetyGate::approve(subthreshold, non_isolation_policy));
        assert(!brain.record_evolution_evaluation(subthreshold));
        assert(!brain.adopt_evolution_experiment(subthreshold));

        assert(brain.register_evolution_parameter("safety.mismatch", 0.2));
        EvolutionExperiment mismatched{
            "safety-mismatched-evaluation",
            EvolutionProposal{"safety.mismatch", 0.2, 0.3, 0.1, 0.99},
            0.70, 0.82, 0.01, 0.99, ExperimentOutcome::Improved, true};
        attest_isolated(mismatched);
        assert(brain.record_evolution_evaluation(mismatched));
        mismatched.candidate_fitness = 0.90;
        assert(!brain.adopt_evolution_experiment(mismatched));
        const auto* unchanged_mismatch = brain.evolution_parameter("safety.mismatch");
        assert(unchanged_mismatch != nullptr && unchanged_mismatch->value == 0.2);
        const auto* rejected_direct = brain.evolution_parameter("direct.rollback");
        assert(rejected_direct != nullptr);
        assert(rejected_direct->value == direct_baseline);

        brain.observe_evolution_canary("planner.weight", "brain-evolution-1", {0.90, 0.89});
        brain.observe_evolution_canary("planner.weight", "brain-evolution-1", {0.90, 0.88});
        const auto decision = brain.observe_evolution_canary(
            "planner.weight", "brain-evolution-1", {0.90, 0.84});
        assert(decision.sufficient_evidence);
        assert(decision.rollback);

        assert(brain.register_evolution_parameter("canary.persist", 0.3));
        EvolutionExperiment canary_experiment{
            "canary-persist-1",
            EvolutionProposal{"canary.persist", 0.3, 0.4, 0.1, 0.90},
            0.70, 0.85, 0.01, 0.90, ExperimentOutcome::Improved, true};
        attest_isolated(canary_experiment);
        assert(brain.record_evolution_evaluation(canary_experiment));
        assert(brain.adopt_evolution_experiment(canary_experiment));
        const auto pending_canary = brain.observe_evolution_canary(
            "canary.persist", "canary-persist-1", {0.90, 0.89});
        assert(!pending_canary.sufficient_evidence);
        const auto pending_canary_again = brain.observe_evolution_canary(
            "canary.persist", "canary-persist-1", {0.90, 0.88});
        assert(!pending_canary_again.sufficient_evidence);
        assert(brain.register_evolution_parameter("replay.persist", 0.3));
        EvolutionExperiment replayable{
            "replay-evaluation-1",
            EvolutionProposal{"replay.persist", 0.3, 0.4, 0.1, 0.90},
            0.70, 0.82, 0.01, 0.90, ExperimentOutcome::Improved, true};
        attest_isolated(replayable);
        assert(brain.record_evolution_evaluation(replayable));
        assert(!brain.record_evolution_evaluation(replayable));
        assert(brain.evolution_history().size() == 10);
    }

    {
        Brain restarted(path, test_policy);
        const auto* parameter = restarted.evolution_parameter("planner.weight");
        assert(parameter != nullptr);
        assert(parameter->value == parameter->baseline);
        assert(parameter->observations == 3);
        assert(parameter->value == parameter->baseline);
        const auto* missing_evaluation = restarted.evolution_parameter("safety.missing-evaluation");
        assert(missing_evaluation != nullptr && missing_evaluation->value == missing_evaluation->baseline);
        const auto* equal_fitness = restarted.evolution_parameter("safety.equal-fitness");
        assert(equal_fitness != nullptr && equal_fitness->value == equal_fitness->baseline);
        const auto* subthreshold = restarted.evolution_parameter("safety.subthreshold");
        assert(subthreshold != nullptr && subthreshold->value == subthreshold->baseline);
        const auto* mismatch = restarted.evolution_parameter("safety.mismatch");
        assert(mismatch != nullptr && mismatch->value == mismatch->baseline);
        const auto* direct = restarted.evolution_parameter("direct.rollback");
        assert(direct != nullptr);
        assert(direct->value == direct->baseline);
        assert(direct->observations == 2);
        const auto* manual = restarted.evolution_parameter("manual.rollback");
        assert(manual != nullptr);
        assert(manual->value == manual->baseline);
        assert(manual->observations == 0);

        const auto restarted_history = restarted.evolution_history();
        assert(restarted_history.size() == 10);
        assert(restarted_history.front().experiment_id == "brain-evolution-1");
        assert(restarted_history.front().action == EvolutionRecordAction::Evaluated);
        assert(restarted_history[1].action == EvolutionRecordAction::Adopted);
        assert(restarted_history.back().experiment_id == "replay-evaluation-1");
        assert(restarted_history.back().action == EvolutionRecordAction::Evaluated);
        EvolutionExperiment replayed{
            "replay-evaluation-1",
            EvolutionProposal{"replay.persist", 0.3, 0.4, 0.1, 0.90},
            0.70, 0.82, 0.01, 0.90, ExperimentOutcome::Improved, true};
        replayed.isolated = true;
        assert(restarted.adopt_evolution_experiment(replayed));
        const auto* replayed_parameter = restarted.evolution_parameter("replay.persist");
        assert(replayed_parameter != nullptr && replayed_parameter->value == 0.4);

        const auto persisted_canary = restarted.observe_evolution_canary(
            "canary.persist", "canary-persist-1", {0.90, 0.80});
        assert(persisted_canary.sufficient_evidence);
        assert(persisted_canary.rollback);

        const auto rollback_history = restarted.evolution_history();
        assert(!rollback_history.empty());
        assert(rollback_history.back().action == EvolutionRecordAction::RolledBack);

        Brain restarted_again(path, test_policy);
        const auto* direct_parameter = restarted_again.evolution_parameter("planner.weight");
        assert(direct_parameter != nullptr);
        assert(direct_parameter->value == direct_parameter->baseline);
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::filesystem::remove(baseline_artifact_path, ec);
    std::filesystem::remove(candidate_artifact_path, ec);
    return 0;
}
