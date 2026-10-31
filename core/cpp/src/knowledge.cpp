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

    // Repeated observations from one source and one verified origin update
    // that claim's quality estimate; they do not create extra evidence origins.
    const auto existing = std::find_if(
        claims_.begin(), claims_.end(), [&](const ClaimEvidence& claim) {
            return claim.source == evidence.source && claim.key == evidence.key &&
                   claim.value == evidence.value &&
                   claim.provenance_id == evidence.provenance_id;
        });
    if (existing == claims_.end()) {
        claims_.push_back(ClaimEvidence{
            evidence.source, evidence.key, evidence.value, 1, quality,
            evidence.provenance_id});
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
        std::vector<std::string> origins;
        std::vector<std::pair<std::string, double>> origin_weights;
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
            candidates.push_back(CandidateSupport{claim.value, {}, {}, {}, 0, 0.0});
            candidate = std::prev(candidates.end());
        }
        candidate->observations += claim.observations;
        if (std::find(candidate->sources.begin(), candidate->sources.end(), claim.source) ==
            candidate->sources.end()) {
            candidate->sources.push_back(claim.source);
        }

        if (!claim.provenance_id.empty() &&
            std::find(candidate->origins.begin(), candidate->origins.end(),
                      claim.provenance_id) == candidate->origins.end()) {
            candidate->origins.push_back(claim.provenance_id);
        }

        const auto metric = sources_.find(claim.source);
        // Uncalibrated sources receive a neutral prior. Calibration affects
        // evidence weight only after three explicit outcomes; it never deletes
        // low-trust observations.
        const double trust = metric != sources_.end() &&
                             metric->second.calibration_observations >= 3
            ? metric->second.empirical_accuracy : 0.5;
        const double source_weight =
            claim.observation_quality * (0.5 + trust);

        // All observations without verified provenance share one unknown-origin
        // bucket. Distinct source strings alone therefore cannot manufacture
        // independent corroboration. Multiple reporters of a verified origin
        // contribute at most that origin's strongest source weight.
        const std::string origin_key = claim.provenance_id.empty()
            ? std::string("\x1funknown")
            : std::string("\x1fknown:") + claim.provenance_id;
        const auto origin = std::find_if(
            candidate->origin_weights.begin(), candidate->origin_weights.end(),
            [&](const auto& item) { return item.first == origin_key; });
        if (origin == candidate->origin_weights.end()) {
            candidate->origin_weights.emplace_back(origin_key, source_weight);
        } else {
            origin->second = std::max(origin->second, source_weight);
        }
    }

    if (candidates.empty()) return std::nullopt;
    for (auto& candidate : candidates) {
        candidate.evidence_weight = 0.0;
        for (const auto& [_, weight] : candidate.origin_weights)
            candidate.evidence_weight += weight;
    }

    const auto strongest = std::max_element(
        candidates.begin(), candidates.end(), [](const auto& left, const auto& right) {
            if (left.evidence_weight != right.evidence_weight)
                return left.evidence_weight < right.evidence_weight;
            if (left.origins.size() != right.origins.size())
                return left.origins.size() < right.origins.size();
            return left.sources.size() < right.sources.size();
        });
    KnowledgeAssessment result{};
    result.key = key;
    if (candidates.size() == 1) result.candidate = strongest->value;
    result.supporting_sources = strongest->sources.size();
    result.supporting_origins = strongest->origins.size();
    result.observations = strongest->observations;
    result.evidence_weight = strongest->evidence_weight;
    if (candidates.size() > 1) {
        for (const auto& candidate : candidates) {
            if (candidate.value == strongest->value) continue;
            result.conflicting_sources += candidate.sources.size();
            result.conflicting_origins += candidate.origins.size();
        }
        // A weighted lead is not sufficient to erase a contradiction.
        result.status = KnowledgeStatus::disputed;
    } else if (result.supporting_origins >= 2 && result.evidence_weight >= 1.0) {
        result.status = KnowledgeStatus::corroborated;
    } else {
        result.status = KnowledgeStatus::provisional;
    }
    return result;
}

} // namespace jarvis::core
