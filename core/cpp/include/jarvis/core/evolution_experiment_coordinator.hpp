#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/evolution_trials.hpp"
#include "jarvis/core/process_isolation.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

struct EvolutionTrialConfig {
    std::size_t baseline_trials{4};
    std::size_t candidate_trials{4};
    double minimum_improvement{0.01};
    double minimum_confidence{0.75};
    // False is for controlled simulation/testing only; adoption safety policy
    // still independently decides whether non-isolated evidence is admissible.
    bool require_isolation{true};
};

struct EvolutionTrialBatch {
    TrialStatistics baseline;
    TrialStatistics candidate;
    bool executed{false};
    ExperimentOutcome outcome{ExperimentOutcome::Invalid};
};

class EvolutionExperimentCoordinator {
public:
    static EvolutionTrialBatch run_isolated(
        EvolutionExperiment& experiment,
        const ProcessIsolationBackend& backend,
        const std::string& procedure_id,
        const LocalFitnessProcedure& procedure,
        EvolutionTrialConfig config = {}) noexcept;

    static EvolutionTrialBatch run(EvolutionExperiment& experiment,
                                   const EvolutionSandbox& sandbox,
                                   const CandidateExecutor& baseline_executor,
                                   const CandidateExecutor& candidate_executor,
                                   EvolutionTrialConfig config = {}) noexcept;
};

} // namespace jarvis::core
