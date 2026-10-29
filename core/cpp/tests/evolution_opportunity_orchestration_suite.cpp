#include "jarvis/core/evolution_opportunity.hpp"
#include "jarvis/core/evolution_orchestrator.hpp"
#include "jarvis/core/process_isolation.hpp"
#include "evolution_test_evaluator.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <vector>
#include <string>

using namespace jarvis::core;

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--test-evaluator")
        return test_support::run_evolution_test_evaluator(argc, argv);
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

    // Default isolated orchestration must use the paired local evaluator,
    // not the callback simulation route.
    EvolutionModel isolated_model;
    assert(isolated_model.register_parameter("isolated", 0.4));
    EvolutionHistory isolated_history;
    EvolutionSafetyPolicy isolated_safety;
    EvolutionController isolated_controller(isolated_model, isolated_history, isolated_safety);
    EvolutionOrchestrator isolated_orchestrator({}, EvolutionTrialConfig{4, 4, 0.01, 0.75, true});
    const IsolatedEvaluationSpec local_evaluator{
        IsolatedCommand{"/proc/self/exe", {"--test-evaluator"}, ""},
        "local-test-procedure-v1", "unused-baseline", "unused-candidate", 0.4, 0.5};
    const auto isolated_result = isolated_orchestrator.run(
        opportunities.front(),
        [](const EvolutionOpportunity&) {
            return std::vector<EvolutionProposal>{{"isolated", 0.4, 0.5, 0.1, 0.8}};
        },
        sandbox, CandidateExecutor{}, CandidateExecutor{}, isolated_history,
        now, now - std::chrono::seconds(2), true, &isolated_controller, &local_evaluator);
    assert(isolated_result.schedule.allowed);
    assert(isolated_result.experiments.size() == 1);
    assert(isolated_result.experiments.front().has_valid_isolation_attestation());
    assert(isolated_result.adopted == 1);
    const auto* isolated_parameter = isolated_model.parameter("isolated");
    assert(isolated_parameter != nullptr && isolated_parameter->value == 0.5);
    assert(isolated_history.for_experiment(isolated_result.experiments.front().id).size() == 2);
    return 0;
}
