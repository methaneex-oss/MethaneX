#include "jarvis/core/cognitive_trigger.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double normalize(double value) noexcept {
    return std::clamp(std::isfinite(value) ? value : 0.0, 0.0, 1.0);
}

} // namespace

CognitiveTriggerPolicy::CognitiveTriggerPolicy(CognitiveTriggerConfig config)
    : config_(config) {
    config_.novelty_threshold = normalize(config_.novelty_threshold);
    config_.urgency_threshold = normalize(config_.urgency_threshold);
    config_.uncertainty_threshold = normalize(config_.uncertainty_threshold);
}

CognitiveTriggerDecision CognitiveTriggerPolicy::evaluate(
    const CognitiveTriggerSignals& signals) const noexcept {
    const auto novelty = normalize(signals.novelty);
    const auto urgency = normalize(signals.urgency);
    const auto uncertainty = normalize(signals.uncertainty);

    const bool triggered = novelty >= config_.novelty_threshold ||
                           urgency >= config_.urgency_threshold ||
                           uncertainty >= config_.uncertainty_threshold;
    if (!triggered) return {};

    return {true, std::max({novelty, urgency, uncertainty})};
}

} // namespace jarvis::core
