#pragma once

#include "jarvis/core/evolution_experiment.hpp"
#include "jarvis/core/process_isolation.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace jarvis::core {

struct EvolutionEvaluationRequest {
    // Only compiled-in local procedures are accepted. Unknown procedures fail closed.
    std::string procedure_id{"scalar-regression-fitness-v1"};
    std::vector<double> inputs;
    std::vector<double> targets;
    std::uint64_t seed_base{17};
};

struct EvolutionEvaluationEvidence {
    std::string experiment_id;
    std::string parameter_key;
    std::string candidate_id;
    std::string candidate_configuration_digest;
    std::string baseline_configuration_digest;
    std::string procedure_id;
    std::string procedure_digest;
    std::string evaluator_binary_digest;
    double baseline_value{0.0};
    double candidate_value{0.0};
    double minimum_improvement{0.0};
    double minimum_confidence{0.0};
    std::uint64_t seed_base{0};
    std::vector<double> inputs;
    std::vector<double> targets;
    std::vector<double> baseline_measurements;
    std::vector<double> candidate_measurements;

    std::string payload() const;
    std::string serialize() const;
    static std::optional<EvolutionEvaluationEvidence> parse(const std::string& serialized);
    std::string digest() const;
};

class EvolutionTrustedEvaluator {
public:
    static std::optional<EvolutionEvaluationEvidence> evaluate(
        const EvolutionExperiment& experiment,
        const EvolutionEvaluationRequest& request,
        std::size_t baseline_trials,
        std::size_t candidate_trials,
        double minimum_confidence,
        const ProcessIsolationBackend& backend) noexcept;

    // Re-executes the project-owned evaluator for every recorded baseline and
    // candidate trial. Serialized Boolean claims alone are never trusted.
    static bool verify(EvolutionExperiment& experiment,
                       const ProcessIsolationBackend& backend) noexcept;

    static std::string evaluator_executable_path();
    static std::string procedure_digest(const std::string& procedure_id);
};

} // namespace jarvis::core
