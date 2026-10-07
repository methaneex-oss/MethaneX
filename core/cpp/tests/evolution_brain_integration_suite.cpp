#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>
#include <algorithm>

using namespace jarvis::core;

int main() {
    const std::filesystem::path path = "evolution_brain_integration_test.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);

    {
        Brain brain(path);
        assert(brain.register_evolution_parameter("planner.weight", 0.4));
        assert(!brain.register_evolution_parameter("planner.weight", 0.4));
        brain.predict("planner.weight", Scalar{0.4}, 0.9);
        const auto learning_cycle = brain.learn_from_prediction("planner.weight", Scalar{0.6}, 0.8);
        assert(learning_cycle.adaptation.observations == 1);
        const auto* after_prediction = brain.evolution_parameter("planner.weight");
        assert(after_prediction != nullptr);
        assert(after_prediction->observations == 1);
        brain.observe_evolution_fitness("planner.weight", 0.9);
        brain.observe_evolution_fitness("planner.weight", 0.9);
        const auto* after_fitness = brain.evolution_parameter("planner.weight");
        assert(after_fitness != nullptr);
        assert(after_fitness->observations == 3);
        const auto proposals = brain.evolution_options();
        assert(!proposals.empty());

        EvolutionExperiment experiment{
            "brain-evolution-1", proposals.front(), 0.70, 0.90, 0.01, 0.95,
            ExperimentOutcome::Improved, true};
        assert(brain.record_evolution_evaluation(experiment));
        const evaluated_history = brain.evolution_history();
        assert(evaluated_history.size() == 1);
        assert(evaluated_history.front().action == EvolutionRecordAction::Evaluated);
        assert(brain.adopt_evolution_experiment(experiment));
        const auto live_history = brain.evolution_history();
        assert(live_history.size() == 2);
        assert(live_history.front().action == EvolutionRecordAction::Evaluated);
        assert(live_history.back().experiment_id == "brain-evolution-1");
        assert(live_history.back().action == EvolutionRecordAction::Adopted);

        assert(brain.register_evolution_parameter("direct.rollback", 0.2));
        brain.observe_evolution_fitness("direct.rollback", 0.9);
        brain.observe_evolution_fitness("direct.rollback", 0.9);
        const auto direct_proposals = brain.evolution_options();
        const auto direct_it = std::find_if(
            direct_proposals.begin(), direct_proposals.end(),
            [](const EvolutionProposal& proposal) { return proposal.key == "direct.rollback"; });
        assert(direct_it != direct_proposals.end());
        assert(brain.adopt_evolution(*direct_it));
        const auto* adopted_direct = brain.evolution_parameter("direct.rollback");
        assert(adopted_direct != nullptr);
        assert(adopted_direct->value != adopted_direct->baseline);
        assert(brain.rollback_evolution("direct.rollback"));
        const auto* rolled_direct = brain.evolution_parameter("direct.rollback");
        assert(rolled_direct != nullptr);
        assert(rolled_direct->value == rolled_direct->baseline);

        brain.observe_evolution_canary("planner.weight", "brain-evolution-1", {0.90, 0.89});
        brain.observe_evolution_canary("planner.weight", "brain-evolution-1", {0.90, 0.88});
        const auto decision = brain.observe_evolution_canary(
            "planner.weight", "brain-evolution-1", {0.90, 0.84});
        assert(decision.sufficient_evidence);
        assert(decision.rollback);

        assert(brain.register_evolution_parameter("canary.persist", 0.3));
        const auto pending_canary = brain.observe_evolution_canary(
            "canary.persist", "canary-persist-1", {0.90, 0.89});
        assert(!pending_canary.sufficient_evidence);
        const auto pending_canary_again = brain.observe_evolution_canary(
            "canary.persist", "canary-persist-1", {0.90, 0.88});
        assert(!pending_canary_again.sufficient_evidence);
        EvolutionExperiment replayable{
            "replay-evaluation-1",
            EvolutionProposal{"canary.persist", 0.3, 0.4, 0.1, 0.90},
            0.70, 0.82, 0.01, 0.90, ExperimentOutcome::Improved, true};
        assert(brain.record_evolution_evaluation(replayable));
        assert(!brain.record_evolution_evaluation(replayable));
        assert(brain.evolution_history().size() == 4);
    }

    {
        Brain restarted(path);
        const auto* parameter = restarted.evolution_parameter("planner.weight");
        assert(parameter != nullptr);
        assert(parameter->value == parameter->baseline);
        assert(parameter->observations == 3);
        assert(parameter->value == parameter->baseline);
        const auto* direct = restarted.evolution_parameter("direct.rollback");
        assert(direct != nullptr);
        assert(direct->value == direct->baseline);
        assert(direct->observations == 2);

        const auto restarted_history = restarted.evolution_history();
        assert(restarted_history.size() == 4);
        assert(restarted_history.front().experiment_id == "brain-evolution-1");
        assert(restarted_history.front().action == EvolutionRecordAction::Evaluated);
        assert(restarted_history[1].action == EvolutionRecordAction::Adopted);
        assert(restarted_history.back().experiment_id == "brain-evolution-1");
        assert(restarted_history.back().experiment_id == "replay-evaluation-1");
        assert(restarted_history.back().action == EvolutionRecordAction::Evaluated);
        EvolutionExperiment replayed{
            "replay-evaluation-1",
            EvolutionProposal{"canary.persist", 0.3, 0.4, 0.1, 0.90},
            0.70, 0.82, 0.01, 0.90, ExperimentOutcome::Improved, true};
        assert(restarted.adopt_evolution_experiment(replayed));
        const auto* replayed_parameter = restarted.evolution_parameter("canary.persist");
        assert(replayed_parameter != nullptr && replayed_parameter->value == 0.4);

        const auto persisted_canary = restarted.observe_evolution_canary(
            "canary.persist", "canary-persist-1", {0.90, 0.80});
        assert(persisted_canary.sufficient_evidence);
        assert(persisted_canary.rollback);

        Brain restarted_again(path);
        const auto* direct_parameter = restarted_again.evolution_parameter("planner.weight");
        assert(direct_parameter != nullptr);
        assert(direct_parameter->value == direct_parameter->baseline);
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
