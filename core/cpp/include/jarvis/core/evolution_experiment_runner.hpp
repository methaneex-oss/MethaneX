#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/process_isolation.hpp"
#include "jarvis/core/evolution_trials.hpp"

namespace jarvis::core {

class EvolutionExperimentRunner {
public:
    static ExperimentOutcome run(EvolutionExperiment& experiment,
                                 const EvolutionSandbox& sandbox,
                                 const CandidateExecutor& executor) noexcept;

    // Runs the same repository-owned C++ fitness procedure against baseline and\n    // candidate values in isolated child processes. A non-empty stable procedure\n    // ID is required so persisted evidence identifies the measurement method.\n    static ExperimentOutcome run_isolated_evaluator(\n        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,\n        const std::string& procedure_id, const LocalFitnessProcedure& procedure,\n        std::size_t baseline_trials = 4, std::size_t candidate_trials = 4,\n        double minimum_confidence = 0.75) noexcept;\n\n    // Legacy command execution is diagnostic only; command output alone is not\n    // trusted evaluation evidence and cannot authorize adoption.\n    // Executes the candidate command in the local process-isolation backend.
    // Standard output must contain one finite numeric fitness value.
    static ExperimentOutcome run_isolated_command(
        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
        const IsolatedCommand& command) noexcept;
};

} // namespace jarvis::core
