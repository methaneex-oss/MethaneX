#include "jarvis/core/evolution_adoption.hpp"

namespace jarvis::core {

bool EvolutionAdoption::adopt(EvolutionModel& model,
                              const EvolutionExperiment& experiment,
                              const EvolutionSafetyPolicy& policy) noexcept {
    // This low-level helper has no evaluation journal and therefore cannot
    // establish that the proposal matches a recorded experiment. Keep it
    // fail-closed; use EvolutionController after recording sandbox evidence.
    (void)model;
    (void)experiment;
    (void)policy;
    return false;
}

} // namespace jarvis::core
