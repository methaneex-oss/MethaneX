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
    double reliability{0.5};
    std::uint64_t observations{0};
};

// Corroboration is deliberately weaker than verification. Independent sources
// can support a candidate, but this status alone never proves truth or safety.
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
};

class KnowledgeModel {
public:
    double assimilate(const KnowledgeEvidence& evidence);
    void score_source(const std::string& source, bool correct);
    const KnowledgeMetric* source_metric(const std::string& source) const noexcept;
    std::optional<KnowledgeAssessment> assess(const std::string& key) const;

private:
    struct ClaimEvidence {
        std::string source;
        std::string key;
        Scalar value;
        std::size_t observations{0};
    };

    std::unordered_map<std::string, KnowledgeMetric> sources_;
    std::vector<ClaimEvidence> claims_;
};

} // namespace jarvis::core
