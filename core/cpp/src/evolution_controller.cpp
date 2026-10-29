#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_rollback.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

EvolutionController::EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                                         EvolutionSafetyPolicy policy)
    : model_(model), history_(history), policy_(policy), canaries_{}, adoption_journal_{} {}

bool EvolutionController::record_evaluation(const EvolutionExperiment& experiment) {
    if (experiment.id.empty() || experiment.proposal.key.empty() ||
        !experiment.candidate_executed ||
        !std::isfinite(experiment.baseline_fitness) ||
        !std::isfinite(experiment.candidate_fitness) ||
        !std::isfinite(experiment.confidence) ||
        !std::isfinite(experiment.proposal.current) ||
        !std::isfinite(experiment.proposal.proposed) ||
        !std::isfinite(experiment.proposal.expected_gain) ||
        experiment.confidence < 0.0 || experiment.confidence > 1.0 ||
        experiment.outcome == ExperimentOutcome::Pending ||
        experiment.outcome == ExperimentOutcome::Invalid ||
        policy_.trusted_evaluator_digest.empty() ||
        experiment.evaluator_artifact_digest != policy_.trusted_evaluator_digest ||
        !experiment.has_valid_isolation_attestation() ||
        !experiment.has_valid_evaluation_evidence()) {
        return false;
    }
    EvolutionExperiment verified = experiment;
    if (EvolutionExperimentEngine::evaluate(verified) != experiment.outcome) return false;

    for (const auto& record : history_.for_experiment(experiment.id)) {
        if (record.action == EvolutionRecordAction::Evaluated) {
            const auto journal = adoption_journal_.get(experiment.id);
            return record.parameter_key == experiment.proposal.key &&
                   record.outcome == experiment.outcome &&
                   record.baseline_fitness == experiment.baseline_fitness &&
                   record.candidate_fitness == experiment.candidate_fitness &&
                   record.confidence == experiment.confidence &&
                   journal.has_value() &&
                   (journal->state == AdoptionState::Pending ||
                    journal->state == AdoptionState::Adopted) &&
                   journal->parameter_key == experiment.proposal.key &&
                   journal->baseline_fitness == experiment.baseline_fitness &&
                   journal->candidate_fitness == experiment.candidate_fitness &&
                   journal->confidence == experiment.confidence &&
                   journal->proposal_current == experiment.proposal.current &&
                   journal->proposal_proposed == experiment.proposal.proposed &&
                   journal->expected_gain == experiment.proposal.expected_gain &&
                   journal->proposal_confidence == experiment.proposal.confidence &&
                   journal->minimum_improvement == experiment.minimum_improvement &&
                   journal->isolated == experiment.isolated &&
                   journal->evaluation_procedure_id == experiment.evaluation_procedure_id &&
                   journal->evaluation_config_id == experiment.evaluation_config_id &&
                   journal->baseline_artifact_digest == experiment.baseline_artifact_digest &&
                   journal->candidate_artifact_digest == experiment.candidate_artifact_digest &&
                   journal->evaluator_artifact_digest == experiment.evaluator_artifact_digest &&
                   journal->baseline_trial_count == experiment.baseline_trial_count &&
                   journal->candidate_trial_count == experiment.candidate_trial_count &&
                   journal->evaluation_evidence_digest == experiment.evaluation_evidence_digest;
        }
    }

    if (!adoption_journal_.stage(experiment)) return false;
    if (history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Evaluated,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "evaluation", {}})) {
        return true;
    }
    // Keep the evaluation Pending when history persistence fails so a later
    // durable replay can retry it; a failed write must not consume the experiment.
    return false;
}

bool EvolutionController::validate_evaluation_for_brain(
    const EvolutionExperiment& experiment) const noexcept {
    if (experiment.id.empty() || experiment.proposal.key.empty() ||
        !experiment.candidate_executed ||
        !std::isfinite(experiment.baseline_fitness) ||
        !std::isfinite(experiment.candidate_fitness) ||
        !std::isfinite(experiment.confidence) ||
        !std::isfinite(experiment.proposal.current) ||
        !std::isfinite(experiment.proposal.proposed) ||
        !std::isfinite(experiment.proposal.expected_gain) ||
        experiment.confidence < 0.0 || experiment.confidence > 1.0 ||
        experiment.outcome == ExperimentOutcome::Pending ||
        experiment.outcome == ExperimentOutcome::Invalid ||
        policy_.trusted_evaluator_digest.empty() ||
        experiment.evaluator_artifact_digest != policy_.trusted_evaluator_digest ||
        !experiment.has_valid_isolation_attestation() ||
        !experiment.has_valid_evaluation_evidence() ||
        adoption_journal_.get(experiment.id).has_value()) {
        return false;
    }
    EvolutionExperiment verified = experiment;
    return EvolutionExperimentEngine::evaluate(verified) == experiment.outcome;
}

