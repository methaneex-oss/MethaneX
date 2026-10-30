#include "jarvis/core/knowledge.hpp"

#include <cassert>
#include <limits>
#include <cmath>
#include <string>

using namespace jarvis::core;

int main() {
    KnowledgeModel knowledge;

    const auto first = knowledge.assimilate(KnowledgeEvidence{"sensor-a", "temperature", 20.0, 0.8});
    assert(std::abs(first - 0.8) < 1e-12);
    const auto* metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 1);
    assert(std::abs(metric->reliability - 0.8) < 1e-12);

    const auto second = knowledge.assimilate(KnowledgeEvidence{"sensor-a", "temperature", 21.0, 0.4});
    assert(std::abs(second - 0.6) < 1e-12);
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 2);
    assert(std::abs(metric->reliability - 0.6) < 1e-12);

    knowledge.score_source("sensor-a", true);
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 3);
    assert(std::abs(metric->reliability - (0.6 * 2.0 + 1.0) / 3.0) < 1e-12);

    knowledge.score_source("sensor-a", false);
    metric = knowledge.source_metric("sensor-a");
    assert(metric != nullptr);
    assert(metric->observations == 4);
    assert(metric->reliability >= 0.0 && metric->reliability <= 1.0);

    // Repetition by one source is not independent corroboration.
    KnowledgeModel assessment;
    assessment.assimilate(KnowledgeEvidence{"sensor-a", "surface-risk", std::string("hazardous"), 0.9});
    assessment.assimilate(KnowledgeEvidence{"sensor-a", "surface-risk", std::string("hazardous"), 0.9});
    auto claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(claim->status == KnowledgeStatus::provisional);
    assert(claim->candidate.has_value());
    assert(claim->supporting_sources == 1);
    assert(claim->observations == 2);

    // A second distinct source corroborates the candidate without converting
    // corroboration into certainty or a safety/value judgement.
    assessment.assimilate(KnowledgeEvidence{"sensor-b", "surface-risk", std::string("hazardous"), 0.7});
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(claim->status == KnowledgeStatus::corroborated);
    assert(claim->candidate.has_value());
    assert(claim->supporting_sources == 2);

    // Any incompatible value remains visible as a dispute even when more
    // sources support one side. Majority is not silently equated with truth.
    assessment.assimilate(KnowledgeEvidence{"sensor-c", "surface-risk", std::string("safe"), 0.8});
    assessment.assimilate(KnowledgeEvidence{"sensor-d", "surface-risk", std::string("hazardous"), 0.8});
    claim = assessment.assess("surface-risk");
    assert(claim.has_value());
    assert(claim->status == KnowledgeStatus::disputed);
    assert(!claim->candidate.has_value());
    assert(claim->supporting_sources == 3);
    assert(claim->conflicting_sources == 1);
    assert(!assessment.assess("unknown-claim").has_value());

    // Invalid evidence must not enter source metrics or claim history.
    const auto metric_before = assessment.source_metric("sensor-a")->observations;
    const auto invalid_reliability =
        assessment.assimilate(KnowledgeEvidence{"sensor-a", "surface-risk",
            std::string("hazardous"), std::numeric_limits<double>::quiet_NaN()});
    assert(invalid_reliability == 0.0);
    assert(assessment.source_metric("sensor-a")->observations == metric_before);

    // Dispute counts include every source attached to every competing value,
    // not only sources opposing whichever candidate happens to win max_element.
    KnowledgeModel tied;
    tied.assimilate(KnowledgeEvidence{"a1", "claim", std::string("left"), 0.8});
    tied.assimilate(KnowledgeEvidence{"a2", "claim", std::string("left"), 0.8});
    tied.assimilate(KnowledgeEvidence{"b1", "claim", std::string("right"), 0.8});
    tied.assimilate(KnowledgeEvidence{"b2", "claim", std::string("right"), 0.8});
    const auto tied_assessment = tied.assess("claim");
    assert(tied_assessment.has_value());
    assert(tied_assessment->status == KnowledgeStatus::disputed);
    assert(!tied_assessment->candidate.has_value());
    assert(tied_assessment->supporting_sources + tied_assessment->conflicting_sources == 4);


    return 0;
}
