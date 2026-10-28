#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/process_isolation.hpp"

namespace jarvis::core {

class EvolutionExperimentRunner {
public:
    static ExperimentOutcome run(EvolutionExperiment& experiment,
                                 const EvolutionSandbox& sandbox,
                                 const CandidateExecutor& executor) noexcept;

    // Executes the candidate command in the local process-isolation backend.
    // Standard output must contain one finite numeric fitness value.
    static ExperimentOutcome run_isolated_command(
        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
        const IsolatedCommand& command) noexcept;
};

} // namespace jarvis::core
