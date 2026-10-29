#include "jarvis/core/brain.hpp"
#include "jarvis/core/evolution_safety.hpp"
#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/process_isolation.hpp"
#include "evolution_test_evaluator.hpp"

#include <cassert>
#include <filesystem>
#include <algorithm>
#include <string>

using namespace jarvis::core;

namespace {
void attest_isolated(EvolutionExperiment& experiment,
                     const std::string& procedure = "local-test-procedure-v1") {
    ProcessIsolationBackend backend;
    const IsolatedEvaluationSpec spec{
        IsolatedCommand{"/proc/self/exe", {"--test-evaluator"}, ""},
        procedure,
        "baseline:" + experiment.proposal.key + ":" + std::to_string(experiment.proposal.current),
        "candidate:" + experiment.proposal.key + ":" + std::to_string(experiment.proposal.proposed),
        experiment.proposal.current,
        experiment.proposal.proposed};
    EvolutionExperimentRunner::run_isolated_evaluation(experiment, backend, spec);
}
} // namespace

int main(int argc, char** argv) {\n    if (argc > 1 && std::string(argv[1]) == "--test-evaluator")\n        return test_support::run_evolution_test_evaluator(argc, argv);
    const std::filesystem::path path = "evolution_brain_integration_test.bin";
    std::error_code ec;
    // A persisted legacy adoption event without experiment evidence must
    // not bypass the evaluation gate when a Brain reconstructs from disk.
    const std::filesystem::path legacy_path = "evolution_legacy_adoption_test.bin";
    std::filesystem::remove(legacy_path, ec);
    std::filesystem::remove(legacy_path.string() + ".meta", ec);
    {
        Brain source(legacy_path);
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
        Brain restarted_legacy(legacy_path);
        const auto* parameter = restarted_legacy.evolution_parameter("legacy.replay");
        assert(parameter != nullptr);
        assert(parameter->value == parameter->baseline);
    }
    std::filesystem::remove(legacy_path, ec);
    std::filesystem::remove(legacy_path.string() + ".meta", ec);

    // A versioned adoption event still cannot apply a proposal without a
    // preceding valid evaluation record, even if it claims isolation and
    // includes superficial provenance fields.
    const std::filesystem::path forged_path = "evolution_forged_replay_test.bin";
    std::filesystem::remove(forged_path, ec);
    std::filesystem::remove(forged_path.string() + ".meta", ec);
    {
        Brain source(forged_path);
        assert(source.register_evolution_parameter("forged.replay", 0.25));
    }
    {
        Memory journal(256, forged_path);
        Event forged_adoption{
            0, 1, "test", "evolution_adopt",
            {{"key", std::string("forged.replay")}, {"current", 0.25},
             {"proposed", 0.95}, {"expected_gain", 0.70}, {"confidence", 0.99},
             {"proposal_confidence", 0.99}, {"experiment_id", std::string("forged-no-evaluation")},
             {"outcome", static_cast<std::int64_t>(ExperimentOutcome::Improved)},
             {"baseline", 0.70}, {"candidate", 0.95}, {"minimum_improvement", 0.01},
             {"isolated", true}, {"evaluation_procedure_id", std::string("local-test-procedure-v1")},
             {"baseline_artifact_id", std::string("baseline:forged")},
             {"candidate_artifact_id", std::string("candidate:forged")}}};
        assert(journal.append(forged_adoption) != 0);
    }
    {
        Brain restarted_forged(forged_path);
        const auto* parameter = restarted_forged.evolution_parameter("forged.replay");
        assert(parameter != nullptr && parameter->value == parameter->baseline);
    }
    std::filesystem::remove(forged_path, ec);
    std::filesystem::remove(forged_path.string() + ".meta", ec);

    // An unversioned legacy rollback must not undo a newer adoption during
    // journal replay: it does not identify the experiment it belongs to.
    const std::filesystem::path legacy_rollback_path = "evolution_legacy_rollback_test.bin";
    std::filesystem::remove(legacy_rollback_path, ec);
    std::filesystem::remove(legacy_rollback_path.string() + ".meta", ec);
    {
        Brain source(legacy_rollback_path);
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
        Brain restarted_legacy(legacy_rollback_path);
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

    std::filesystem::remove(path, ec);

    {
        Brain brain(path);
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
        attest_isolated(equal_fitness, "equal-fitness");
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
        attest_isolated(subthreshold, "subthreshold");
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
        Brain restarted(path);
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
        attest_isolated(replayed);
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

        Brain restarted_again(path);
        const auto* direct_parameter = restarted_again.evolution_parameter("planner.weight");
        assert(direct_parameter != nullptr);
        assert(direct_parameter->value == direct_parameter->baseline);
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
