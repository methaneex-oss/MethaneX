#pragma once

#include "jarvis/core/evolution.hpp"

#include <string>

namespace jarvis::core {

enum class ExperimentOutcome { Pending, Improved, Neutral, Degraded, Invalid };

class EvolutionExperimentRunner;
class EvolutionController;
class Brain;

struct EvolutionExperiment {
    EvolutionExperiment() = default;
    EvolutionExperiment(std::string experiment_id, EvolutionProposal candidate,
                        double baseline = 0.0, double measured_candidate = 0.0,
                        double required_improvement = 0.0, double measured_confidence = 0.0,
                        ExperimentOutcome measured_outcome = ExperimentOutcome::Pending,
                        bool executed = false)
        : id(std::move(experiment_id)), proposal(std::move(candidate)),
          baseline_fitness(baseline), candidate_fitness(measured_candidate),
          minimum_improvement(required_improvement), confidence(measured_confidence),
          outcome(measured_outcome), candidate_executed(executed) {}

    std::string id;
    EvolutionProposal proposal;
    double baseline_fitness{0.0};
    double candidate_fitness{0.0};
    double minimum_improvement{0.0};
    double confidence{0.0};
    ExperimentOutcome outcome{ExperimentOutcome::Pending};
    bool candidate_executed{false};
    bool isolation_verified() const noexcept { return isolation_attested_; }

private:
    // Only the sandbox runner can mint this process-local attestation. A caller
    // cannot turn a hand-constructed experiment into isolated evidence by
    // setting a public Boolean.
    bool isolation_attested_{false};
    friend class EvolutionExperimentRunner;
    friend class EvolutionController;
    friend class Brain;
};

class EvolutionExperimentEngine {
public:
    static ExperimentOutcome evaluate(EvolutionExperiment& experiment) noexcept;
};

} // namespace jarvis::core
