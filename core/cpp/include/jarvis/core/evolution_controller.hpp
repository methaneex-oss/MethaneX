#pragma once

#include "jarvis/core/evolution_adoption.hpp"
#include "jarvis/core/evolution_adoption_journal.hpp"
#include "jarvis/core/evolution_canary.hpp"
#include "jarvis/core/evolution_history.hpp"

#include <unordered_map>

namespace jarvis::core {

class EvolutionController {
public:
    EvolutionController(EvolutionModel& model, EvolutionHistory& history,
                        EvolutionSafetyPolicy policy = {});

    bool record_evaluation(const EvolutionExperiment& experiment);
    bool validate_evaluation_for_brain(const EvolutionExperiment& experiment) const noexcept;
    bool record_evaluation_for_brain(const EvolutionExperiment& experiment) noexcept;
    bool replay_evaluation(const EvolutionExperiment& experiment) noexcept;
    bool adopt(EvolutionExperiment& experiment);
    CanaryDecision observe_canary(const std::string& parameter_key,
                                  const std::string& experiment_id,
                                  const CanaryObservation& observation);
    CanaryDecision preview_canary_for_brain(const std::string& experiment_id,
                                             const CanaryObservation& observation) const noexcept;
    CanaryDecision observe_canary_for_brain(const std::string& experiment_id,
                                            const CanaryObservation& observation) noexcept;
    bool validate_adoption_for_brain(const EvolutionExperiment& experiment) const noexcept;
    bool adopt_for_brain(EvolutionExperiment& experiment) noexcept;
    bool replay_adoption(const EvolutionExperiment& experiment) noexcept;
    bool replay_rollback(const std::string& experiment_id, const std::string& reason) noexcept;
    bool rollback(const std::string& parameter_key, const std::string& experiment_id,
                  const std::string& reason = "manual_rollback",
                  double observed_delta = 0.0);
    const EvolutionAdoptionJournal& adoption_journal() const noexcept { return adoption_journal_; }

private:
    EvolutionModel& model_;
    EvolutionHistory& history_;
    EvolutionSafetyPolicy policy_;
    std::unordered_map<std::string, EvolutionCanary> canaries_;
    EvolutionAdoptionJournal adoption_journal_;
};

} // namespace jarvis::core
