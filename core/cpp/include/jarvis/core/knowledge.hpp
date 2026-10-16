#pragma once

#include "event.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>

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

class KnowledgeModel {
public:
    double assimilate(const KnowledgeEvidence& evidence);
    void score_source(const std::string& source, bool correct);
    const KnowledgeMetric* source_metric(const std::string& source) const noexcept;

private:
    std::unordered_map<std::string, KnowledgeMetric> sources_;
};

} // namespace jarvis::core
