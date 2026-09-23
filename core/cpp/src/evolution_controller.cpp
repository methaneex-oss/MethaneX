#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_rollback.hpp"

namespace jarvis::core {

EvolutionController::EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                                         EvolutionSafetyPolicy policy)
    : model_(model), history_(history), policy_(policy), canary_{}, adoption_journal_{} {}

bool EvolutionController::record_evaluation(const EvolutionExperiment& experiment) {
    if (!adoption_journal_.stage(experiment)) return false;
    const bool recorded = history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Evaluated,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "evaluation", {}});
    if (!recorded) {
        adoption_journal_.reject(experiment.id, "evaluation_record_failed");
        return false;
    }
    return true;
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
        history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Rejected,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "model_adoption_failed", {}});
        return false;
    }

    if (!adoption_journal_.commit(experiment.id, "adopted")) {
        const bool model_rolled_back = model_.rollback(experiment.proposal.key);
        adoption_journal_.reject(experiment.id, "adoption_commit_failed");
        history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Rejected,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0,
            model_rolled_back ? "adoption_commit_failed" : "adoption_commit_failed_model_rollback_failed",
            {}});
        return false;
    }

    canary_.reset();
    canary_.observe(CanaryObservation{
        experiment.baseline_fitness, experiment.candidate_fitness});

    const bool recorded = history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Adopted,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "adopted", {}});
    if (!recorded) {
        const bool model_rolled_back = model_.rollback(experiment.proposal.key);
        const bool journal_rolled_back = adoption_journal_.rollback(
            experiment.id, "adoption_history_commit_failed");
        return model_rolled_back && journal_rolled_back;
    }

    return true;
}

CanaryDecision EvolutionController::observe_canary(const std::string& parameter_key,
                                                   const std::string& experiment_id,
                                                   const CanaryObservation& observation) {
    const auto decision = canary_.observe(observation);
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
    return journaled && recorded;
}

} // namespace jarvis::core
