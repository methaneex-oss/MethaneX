#pragma once

#include "jarvis/core/evolution.hpp"
#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_safety.hpp"

namespace jarvis::core {

class EvolutionAdoption {
public:
    static bool adopt(EvolutionModel& model,
                      const EvolutionExperiment& experiment,
                      const EvolutionSafetyPolicy& policy) noexcept;
};

} // namespace jarvis::core
