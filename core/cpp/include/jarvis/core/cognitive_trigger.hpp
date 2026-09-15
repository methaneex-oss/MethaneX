#pragma once

namespace jarvis::core {

struct CognitiveTriggerConfig {
    double novelty_threshold{0.5};
    double urgency_threshold{0.5};
    double uncertainty_threshold{0.5};
    double novelty_weight{1.0};
    double urgency_weight{1.0};
    double uncertainty_weight{1.0};
};

// Normalized signals produced upstream by the cognitive system. The trigger
// does not interpret event attributes or map phrases to behavior.
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
