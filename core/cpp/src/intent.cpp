#include "jarvis/core/intent.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

Intent IntentModel::select(const std::vector<Goal>& goals, double threat,
                           double uncertainty, std::uint64_t cycle) const {
    const Goal* best = nullptr;
    double best_score = -1.0;
    for (const auto& goal : goals) {
        if (goal.status != GoalStatus::active && goal.status != GoalStatus::pending) continue;
        const double deadline = goal.deadline_cycle > cycle
            ? 1.0 / (1.0 + static_cast<double>(goal.deadline_cycle - cycle)) : 1.0;
        const double progress_need = std::clamp(1.0 - goal.progress, 0.0, 1.0);
        const double score = std::max(0.0, goal.priority) * (0.5 + 0.5 * progress_need) + deadline * 0.25;
        if (score > best_score) { best_score = score; best = &goal; }
    }
    if (!best) return {};

    Intent intent;
    intent.id = best->id;
    intent.description = best->description;
    intent.priority = std::clamp(best->priority, 0.0, 1.0);
    intent.urgency = std::clamp(std::max(threat, best->deadline_cycle > cycle
        ? 1.0 / (1.0 + static_cast<double>(best->deadline_cycle - cycle)) : 1.0), 0.0, 1.0);
    intent.uncertainty = std::clamp(uncertainty, 0.0, 1.0);
    intent.confidence = std::clamp(1.0 - intent.uncertainty, 0.0, 1.0);
    intent.created_cycle = cycle;
    return intent;
}

} // namespace jarvis::core
