#include "jarvis/core/attention.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

AttentionSignal AttentionModel::score(const Event& event, double novelty, double strongest_belief) const {
    const double uncertainty = 1.0 - std::clamp(strongest_belief, 0.0, 1.0);
    const double urgency = event.kind.empty() ? 0.0 :
        (event.kind.find("threat") != std::string::npos || event.kind.find("failure") != std::string::npos ? 1.0 : 0.0);
    const double salience = std::clamp(0.45 * novelty + 0.35 * uncertainty + 0.20 * urgency, 0.0, 1.0);
    return AttentionSignal{event.kind, salience, novelty, uncertainty, urgency};
}

std::vector<AttentionSignal> AttentionModel::focus(const std::vector<Event>& events,
                                                    double strongest_belief) const {
    std::vector<AttentionSignal> result;
    result.reserve(events.size());
    for (const auto& event : events) {
        result.push_back(score(event, 1.0, strongest_belief));
    }
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.salience > b.salience;
    });
    return result;
}

} // namespace jarvis::core
