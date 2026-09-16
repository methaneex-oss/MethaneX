#pragma once

#include "jarvis/core/evolution_experiment.hpp"

#include <cstddef>
#include <functional>

namespace jarvis::core {

struct EvolutionTrialStatistics {
    double mean{0.0};
    double variance{0.0};
    std::size_t trials{0};
};

struct EvolutionExperimentRun {
    EvolutionTrialStatistics baseline;
    EvolutionTrialStatistics candidate;
    double improvement{0.0};
    double confidence{0.0};
    ExperimentOutcome outcome{ExperimentOutcome::Invalid};
};

class EvolutionExperimentRunner {
public:
    using FitnessEvaluator = std::function<double(double parameter)>;

    static EvolutionExperimentRun run(const EvolutionExperiment& experiment,
                                       FitnessEvaluator baseline_evaluator,
                                       FitnessEvaluator candidate_evaluator,
                                       std::size_t trials = 3) noexcept;
};

} // namespace jarvis::core
