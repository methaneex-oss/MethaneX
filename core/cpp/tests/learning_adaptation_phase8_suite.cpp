#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <limits>

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
    const auto outcomes = brain.memory().by_kind("prediction_outcome");
    assert(!outcomes.empty());
    assert(std::get<double>(outcomes.back().data.at("error")) == 0.4);
    assert(cycle.adaptation.observations == 1);
    assert(cycle.adaptation.mean_error >= 0.0 && cycle.adaptation.mean_error <= 1.0);
    assert(cycle.adaptation.recent_error >= 0.0 && cycle.adaptation.recent_error <= 1.0);
    assert(cycle.confidence >= 0.0 && cycle.confidence <= 1.0);
    assert(brain.learning_metric("forecast") != nullptr);

    const auto second = brain.predict("forecast", Scalar{0.9}, 0.9);
    const auto cycle2 = brain.learn_from_prediction("forecast", Scalar{0.9}, 0.8);
    assert(cycle2.adaptation.observations == 2);
    assert(cycle2.adaptation.mean_error < cycle.adaptation.mean_error);
    assert(cycle2.adaptation.recent_error < cycle.adaptation.recent_error);
    assert(second.created_sequence != 0);

    for (int i = 0; i < 10; ++i) {
        brain.predict("forecast", Scalar{0.9}, 0.9);
        const auto experience = brain.learn_from_prediction("forecast", Scalar{0.9}, 0.8);
        assert(experience.adaptation.observations == static_cast<std::uint64_t>(i + 3));
    }
    const auto* parameter = brain.evolution_parameter("forecast");
    assert(parameter != nullptr);
    assert(parameter->observations == 12);
    assert(parameter->value > 0.5);

    // Developmental adaptation must respond to a changed environment even after
    // a long history of successful predictions. Long-term experience is retained,
    // but recent prediction errors must reduce confidence quickly.
    const auto* before_change = brain.learning_metric("forecast");
    assert(before_change != nullptr);
    const double stable_confidence = brain.learning_confidence("forecast");
    for (int i = 0; i < 4; ++i) {
        brain.predict("forecast", Scalar{0.9}, 0.9);
        (void)brain.learn_from_prediction("forecast", Scalar{0.1}, 0.8);
    }
    const auto* after_change = brain.learning_metric("forecast");
    assert(after_change != nullptr);
    assert(after_change->observations == 16);
    assert(after_change->recent_error > before_change->recent_error);
    assert(brain.learning_confidence("forecast") < stable_confidence);
    assert(after_change->mean_error < 0.5);

    const auto invalid = brain.learn_from_prediction("", Scalar{0.5}, 0.8);
    assert(invalid.adaptation.observations == 0);
    assert(invalid.adopted == 0);

    assert(brain.memory().all().size() >= 32);

    Brain restored(path);
    const auto* metric = restored.learning_metric("forecast");
    assert(metric != nullptr);
    assert(metric->observations == 16);
    assert(std::isfinite(metric->mean_error));
    assert(std::isfinite(metric->recent_error));
    const auto* restored_parameter = restored.evolution_parameter("forecast");
    assert(restored_parameter != nullptr);
    assert(restored_parameter->observations == 16);
    assert(restored_parameter->value > 0.5);

    // Finite inputs near the floating-point limits must still produce a
    // gradual estimate update instead of overflowing the delta and snapping
    // directly to the latest observation.
    AdaptationModel extreme_model;
    const double limit = std::numeric_limits<double>::max();
    const auto extreme_first = extreme_model.observe("extreme", -limit, -limit);
    assert(extreme_first.observations == 1);
    assert(extreme_first.estimate == -limit);
    const auto extreme_second = extreme_model.observe("extreme", -limit, limit);
    assert(extreme_second.observations == 2);
    assert(std::isfinite(extreme_second.estimate));
    assert(extreme_second.estimate < 0.0);
    assert(extreme_second.estimate > -limit);
    assert(extreme_second.mean_error >= 0.0 && extreme_second.mean_error <= 1.0);
    assert(extreme_second.recent_error >= 0.0 && extreme_second.recent_error <= 1.0);

    // Same-sign extreme values must remain finite as well.
    AdaptationModel same_sign_model;
    const auto same_sign_first = same_sign_model.observe("extreme", limit, limit);
    const auto same_sign_second = same_sign_model.observe("extreme", limit, limit);
    assert(same_sign_first.estimate == limit);
    assert(same_sign_second.observations == 2);
    assert(std::isfinite(same_sign_second.estimate));
    assert(same_sign_second.estimate == limit);

    // Invalid samples are ignored and cannot poison or increment the metric.
    const auto invalid_sample = extreme_model.observe(
        "extreme", 1.0, std::numeric_limits<double>::infinity());
    assert(invalid_sample.observations == 2);
    assert(std::isfinite(invalid_sample.estimate));

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}
