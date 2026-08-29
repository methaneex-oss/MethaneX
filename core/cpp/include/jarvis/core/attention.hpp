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

// Policy is supplied as learned/runtime state. No cognitive weighting is
// hidden in the implementation; the initial state is neutral and replaceable.
struct AttentionPolicy {
    double novelty_weight{1.0};
    double uncertainty_weight{1.0};
    double urgency_weight{1.0};
};

class AttentionModel {
public:
    explicit AttentionModel(AttentionPolicy policy = {}) : policy_(policy) {}

    AttentionSignal score(const Event& event, double novelty, double strongest_belief) const;
    std::vector<AttentionSignal> focus(const std::vector<Event>& events,
                                       double strongest_belief) const;

    void reinforce(const AttentionSignal& signal, double reward);
    void suppress(const AttentionSignal& signal, double penalty);
    void set_policy(AttentionPolicy policy) noexcept { policy_ = policy; }
    AttentionPolicy policy() const noexcept;

private:
    AttentionPolicy policy_{};
};

} // namespace jarvis::core
