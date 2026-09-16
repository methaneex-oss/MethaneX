#pragma once

#include "jarvis/core/evolution.hpp"

#include <string>

namespace jarvis::core {

enum class ExperimentOutcome { Pending, Improved, Neutral, Degraded, Invalid };

struct EvolutionExperiment {
    std::string id;
    EvolutionProposal proposal;
    double baseline_fitness{0.0};
    double candidate_fitness{0.0};
    double minimum_improvement{0.0};
    double confidence{0.0};
    ExperimentOutcome outcome{ExperimentOutcome::Pending};
};

class EvolutionExperimentEngine {
public:
    static ExperimentOutcome evaluate(EvolutionExperiment& experiment) noexcept;
};

} // namespace jarvis::core