bool EvolutionController::record_evaluation_for_brain(
    const EvolutionExperiment& experiment) noexcept {
    if (!validate_evaluation_for_brain(experiment)) return false;
    if (!adoption_journal_.stage(experiment)) return false;
    if (history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Evaluated,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "evaluation", {}})) {
        return true;
    }
    // Keep the staged evaluation Pending so event replay can retry history persistence.
    return false;
}

bool EvolutionController::replay_evaluation(
    const EvolutionExperiment& experiment) noexcept {
    if (experiment.id.empty() || experiment.proposal.key.empty() ||
        policy_.trusted_evaluator_digest.empty() ||
        experiment.evaluator_artifact_digest != policy_.trusted_evaluator_digest ||
        !experiment.has_valid_evaluation_evidence()) return false;
    EvolutionExperiment recomputed = experiment;
    if (EvolutionExperimentEngine::evaluate(recomputed) != experiment.outcome) return false;

    const auto records = history_.for_experiment(experiment.id);
    bool evaluated = false;
    for (const auto& record : records) {
        if (record.action != EvolutionRecordAction::Evaluated) continue;
        if (record.parameter_key != experiment.proposal.key ||
            record.outcome != experiment.outcome ||
            record.baseline_fitness != experiment.baseline_fitness ||
            record.candidate_fitness != experiment.candidate_fitness ||
            record.confidence != experiment.confidence) return false;
        evaluated = true;
    }
    const auto existing = adoption_journal_.get(experiment.id);
    if (existing.has_value() &&
        existing->state != AdoptionState::Pending &&
        existing->state != AdoptionState::Adopted) return false;
    if (!adoption_journal_.stage(experiment)) return false;
    if (evaluated) return true;
    return history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Evaluated,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "replayed", {}});
}

bool EvolutionController::adopt(EvolutionExperiment& experiment) {
    // Keep the direct controller API subject to the same durable-evaluation
    // invariant as Brain-mediated adoption.
    if (!validate_adoption_for_brain(experiment)) return false;

    if (!model_.adopt(experiment.proposal)) {
        adoption_journal_.reject(experiment.id, "model_adoption_failed");
        history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Rejected,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "model_adoption_failed", {}});
        return false;
    }

    // Complete the controller-local transaction before publishing lifecycle history.
    // If either step fails, restore the exact pre-adoption model value.
    if (!adoption_journal_.commit(experiment.id, "adopted")) {
        model_.restore_previous(experiment.proposal.key);
        adoption_journal_.restore_pending(experiment.id, "adoption_commit_failed");
        return false;
    }

    if (!history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Adopted,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "adopted", {}})) {
        model_.restore_previous(experiment.proposal.key);
        adoption_journal_.restore_adopted(experiment.id, "adoption_history_failed");
        return false;
    }

    canaries_.erase(experiment.id);
    return true;
}

bool EvolutionController::validate_adoption_for_brain(const EvolutionExperiment& experiment) const noexcept {
    if (experiment.id.empty() || !experiment.candidate_executed ||
        policy_.trusted_evaluator_digest.empty() ||
        experiment.evaluator_artifact_digest != policy_.trusted_evaluator_digest) return false;

    // Adoption is permitted only when durable history contains an evaluation
    // for this exact experiment and the request still matches that evidence.
    // A staged in-memory journal record alone is not evaluation evidence.
    bool matching_evaluation = false;
    for (const auto& record : history_.for_experiment(experiment.id)) {
        if (record.action != EvolutionRecordAction::Evaluated) continue;
        if (record.parameter_key != experiment.proposal.key ||
            record.outcome != experiment.outcome ||
            record.baseline_fitness != experiment.baseline_fitness ||
            record.candidate_fitness != experiment.candidate_fitness ||
            record.confidence != experiment.confidence) return false;
        matching_evaluation = true;
    }
    if (!matching_evaluation) return false;

    EvolutionExperiment independently_evaluated = experiment;
    if (EvolutionExperimentEngine::evaluate(independently_evaluated) !=
        experiment.outcome) return false;

    const auto record = adoption_journal_.get(experiment.id);
    if (!record.has_value() || record->state != AdoptionState::Pending ||
        record->parameter_key != experiment.proposal.key ||
        record->baseline_fitness != experiment.baseline_fitness ||
        record->candidate_fitness != experiment.candidate_fitness ||
        record->confidence != experiment.confidence ||
        record->proposal_current != experiment.proposal.current ||
        record->proposal_proposed != experiment.proposal.proposed ||
        record->expected_gain != experiment.proposal.expected_gain ||
        record->proposal_confidence != experiment.proposal.confidence ||
        record->minimum_improvement != experiment.minimum_improvement ||
        record->isolated != experiment.isolated ||
        record->evaluation_procedure_id != experiment.evaluation_procedure_id ||
        record->evaluation_config_id != experiment.evaluation_config_id ||
        record->baseline_artifact_digest != experiment.baseline_artifact_digest ||
        record->candidate_artifact_digest != experiment.candidate_artifact_digest ||
        record->evaluator_artifact_digest != experiment.evaluator_artifact_digest ||
        record->baseline_trial_count != experiment.baseline_trial_count ||
        record->candidate_trial_count != experiment.candidate_trial_count ||
        record->evaluation_evidence_digest != experiment.evaluation_evidence_digest) return false;

    // Replay must validate recomputable evidence; a persisted isolated Boolean
    // never recreates the runner's in-memory attestation.
    if (!experiment.has_valid_evaluation_evidence() ||
        !EvolutionSafetyGate::approve(experiment, policy_)) return false;

    const auto evaluation = model_.evaluate(experiment.proposal);
    if (!evaluation.eligible) return false;
    const auto& policy = model_.policy();
    const double bounded_proposed =
        std::clamp(experiment.proposal.proposed, policy.parameter_minimum,
                   policy.parameter_maximum);
    return std::isfinite(bounded_proposed) &&
           bounded_proposed != experiment.proposal.current;
}

