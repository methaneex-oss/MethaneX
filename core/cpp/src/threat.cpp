#include "jarvis/core/threat.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {
namespace {

double number(const Attributes& data, const char* key) {
    const auto it = data.find(key);
    if (it == data.end()) return 0.0;
    if (const auto p = std::get_if<double>(&it->second)) return std::clamp(*p, 0.0, 1.0);
    if (const auto p = std::get_if<std::int64_t>(&it->second)) return std::clamp(static_cast<double>(*p), 0.0, 1.0);
    if (const auto p = std::get_if<bool>(&it->second)) return *p ? 1.0 : 0.0;
    return 0.0;
}

} // namespace

ThreatAssessment ThreatModel::assess(const Event& event) const {
    const double anomaly = number(event.data, "anomaly");
    const double integrity = number(event.data, "integrity_risk");
    const double intrusion = number(event.data, "intrusion_risk");
    const double explicit_threat = number(event.data, "threat_score");
    const double score = std::clamp(0.30 * anomaly + 0.25 * integrity + 0.30 * intrusion + 0.15 * explicit_threat, 0.0, 1.0);
    const SecurityPosture posture = score < 0.25 ? SecurityPosture::Normal
        : score < 0.50 ? SecurityPosture::Watch
        : score < 0.80 ? SecurityPosture::Defensive
        : SecurityPosture::Containment;
    return ThreatAssessment{score, anomaly, integrity, intrusion, posture};
}

ThreatAssessment ThreatModel::aggregate(const std::vector<ThreatAssessment>& evidence) const {
    if (evidence.empty()) return {};
    ThreatAssessment result{};
    for (const auto& item : evidence) {
        result.score += item.score;
        result.anomaly += item.anomaly;
        result.integrity_risk += item.integrity_risk;
        result.intrusion_risk += item.intrusion_risk;
    }
    const double n = static_cast<double>(evidence.size());
    result.score = std::clamp(result.score / n, 0.0, 1.0);
    result.anomaly = std::clamp(result.anomaly / n, 0.0, 1.0);
    result.integrity_risk = std::clamp(result.integrity_risk / n, 0.0, 1.0);
    result.intrusion_risk = std::clamp(result.intrusion_risk / n, 0.0, 1.0);
    result.posture = result.score < 0.25 ? SecurityPosture::Normal
        : result.score < 0.50 ? SecurityPosture::Watch
        : result.score < 0.80 ? SecurityPosture::Defensive
        : SecurityPosture::Containment;
    return result;
}

} // namespace jarvis::core
