#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/process_isolation.hpp"

namespace jarvis::core {

class EvolutionExperimentRunner {
public:
    // The application registers evaluator binaries during trusted startup.
    // Runtime requests and replay records cannot establish trust by supplying
    // their own executable fingerprint.
    static bool register_trusted_evaluator(const std::string& procedure_id,
                                           const std::string& executable) noexcept;
    static bool is_trusted_evaluator(const std::string& procedure_id,
                                     const std::string& executable,
                                     const std::string& expected_fingerprint) noexcept;
    static bool restore_trusted_attestation(EvolutionExperiment& experiment) noexcept;
    static std::string executable_fingerprint(const std::string& executable) noexcept;
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
