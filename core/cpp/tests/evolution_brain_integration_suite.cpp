#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>

using namespace jarvis::core;

int main() {
    const std::filesystem::path path = "evolution_brain_integration_test.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);

    {
        Brain brain(path);
        brain.register_evolution_parameter("planner.weight", 0.4);
        brain.observe_evolution_fitness("planner.weight", 0.9);
        brain.observe_evolution_fitness("planner.weight", 0.9);
        const auto proposals = brain.evolution_options();
        assert(!proposals.empty());

        EvolutionExperiment experiment{
            "brain-evolution-1", proposals.front(), 0.70, 0.90, 0.01, 0.95,
            0.19, 0.21, 2.0, ExperimentOutcome::Improved, true};
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
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
