#include "jarvis/core/evolution_experiment_runner.hpp"
#include "jarvis/core/evolution_digest.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace jarvis::core {
namespace {

std::string number(double value) {
    std::ostringstream out;
    out << std::setprecision(17) << value;
    return out.str();
}

bool parse_record(const std::string& output, const std::string& experiment_id,
                  const std::string& mode, const EvolutionProposal& proposal,
                  double evaluated_value, const std::string& artifact_digest,
                  const IsolatedEvaluationProcedure& procedure,
                  const std::string& evaluator_digest, double& fitness) {
    std::vector<std::string> fields;
    std::size_t start = 0;
    for (;;) {
        const auto end = output.find('\t', start);
        fields.push_back(output.substr(start, end == std::string::npos
            ? std::string::npos : end - start));
        if (end == std::string::npos) break;
        start = end + 1;
    }
    // Protocol is exact: arbitrary numeric output and extra/trailing fields fail.
    if (fields.size() != 12 || fields[0] != "JARVIS_EVAL_V1" ||
        fields[1] != experiment_id || fields[2] != mode ||
        fields[3] != proposal.key || fields[4] != number(evaluated_value) ||
        fields[5] != number(proposal.current) || fields[6] != number(proposal.proposed) ||
        fields[7] != artifact_digest || fields[8] != procedure.configuration_id ||
        fields[9] != procedure.procedure_id || fields[10] != evaluator_digest) return false;
    try {
        std::size_t used = 0;
        fitness = std::stod(fields[11], &used);
        return used == fields[11].size() && std::isfinite(fitness);
    } catch (...) {
        return false;
    }
}

bool measure(const EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
             const IsolatedEvaluationProcedure& procedure, const std::string& mode,
             double value, const std::string& artifact_path,
             const std::string& artifact_digest, const std::string& evaluator_digest,
             double& fitness) {
    IsolatedCommand command = procedure.command;
    command.arguments.insert(command.arguments.end(), {
        "--jarvis-evaluate-v1", experiment.id, mode, experiment.proposal.key,
        number(value), number(experiment.proposal.current),
        number(experiment.proposal.proposed), artifact_path, artifact_digest,
        procedure.configuration_id, procedure.procedure_id, evaluator_digest});
    const auto result = backend.run(command);
    if (!result.started || !result.isolated || !result.completed || result.timed_out ||
        result.output_limited || result.exit_code != 0) return false;
    return parse_record(result.output, experiment.id, mode, experiment.proposal, value,
                        artifact_digest, procedure, evaluator_digest, fitness);
}

} // namespace

bool EvolutionExperiment::has_valid_evaluation_evidence() const noexcept {
    if (!isolated || !candidate_executed || id.empty() || proposal.key.empty() ||
        evaluation_procedure_id.empty() || evaluation_config_id.empty() ||
        baseline_artifact_digest.empty() || candidate_artifact_digest.empty() ||
        evaluator_artifact_digest.empty() || baseline_trial_count < 2 ||
        candidate_trial_count < 2 || evaluation_evidence_digest.empty() ||
        !std::isfinite(baseline_fitness) || !std::isfinite(candidate_fitness) ||
        !std::isfinite(minimum_improvement) || minimum_improvement < 0.0 ||
        !std::isfinite(confidence) || confidence < 0.0 || confidence > 1.0 ||
        !std::isfinite(proposal.current) || !std::isfinite(proposal.proposed) ||
        !std::isfinite(proposal.expected_gain) || !std::isfinite(proposal.confidence))
        return false;

    const std::string evidence = id + "\n" + proposal.key + "\n" +
        number(proposal.current) + "\n" + number(proposal.proposed) + "\n" +
        number(proposal.expected_gain) + "\n" + number(proposal.confidence) + "\n" +
        number(baseline_fitness) + "\n" + number(candidate_fitness) + "\n" +
        number(minimum_improvement) + "\n" + number(confidence) + "\n" +
        evaluation_procedure_id + "\n" + evaluation_config_id + "\n" +
        baseline_artifact_digest + "\n" + candidate_artifact_digest + "\n" +
        evaluator_artifact_digest + "\n" + std::to_string(baseline_trial_count) +
        "\n" + std::to_string(candidate_trial_count);
    return detail::sha256_hex(evidence) == evaluation_evidence_digest;
}

