#include "jarvis/core/attention.hpp"

#include <algorithm>

namespace jarvis::core {

AttentionSignal AttentionModel::score(const Event& event, double novelty, double strongest_belief) const {
    const double uncertainty = 1.0 - std::clamp(strongest_belief, 0.0, 1.0);
    double urgency = 0.0;
    if (const auto it = event.data.find("urgency"); it != event.data.end()) {
        if (const auto p = std::get_if<double>(&it->second)) urgency = std::clamp(*p, 0.0, 1.0);
        else if (const auto p = std::get_if<std::int64_t>(&it->second)) urgency = std::clamp(static_cast<double>(*p), 0.0, 1.0);
        else if (const auto p = std::get_if<bool>(&it->second)) urgency = *p ? 1.0 : 0.0;
    }
    const double salience = std::clamp(0.45 * novelty + 0.35 * uncertainty + 0.20 * urgency, 0.0, 1.0);
    return AttentionSignal{event.kind, salience, novelty, uncertainty, urgency};
}

std::vector<AttentionSignal> AttentionModel::focus(const std::vector<Event>& events,
                                                    double strongest_belief) const {
    std::vector<AttentionSignal> result;
    result.reserve(events.size());
    for (const auto& event : events) result.push_back(score(event, 1.0, strongest_belief));
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.salience > b.salience;
    });
    return result;
}

} // namespace jarvis::core
