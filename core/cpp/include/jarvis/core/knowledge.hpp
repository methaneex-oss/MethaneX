#pragma once

#include "event.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace jarvis::core {

struct KnowledgeEvidence {
    std::string source;
    std::string key;
    Scalar value;
    double reliability{0.5};
    // Host-verified identity of the underlying evidence origin. Empty means
    // provenance is unknown and must not count as independent corroboration.
    std::string provenance_id;
};

struct KnowledgeMetric {
    // Compatibility field: running mean of incoming observation quality only.
    double reliability{0.5};
    std::uint64_t observations{0};
    // Lifetime empirical source calibration is an audit signal. Assessment
    // uses it only when an explicit freshness policy admits enough recent outcomes.
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
    // Distinct reporting source identifiers; not assumed independent.
    std::size_t supporting_sources{0};
    std::size_t conflicting_sources{0};
    std::size_t observations{0};
    // Weight from distinct host-verified origins only.
    double evidence_weight{0.0};
    // Best unverified-origin weight is exposed separately and never contributes
    // to the corroboration threshold.
    double unverified_evidence_weight{0.0};
    // Distinct origins accepted by the host provenance verifier.
    std::size_t supporting_origins{0};
    std::size_t conflicting_origins{0};
};

struct KnowledgeCalibrationPolicy {
    // Both fields must be explicitly configured by the embedding host.
    // Zero in either field disables calibrated weighting by default.
    std::size_t minimum_observations{0};
    std::uint64_t maximum_age_events{0};
};

class KnowledgeModel {
public:
    double assimilate(const KnowledgeEvidence& evidence);
    // Records an externally established outcome. This API does not itself
    // establish evaluator independence or truth; callers must validate that.
    void score_source(const std::string& source, bool correct);
    void score_source(const std::string& source, bool correct, std::uint64_t sequence);
    const KnowledgeMetric* source_metric(const std::string& source) const noexcept;
    std::optional<KnowledgeAssessment> assess(const std::string& key) const;
    std::optional<KnowledgeAssessment> assess(
        const std::string& key, std::uint64_t current_sequence,
        const KnowledgeCalibrationPolicy& policy) const;

private:
    struct ClaimEvidence {
        std::string source;
        std::string key;
        Scalar value;
        std::size_t observations{0};
        double observation_quality{0.5};
        std::string provenance_id;
    };

    struct CalibrationOutcome {
        std::uint64_t sequence{0};
        bool correct{false};
    };

    std::unordered_map<std::string, KnowledgeMetric> sources_;
    std::unordered_map<std::string, std::vector<CalibrationOutcome>> calibration_outcomes_;
    std::vector<ClaimEvidence> claims_;
    std::uint64_t next_legacy_calibration_sequence_{1};
};

} // namespace jarvis::core
