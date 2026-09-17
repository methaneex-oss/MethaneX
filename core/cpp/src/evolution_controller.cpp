#include "jarvis/core/evolution_controller.hpp"

namespace jarvis::core {

EvolutionController::EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                                         EvolutionSafetyPolicy policy)
    : model_(model), history_(history), policy_(policy) {}

bool EvolutionController::record_evaluation(const EvolutionExperiment& experiment) {
    return history_.append(EvolutionHistoryRecord{
        experiment.id,
        experiment.proposal.key,
        EvolutionRecordAction::Evaluated,
        experiment.outcome,
        experiment.baseline_fitness,
        experiment.candidate_fitness,
        experiment.confidence,
        0});
}

bool EvolutionController::adopt(EvolutionExperiment& experiment) {
    if (!experiment.candidate_executed) return false;
    if (!EvolutionSafetyGate::approve(experiment, policy_)) {
        history_.append(EvolutionHistoryRecord{experiment.id, experiment.proposal.key,
            EvolutionRecordAction::Rejected, experiment.outcome,
            experiment.baseline_fitness, experiment.candidate_fitness,
            experiment.confidence, 0});
        return false;
    }

    if (!model_.adopt(experiment.proposal)) return false;
    history_.append(EvolutionHistoryRecord{experiment.id, experiment.proposal.key,
        EvolutionRecordAction::Adopted, experiment.outcome,
        experiment.baseline_fitness, experiment.candidate_fitness,
        experiment.confidence, 0});
    return true;
}

bool EvolutionController::rollback(const std::string& parameter_key, const std::string& experiment_id) {
    if (!model_.rollback(parameter_key)) return false;
    return history_.append(EvolutionHistoryRecord{
        experiment_id, parameter_key, EvolutionRecordAction::RolledBack,
        ExperimentOutcome::Degraded, 0.0, 0.0, 0.0, 0});
}

} // namespace jarvis::core
