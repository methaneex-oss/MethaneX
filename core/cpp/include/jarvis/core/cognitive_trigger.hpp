#pragma once

#include <cstddef>

namespace jarvis::core {

struct CognitiveTriggerConfig {
    double novelty_threshold{0.5};
    double urgency_threshold{0.5};
    double uncertainty_threshold{0.5};
    std::size_t max_events_per_window{64};
};

struct CognitiveTriggerSignals {
    double novelty{0.0};
    double urgency{0.0};
    double uncertainty{0.0};
};

struct CognitiveTriggerDecision {
    bool should_cognize{false};
    double priority{0.0};
};

class CognitiveTriggerPolicy {
public:
    explicit CognitiveTriggerPolicy(CognitiveTriggerConfig config = {});

    CognitiveTriggerDecision evaluate(const CognitiveTriggerSignals& signals) const noexcept;

private:
    CognitiveTriggerConfig config_;
};

} // namespace jarvis::core
