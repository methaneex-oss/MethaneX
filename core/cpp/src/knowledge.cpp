#include "jarvis/core/knowledge.hpp"

#include <algorithm>

namespace jarvis::core {

double KnowledgeModel::assimilate(const Evidence& evidence) {
    auto& metric = sources_[evidence.source];
    if (metric.observations == 0) metric.reliability = std::clamp(evidence.reliability, 0.0, 1.0);
    ++metric.observations;
    return std::clamp(0.5 * metric.reliability + 0.5 * evidence.reliability, 0.0, 1.0);
}

void KnowledgeModel::score_source(const std::string& source, bool correct) {
    auto& metric = sources_[source];
    const double observation = correct ? 1.0 : 0.0;
    metric.reliability = (metric.reliability * static_cast<double>(metric.observations) + observation) /
                         static_cast<double>(metric.observations + 1);
    ++metric.observations;
}

const KnowledgeMetric* KnowledgeModel::source_metric(const std::string& source) const noexcept {
    const auto it = sources_.find(source);
    return it == sources_.end() ? nullptr : &it->second;
}

} // namespace jarvis::core
