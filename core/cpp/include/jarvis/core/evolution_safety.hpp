#pragma once

#include "jarvis/core/evolution_experiment.hpp"

namespace jarvis::core {

struct EvolutionSafetyPolicy {
    double minimum_confidence{0.90};
    double maximum_regression{0.0};
    bool require_isolation{true};
    // Explicitly test-only escape hatch for simulated callback fixtures.
    // Production callers must leave this false; simulation evidence cannot
    // authorize adoption unless both flags are deliberately set.
    bool allow_simulated_evidence{false};
    bool require_finite_fitness{true};
};

class EvolutionSafetyGate {
public:
    static bool approve(const EvolutionExperiment& experiment,
                        const EvolutionSafetyPolicy& policy) noexcept;
};

} // namespace jarvis::core
