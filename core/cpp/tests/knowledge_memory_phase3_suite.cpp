#include "jarvis/core/knowledge.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <string>

using namespace jarvis::core;

int main() {
    KnowledgeModel knowledge;
    const auto first = knowledge.assimilate(
        KnowledgeEvidence{"sensor-a", "temperature", 20.0, 0.8});
    assert(std::abs(first - 0.8) < 1e-12);
    const auto* metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 1);
    assert(std::abs(metric->reliability - 0.8) < 1e-12);
    assert(metric->calibration_observations == 0);
    assert(std::abs(metric->empirical_accuracy - 0.5) < 1e-12);

    knowledge.assimilate(KnowledgeEvidence{"sensor-a", "temperature", 21.0, 0.4});
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr && metric->observations == 2);
    assert(std::abs(metric->reliability - 0.6) < 1e-12);
    assert(metric->calibration_observations == 0);

    knowledge.score_source("sensor-a", true);
    knowledge.score_source("sensor-a", true);
    knowledge.score_source("sensor-a", false);
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 2); // feedback is not an observation
    assert(metric->calibration_observations == 3);
    assert(std::abs(metric->empirical_accuracy - (2.0 / 3.0)) < 1e-12);
    assert(std::abs(metric->reliability - 0.6) < 1e-12);

    // Calibration is experience-dependent: an initially reliable source
    // degrades after incorrect adjudications and improves again after correct ones.
    KnowledgeModel changing_source;
    for (int i = 0; i < 3; ++i) changing_source.score_source("changing", true);
    assert(std::abs(changing_source.source_metric("changing")->empirical_accuracy - 1.0) < 1e-12);
    for (int i = 0; i < 3; ++i) changing_source.score_source("changing", false);
    assert(std::abs(changing_source.source_metric("changing")->empirical_accuracy - 0.5) < 1e-12);
    for (int i = 0; i < 3; ++i) changing_source.score_source("changing", true);
    assert(std::abs(changing_source.source_metric("changing")->empirical_accuracy - (2.0 / 3.0)) < 1e-12);

    // Empirical accuracy can outweigh a higher incoming quality score: a
    // repeatedly incorrect high-quality source must not dominate a lower-
    // quality source with a consistently correct calibration record.
    KnowledgeModel calibrated_competition;
    calibrated_competition.assimilate(KnowledgeEvidence{
        "high-quality-poor", "bridge-safety", std::string("unsafe"), 0.9, "origin-poor"});
    for (int i = 0; i < 3; ++i)
        calibrated_competition.score_source("high-quality-poor", false);
    calibrated_competition.assimilate(KnowledgeEvidence{
        "lower-quality-accurate", "bridge-safety", std::string("safe"), 0.4, "origin-accurate"});
    for (int i = 0; i < 3; ++i)
        calibrated_competition.score_source("lower-quality-accurate", true);
    const auto calibrated_competition_assessment =
        calibrated_competition.assess("bridge-safety", std::numeric_limits<std::uint64_t>::max(), KnowledgeCalibrationPolicy{3, std::numeric_limits<std::uint64_t>::max()});
    assert(calibrated_competition_assessment.has_value());
    assert(calibrated_competition_assessment->status == KnowledgeStatus::disputed);
    assert(!calibrated_competition_assessment->candidate.has_value());
    assert(calibrated_competition_assessment->supporting_origins == 1);
    assert(calibrated_competition_assessment->conflicting_origins == 1);
    assert(std::abs(calibrated_competition_assessment->evidence_weight - 0.6) < 1e-12);


    // The default assessment path never silently activates lifetime calibration.
    KnowledgeModel default_closed;
    default_closed.assimilate(KnowledgeEvidence{
        "default-source", "default-policy", std::string("present"), 0.8, "default-origin"});
    for (int i = 0; i < 3; ++i) default_closed.score_source("default-source", true);
    const auto default_assessment = default_closed.assess("default-policy");
    assert(default_assessment.has_value());
    assert(std::abs(default_assessment->evidence_weight - 0.8) < 1e-12);


    // One persisted feedback event sequence cannot be counted twice, even if
    // a caller attempts to submit conflicting results against the same record.
    KnowledgeModel duplicate_sequence;
    duplicate_sequence.assimilate(KnowledgeEvidence{
        "duplicate-source", "duplicate-sequence", std::string("present"), 0.8,
        "duplicate-origin"});
    duplicate_sequence.score_source("duplicate-source", true, 7);
    duplicate_sequence.score_source("duplicate-source", false, 7);
    const auto* duplicate_metric = duplicate_sequence.source_metric("duplicate-source");
    assert(duplicate_metric != nullptr);
    assert(duplicate_metric->calibration_observations == 1);
    assert(std::abs(duplicate_metric->empirical_accuracy - 1.0) < 1e-12);
    const auto duplicate_assessment = duplicate_sequence.assess(
        "duplicate-sequence", 7, KnowledgeCalibrationPolicy{1, 10});
    assert(duplicate_assessment.has_value());
    assert(std::abs(duplicate_assessment->evidence_weight - 1.2) < 1e-12);

    KnowledgeModel assessment;
    assessment.assimilate(KnowledgeEvidence{
        "sensor-a", "surface-risk", std::string("hazardous"), 0.9, "origin-a"});
    assessment.assimilate(KnowledgeEvidence{
        "sensor-a", "surface-risk", std::string("hazardous"), 0.9, "origin-a"});
    auto claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(claim->status == KnowledgeStatus::provisional);
    assert(claim->candidate.has_value());
    assert(claim->supporting_sources == 1);
    assert(claim->observations == 2);
    assert(std::abs(claim->evidence_weight - 0.9) < 1e-12);

    // Repetition by the same source does not add independent weight.
    const double repeated_weight = claim->evidence_weight;
    assessment.assimilate(KnowledgeEvidence{
        "sensor-a", "surface-risk", std::string("hazardous"), 0.9, "origin-a"});
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(std::abs(claim->evidence_weight - repeated_weight) < 1e-12);

    // Explicit calibration affects source evidence weight independently of
    // incoming observation quality.
    assessment.score_source("sensor-a", true);
    assessment.score_source("sensor-a", true);
    assessment.score_source("sensor-a", true);
    claim = assessment.assess("surface-risk", std::numeric_limits<std::uint64_t>::max(), KnowledgeCalibrationPolicy{3, std::numeric_limits<std::uint64_t>::max()});
    assert(claim.has_value());
    assert(std::abs(claim->evidence_weight - 1.35) < 1e-12);

    assessment.assimilate(KnowledgeEvidence{
        "sensor-b", "surface-risk", std::string("hazardous"), 0.7, "origin-b"});
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(claim->status == KnowledgeStatus::corroborated);
    assert(claim->candidate.has_value());
    assert(claim->supporting_sources == 2);
    assert(claim->supporting_origins == 2);

    // Two source identifiers that share one verified origin are correlated.
    // They contribute one origin's weight and cannot independently corroborate.
    KnowledgeModel correlated;
    correlated.assimilate(KnowledgeEvidence{
        "sensor-a", "origin-claim", std::string("present"), 0.8, "shared-origin"});
    correlated.assimilate(KnowledgeEvidence{
        "sensor-b", "origin-claim", std::string("present"), 0.9, "shared-origin"});
    auto correlated_assessment = correlated.assess("origin-claim");
    assert(correlated_assessment.has_value());
    assert(correlated_assessment->status == KnowledgeStatus::provisional);
    assert(correlated_assessment->supporting_sources == 2);
    assert(correlated_assessment->supporting_origins == 1);
    assert(std::abs(correlated_assessment->evidence_weight - 0.9) < 1e-12);
    correlated.assimilate(KnowledgeEvidence{
        "sensor-c", "origin-claim", std::string("present"), 0.7, "independent-origin"});
    correlated_assessment = correlated.assess("origin-claim");
    assert(correlated_assessment.has_value());
    assert(correlated_assessment->status == KnowledgeStatus::corroborated);
    assert(correlated_assessment->supporting_origins == 2);
    assert(std::abs(correlated_assessment->evidence_weight - 1.6) < 1e-12);

    // Missing provenance is unknown, not evidence that distinct source strings
    // represent independent origins.
    KnowledgeModel unknown_provenance;
    unknown_provenance.assimilate(KnowledgeEvidence{
        "sensor-x", "unknown-origin-claim", std::string("present"), 0.8});
    unknown_provenance.assimilate(KnowledgeEvidence{
        "sensor-y", "unknown-origin-claim", std::string("present"), 0.9});
    const auto unknown_assessment = unknown_provenance.assess("unknown-origin-claim");
    assert(unknown_assessment.has_value());
    assert(unknown_assessment->status == KnowledgeStatus::provisional);
    assert(unknown_assessment->supporting_sources == 2);
    assert(unknown_assessment->supporting_origins == 0);
    assert(std::abs(unknown_assessment->evidence_weight) < 1e-12);
    assert(std::abs(unknown_assessment->unverified_evidence_weight - 0.9) < 1e-12);

    // A source that first reports without provenance and later supplies a
    // verified origin must not count its own history twice.
    KnowledgeModel mixed_provenance;
    mixed_provenance.assimilate(KnowledgeEvidence{
        "sensor-mixed", "mixed-origin-claim", std::string("present"), 0.9});
    mixed_provenance.assimilate(KnowledgeEvidence{
        "sensor-mixed", "mixed-origin-claim", std::string("present"), 0.8, "verified-origin"});
    const auto mixed_assessment = mixed_provenance.assess("mixed-origin-claim");
    assert(mixed_assessment.has_value());
    assert(mixed_assessment->supporting_sources == 1);
    assert(mixed_assessment->supporting_origins == 1);
    assert(std::abs(mixed_assessment->evidence_weight - 0.8) < 1e-12);

    // Two reporters from one origin disagreeing on a value remain disputed.
    KnowledgeModel same_origin_conflict;
    same_origin_conflict.assimilate(KnowledgeEvidence{
        "sensor-left", "origin-conflict", std::string("left"), 0.8, "same-origin"});
    same_origin_conflict.assimilate(KnowledgeEvidence{
        "sensor-right", "origin-conflict", std::string("right"), 0.8, "same-origin"});
    const auto same_origin_dispute = same_origin_conflict.assess("origin-conflict");
    assert(same_origin_dispute.has_value());
    assert(same_origin_dispute->status == KnowledgeStatus::disputed);
    assert(!same_origin_dispute->candidate.has_value());
    assert(same_origin_dispute->supporting_origins == 1);
    assert(same_origin_dispute->conflicting_origins == 1);

    // Conflicting evidence remains disputed even when calibrated weighting
    // strongly favours one side.
    assessment.assimilate(KnowledgeEvidence{
        "sensor-c", "surface-risk", std::string("safe"), 0.8, "origin-c"});
    assessment.assimilate(KnowledgeEvidence{
        "sensor-d", "surface-risk", std::string("hazardous"), 0.8, "origin-d"});
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(claim->status == KnowledgeStatus::disputed);
    assert(!claim->candidate.has_value());
    assert(claim->supporting_sources == 3);
    assert(claim->conflicting_sources == 1);
    assert(!assessment.assess("unknown-claim").has_value());

    const auto metric_before = assessment.source_metric("sensor-a")->observations;
    const auto invalid_reliability = assessment.assimilate(
        KnowledgeEvidence{"sensor-a", "surface-risk", std::string("hazardous"),
                          std::numeric_limits<double>::quiet_NaN()});
    assert(invalid_reliability == 0.0);
    assert(assessment.source_metric("sensor-a")->observations == metric_before);

    KnowledgeModel tied;
    tied.assimilate(KnowledgeEvidence{"a1", "claim", std::string("left"), 0.8, "origin-a1"});
    tied.assimilate(KnowledgeEvidence{"a2", "claim", std::string("left"), 0.8, "origin-a2"});
    tied.assimilate(KnowledgeEvidence{"b1", "claim", std::string("right"), 0.8, "origin-b1"});
    tied.assimilate(KnowledgeEvidence{"b2", "claim", std::string("right"), 0.8, "origin-b2"});
    const auto tied_assessment = tied.assess("claim");
    assert(tied_assessment.has_value());
    assert(tied_assessment->status == KnowledgeStatus::disputed);
    assert(!tied_assessment->candidate.has_value());
    assert(tied_assessment->supporting_sources +
           tied_assessment->conflicting_sources == 4);


    // Repeated incorrect outcomes must reduce this source's evidential weight,
    // but must not erase the observation or silently resolve a contradiction.
    KnowledgeModel degraded_source;
    degraded_source.assimilate(KnowledgeEvidence{
        "sensor-low-trust", "bridge-condition", std::string("safe"), 0.9, "origin-low"});
    const auto uncalibrated = degraded_source.assess("bridge-condition");
    assert(uncalibrated.has_value());
    assert(std::abs(uncalibrated->evidence_weight - 0.9) < 1e-12);
    degraded_source.score_source("sensor-low-trust", false);
    degraded_source.score_source("sensor-low-trust", false);
    degraded_source.score_source("sensor-low-trust", false);
    // Inspect the calibrated source before introducing a stronger conflicting
    // source. The assessment's evidence_weight is the strongest candidate's
    // weight, not the weight of every alternative in a disputed claim.
    const auto calibrated_low_trust = degraded_source.assess("bridge-condition", std::numeric_limits<std::uint64_t>::max(), KnowledgeCalibrationPolicy{3, std::numeric_limits<std::uint64_t>::max()});
    assert(calibrated_low_trust.has_value());
    assert(calibrated_low_trust->status == KnowledgeStatus::provisional);
    assert(calibrated_low_trust->candidate.has_value());
    assert(std::abs(calibrated_low_trust->evidence_weight - 0.45) < 1e-12);

    degraded_source.assimilate(KnowledgeEvidence{
        "sensor-independent", "bridge-condition", std::string("unsafe"), 0.8, "origin-independent"});
    const auto degraded = degraded_source.assess("bridge-condition", std::numeric_limits<std::uint64_t>::max(), KnowledgeCalibrationPolicy{3, std::numeric_limits<std::uint64_t>::max()});
    assert(degraded.has_value());
    assert(degraded->status == KnowledgeStatus::disputed);
    assert(!degraded->candidate.has_value());
    assert(degraded->supporting_sources == 1);
    assert(degraded->conflicting_sources == 1);
    assert(degraded->supporting_origins == 1);
    assert(degraded->conflicting_origins == 1);
    // The independent source is now the strongest alternative (0.8), while
    // the previously calibrated source remains present at weight 0.45.
    assert(degraded_source.source_metric("sensor-low-trust")->observations == 1);
    assert(degraded_source.source_metric("sensor-low-trust")->calibration_observations == 3);

    return 0;
}
