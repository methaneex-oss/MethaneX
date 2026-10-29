#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/process_isolation.hpp"

#include <vector>

namespace jarvis::core {

class EvolutionExperimentRunner {
public:
    // Register evaluator identity at trusted application startup. Runtime
    // requests and journal records cannot establish trust by supplying a hash.
    // The digest binds executable identity; authorization comes from this local
    // registry, not from a digest supplied by an untrusted request or journal.
    static bool register_trusted_evaluator(const std::string& procedure_id,
                                           const std::string& executable,
                                           const std::vector<std::string>& procedure_arguments = {}) noexcept;
    static bool is_trusted_evaluator(const std::string& procedure_id,
                                     const std::string& executable,
                                     const std::string& expected_fingerprint) noexcept;
    static bool is_trusted_evaluator(const std::string& procedure_id,
                                     const std::string& executable,
                                     const std::string& expected_fingerprint,
                                     const std::vector<std::string>& procedure_arguments) noexcept;
    static bool restore_trusted_attestation(EvolutionExperiment& experiment) noexcept;
    static std::string executable_fingerprint(const std::string& executable) noexcept;
    static ExperimentOutcome run(EvolutionExperiment& experiment,
                                 const EvolutionSandbox& sandbox,
                                 const CandidateExecutor& executor) noexcept;

    // Executes the pre-registered local evaluator twice in the process-isolation
    // backend. Each response must identify the exact experiment, parameter value,
    // role, procedure, evaluator binary fingerprint, artifact fingerprint, and
    // finite measured fitness. A numeric-only response is rejected.
    static ExperimentOutcome run_isolated_command(
        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
        const IsolatedCommand& command) noexcept;
};

} // namespace jarvis::core
