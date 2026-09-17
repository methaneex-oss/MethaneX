#pragma once

#include "jarvis/core/evolution_adoption.hpp"
#include "jarvis/core/evolution_history.hpp"

namespace jarvis::core {

class EvolutionController {
public:
    EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                        EvolutionSafetyPolicy policy = {});

    bool record_evaluation(const EvolutionExperiment& experiment);
    bool adopt(EvolutionExperiment& experiment);
    bool rollback(const std::string& parameter_key, const std::string& experiment_id);

private:
    EvolutionModel& model_;
    EvolutionHistory& history_;
    EvolutionSafetyPolicy policy_;
};

} // namespace jarvis::core
