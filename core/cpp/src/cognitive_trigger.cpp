#include "jarvis/core/cognitive_trigger.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double bounded(double value) noexcept {
    return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0);
}

double positive_weight(double value) noexcept {
    return std::max(0.0, std::isfinite(value) ? value : 0.0);
}

} // namespace

CognitiveTriggerPolicy::CognitiveTriggerPolicy(CognitiveTriggerConfig config)
    : config_(config) {
    config_.novelty_threshold = bounded(config_.novelty_threshold);
    config_.urgency_threshold = bounded(config_.urgency_threshold);
    config_.uncertainty_threshold = bounded(config_.uncertainty_threshold);
}

CognitiveTriggerDecision CognitiveTriggerPolicy::evaluate(
    const CognitiveTriggerSignals& signals) const noexcept {
    const double novelty = bounded(signals.novelty);
    const double urgency = bounded(signals.urgency);
    const double uncertainty = bounded(signals.uncertainty);

    const bool triggered = novelty >= config_.novelty_threshold ||
                           urgency >= config_.urgency_threshold ||
                           uncertainty >= config_.uncertainty_threshold;
    if (!triggered) return {};

    const double novelty_weight = positive_weight(config_.novelty_weight);
    const double urgency_weight = positive_weight(config_.urgency_weight);
    const double uncertainty_weight = positive_weight(config_.uncertainty_weight);
    const double total_weight = novelty_weight + urgency_weight + uncertainty_weight;

    double priority = 0.0;
    if (total_weight > 0.0) {
        priority = (novelty * novelty_weight + urgency * urgency_weight +
                    uncertainty * uncertainty_weight) /
                   total_weight;
    }
    return {true, bounded(priority)};
}

} // namespace jarvis::core
