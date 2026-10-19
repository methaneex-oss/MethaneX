#pragma once

#include "jarvis/core/evolution_adoption.hpp"
#include "jarvis/core/evolution_adoption_journal.hpp"
#include "jarvis/core/evolution_canary.hpp"
#include "jarvis/core/evolution_history.hpp"

namespace jarvis::core {

class EvolutionController {
public:
    EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                        EvolutionSafetyPolicy policy = {});

    bool record_evaluation(const EvolutionExperiment& experiment);
    bool adopt(EvolutionExperiment& experiment);
    CanaryDecision observe_canary(const std::string& parameter_key,
                                  const std::string& experiment_id,
                                  const CanaryObservation& observation);
    bool rollback(const std::string& parameter_key, const std::string& experiment_id,
                  const std::string& reason = "manual_rollback",
                  double observed_delta = 0.0);
    std::size_t canary_minimum_observations() const noexcept {
        return canary_.minimum_observations();
    }
    const EvolutionAdoptionJournal& adoption_journal() const noexcept { return adoption_journal_; }

private:
    EvolutionModel& model_;
    EvolutionHistory& history_;
    EvolutionSafetyPolicy policy_;
    EvolutionCanary canary_;
    EvolutionAdoptionJournal adoption_journal_;
};

} // namespace jarvis::core
