#include "jarvis/core/knowledge.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits>

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
    if (next_legacy_calibration_sequence_ ==
        std::numeric_limits<std::uint64_t>::max()) return;
    score_source(source, correct, next_legacy_calibration_sequence_++);
}

void KnowledgeModel::score_source(
    const std::string& source, bool correct, std::uint64_t sequence) {
    if (source.empty() || sequence == 0) return;

    const auto existing = calibration_sequences_.find(sequence);
    if (existing == calibration_sequences_.end()) {
        calibration_sequences_.emplace(
            sequence, CalibrationSequence{source, correct, false});
        calibration_outcomes_[source].push_back(
            CalibrationOutcome{sequence, correct, false});
        // Keep the normal append path O(1). Full recomputation is reserved
        // for the exceptional case where a previously counted sequence is
        // later found to be ambiguous.
        auto& metric = sources_[source];
        const double outcome = correct ? 1.0 : 0.0;
        metric.empirical_accuracy +=
            (outcome - metric.empirical_accuracy) /
            static_cast<double>(metric.calibration_observations + 1);
        ++metric.calibration_observations;
        return;
    }

    // Repeated identical delivery is idempotent. Reusing one durable event
    // sequence for another source or a different verdict makes that event
    // ambiguous; invalidate it rather than retaining whichever arrived first.
    auto& prior = existing->second;
    if (prior.conflicted) return;
    if (prior.source == source && prior.correct == correct) return;

    prior.conflicted = true;
    const std::string prior_source = prior.source;
    const auto prior_history = calibration_outcomes_.find(prior_source);
    if (prior_history != calibration_outcomes_.end()) {
        for (auto& outcome : prior_history->second) {
            if (outcome.sequence == sequence) outcome.conflicted = true;
        }
    }
    if (source != prior_source) {
        calibration_outcomes_[source].push_back(
            CalibrationOutcome{sequence, correct, true});
        recompute_calibration_metric(source);
    }
    recompute_calibration_metric(prior_source);
}

void KnowledgeModel::recompute_calibration_metric(const std::string& source) {
    auto& metric = sources_[source];
    std::size_t count = 0;
    std::size_t correct = 0;
    const auto history = calibration_outcomes_.find(source);
    if (history != calibration_outcomes_.end()) {
        for (const auto& outcome : history->second) {
            if (outcome.conflicted) continue;
            ++count;
            if (outcome.correct) ++correct;
        }
    }
    metric.calibration_observations = count;
    metric.empirical_accuracy = count == 0
        ? 0.5
        : static_cast<double>(correct) / static_cast<double>(count);
}

const KnowledgeMetric* KnowledgeModel::source_metric(const std::string& source) const noexcept {
    const auto it = sources_.find(source);
    return it == sources_.end() ? nullptr : &it->second;
}

std::optional<KnowledgeAssessment> KnowledgeModel::assess(const std::string& key) const {
    // The convenience API is deliberately uncalibrated. Callers must provide
    // an explicit freshness policy before historical outcomes affect evidence.
    return assess(key, 0, KnowledgeCalibrationPolicy{});
}

std::optional<KnowledgeAssessment> KnowledgeModel::assess(
    const std::string& key, std::uint64_t current_sequence,
    const KnowledgeCalibrationPolicy& policy) const {
    const auto calibrated_accuracy = [&](const std::string& source)
        -> std::optional<double> {
        if (policy.maximum_age_events == 0 || policy.minimum_observations == 0 ||
            current_sequence == 0) return std::nullopt;
        const auto history = calibration_outcomes_.find(source);
        if (history == calibration_outcomes_.end()) return std::nullopt;
        std::size_t count = 0;
        std::size_t correct = 0;
        for (const auto& outcome : history->second) {
            if (outcome.conflicted || outcome.sequence > current_sequence ||
                current_sequence - outcome.sequence > policy.maximum_age_events)
                continue;
            ++count;
            if (outcome.correct) ++correct;
        }
        if (count < policy.minimum_observations) return std::nullopt;
        return static_cast<double>(correct) / static_cast<double>(count);
    };
    struct CandidateSupport {
        Scalar value;
        std::vector<std::string> sources;
        std::vector<std::string> origins;
        std::vector<std::string> verified_sources;
        std::vector<std::pair<std::string, double>> origin_weights;
        std::size_t observations{0};
        double evidence_weight{0.0};
        double unverified_evidence_weight{0.0};
    };
    std::vector<CandidateSupport> candidates;
    for (const auto& claim : claims_) {
        if (claim.key != key) continue;
        auto candidate = std::find_if(
            candidates.begin(), candidates.end(), [&](const CandidateSupport& item) {
                return item.value == claim.value;
            });
        if (candidate == candidates.end()) {
            candidates.push_back(CandidateSupport{claim.value, {}, {}, {}, {}, 0, 0.0, 0.0});
            candidate = std::prev(candidates.end());
        }
        candidate->observations += claim.observations;
        if (std::find(candidate->sources.begin(), candidate->sources.end(), claim.source) ==
            candidate->sources.end()) {
            candidate->sources.push_back(claim.source);
        }
        if (!claim.provenance_id.empty()) {
            if (std::find(candidate->origins.begin(), candidate->origins.end(),
                          claim.provenance_id) == candidate->origins.end()) {
                candidate->origins.push_back(claim.provenance_id);
            }
            if (std::find(candidate->verified_sources.begin(),
                          candidate->verified_sources.end(), claim.source) ==
                candidate->verified_sources.end()) {
                candidate->verified_sources.push_back(claim.source);
            }
        }
    }

    for (const auto& claim : claims_) {
        if (claim.key != key) continue;
        const auto candidate = std::find_if(
            candidates.begin(), candidates.end(), [&](const CandidateSupport& item) {
                return item.value == claim.value;
            });
        if (candidate == candidates.end()) continue;
        // If this source has verified provenance for this claim, an additional
        // unverified copy from the same source must not create a second weight.
        if (claim.provenance_id.empty() &&
            std::find(candidate->verified_sources.begin(),
                      candidate->verified_sources.end(), claim.source) !=
                candidate->verified_sources.end()) continue;

        // Calibration contributes only when the host-configured freshness
        // horizon contains enough recent, distinct claim outcomes. Lifetime
        // accuracy remains available for audit but cannot silently stay active.
        const auto recent_accuracy = calibrated_accuracy(claim.source);
        const double trust = recent_accuracy.has_value()
            ? *recent_accuracy : 0.5;
        const double source_weight =
            claim.observation_quality * (0.5 + trust);

        if (claim.provenance_id.empty()) {
            // Unknown-origin evidence remains visible but cannot add to the
            // independent evidence weight used for corroboration.
            candidate->unverified_evidence_weight = std::max(
                candidate->unverified_evidence_weight, source_weight);
            continue;
        }

        // Multiple reporters of one verified origin contribute at most that
        // origin's strongest source weight, never one weight per source string.
        const std::string origin_key =
            std::string("\x1fknown:") + claim.provenance_id;
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
        for (const auto& origin_weight : candidate.origin_weights)
            candidate.evidence_weight += origin_weight.second;
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
    result.unverified_evidence_weight = strongest->unverified_evidence_weight;
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
