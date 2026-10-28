#pragma once

#include "jarvis/core/evolution.hpp"

#include <string>
#include <utility>

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
    bool isolation_verified() const noexcept {
        return isolation_attested_ && attested_id_ == id &&
               attested_proposal_.key == proposal.key &&
               attested_proposal_.current == proposal.current &&
               attested_proposal_.proposed == proposal.proposed &&
               attested_proposal_.expected_gain == proposal.expected_gain &&
               attested_proposal_.confidence == proposal.confidence &&
               attested_baseline_fitness_ == baseline_fitness &&
               attested_candidate_fitness_ == candidate_fitness &&
               attested_minimum_improvement_ == minimum_improvement &&
               attested_confidence_ == confidence &&
               attested_outcome_ == outcome &&
               attested_candidate_executed_ == candidate_executed;
    }

private:
    // The runner snapshots every adoption-relevant field after a successful
    // isolated run. Mutating public experiment fields invalidates the evidence.
    void attest_current_evaluation() noexcept {
        attested_id_ = id;
        attested_proposal_ = proposal;
        attested_baseline_fitness_ = baseline_fitness;
        attested_candidate_fitness_ = candidate_fitness;
        attested_minimum_improvement_ = minimum_improvement;
        attested_confidence_ = confidence;
        attested_outcome_ = outcome;
        attested_candidate_executed_ = candidate_executed;
        isolation_attested_ = true;
    }
    bool isolation_attested_{false};
    std::string attested_id_;
    EvolutionProposal attested_proposal_{};
    double attested_baseline_fitness_{0.0};
    double attested_candidate_fitness_{0.0};
    double attested_minimum_improvement_{0.0};
    double attested_confidence_{0.0};
    ExperimentOutcome attested_outcome_{ExperimentOutcome::Pending};
    bool attested_candidate_executed_{false};
    friend class EvolutionExperimentRunner;
    friend class EvolutionController;
    friend class Brain;
};

class EvolutionExperimentEngine {
public:
    static ExperimentOutcome evaluate(EvolutionExperiment& experiment) noexcept;
};

} // namespace jarvis::core
