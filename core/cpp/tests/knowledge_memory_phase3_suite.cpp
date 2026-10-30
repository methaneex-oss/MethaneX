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

    KnowledgeModel assessment;
    assessment.assimilate(KnowledgeEvidence{
        "sensor-a", "surface-risk", std::string("hazardous"), 0.9});
    assessment.assimilate(KnowledgeEvidence{
        "sensor-a", "surface-risk", std::string("hazardous"), 0.9});
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
        "sensor-a", "surface-risk", std::string("hazardous"), 0.9});
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(std::abs(claim->evidence_weight - repeated_weight) < 1e-12);

    // Explicit calibration affects source evidence weight independently of
    // incoming observation quality.
    assessment.score_source("sensor-a", true);
    assessment.score_source("sensor-a", true);
    assessment.score_source("sensor-a", true);
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(std::abs(claim->evidence_weight - 1.35) < 1e-12);

    assessment.assimilate(KnowledgeEvidence{
        "sensor-b", "surface-risk", std::string("hazardous"), 0.7});
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(claim->status == KnowledgeStatus::corroborated);
    assert(claim->candidate.has_value());
    assert(claim->supporting_sources == 2);

    // Conflicting evidence remains disputed even when calibrated weighting
    // strongly favours one side.
    assessment.assimilate(KnowledgeEvidence{
        "sensor-c", "surface-risk", std::string("safe"), 0.8});
    assessment.assimilate(KnowledgeEvidence{
        "sensor-d", "surface-risk", std::string("hazardous"), 0.8});
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
    tied.assimilate(KnowledgeEvidence{"a1", "claim", std::string("left"), 0.8});
    tied.assimilate(KnowledgeEvidence{"a2", "claim", std::string("left"), 0.8});
    tied.assimilate(KnowledgeEvidence{"b1", "claim", std::string("right"), 0.8});
    tied.assimilate(KnowledgeEvidence{"b2", "claim", std::string("right"), 0.8});
    const auto tied_assessment = tied.assess("claim");
    assert(tied_assessment.has_value());
    assert(tied_assessment->status == KnowledgeStatus::disputed);
    assert(!tied_assessment->candidate.has_value());
    assert(tied_assessment->supporting_sources +
           tied_assessment->conflicting_sources == 4);

    return 0;
}
