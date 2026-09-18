#pragma once

#include "jarvis/core/evolution_candidate_generator.hpp"
#include "jarvis/core/evolution_experiment_coordinator.hpp"
#include "jarvis/core/evolution_scheduler.hpp"
#include "jarvis/core/evolution_strategy.hpp"

#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

struct EvolutionOrchestrationResult {
    EvolutionScheduleDecision schedule;
    std::vector<EvolutionExperiment> experiments;
};

class EvolutionOrchestrator {
public:
    explicit EvolutionOrchestrator(EvolutionSchedulePolicy policy = {});

    EvolutionOrchestrationResult run(
        const EvolutionOpportunity& opportunity,
        const EvolutionCandidateGenerator& generator,
        const EvolutionSandbox& sandbox,
        const CandidateExecutor& baseline_executor,
        const CandidateExecutor& candidate_executor,
        const EvolutionHistory& history,
        std::chrono::steady_clock::time_point now,
        std::chrono::steady_clock::time_point last_run,
        bool system_idle) const noexcept;

private:
    EvolutionScheduler scheduler_;
    EvolutionTrialConfig trial_config_{};
};

} // namespace jarvis::core
