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
    double confidence_interval_low{0.0};
    double confidence_interval_high{0.0};
    double effect_size{0.0};
    ExperimentOutcome outcome{ExperimentOutcome::Pending};
    bool candidate_executed{false};
};

class EvolutionExperimentEngine {
public:
    static ExperimentOutcome evaluate(EvolutionExperiment& experiment) noexcept;
};

} // namespace jarvis::core
