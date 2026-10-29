#include "jarvis/core/evolution_opportunity.hpp"
#include "jarvis/core/evolution_orchestrator.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <vector>

using namespace jarvis::core;

int main() {
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
    assert(!result.experiments[0].has_valid_evaluation_evidence());
    assert(!result.experiments[1].has_valid_evaluation_evidence());
    // Callback simulations are useful for ranking/trial tests, but cannot
    // create a production evaluation record or authorize an adoption.
    assert(result.adopted == 0);
    assert(result.rejected == 2);
    assert(result.lifecycle[0] == EvolutionLifecycleState::EvaluationRejected);
    assert(result.lifecycle[1] == EvolutionLifecycleState::EvaluationRejected);
    const auto* fast = model.parameter("fast");
    const auto* slow = model.parameter("slow");
    assert(fast != nullptr && slow != nullptr);
    assert(fast->value == fast->baseline);
    assert(slow->value == slow->baseline);
    assert(!controller.adoption_journal().get(result.experiments[0].id).has_value());
    assert(!controller.adoption_journal().get(result.experiments[1].id).has_value());
    assert(history.for_experiment(result.experiments[0].id).empty());
    assert(history.for_experiment(result.experiments[1].id).empty());

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
    return 0;
}
