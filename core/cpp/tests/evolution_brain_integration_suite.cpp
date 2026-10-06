#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>
#include <cmath>

using namespace jarvis::core;

int main() {
    const std::filesystem::path path = "evolution_brain_integration_test.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);

    {
        Brain brain(path);
        brain.register_evolution_parameter("planner.weight", 0.4);
        brain.predict("planner.weight", Scalar{0.4}, 0.9);
        const auto learning_cycle = brain.learn_from_prediction("planner.weight", Scalar{0.6}, 0.8);
        assert(std::isfinite(learning_cycle.adaptation.confidence));
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
        assert(brain.adopt_evolution_experiment(experiment));
        assert(!brain.evolution_history().empty());

        brain.observe_evolution_canary("planner.weight", "brain-evolution-1", {0.90, 0.89});
        brain.observe_evolution_canary("planner.weight", "brain-evolution-1", {0.90, 0.88});
        const auto decision = brain.observe_evolution_canary(
            "planner.weight", "brain-evolution-1", {0.90, 0.84});
        assert(decision.sufficient_evidence);
        assert(decision.rollback);
    }

    {
        Brain restarted(path);
        const auto* parameter = restarted.evolution_parameter("planner.weight");
        assert(parameter != nullptr);
        assert(parameter->value == parameter->baseline);
        assert(parameter->observations == 3);
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
