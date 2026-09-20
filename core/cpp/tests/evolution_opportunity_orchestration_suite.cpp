#include "jarvis/core/evolution_opportunity.hpp"
#include "jarvis/core/evolution_orchestrator.hpp"

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
    EvolutionController controller(model, history, safety);
    EvolutionOrchestrator orchestrator;
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
