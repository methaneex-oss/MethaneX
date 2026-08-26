#pragma once

#include "event.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

struct AttentionSignal {
    std::string key;
    double salience{0.0};
    double novelty{0.0};
    double uncertainty{0.0};
    double urgency{0.0};
};

class AttentionModel {
public:
    AttentionSignal score(const Event& event, double novelty, double strongest_belief) const;
    std::vector<AttentionSignal> focus(const std::vector<Event>& events,
                                       double strongest_belief) const;
};

} // namespace jarvis::core
