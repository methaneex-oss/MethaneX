#pragma once

#include "event.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

enum class SecurityPosture { Normal, Watch, Defensive, Containment };

struct ThreatAssessment {
    double score{0.0};
    double anomaly{0.0};
    double integrity_risk{0.0};
    double intrusion_risk{0.0};
    SecurityPosture posture{SecurityPosture::Normal};
};

class ThreatModel {
public:
    ThreatAssessment assess(const Event& event) const;
    ThreatAssessment aggregate(const std::vector<ThreatAssessment>& evidence) const;
};

} // namespace jarvis::core
