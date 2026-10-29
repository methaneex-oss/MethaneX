#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_sandbox.hpp"
#include "jarvis/core/evolution_trials.hpp"\n#include "jarvis/core/process_isolation.hpp"

#include <cstddef>
#include <vector>

namespace jarvis::core {

struct EvolutionTrialConfig {
    std::size_t baseline_trials{4};
    std::size_t candidate_trials{4};
    double minimum_improvement{0.01};
    double minimum_confidence{0.75};
    // False is for controlled simulation/testing only; adoption safety policy
    // still independently decides whether non-isolated evidence is admissible.
    bool require_isolation{true};\n    // Production mode requires real held-out experience. Callback executors\n    // are simulation-only and are ignored while isolation is required.\n    std::vector<EvolutionFitnessCase> evaluation_cases;
};

struct EvolutionTrialBatch {
    TrialStatistics baseline;
    TrialStatistics candidate;
    bool executed{false};
    ExperimentOutcome outcome{ExperimentOutcome::Invalid};
};

class EvolutionExperimentCoordinator {
public:
    static EvolutionTrialBatch run(EvolutionExperiment& experiment,
                                   const EvolutionSandbox& sandbox,
                                   const CandidateExecutor& baseline_executor,
                                   const CandidateExecutor& candidate_executor,
                                   EvolutionTrialConfig config = {}) noexcept;
};

} // namespace jarvis::core
