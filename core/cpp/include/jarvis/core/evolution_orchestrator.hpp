#pragma once

#include "jarvis/core/evolution_candidate_generator.hpp"
#include "jarvis/core/evolution_controller.hpp"
#include "jarvis/core/evolution_experiment_coordinator.hpp"
#include "jarvis/core/evolution_scheduler.hpp"
#include "jarvis/core/evolution_strategy.hpp"

#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

enum class EvolutionLifecycleState {
    Scheduled,
    CandidateEvaluated,
    SafetyRejected,
    Canarying,
    Retained,
    Adopted,
    RolledBack,
    Superseded,
    EvaluationRejected
};

struct EvolutionOrchestrationResult {
    EvolutionScheduleDecision schedule;
    std::vector<EvolutionExperiment> experiments;
    std::vector<EvolutionLifecycleState> lifecycle;
    std::size_t adopted{0};
    std::size_t rejected{0};
};

class EvolutionOrchestrator {
public:
    explicit EvolutionOrchestrator(EvolutionSchedulePolicy policy = {},
                                   EvolutionTrialConfig trial_config = {});

    EvolutionOrchestrationResult run(
        const EvolutionOpportunity& opportunity,
        const EvolutionCandidateGenerator& generator,
        const EvolutionSandbox& sandbox,
        const CandidateExecutor& baseline_executor,
        const CandidateExecutor& candidate_executor,
        const EvolutionHistory& history,
        std::chrono::steady_clock::time_point now,
        std::chrono::steady_clock::time_point last_run,
        bool system_idle,
        EvolutionController* controller = nullptr) const noexcept;

    // Production route: baseline and candidate trials use the pinned local
    // evaluator and enforced process isolation; callback simulation is separate.
    EvolutionOrchestrationResult run_isolated(
        const EvolutionOpportunity& opportunity,
        const EvolutionCandidateGenerator& generator,
        const ProcessIsolationBackend& backend,
        const IsolatedEvaluationProcedure& procedure,
        const EvolutionHistory& history,
        std::chrono::steady_clock::time_point now,
        std::chrono::steady_clock::time_point last_run,
        bool system_idle,
        EvolutionController* controller = nullptr) const noexcept;

private:
    EvolutionScheduler scheduler_;
    EvolutionTrialConfig trial_config_{};
};

} // namespace jarvis::core
