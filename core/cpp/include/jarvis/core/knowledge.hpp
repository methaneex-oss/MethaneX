#pragma once

#include "event.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

struct KnowledgeEvidence {
    std::string source;
    std::string key;
    Scalar value;
    double reliability{0.5};
};

struct KnowledgeMetric {
    // Compatibility field: running mean of incoming observation quality only.
    double reliability{0.5};
    std::uint64_t observations{0};
    // Empirical source calibration is a separate signal. It is deliberately
    // unavailable to assessment until enough explicit outcomes have accrued.
    double empirical_accuracy{0.5};
    std::uint64_t calibration_observations{0};
};

enum class KnowledgeStatus : std::uint8_t {
    provisional,
    corroborated,
    disputed,
};

struct KnowledgeAssessment {
    std::string key;
    std::optional<Scalar> candidate;
    KnowledgeStatus status{KnowledgeStatus::provisional};
    std::size_t supporting_sources{0};
    std::size_t conflicting_sources{0};
    std::size_t observations{0};
    double evidence_weight{0.0};
};

class KnowledgeModel {
public:
    double assimilate(const KnowledgeEvidence& evidence);
    // Records an externally established outcome. This API does not itself
    // establish evaluator independence or truth; callers must validate that.
    void score_source(const std::string& source, bool correct);
    const KnowledgeMetric* source_metric(const std::string& source) const noexcept;
    std::optional<KnowledgeAssessment> assess(const std::string& key) const;

private:
    struct ClaimEvidence {
        std::string source;
        std::string key;
        Scalar value;
        std::size_t observations{0};
        double observation_quality{0.5};
    };

    std::unordered_map<std::string, KnowledgeMetric> sources_;
    std::vector<ClaimEvidence> claims_;
};

} // namespace jarvis::core