bool EvolutionController::adopt_for_brain(EvolutionExperiment& experiment) noexcept {
    if (!validate_adoption_for_brain(experiment)) return false;
    if (!adoption_journal_.stage(experiment)) return false;
    if (!model_.adopt(experiment.proposal)) {
        adoption_journal_.reject(experiment.id, "model_adoption_failed");
        return false;
    }
    if (!adoption_journal_.commit(experiment.id, "adopted")) {
        model_.restore_previous(experiment.proposal.key);
        adoption_journal_.restore_pending(experiment.id, "adoption_commit_failed");
        history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Rejected,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "adoption_commit_failed", {}});
        return false;
    }
    return true;
}

bool EvolutionController::compensate_adoption_for_brain(
    const EvolutionExperiment& experiment) noexcept {
    if (experiment.id.empty() || experiment.proposal.key.empty()) return false;
    const auto record = adoption_journal_.get(experiment.id);
    if (!record.has_value() || record->state != AdoptionState::Adopted ||
        record->parameter_key != experiment.proposal.key) return false;
    if (!model_.restore_previous(experiment.proposal.key)) return false;
    return adoption_journal_.restore_pending(experiment.id, "adoption_persistence_failed");
}

bool EvolutionController::replay_adoption(const EvolutionExperiment& experiment) noexcept {
    // Brain replay calls this after applying the proposal to the model. Recheck
    // every evidence/journal invariant here, then verify the applied value and
    // previous value instead of rerunning the pre-adoption eligibility check.
    if (experiment.id.empty() || experiment.proposal.key.empty() ||
        !experiment.candidate_executed ||
        policy_.trusted_evaluator_digest.empty() ||
        experiment.evaluator_artifact_digest != policy_.trusted_evaluator_digest ||
        !experiment.has_valid_evaluation_evidence() ||
        !EvolutionSafetyGate::approve(experiment, policy_)) return false;

    bool matching_evaluation = false;
    for (const auto& item : history_.for_experiment(experiment.id)) {
        if (item.action == EvolutionRecordAction::Rejected ||
            item.action == EvolutionRecordAction::RolledBack) return false;
        if (item.action != EvolutionRecordAction::Evaluated) continue;
        if (item.parameter_key != experiment.proposal.key ||
            item.outcome != experiment.outcome ||
            item.baseline_fitness != experiment.baseline_fitness ||
            item.candidate_fitness != experiment.candidate_fitness ||
            item.confidence != experiment.confidence) return false;
        matching_evaluation = true;
    }
    if (!matching_evaluation) return false;

    const auto record = adoption_journal_.get(experiment.id);
    if (!record.has_value() || record->state != AdoptionState::Pending ||
        record->parameter_key != experiment.proposal.key ||
        record->baseline_fitness != experiment.baseline_fitness ||
        record->candidate_fitness != experiment.candidate_fitness ||
        record->confidence != experiment.confidence ||
        record->proposal_current != experiment.proposal.current ||
        record->proposal_proposed != experiment.proposal.proposed ||
        record->expected_gain != experiment.proposal.expected_gain ||
        record->proposal_confidence != experiment.proposal.confidence ||
        record->minimum_improvement != experiment.minimum_improvement ||
        record->isolated != experiment.isolated ||
        record->evaluation_procedure_id != experiment.evaluation_procedure_id ||
        record->evaluation_config_id != experiment.evaluation_config_id ||
        record->baseline_artifact_digest != experiment.baseline_artifact_digest ||
        record->candidate_artifact_digest != experiment.candidate_artifact_digest ||
        record->evaluator_artifact_digest != experiment.evaluator_artifact_digest ||
        record->baseline_trial_count != experiment.baseline_trial_count ||
        record->candidate_trial_count != experiment.candidate_trial_count ||
        record->evaluation_evidence_digest != experiment.evaluation_evidence_digest) return false;

    const auto* parameter = model_.parameter(experiment.proposal.key);
    if (parameter == nullptr || parameter->value != experiment.proposal.proposed ||
        parameter->previous_value != experiment.proposal.current) return false;

    if (!adoption_journal_.commit(experiment.id, "replayed")) return false;
    return history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Adopted,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "replayed", {}});
}

