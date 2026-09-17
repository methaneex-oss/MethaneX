#include "jarvis/core/evolution_adoption.hpp"

namespace jarvis::core {

bool EvolutionAdoption::adopt(EvolutionModel& model,
                              const EvolutionExperiment& experiment,
                              const EvolutionSafetyPolicy& policy) noexcept {
    if (!experiment.candidate_executed) return false;
    if (!EvolutionSafetyGate::approve(experiment, policy)) return false;
    return model.adopt(experiment.proposal);
}

} // namespace jarvis::core
