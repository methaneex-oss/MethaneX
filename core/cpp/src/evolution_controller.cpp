#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_rollback.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

EvolutionController::EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                                         EvolutionSafetyPolicy policy)
    : model_(model), history_(history), policy_(policy), canaries_{}, adoption_journal_{} {}

bool EvolutionController::record_evaluation(const EvolutionExperiment& experiment) {
    const bool staged = adoption_journal_.stage(experiment);
    const bool recorded = history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Evaluated,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "evaluation", {}});
    if (staged && !recorded) {
        adoption_journal_.reject(experiment.id, "evaluation_history_failed");
    }
    return staged && recorded;
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
        adoption_journal_.get(experiment.id).has_value()) {
        return false;
    }
    return true;
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
    adoption_journal_.reject(experiment.id, "evaluation_history_failed");
    return false;
}

bool EvolutionController::replay_evaluation(
    const EvolutionExperiment& experiment) noexcept {
    if (experiment.id.empty() || experiment.proposal.key.empty()) return false;
    const auto records = history_.for_experiment(experiment.id);
    for (const auto& record : records) {
        if (record.action == EvolutionRecordAction::Evaluated) return true;
    }
    if (!adoption_journal_.stage(experiment)) return false;
    return history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Evaluated,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "replayed", {}});
}

bool EvolutionController::adopt(EvolutionExperiment& experiment) {
    if (!experiment.candidate_executed) return false;
    if (!adoption_journal_.stage(experiment)) return false;
    if (!EvolutionSafetyGate::approve(experiment, policy_)) {
        adoption_journal_.reject(experiment.id, "safety_gate_rejected");
        history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Rejected,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "safety_gate_rejected", {}});
        return false;
    }
    if (!model_.adopt(experiment.proposal)) {
        adoption_journal_.reject(experiment.id, "model_adoption_failed");
        return false;
    }
    if (!adoption_journal_.commit(experiment.id, "adopted")) {
        model_.rollback(experiment.proposal.key);
        adoption_journal_.reject(experiment.id, "adoption_commit_failed");
        return false;
    }

    const bool recorded = history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Adopted,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "adopted", {}});
    if (!recorded) {
        model_.rollback(experiment.proposal.key);
        adoption_journal_.rollback(experiment.id, "adoption_history_failed");
        return false;
    }

    canaries_.erase(experiment.id);
    return true;
}

bool EvolutionController::validate_adoption_for_brain(const EvolutionExperiment& experiment) const noexcept {
    if (experiment.id.empty() || !experiment.candidate_executed ||
        !EvolutionSafetyGate::approve(experiment, policy_)) return false;
    if (const auto record = adoption_journal_.get(experiment.id);
        record.has_value() && record->state != AdoptionState::Pending) return false;
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
    if (!model_.adopt(experiment.proposal)) return false;
    if (!adoption_journal_.commit(experiment.id, "adopted")) {
        model_.rollback(experiment.proposal.key);
        adoption_journal_.reject(experiment.id, "adoption_commit_failed");
        return false;
    }
    return true;
}

bool EvolutionController::replay_adoption(const EvolutionExperiment& experiment) noexcept {
    if (experiment.id.empty() || !adoption_journal_.stage(experiment)) return false;
    return adoption_journal_.commit(experiment.id, "replayed");
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
    if (!adoption_journal_.rollback(experiment_id, reason)) return false;
    return history_.append(EvolutionHistoryRecord{
        experiment_id, parameter_key, EvolutionRecordAction::RolledBack,
        ExperimentOutcome::Degraded, 0.0, observed_delta, 0.0, 0,
        reason, experiment_id});
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
    if (!model_.rollback(parameter_key)) return false;
    const bool journaled = adoption_journal_.rollback(experiment_id, reason);
    const bool recorded = history_.append(EvolutionHistoryRecord{
        experiment_id, parameter_key, EvolutionRecordAction::RolledBack,
        ExperimentOutcome::Degraded, 0.0, observed_delta, 0.0, 0,
        reason, experiment_id});
    if (journaled && recorded) canaries_.erase(experiment_id);
    return journaled && recorded;
}

} // namespace jarvis::core
