#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/evolution_digest.hpp"

#include <cmath>

namespace jarvis::core {
namespace {
std::string evidence_number(double value) {
    std::ostringstream out;
    out << std::setprecision(17) << value;
    return out.str();
}

} // namespace

bool EvolutionExperiment::has_valid_evaluation_evidence() const noexcept {
    if (!isolated || !candidate_executed || evaluation_procedure_id.empty() ||
        evaluation_config_id.empty() || baseline_artifact_digest.empty() ||
        candidate_artifact_digest.empty() || evaluator_artifact_digest.empty() ||
        baseline_trial_count < 2 || candidate_trial_count < 2 ||
        evaluation_evidence_digest.empty()) return false;
    const std::string evidence = id + "\n" + proposal.key + "\n" +
        evidence_number(proposal.current) + "\n" + evidence_number(proposal.proposed) + "\n" +
        evidence_number(proposal.expected_gain) + "\n" + evidence_number(proposal.confidence) + "\n" +
        evidence_number(baseline_fitness) + "\n" + evidence_number(candidate_fitness) + "\n" +
        evidence_number(minimum_improvement) + "\n" + evidence_number(confidence) + "\n" +
        std::to_string(static_cast<int>(outcome)) + "\n" + evaluation_procedure_id + "\n" + evaluation_config_id + "\n" +
        baseline_artifact_digest + "\n" + candidate_artifact_digest + "\n" +
        evaluator_artifact_digest + "\n" + std::to_string(baseline_trial_count) + "\n" +
        std::to_string(candidate_trial_count);
    if (detail::sha256_hex(evidence) != evaluation_evidence_digest) return false;
    EvolutionExperiment recomputed = *this;
    return EvolutionExperimentEngine::evaluate(recomputed) == outcome;
}

ExperimentOutcome EvolutionExperimentEngine::evaluate(EvolutionExperiment& experiment) noexcept {
    const auto& proposal = experiment.proposal;
    const bool valid = !experiment.id.empty() && !proposal.key.empty() &&
                       std::isfinite(proposal.current) && std::isfinite(proposal.proposed) &&
                       std::isfinite(proposal.expected_gain) && std::isfinite(proposal.confidence) &&
                       proposal.confidence >= 0.0 && proposal.confidence <= 1.0 &&
                       std::isfinite(experiment.baseline_fitness) &&
                       std::isfinite(experiment.candidate_fitness) &&
                       std::isfinite(experiment.minimum_improvement) &&
                       experiment.minimum_improvement >= 0.0 &&
                       std::isfinite(experiment.confidence) &&
                       experiment.confidence >= 0.0 && experiment.confidence <= 1.0 &&
                       experiment.candidate_executed;
    if (!valid) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    const double improvement = experiment.candidate_fitness - experiment.baseline_fitness;
    if (improvement > experiment.minimum_improvement &&
        experiment.confidence >= proposal.confidence) {
        experiment.outcome = ExperimentOutcome::Improved;
    } else if (improvement < -experiment.minimum_improvement) {
        experiment.outcome = ExperimentOutcome::Degraded;
    } else {
        experiment.outcome = ExperimentOutcome::Neutral;
    }
    return experiment.outcome;
}

} // namespace jarvis::core
