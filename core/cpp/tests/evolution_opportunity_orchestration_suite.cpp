#include "jarvis/core/evolution_opportunity.hpp"
#include "jarvis/core/evolution_orchestrator.hpp"
#include "evolution_test_evaluator.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
std::string evaluator_executable;
IsolatedCommand evaluator_command() {
    return IsolatedCommand{evaluator_executable,
        {"--test-evaluator-from-parameter"}, "", "jarvis.test.fixture.v1",
        EvolutionExperimentRunner::executable_fingerprint(evaluator_executable)};
}
} // namespace

int main(int argc, char** argv) {
    if (test_support::run_evolution_evaluator_fixture(argc, argv)) return 0;
    evaluator_executable = std::filesystem::absolute(argv[0]).string();
    if (!EvolutionExperimentRunner::register_trusted_evaluator(
            "jarvis.test.fixture.v1", evaluator_executable,
            {"--test-evaluator-from-parameter"})) return 1;
    assert(EvolutionExperimentRunner::register_trusted_evaluator(
            "jarvis.test.fixture.v1", evaluator_executable,
            {"--test-evaluator-from-parameter"}));
    EvolutionOpportunityDetector detector;
    const auto opportunities = detector.detect({
        {"diagnostics", 0.9, 0.8, 0.9, 1.0, 0.4},
        {"diagnostics", 0.8, 0.7, 0.8, 1.0, 0.5},
        {"noise", 0.2, 0.2, 0.9, 1.0, 0.9},
    }, 42);
    assert(opportunities.size() == 1);
    assert(opportunities.front().source == "diagnostics");
    assert(opportunities.front().evidence_count == 2);
    assert(opportunities.front().score >= 0.5);

    EvolutionSandbox sandbox;
    EvolutionModel model;
    model.register_parameter("slow", 0.0);
    model.register_parameter("fast", 0.0);
    EvolutionHistory history;
    EvolutionSafetyPolicy safety;
    safety.minimum_confidence = 0.75;
    safety.require_isolation = false; // This suite exercises orchestration with simulated evaluators.
    safety.allow_simulated_evidence = true;
    EvolutionController controller(model, history, safety);
    EvolutionOrchestrator orchestrator({}, EvolutionTrialConfig{4, 4, 0.01, 0.75, false});
    const auto now = std::chrono::steady_clock::now();

    const auto result = orchestrator.run(
        opportunities.front(),
        [](const EvolutionOpportunity&) {
            return std::vector<EvolutionProposal>{
                {"slow", 0.0, 0.1, 0.2, 0.95},
                {"fast", 0.0, 0.2, 0.3, 0.9},
            };
        },
        sandbox,
        [](const EvolutionProposal&, const SandboxLimits&) {
            return SandboxResult{true, true, false, false, true, 0.5, {}};
        },
        [](const EvolutionProposal& proposal, const SandboxLimits&) {
            return SandboxResult{true, true, false, false, true,
                                 proposal.key == "fast" ? 0.8 : 0.6, {}};
        },
        history, now, now - std::chrono::seconds(2), true, &controller);

    assert(result.schedule.allowed);
    assert(result.experiments.size() == 2);
    assert(result.experiments[0].candidate_executed);
    assert(result.experiments[1].candidate_executed);
    assert(result.experiments[0].outcome == ExperimentOutcome::Improved);
    assert(result.experiments[0].confidence >= 0.75);
    assert(result.adopted == 1);
    assert((result.lifecycle[0] == EvolutionLifecycleState::Retained) !=
           (result.lifecycle[1] == EvolutionLifecycleState::Retained));
    assert((result.lifecycle[0] == EvolutionLifecycleState::Superseded) !=
           (result.lifecycle[1] == EvolutionLifecycleState::Superseded));
    const auto* fast = model.parameter("fast");
    const auto* slow = model.parameter("slow");
    assert(fast != nullptr && slow != nullptr);
    assert((fast->value != fast->baseline) != (slow->value != slow->baseline));
    assert((fast->value != fast->baseline) || (slow->value != slow->baseline));
    const auto fast_adoption = controller.adoption_journal().get(result.experiments[0].id);
    const auto slow_adoption = controller.adoption_journal().get(result.experiments[1].id);
    const std::string adopted_key =
        fast->value != fast->baseline ? "fast" : "slow";
    const auto adopted_experiment = std::find_if(
        result.experiments.begin(), result.experiments.end(),
        [&](const EvolutionExperiment& experiment) {
            return experiment.proposal.key == adopted_key;
        });
    assert(adopted_experiment != result.experiments.end());
    const auto adopted_id = adopted_experiment->id;
    const auto adopted_record = controller.adoption_journal().get(adopted_id);
    assert(adopted_record.has_value() && adopted_record->state == AdoptionState::Adopted);
    assert(history.for_experiment(adopted_id).size() == 2);
    assert(fast_adoption.has_value() || slow_adoption.has_value());

    const auto blocked = orchestrator.run(
        opportunities.front(),
        [](const EvolutionOpportunity&) {
            return std::vector<EvolutionProposal>{{"blocked", 0.0, 0.1, 0.2, 0.9}};
        },
        sandbox,
        [](const EvolutionProposal&, const SandboxLimits&) {
            return SandboxResult{true, true, false, false, true, 0.5, {}};
        },
        [](const EvolutionProposal&, const SandboxLimits&) {
            return SandboxResult{true, true, false, false, true, 0.8, {}};
        },
        history, now, now, false);

    assert(!blocked.schedule.allowed);

    // Production orchestration uses the isolated evaluator path with the
    // default isolation policy; callback simulation above is a separate path.
    EvolutionModel isolated_model;
    isolated_model.register_parameter("slow", 0.0);
    isolated_model.register_parameter("fast", 0.0);
    EvolutionHistory isolated_history;
    EvolutionSafetyPolicy isolated_safety;
    isolated_safety.minimum_confidence = 0.75;
    EvolutionController isolated_controller(isolated_model, isolated_history, isolated_safety);
    EvolutionOrchestrator isolated_orchestrator; // Exercise default isolation/trial policy.
    ProcessIsolationLimits isolated_limits;
    isolated_limits.sandbox.timeout = std::chrono::milliseconds{5000};
    isolated_limits.max_cpu_seconds = 10;
    ProcessIsolationBackend isolated_backend(isolated_limits);
    const auto isolated_result = isolated_orchestrator.run_isolated(
        opportunities.front(),
        [](const EvolutionOpportunity&) {
            return std::vector<EvolutionProposal>{
                {"slow", 0.0, 0.1, 0.2, 0.95},
                {"fast", 0.0, 0.2, 0.3, 0.9},
            };
        },
        isolated_backend, evaluator_command(), isolated_history,
        now, now - std::chrono::seconds(2), true, &isolated_controller);
    assert(isolated_result.schedule.allowed);
    assert(isolated_result.experiments.size() == 2);
    assert(isolated_result.adopted == 1);
    assert(std::any_of(isolated_result.experiments.begin(), isolated_result.experiments.end(),
        [](const EvolutionExperiment& experiment) {
            return experiment.has_valid_isolation_attestation();
        }));
    return 0;
}
