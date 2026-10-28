#include "jarvis/core/evolution_adoption.hpp"

namespace jarvis::core {

bool EvolutionAdoption::adopt(EvolutionModel& model,
                              const EvolutionExperiment& experiment,
                              const EvolutionSafetyPolicy& policy) noexcept {
    // This stateless helper cannot verify durable, matching evaluation history.
    // Fail closed; adoption must go through EvolutionController.
    (void)model;
    (void)experiment;
    (void)policy;
    return false;
}

} // namespace jarvis::core
