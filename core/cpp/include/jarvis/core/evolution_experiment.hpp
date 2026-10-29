#pragma once

#include "jarvis/core/evolution.hpp"

#include <string>
#include <cstdint>
#include <utility>

namespace jarvis::core {

class EvolutionExperimentRunner;
class EvolutionController;
class Brain;

enum class ExperimentOutcome { Pending, Improved, Neutral, Degraded, Invalid };

struct EvolutionExperiment {
    EvolutionExperiment() = default;
    EvolutionExperiment(std::string id_value, EvolutionProposal proposal_value,
                        double baseline, double candidate, double minimum,
                        double confidence_value,
                        ExperimentOutcome outcome_value = ExperimentOutcome::Pending,
                        bool executed = false, bool isolated_value = false)
        : id(std::move(id_value)), proposal(std::move(proposal_value)),
          baseline_fitness(baseline), candidate_fitness(candidate),
          minimum_improvement(minimum), confidence(confidence_value),
          outcome(outcome_value), candidate_executed(executed),
          isolated(isolated_value) {}

    std::string id;
    EvolutionProposal proposal;
    double baseline_fitness{0.0};
    double candidate_fitness{0.0};
    double minimum_improvement{0.0};
    double confidence{0.0};
    ExperimentOutcome outcome{ExperimentOutcome::Pending};
    bool candidate_executed{false};
    // Serialized result bit; the private snapshot below proves that this
    // instance's evaluated fields have not changed since sandbox attestation.
    bool isolated{false};
    // Provenance produced by the registered local evaluator, persisted with
    // the evaluation event so replay can compare the same procedure/artifacts.
    std::string evaluation_procedure_id;
    std::string baseline_artifact_id;
    std::string candidate_artifact_id;

    bool has_valid_isolation_attestation() const noexcept {
        return isolation_attested_ && id == attested_id_ &&
               proposal.key == attested_key_ &&
               proposal.current == attested_current_ &&
               proposal.proposed == attested_proposed_ &&
               proposal.expected_gain == attested_expected_gain_ &&
               proposal.confidence == attested_proposal_confidence_ &&
               baseline_fitness == attested_baseline_ &&
               candidate_fitness == attested_candidate_ &&
               minimum_improvement == attested_minimum_ &&
               confidence == attested_confidence_ &&
               outcome == attested_outcome_ &&
               evaluation_procedure_id == attested_procedure_id_ &&
               baseline_artifact_id == attested_baseline_artifact_id_ &&
               candidate_artifact_id == attested_candidate_artifact_id_ &&
               candidate_executed && isolated;
    }

private:
    void attest_isolated_result() noexcept {
        isolation_attested_ = isolated && candidate_executed;
        attested_id_ = id;
        attested_key_ = proposal.key;
        attested_current_ = proposal.current;
        attested_proposed_ = proposal.proposed;
        attested_expected_gain_ = proposal.expected_gain;
        attested_proposal_confidence_ = proposal.confidence;
        attested_baseline_ = baseline_fitness;
        attested_candidate_ = candidate_fitness;
        attested_minimum_ = minimum_improvement;
        attested_confidence_ = confidence;
        attested_outcome_ = outcome;
        attested_procedure_id_ = evaluation_procedure_id;
        attested_baseline_artifact_id_ = baseline_artifact_id;
        attested_candidate_artifact_id_ = candidate_artifact_id;
    }

    bool isolation_attested_{false};
    std::string attested_id_;
    std::string attested_key_;
    double attested_current_{0.0};
    double attested_proposed_{0.0};
    double attested_expected_gain_{0.0};
    double attested_proposal_confidence_{0.0};
    double attested_baseline_{0.0};
    double attested_candidate_{0.0};
    double attested_minimum_{0.0};
    double attested_confidence_{0.0};
    ExperimentOutcome attested_outcome_{ExperimentOutcome::Pending};
    std::string attested_procedure_id_;
    std::string attested_baseline_artifact_id_;
    std::string attested_candidate_artifact_id_;

    friend class EvolutionExperimentRunner;
    friend class EvolutionExperimentCoordinator;
    friend class EvolutionController;
    friend class Brain;
};

class EvolutionExperimentEngine {
public:
    static ExperimentOutcome evaluate(EvolutionExperiment& experiment) noexcept;
};

} // namespace jarvis::core
