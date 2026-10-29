#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cmath>
#include <filesystem>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

namespace jarvis::core {

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
    experiment.isolated = false; // callback results are not trusted isolation evidence
    return EvolutionExperimentEngine::evaluate(experiment);
}

namespace {
std::string numeric_argument(double value) {
    std::ostringstream out;
    out << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
    return out.str();
}

std::string command_identity(const IsolatedCommand& command) {
    std::ostringstream out;
    const auto field = [&](const std::string& value) {
        out << value.size() << ':' << value;
    };
    field(command.executable);
    field(command.working_directory);
    for (const auto& argument : command.arguments) field(argument);
    return out.str();
}

bool parse_evaluation_record(const ProcessIsolationResult& result,
                             const std::string& procedure,
                             const std::string& parameter,
                             const std::string& artifact,
                             double value,
                             double& fitness) {
    if (!result.started || !result.isolated || !result.completed ||
        result.timed_out || result.output_limited || result.exit_code != 0) return false;
    std::istringstream input(result.output);
    std::string version, procedure_line, parameter_line, value_line, artifact_line, fitness_line, extra;
    if (!std::getline(input, version) || !std::getline(input, procedure_line) ||
        !std::getline(input, parameter_line) || !std::getline(input, value_line) ||
        !std::getline(input, artifact_line) || !std::getline(input, fitness_line) ||
        std::getline(input, extra)) return false;
    if (version != "JARVIS_EVAL_V1" ||
        procedure_line != "procedure=" + procedure ||
        parameter_line != "parameter=" + parameter ||
        value_line != "value=" + numeric_argument(value) ||
        artifact_line != "artifact=" + artifact ||
        fitness_line.rfind("fitness=", 0) != 0) return false;
    try {
        std::size_t parsed = 0;
        fitness = std::stod(fitness_line.substr(8), &parsed);
        return parsed == fitness_line.size() - 8 && std::isfinite(fitness);
    } catch (...) {
        return false;
    }
}
} // namespace

ExperimentOutcome EvolutionExperimentRunner::run_isolated_evaluation(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedEvaluationSpec& spec) noexcept {
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    if (spec.evaluator.executable.empty() || spec.procedure_id.empty() ||
        spec.baseline_artifact_id.empty() || spec.candidate_artifact_id.empty() ||
        spec.baseline_artifact_id == spec.candidate_artifact_id ||
        experiment.proposal.key.empty() ||
        !std::isfinite(spec.baseline_value) || !std::isfinite(spec.candidate_value) ||
        spec.baseline_value != experiment.proposal.current ||
        spec.candidate_value != experiment.proposal.proposed) return experiment.outcome;

    auto run_one = [&](const std::string& artifact, double value, double& fitness) {
        IsolatedCommand command = spec.evaluator;
        command.arguments.insert(command.arguments.end(), {
            "--jarvis-evaluate-v1", "--procedure", spec.procedure_id,
            "--parameter", experiment.proposal.key, "--value", numeric_argument(value),
            "--artifact", artifact});
        const auto result = backend.run(command);
        return parse_evaluation_record(result, spec.procedure_id,
                                       experiment.proposal.key, artifact, value, fitness);
    };

    double baseline = 0.0;
    double candidate = 0.0;
    if (!run_one(spec.baseline_artifact_id, spec.baseline_value, baseline) ||
        !run_one(spec.candidate_artifact_id, spec.candidate_value, candidate)) {
        return experiment.outcome;
    }
    experiment.baseline_fitness = baseline;
    experiment.candidate_fitness = candidate;
    experiment.evaluation_procedure_id = spec.procedure_id;
    experiment.evaluation_command_identity = command_identity(spec.evaluator);
    experiment.baseline_artifact_id = spec.baseline_artifact_id;
    experiment.candidate_artifact_id = spec.candidate_artifact_id;
    experiment.candidate_executed = true;
    experiment.isolated = true;
    experiment.outcome = EvolutionExperimentEngine::evaluate(experiment);
    if (experiment.outcome != ExperimentOutcome::Invalid) experiment.attest_isolated_result();
    return experiment.outcome;
}

ExperimentOutcome EvolutionExperimentRunner::run_isolated_command(
    EvolutionExperiment& experiment, const ProcessIsolationBackend& backend,
    const IsolatedCommand& command) noexcept {
    // A generic command's stdout is not evidence that the proposed candidate
    // was evaluated. In particular, shell snippets that print a supplied
    // fitness number must never create an adoption-capable attestation.
    (void)backend;
    (void)command;
    experiment.candidate_executed = false;
    experiment.isolated = false;
    experiment.outcome = ExperimentOutcome::Invalid;
    return experiment.outcome;
}

} // namespace jarvis::core
