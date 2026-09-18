#include "jarvis/core/evolution_controller.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    EvolutionModel model;
    model.register_parameter("reasoning.weight", 0.4);
    EvolutionHistory history;
    EvolutionSafetyPolicy policy;
    policy.minimum_confidence = 0.8;

    EvolutionController controller(model, history, policy);
    EvolutionExperiment experiment{
        "exp-canary",
        EvolutionProposal{"reasoning.weight", 0.4, 0.5, 0.1, 0.95},
        0.70, 0.84, 0.05, 0.95, ExperimentOutcome::Improved, true};

    assert(controller.record_evaluation(experiment));
    assert(controller.adopt(experiment));
    const auto* adopted = model.parameter("reasoning.weight");
    assert(adopted != nullptr && adopted->value != adopted->baseline);

    controller.observe_canary("reasoning.weight", "exp-canary", {0.84, 0.82});
    controller.observe_canary("reasoning.weight", "exp-canary", {0.84, 0.80});
    const auto decision = controller.observe_canary("reasoning.weight", "exp-canary", {0.84, 0.78});
    assert(decision.sufficient_evidence);
    assert(decision.rollback);

    const auto* restored = model.parameter("reasoning.weight");
    assert(restored != nullptr && restored->value == restored->baseline);
    const auto records = history.for_experiment("exp-canary");
    assert(records.size() >= 2);
    assert(records.back().action == EvolutionRecordAction::RolledBack);
    assert(!records.back().reason.empty());
    return 0;
}
