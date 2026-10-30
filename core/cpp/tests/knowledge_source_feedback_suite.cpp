#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <string>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() /
                         "jarvis_knowledge_source_feedback.bin";
    std::error_code error;
    std::filesystem::remove(journal, error);

    std::uint64_t claim_sequence = 0;
    double observation_quality = 0.0;
    {
        Brain brain(journal);
        const auto observed = brain.observe(Event{0, 0, "sensor-a", "observation",
            {{"temperature", Scalar{20.0}}, {"humidity", Scalar{50.0}}, {"reliability", Scalar{0.99}}}});
        claim_sequence = observed.event.sequence;
        assert(claim_sequence != 0);
        assert(brain.observe(Event{0, 0, "sensor-b", "observation",
            {{"temperature", Scalar{25.0}}}}).event.sequence != 0);
        const auto baseline_assessment = brain.knowledge_assessment("temperature");
        assert(baseline_assessment.has_value());
        const double baseline_weight = baseline_assessment->evidence_weight;
        assert(baseline_assessment->status == KnowledgeStatus::disputed);
        const auto forged = brain.observe(Event{0, 0, "external-reviewer",
            "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(claim_sequence)}},
             {"claim_source", Scalar{std::string("sensor-a")}},
             {"claim_key", Scalar{std::string("temperature")}},
             {"claim_value", Scalar{20.0}},
             {"evaluator", Scalar{std::string("external-reviewer")}},
             {"correct", Scalar{true}}}});
        assert(forged.event.sequence == 0);

        const auto* initial = brain.knowledge_source("sensor-a");
        assert(initial != nullptr);
        observation_quality = initial->reliability;
        assert(initial->observations == 2);
        assert(initial->calibration_observations == 0);

        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0}, "sensor-a", true));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{21.0}, "independent-reviewer", true));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "reliability", Scalar{0.99}, "independent-reviewer", true));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence + 100, "temperature", Scalar{20.0},
            "independent-reviewer", true));

        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", true));
        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "humidity", Scalar{50.0},
            "independent-reviewer", true));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false));
        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "second-reviewer", false));
        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "third-reviewer", true));

        const auto* calibrated = brain.knowledge_source("sensor-a");
        assert(calibrated != nullptr);
        assert(calibrated->calibration_observations == 4);
        assert(std::abs(calibrated->empirical_accuracy - 0.75) < 1e-12);
        assert(calibrated->observations == 2);
        assert(std::abs(calibrated->reliability - observation_quality) < 1e-12);
        const auto calibrated_assessment = brain.knowledge_assessment("temperature");
        assert(calibrated_assessment.has_value());
        assert(calibrated_assessment->status == KnowledgeStatus::disputed);
        assert(calibrated_assessment->evidence_weight > baseline_weight);
    }

    {
        Brain restored(journal);
        const auto* metric = restored.knowledge_source("sensor-a");
        assert(metric != nullptr);
        assert(metric->calibration_observations == 4);
        assert(std::abs(metric->empirical_accuracy - 0.75) < 1e-12);
        assert(metric->observations == 2);
        assert(std::abs(metric->reliability - observation_quality) < 1e-12);
        const auto restored_assessment = restored.knowledge_assessment("temperature");
        assert(restored_assessment.has_value());
        assert(restored_assessment->status == KnowledgeStatus::disputed);
        assert(restored_assessment->evidence_weight > 0.7);
        assert(!restored.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false));
    }

    std::filesystem::remove(journal, error);
    return 0;
}
