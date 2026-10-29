#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/process_isolation.hpp"
#include "jarvis/core/evolution_trials.hpp"

#include <cstddef>
#include <string>

namespace jarvis::core {

// A trusted local evaluator is invoked identically for baseline and candidate.
// It must emit one tab-delimited JARVIS_EVAL_V1 record echoing all identity
// arguments supplied by the runner plus the measured fitness.
struct IsolatedEvaluationProcedure {
    IsolatedCommand command;
    std::string procedure_id;
    std::string configuration_id;
    std::string baseline_artifact_path;
    std::string candidate_artifact_path;
    // Supplied by trusted local configuration, not derived from evaluator output.
    // The runner refuses to execute an evaluator whose bytes do not match it.
    std::string expected_evaluator_digest;
};

class EvolutionExperimentRunner {
public:
    static ExperimentOutcome run(EvolutionExperiment& experiment,
                                 const EvolutionSandbox& sandbox,
                                 const CandidateExecutor& executor) noexcept;

    // Legacy numeric-only command execution is deliberately non-authoritative:
    // it cannot create evidence accepted for adoption.
    static ExperimentOutcome run_isolated_command(
        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
        const IsolatedCommand& command) noexcept;

    // Measures baseline and candidate repeatedly through one identity-bound,
    // local C++ evaluation procedure. Arbitrary numeric stdout is rejected.
    static ExperimentOutcome run_isolated_evaluation(
        EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
        const IsolatedEvaluationProcedure& procedure,
        std::size_t baseline_trials, std::size_t candidate_trials,
        double minimum_confidence,
        TrialStatistics* baseline_summary = nullptr,
        TrialStatistics* candidate_summary = nullptr) noexcept;
};

} // namespace jarvis::core
