#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
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

    const auto invalid = brain.learn_from_prediction("", Scalar{0.5}, 0.8);
    assert(invalid.adaptation.observations == 0);
    assert(invalid.adopted == 0);

    assert(brain.memory().all().size() >= 4);

    Brain restored(path);
    const auto* metric = restored.learning_metric("forecast");
    assert(metric != nullptr);
    assert(metric->observations == 2);
    assert(std::isfinite(metric->mean_error));

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
