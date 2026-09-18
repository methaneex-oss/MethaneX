#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_rollback.hpp"

namespace jarvis::core {

EvolutionController::EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                                         EvolutionSafetyPolicy policy)
    : model_(model), history_(history), policy_(policy), canary_{} {}

bool EvolutionController::record_evaluation(const EvolutionExperiment& experiment) {
    return history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Evaluated,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "evaluation", {}});
}

bool EvolutionController::adopt(EvolutionExperiment& experiment) {
    if (!experiment.candidate_executed) return false;
    if (!EvolutionSafetyGate::approve(experiment, policy_)) {
        history_.append(EvolutionHistoryRecord{
            experiment.id, experiment.proposal.key, EvolutionRecordAction::Rejected,
            experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0, "safety_gate_rejected", {}});
        return false;
    }
    if (!model_.adopt(experiment.proposal)) return false;
    canary_.reset();
    canary_.observe(CanaryObservation{experiment.baseline_fitness, experiment.candidate_fitness});
    return history_.append(EvolutionHistoryRecord{
        experiment.id, experiment.proposal.key, EvolutionRecordAction::Adopted,
        experiment.outcome, experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0, "adopted", {}});
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
    return history_.append(EvolutionHistoryRecord{
        experiment_id, parameter_key, EvolutionRecordAction::RolledBack,
        ExperimentOutcome::Degraded, 0.0, observed_delta, 0.0, 0,
        reason, experiment_id});
}

} // namespace jarvis::core
