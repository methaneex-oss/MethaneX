#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>

namespace jarvis::core {
namespace {
std::uint64_t prediction_now_ns() noexcept {
    return static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
}
}

Prediction Brain::predict_with_context(std::string key, Scalar value, double confidence,
                                       double minimum_strength,
                                       std::size_t minimum_shared_contexts) {
    std::unique_lock lock(mutex_);
    if (key.empty()) return Prediction{};

    const auto candidates = association_.concept_candidates(
        std::clamp(minimum_strength, 0.0, 1.0), minimum_shared_contexts);

    PredictionContext context{};
    for (const auto& candidate : candidates) {
        if (std::find(candidate.members.begin(), candidate.members.end(), key) == candidate.members.end()) {
            continue;
        }
        if (candidate.coherence > context.evidence_strength) {
            context.evidence_strength = candidate.coherence;
            context.concept_members = candidate.members;
        }
    }

    const double base_confidence = std::clamp(confidence, 0.0, 1.0);
    const double contextual_confidence =
        context.evidence_strength > 0.0
            ? 1.0 - ((1.0 - base_confidence) * (1.0 - context.evidence_strength))
            : base_confidence;

    Prediction prediction{std::move(key), std::move(value),
                          std::clamp(contextual_confidence, 0.0, 1.0),
                          state_.cycle, false, 0.0, context};
    Event event{0, prediction_now_ns(), "brain", "prediction",
                {{"key", prediction.key},
                 {"value", prediction.predicted},
                 {"confidence", prediction.confidence},
                 {"concept_members", join_prediction_context_ids(context.concept_members)},
                 {"evidence_strength", context.evidence_strength}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return Prediction{};

    prediction.created_sequence = event.sequence;
    predictions_[prediction.key] = prediction;
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return prediction;
}

} // namespace jarvis::core