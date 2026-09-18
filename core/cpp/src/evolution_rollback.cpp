#include "jarvis/core/evolution_rollback.hpp"

#include <cmath>

namespace jarvis::core {

bool EvolutionRollback::should_rollback(const CanaryDecision& decision) noexcept {
    return decision.sufficient_evidence && decision.rollback;
}

bool EvolutionRollback::record(EvolutionHistory& history, const RollbackRecord& rollback) {
    if (rollback.experiment_id.empty() || rollback.parameter_key.empty() || rollback.reason.empty() ||
        !std::isfinite(rollback.observed_delta)) return false;

    return history.append(EvolutionHistoryRecord{
        rollback.experiment_id,
        rollback.parameter_key,
        EvolutionRecordAction::RolledBack,
        ExperimentOutcome::Degraded,
        0.0,
        rollback.observed_delta,
        0.0,
        0});
}

} // namespace jarvis::core
