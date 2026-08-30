#include "jarvis/core/learning_loop.hpp"

#include <cassert>
#include <cmath>

using namespace jarvis::core;

int main() {
    AdaptationModel adaptation;
    EvolutionModel evolution;
    LearningLoop loop;

    evolution.register_parameter("forecast", 0.5);

    LearningFeedback feedback{"forecast", 0.5, 0.9, 0.8};
    LearningCycle cycle{};
    for (int i = 0; i < 8; ++i) cycle = loop.process(feedback, adaptation, evolution);

    assert(cycle.adaptation.observations == 8);
    assert(cycle.adaptation.estimate > 0.5);
    assert(cycle.confidence >= 0.0 && cycle.confidence <= 1.0);
    assert(!cycle.proposals.empty());
    assert(cycle.adopted <= 1);

    const auto* parameter = evolution.parameter("forecast");
    assert(parameter != nullptr);
    assert(parameter->value >= 0.5);

    const auto before_invalid = parameter->observations;
    const auto invalid = loop.process(LearningFeedback{"", 1.0, 0.0, 1.0}, adaptation, evolution);
    assert(invalid.adopted == 0);
    assert(invalid.proposals.empty());
    assert(evolution.parameter("forecast")->observations == before_invalid);

    const auto* before_nan_metric = adaptation.metric("forecast");
    assert(before_nan_metric != nullptr);
    const auto before_nan_observations = before_nan_metric->observations;
    const auto before_nan_estimate = before_nan_metric->estimate;
    const auto before_nan_error = before_nan_metric->mean_error;

    const auto nan_cycle = loop.process(
        LearningFeedback{"forecast", NAN, 0.5, 0.5}, adaptation, evolution);
    assert(nan_cycle.adopted == 0);
    assert(nan_cycle.proposals.empty());

    const auto* after_nan_metric = adaptation.metric("forecast");
    assert(after_nan_metric != nullptr);
    assert(after_nan_metric->observations == before_nan_observations);
    assert(after_nan_metric->estimate == before_nan_estimate);
    assert(after_nan_metric->mean_error == before_nan_error);
    assert(std::isfinite(nan_cycle.confidence));

    const auto* metric = adaptation.metric("forecast");
    assert(metric != nullptr);
    assert(metric->mean_error >= 0.0 && metric->mean_error <= 1.0);

    return 0;
}
