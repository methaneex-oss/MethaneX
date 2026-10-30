#include "jarvis/core/knowledge.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

double KnowledgeModel::assimilate(const KnowledgeEvidence& evidence) {
    if (evidence.source.empty() || evidence.key.empty() ||
        !std::isfinite(evidence.reliability)) return 0.0;
    auto& metric = sources_[evidence.source];
    const double reliability = std::clamp(evidence.reliability, 0.0, 1.0);
    if (metric.observations == 0) {
        metric.reliability = reliability;
    } else {
        metric.reliability = std::clamp(
            (metric.reliability * static_cast<double>(metric.observations) + reliability) /
            static_cast<double>(metric.observations + 1),
            0.0, 1.0);
    }
    ++metric.observations;

    // Preserve provenance. Repeated observations from one source increase its
    // history but never count as additional independent sources.
    const auto existing = std::find_if(
        claims_.begin(), claims_.end(), [&](const ClaimEvidence& claim) {
            return claim.source == evidence.source && claim.key == evidence.key &&
                   claim.value == evidence.value;
        });
    if (existing == claims_.end()) {
        claims_.push_back(ClaimEvidence{evidence.source, evidence.key, evidence.value, 1});
    } else {
        ++existing->observations;
    }
    return metric.reliability;
}

void KnowledgeModel::score_source(const std::string& source, bool correct) {
    if (source.empty()) return;
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

std::optional<KnowledgeAssessment> KnowledgeModel::assess(const std::string& key) const {
    struct CandidateSupport {
        Scalar value;
        std::vector<std::string> sources;
        std::size_t observations{0};
    };
    std::vector<CandidateSupport> candidates;
    for (const auto& claim : claims_) {
        if (claim.key != key) continue;
        auto candidate = std::find_if(
            candidates.begin(), candidates.end(), [&](const CandidateSupport& item) {
                return item.value == claim.value;
            });
        if (candidate == candidates.end()) {
            candidates.push_back(CandidateSupport{claim.value, {claim.source}, claim.observations});
        } else {
            if (std::find(candidate->sources.begin(), candidate->sources.end(), claim.source) ==
                candidate->sources.end()) candidate->sources.push_back(claim.source);
            candidate->observations += claim.observations;
        }
    }
    if (candidates.empty()) return std::nullopt;

    // Never select a winner from disputed evidence. This avoids insertion-order
    // dependence when competing candidates have equal or unequal support.
    const auto strongest = std::max_element(
        candidates.begin(), candidates.end(), [](const auto& left, const auto& right) {
            return left.sources.size() < right.sources.size();
        });
    KnowledgeAssessment result{};
    result.key = key;
    if (candidates.size() == 1) result.candidate = strongest->value;
    result.supporting_sources = strongest->sources.size();
    result.observations = strongest->observations;
    if (candidates.size() > 1) {
        for (const auto& candidate : candidates)
            result.conflicting_sources += candidate.sources.size();
    }
    if (candidates.size() > 1) {
        result.status = KnowledgeStatus::disputed;
    } else if (result.supporting_sources >= 2) {
        result.status = KnowledgeStatus::corroborated;
    } else {
        result.status = KnowledgeStatus::provisional;
    }
    return result;
}

} // namespace jarvis::core
