#include "jarvis/core/knowledge.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

double KnowledgeModel::assimilate(const KnowledgeEvidence& evidence) {
    if (evidence.source.empty() || evidence.key.empty() ||
        !std::isfinite(evidence.reliability)) return 0.0;
    auto& metric = sources_[evidence.source];
    const double quality = std::clamp(evidence.reliability, 0.0, 1.0);
    if (metric.observations == 0) {
        metric.reliability = quality;
    } else {
        metric.reliability = (metric.reliability * static_cast<double>(metric.observations) +
                              quality) / static_cast<double>(metric.observations + 1);
    }
    ++metric.observations;

    // One source contributes one claim weight regardless of repetition.
    const auto existing = std::find_if(
        claims_.begin(), claims_.end(), [&](const ClaimEvidence& claim) {
            return claim.source == evidence.source && claim.key == evidence.key &&
                   claim.value == evidence.value;
        });
    if (existing == claims_.end()) {
        claims_.push_back(ClaimEvidence{evidence.source, evidence.key, evidence.value, 1, quality});
    } else {
        ++existing->observations;
        existing->observation_quality +=
            (quality - existing->observation_quality) /
            static_cast<double>(existing->observations);
    }
    return metric.reliability;
}

void KnowledgeModel::score_source(const std::string& source, bool correct) {
    if (source.empty()) return;
    auto& metric = sources_[source];
    const double outcome = correct ? 1.0 : 0.0;
    metric.empirical_accuracy +=
        (outcome - metric.empirical_accuracy) /
        static_cast<double>(metric.calibration_observations + 1);
    ++metric.calibration_observations;
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
        double evidence_weight{0.0};
    };
    std::vector<CandidateSupport> candidates;
    for (const auto& claim : claims_) {
        if (claim.key != key) continue;
        auto candidate = std::find_if(
            candidates.begin(), candidates.end(), [&](const CandidateSupport& item) {
                return item.value == claim.value;
            });
        if (candidate == candidates.end()) {
            candidates.push_back(CandidateSupport{claim.value, {}, claim.observations, 0.0});
            candidate = std::prev(candidates.end());
        } else {
            candidate->observations += claim.observations;
        }
        if (std::find(candidate->sources.begin(), candidate->sources.end(), claim.source) ==
            candidate->sources.end()) {
            candidate->sources.push_back(claim.source);
            const auto metric = sources_.find(claim.source);
            // Uncalibrated sources receive a neutral prior, not an invented
            // accuracy estimate. Calibration affects weight only after three
            // explicit outcomes; it never deletes low-trust observations.
            const double trust = metric != sources_.end() &&
                                 metric->second.calibration_observations >= 3
                ? metric->second.empirical_accuracy : 0.5;
            candidate->evidence_weight +=
                claim.observation_quality * (0.5 + trust);
        }
    }
    if (candidates.empty()) return std::nullopt;

    const auto strongest = std::max_element(
        candidates.begin(), candidates.end(), [](const auto& left, const auto& right) {
            if (left.evidence_weight != right.evidence_weight)
                return left.evidence_weight < right.evidence_weight;
            return left.sources.size() < right.sources.size();
        });
    KnowledgeAssessment result{};
    result.key = key;
    if (candidates.size() == 1) result.candidate = strongest->value;
    result.supporting_sources = strongest->sources.size();
    result.observations = strongest->observations;
    result.evidence_weight = strongest->evidence_weight;
    if (candidates.size() > 1) {
        for (const auto& candidate : candidates) {
            if (candidate.value != strongest->value)
                result.conflicting_sources += candidate.sources.size();
        }
        // A weighted lead is not sufficient to erase a contradiction.
        result.status = KnowledgeStatus::disputed;
    } else if (result.supporting_sources >= 2 && result.evidence_weight >= 1.0) {
        result.status = KnowledgeStatus::corroborated;
    } else {
        result.status = KnowledgeStatus::provisional;
    }
    return result;
}

} // namespace jarvis::core
