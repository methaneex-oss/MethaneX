#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_phase8_learning.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    brain.register_evolution_parameter("forecast", 0.5);

    const auto first = brain.predict("forecast", Scalar{0.5}, 0.9);
    assert(first.created_sequence != 0);
    const auto cycle = brain.learn_from_prediction("forecast", Scalar{0.9}, 0.8);
    assert(cycle.adaptation.observations == 1);
    assert(cycle.adaptation.mean_error >= 0.0 && cycle.adaptation.mean_error <= 1.0);
    assert(cycle.confidence >= 0.0 && cycle.confidence <= 1.0);
    assert(brain.learning_metric("forecast") != nullptr);

    const auto second = brain.predict("forecast", Scalar{0.9}, 0.9);
    const auto cycle2 = brain.learn_from_prediction("forecast", Scalar{0.9}, 0.8);
    assert(cycle2.adaptation.observations == 2);
    assert(cycle2.adaptation.mean_error < cycle.adaptation.mean_error);
    assert(second.created_sequence != 0);

    for (int i = 0; i < 6; ++i) {
        brain.predict("forecast", Scalar{0.9}, 0.9);
        const auto experience = brain.learn_from_prediction("forecast", Scalar{0.9}, 0.8);
        assert(experience.adaptation.observations == static_cast<std::uint64_t>(i + 3));
    }
    const auto* parameter = brain.evolution_parameter("forecast");
    assert(parameter != nullptr);
    assert(parameter->observations == 8);
    assert(parameter->value > 0.5);

    const auto invalid = brain.learn_from_prediction("", Scalar{0.5}, 0.8);
    assert(invalid.adaptation.observations == 0);
    assert(invalid.adopted == 0);

    assert(brain.memory().all().size() >= 16);

    Brain restored(path);
    const auto* metric = restored.learning_metric("forecast");
    assert(metric != nullptr);
    assert(metric->observations == 8);
    assert(std::isfinite(metric->mean_error));
    const auto* restored_parameter = restored.evolution_parameter("forecast");
    assert(restored_parameter != nullptr);
    assert(restored_parameter->observations == 8);
    assert(restored_parameter->value > 0.5);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