ExperimentOutcome EvolutionExperimentRunner::run(EvolutionExperiment& experiment,
                                                  const EvolutionSandbox& sandbox,
                                                  const CandidateExecutor& executor) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    const auto result = sandbox.run(experiment.proposal, executor);
    if (!result.started || !result.completed || result.timed_out || result.output_limited ||
        !std::isfinite(result.fitness)) {
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    experiment.candidate_fitness = result.fitness;
    experiment.candidate_executed = true;
    experiment.isolated = false;
    return EvolutionExperimentEngine::evaluate(experiment);
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_command(
    EvolutionExperiment& experiment, const ProcessIsolationBackend&,
    const IsolatedCommand&) noexcept {
    // A command that merely prints a number cannot establish what was measured.
    // Keep this legacy API fail-closed; use run_isolated_evaluation instead.
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    experiment.evaluation_procedure_id.clear();
    experiment.evaluation_config_id.clear();
    experiment.baseline_artifact_digest.clear();
    experiment.candidate_artifact_digest.clear();
    experiment.evaluator_artifact_digest.clear();
    experiment.baseline_trial_count = 0;
    experiment.candidate_trial_count = 0;
    experiment.evaluation_evidence_digest.clear();
    return experiment.outcome;
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_evaluation(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedEvaluationProcedure& procedure, std::size_t baseline_trials,
    std::size_t candidate_trials, double minimum_confidence, TrialStatistics* baseline_summary,
    TrialStatistics* candidate_summary) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    experiment.evaluation_procedure_id.clear();
    experiment.evaluation_config_id.clear();
    experiment.baseline_artifact_digest.clear();
    experiment.candidate_artifact_digest.clear();
    experiment.evaluator_artifact_digest.clear();
    experiment.baseline_trial_count = 0;
    experiment.candidate_trial_count = 0;
    experiment.evaluation_evidence_digest.clear();

    if (experiment.id.empty() || experiment.proposal.key.empty() ||
        !std::isfinite(experiment.proposal.current) ||
        !std::isfinite(experiment.proposal.proposed) || baseline_trials < 2 || candidate_trials < 2 ||
        !std::isfinite(minimum_confidence) || minimum_confidence < 0.0 ||
        minimum_confidence > 1.0 || procedure.command.executable.empty() ||
        procedure.procedure_id.empty() || procedure.configuration_id.empty() ||
        procedure.baseline_artifact_path.empty() ||
        procedure.candidate_artifact_path.empty() ||
        procedure.expected_evaluator_digest.empty() ||
        !backend.limits().require_no_new_privileges ||
        !backend.limits().require_privilege_drop ||
        !backend.limits().require_network_syscall_block) return experiment.outcome;

    const auto baseline_digest = detail::sha256_file(procedure.baseline_artifact_path);
    const auto candidate_digest = detail::sha256_file(procedure.candidate_artifact_path);
    const auto evaluator_digest = detail::sha256_file(procedure.command.executable);
    // The expected digest is provisioned by trusted local configuration. An
    // arbitrary executable cannot declare itself trusted by echoing its own hash.
    if (baseline_digest.empty() || candidate_digest.empty() || evaluator_digest.empty() ||
        evaluator_digest != procedure.expected_evaluator_digest)
        return experiment.outcome;

    std::vector<double> baseline_values;
    std::vector<double> candidate_values;
    baseline_values.reserve(baseline_trials);
    candidate_values.reserve(candidate_trials);
    for (std::size_t i = 0; i < baseline_trials; ++i) {
        double fitness = 0.0;
        if (!measure(experiment, backend, procedure, "baseline",
                     experiment.proposal.current, procedure.baseline_artifact_path,
                     baseline_digest, evaluator_digest, fitness)) return experiment.outcome;
        baseline_values.push_back(fitness);
    }
    for (std::size_t i = 0; i < candidate_trials; ++i) {
        double fitness = 0.0;
        if (!measure(experiment, backend, procedure, "candidate",
                     experiment.proposal.proposed, procedure.candidate_artifact_path,
                     candidate_digest, evaluator_digest, fitness)) return experiment.outcome;
        candidate_values.push_back(fitness);
    }

    const auto baseline = EvolutionTrials::summarize(baseline_values);
    const auto candidate = EvolutionTrials::summarize(candidate_values);
    if (baseline.count < 2 || candidate.count < 2) return experiment.outcome;
    if (baseline_summary != nullptr) *baseline_summary = baseline;
    if (candidate_summary != nullptr) *candidate_summary = candidate;

    experiment.baseline_fitness = baseline.mean;
    experiment.candidate_fitness = candidate.mean;
    if (!std::isfinite(experiment.minimum_improvement) || experiment.minimum_improvement < 0.0) {
        experiment.candidate_executed = false;
        experiment.isolated = false;
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }
    experiment.confidence = std::min(baseline.confidence, candidate.confidence);
    experiment.candidate_executed = true;
    experiment.isolated = true;
    experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (experiment.outcome == ExperimentOutcome::Invalid ||
        experiment.confidence < minimum_confidence) {
        experiment.candidate_executed = false;
        experiment.isolated = false;
        experiment.outcome = ExperimentOutcome::Invalid;
        return experiment.outcome;
    }

    experiment.evaluation_procedure_id = procedure.procedure_id;
    experiment.evaluation_config_id = procedure.configuration_id;
    experiment.baseline_artifact_digest = baseline_digest;
    experiment.candidate_artifact_digest = candidate_digest;
    experiment.evaluator_artifact_digest = evaluator_digest;
    experiment.baseline_trial_count = baseline.count;
    experiment.candidate_trial_count = candidate.count;
    const std::string evidence = experiment.id + "\n" + experiment.proposal.key + "\n" +
        number(experiment.proposal.current) + "\n" + number(experiment.proposal.proposed) + "\n" +
        number(experiment.proposal.expected_gain) + "\n" + number(experiment.proposal.confidence) + "\n" +
        number(experiment.baseline_fitness) + "\n" + number(experiment.candidate_fitness) + "\n" +
        number(experiment.minimum_improvement) + "\n" + number(experiment.confidence) + "\n" +
        std::to_string(static_cast<int>(experiment.outcome)) + "\n" + procedure.procedure_id + "\n" + procedure.configuration_id + "\n" +
        baseline_digest + "\n" + candidate_digest + "\n" + evaluator_digest + "\n" +
        std::to_string(baseline.count) + "\n" + std::to_string(candidate.count);
    experiment.evaluation_evidence_digest = detail::sha256_hex(evidence);
    experiment.attest_isolated_result();
    return experiment.outcome;
}

} // namespace jarvis::core
