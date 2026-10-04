#pragma once

#include <algorithm>
#include <cstdint>
#include <string>

namespace jarvis::core {

struct GoalOutcomeEvidence {
    std::string goal_id;
    double progress_before{0.0};
    double progress_after{0.0};
    double delta{0.0};
    bool completed{false};
    double confidence{0.0};
    std::uint64_t sequence{0};

    void normalize() noexcept {
        progress_before = std::clamp(progress_before, 0.0, 1.0);
        progress_after = std::clamp(progress_after, 0.0, 1.0);
        delta = progress_after - progress_before;
        confidence = std::clamp(confidence, 0.0, 1.0);
        completed = completed || progress_after >= 1.0;
    }
};

struct GoalProgressModel {
    std::string goal_id;
    double progress{0.0};
    double confidence{0.0};
    std::uint64_t positive_outcomes{0};
    std::uint64_t negative_outcomes{0};
    std::uint64_t completed_outcomes{0};

    void observe(const GoalOutcomeEvidence& evidence) noexcept {
        if (!goal_id.empty() && evidence.goal_id != goal_id) return;
        if (goal_id.empty()) goal_id = evidence.goal_id;
        if (evidence.delta > 0.0) ++positive_outcomes;
        else if (evidence.delta < 0.0) ++negative_outcomes;
        if (evidence.completed) ++completed_outcomes;
        progress = std::clamp(evidence.progress_after, 0.0, 1.0);
        const auto observations = positive_outcomes + negative_outcomes;
        if (observations == 1) confidence = evidence.confidence;
        else if (observations > 1) confidence = std::clamp(
            ((confidence * static_cast<double>(observations - 1)) + evidence.confidence) /
            static_cast<double>(observations), 0.0, 1.0);
    }
};

} // namespace jarvis::core