bool EvolutionController::replay_rollback(const std::string& experiment_id,
                                           const std::string& reason) noexcept {
    if (experiment_id.empty()) return false;
    return adoption_journal_.rollback(experiment_id, reason);
}

bool EvolutionController::validate_rollback_for_brain(
    const std::string& parameter_key,
    const std::string& experiment_id) const noexcept {
    if (parameter_key.empty() || experiment_id.empty()) return false;
    const auto* parameter = model_.parameter(parameter_key);
    if (parameter == nullptr || parameter->value == parameter->baseline) return false;
    const auto record = adoption_journal_.get(experiment_id);
    return record.has_value() && record->state == AdoptionState::Adopted &&
           record->parameter_key == parameter_key;
}

bool EvolutionController::rollback_for_brain(
    const std::string& parameter_key,
    const std::string& experiment_id,
    const std::string& reason,
    double observed_delta) noexcept {
    if (!validate_rollback_for_brain(parameter_key, experiment_id)) return false;
    if (!model_.rollback(parameter_key)) return false;
    if (!adoption_journal_.rollback(experiment_id, reason)) {
        model_.restore_previous(parameter_key);
        return false;
    }
    if (!history_.append(EvolutionHistoryRecord{
        experiment_id, parameter_key, EvolutionRecordAction::RolledBack,
        ExperimentOutcome::Degraded, 0.0, observed_delta, 0.0, 0,
        reason, experiment_id})) {
        model_.restore_previous(parameter_key);
        adoption_journal_.restore_adopted(experiment_id, "rollback_history_failed");
        return false;
    }
    return true;
}

std::optional<std::string> EvolutionController::adopted_experiment_for_parameter(
    const std::string& parameter_key) const noexcept {
    if (parameter_key.empty()) return std::nullopt;
    std::optional<std::string> selected;
    std::uint64_t selected_revision = 0;
    for (const auto& record : adoption_journal_.records()) {
        if (record.parameter_key == parameter_key && record.state == AdoptionState::Adopted &&
            record.revision >= selected_revision) {
            selected = record.experiment_id;
            selected_revision = record.revision;
        }
    }
    return selected;
}

CanaryDecision EvolutionController::preview_canary_for_brain(
    const std::string& experiment_id, const CanaryObservation& observation) const noexcept {
    if (experiment_id.empty()) return CanaryDecision{false, false, 0.0, 0.0, "experiment_required"};
    const auto it = canaries_.find(experiment_id);
    if (it == canaries_.end()) return EvolutionCanary{}.preview(observation);
    return it->second.preview(observation);
}

CanaryDecision EvolutionController::observe_canary_for_brain(
    const std::string& experiment_id, const CanaryObservation& observation) noexcept {
    if (experiment_id.empty()) return {false, false, 0.0, 0.0, "experiment_required"};
    return canaries_[experiment_id].observe(observation);
}

CanaryDecision EvolutionController::observe_canary(const std::string& parameter_key,
                                                   const std::string& experiment_id,
                                                   const CanaryObservation& observation) {
    const auto decision = observe_canary_for_brain(experiment_id, observation);
    if (EvolutionRollback::should_rollback(decision)) {
        rollback(parameter_key, experiment_id, decision.reason, decision.mean_delta);
    }
    return decision;
}

bool EvolutionController::rollback(const std::string& parameter_key,
                                    const std::string& experiment_id,
                                    const std::string& reason,
                                    double observed_delta) {
    if (!rollback_for_brain(parameter_key, experiment_id, reason, observed_delta)) return false;
    canaries_.erase(experiment_id);
    return true;
}

} // namespace jarvis::core
