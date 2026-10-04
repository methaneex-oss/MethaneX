#include "jarvis/core/intent.hpp"

#include <algorithm>

namespace jarvis::core {

Intent IntentModel::select(const std::vector<Goal>& goals, double threat,
                           double uncertainty, std::uint64_t cycle) const {
    const Goal* best = nullptr;
    double best_score = -1.0;
    for (const auto& goal : goals) {
        // Intent represents a currently committed objective. Pending goals remain
        // eligible for activation by the goal system but are not yet an intent.
        if (goal.status != GoalStatus::active) continue;
        const double deadline = goal.deadline_cycle == 0
            ? 0.0
            : goal.deadline_cycle > cycle
                ? 1.0 / (1.0 + static_cast<double>(goal.deadline_cycle - cycle))
                : 1.0;
        const double progress_need = std::clamp(1.0 - goal.progress, 0.0, 1.0);
        // Outcome momentum is learned from prior progress/regression. It is a
        // bounded appraisal modifier, not a hardcoded preference for any goal.
        const double learned_momentum = std::clamp(goal.outcome_momentum, -1.0, 1.0);
        const double score = std::max(0.0, goal.priority) * (0.5 + 0.5 * progress_need)
                           + 0.20 * learned_momentum * (0.5 + 0.5 * progress_need)
                           + deadline * 0.25;
        if (score > best_score) { best_score = score; best = &goal; }
    }
    if (!best) return {};

    Intent intent;
    intent.id = best->id;
    intent.description = best->description;
    intent.priority = std::clamp(best->priority + 0.10 * best->outcome_momentum, 0.0, 1.0);
    intent.progress = std::clamp(best->progress, 0.0, 1.0);
    const double deadline_urgency = best->deadline_cycle == 0
        ? 0.0
        : best->deadline_cycle > cycle
            ? 1.0 / (1.0 + static_cast<double>(best->deadline_cycle - cycle))
            : 1.0;
    intent.urgency = std::clamp(std::max(threat, deadline_urgency), 0.0, 1.0);
    intent.uncertainty = std::clamp(uncertainty, 0.0, 1.0);
    intent.confidence = std::clamp(1.0 - intent.uncertainty, 0.0, 1.0);
    intent.created_cycle = cycle;
    return intent;
}

Intent IntentModel::select_with_affect(const std::vector<Goal>& goals, double threat,
                                       double uncertainty, double valence,
                                       double arousal, double affective_uncertainty,
                                       double tension, double stability,
                                       std::uint64_t cycle) const {
    Intent intent = select(goals, threat, uncertainty, cycle);
    if (intent.id.empty()) return intent;

    const double affective_drive = std::clamp(
        valence + 0.25 * arousal - 0.25 * affective_uncertainty - 0.25 * tension,
        -1.0, 1.0);
    const double progress_need = std::clamp(1.0 - intent.progress, 0.0, 1.0);

    // Affect changes the appraisal of an already selected objective. It does not
    // contain an emotion-to-goal rule and cannot create an intent by itself.
    intent.priority = std::clamp(
        intent.priority + 0.15 * affective_drive * progress_need,
        0.0, 1.0);
    intent.urgency = std::clamp(
        intent.urgency + 0.10 * std::max(0.0, arousal + tension) * (1.0 - stability),
        0.0, 1.0);
    intent.uncertainty = std::clamp(
        intent.uncertainty + 0.20 * affective_uncertainty,
        0.0, 1.0);
    intent.confidence = std::clamp(1.0 - intent.uncertainty, 0.0, 1.0);
    return intent;
}

} // namespace jarvis::core
