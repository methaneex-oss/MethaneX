#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include <string>

namespace jarvis::core {

struct EvolutionSafetyPolicy {
    double minimum_confidence{0.90};
    double maximum_regression{0.0};
    bool require_isolation{true};
    bool require_finite_fitness{true};
    // Must be provisioned by trusted local configuration and supplied again on replay.
    std::string trusted_evaluator_digest;
};

class EvolutionSafetyGate {
public:
    static bool approve(const EvolutionExperiment& experiment,
                        const EvolutionSafetyPolicy& policy) noexcept;
};

} // namespace jarvis::core
