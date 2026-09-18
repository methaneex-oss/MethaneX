#include "jarvis/core/evolution_scheduler.hpp"

namespace jarvis::core {

EvolutionScheduler::EvolutionScheduler(EvolutionSchedulePolicy policy) : policy_(policy) {}

EvolutionScheduleDecision EvolutionScheduler::evaluate(
    std::chrono::steady_clock::time_point now,
    std::chrono::steady_clock::time_point last_run,
    bool system_idle) const noexcept {
    if (policy_.max_trials_per_cycle == 0) return {false, "trial_budget_exhausted", 0};
    if (policy_.require_idle_system && !system_idle) return {false, "system_not_idle", 0};
    if (now < last_run || now - last_run < policy_.minimum_interval)
        return {false, "minimum_interval_not_elapsed", 0};
    return {true, "scheduled", policy_.max_trials_per_cycle};
}

} // namespace jarvis::core
