#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/process_isolation.hpp"\n\n#include <vector>

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
        const IsolatedCommand& command) noexcept;\n\n    // Evaluate the current and proposed scalar parameter against the same\n    // held-out experience using the repository-owned native evaluator worker.\n    static ExperimentOutcome run_isolated_evaluation(\n        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,\n        const std::vector<EvolutionFitnessCase>& cases,\n        double minimum_confidence = 0.0) noexcept;\n\n    // Replay must rerun the evaluator; a persisted isolated Boolean is not proof.\n    static bool revalidate_isolated_evaluation(\n        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend) noexcept;
};

} // namespace jarvis::core
