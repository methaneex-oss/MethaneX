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

    const KnowledgeFeedbackVerifier verifier =
        [](const KnowledgeFeedbackRequest& request) {
            return request.attestation == "test-attestation:" + request.evaluator;
        };
    std::uint64_t claim_sequence = 0;
    double observation_quality = 0.0;
    {
        Brain brain(journal,
            {"independent-reviewer", "second-reviewer", "third-reviewer"}, verifier);
        const auto observed = brain.observe(Event{0, 0, "sensor-a", "observation",
            {{"temperature", Scalar{20.0}}, {"humidity", Scalar{50.0}}, {"reliability", Scalar{0.99}}}});
        claim_sequence = observed.event.sequence;
        assert(claim_sequence != 0);
        assert(brain.observe(Event{0, 0, "sensor-b", "observation",
            {{"temperature", Scalar{25.0}}}}).event.sequence != 0);

        // Developmental task/context labels describe the episode rather than
        // world claims. They must not be eligible for source calibration.
        const auto episode = brain.observe(Event{0, 0, "developmental_environment",
            "observation", {{"task", Scalar{std::string("route-delivery")}},
                            {"context", Scalar{std::string("warehouse")}}}});
        assert(episode.event.sequence != 0);
        assert(!brain.record_knowledge_source_feedback(
            episode.event.sequence, "task", Scalar{std::string("route-delivery")},
            "independent-reviewer", true));
        assert(!brain.record_knowledge_source_feedback(
            episode.event.sequence, "context", Scalar{std::string("warehouse")},
            "independent-reviewer", true));
        assert(brain.knowledge_source("developmental_environment") == nullptr);

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
            claim_sequence, "temperature", Scalar{20.0}, "sensor-a", true,
            "test-attestation:sensor-a"));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0}, "untrusted-reviewer", true,
            "test-attestation:untrusted-reviewer"));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{21.0}, "independent-reviewer", true,
            "test-attestation:independent-reviewer"));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "reliability", Scalar{0.99}, "independent-reviewer", true,
            "test-attestation:independent-reviewer"));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence + 100, "temperature", Scalar{20.0},
            "independent-reviewer", true, "test-attestation:independent-reviewer"));

        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", true, "test-attestation:independent-reviewer"));
        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "humidity", Scalar{50.0},
            "independent-reviewer", true, "test-attestation:independent-reviewer"));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false, "test-attestation:independent-reviewer"));
        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "second-reviewer", false, "test-attestation:second-reviewer"));
        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "third-reviewer", true, "test-attestation:third-reviewer"));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false, "forged-attestation"));

        // Bypass both public feedback routes and append directly to Memory.
        // An unauthenticated forged record must not calibrate on replay.
        Event forged_journal_feedback{0, 0, "independent-reviewer",
            "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(claim_sequence)}},
             {"claim_source", Scalar{std::string("sensor-a")}},
             {"claim_key", Scalar{std::string("temperature")}},
             {"claim_value", Scalar{20.0}},
             {"evaluator", Scalar{std::string("independent-reviewer")}},
             {"correct", Scalar{false}},
             {"attestation", Scalar{std::string("forged-attestation")}}}};
        assert(brain.memory().append(forged_journal_feedback) != 0);

        // Even authenticated duplicate adjudications with conflicting outcomes
        // are rejected as a set, rather than making replay order decide trust.
        Event conflicting_duplicate{0, 0, "independent-reviewer",
            "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(claim_sequence)}},
             {"claim_source", Scalar{std::string("sensor-a")}},
             {"claim_key", Scalar{std::string("temperature")}},
             {"claim_value", Scalar{20.0}},
             {"evaluator", Scalar{std::string("independent-reviewer")}},
             {"correct", Scalar{false}},
             {"attestation", Scalar{std::string("test-attestation:independent-reviewer")}}}};
        assert(brain.memory().append(conflicting_duplicate) != 0);

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
        Brain restored(journal,
            {"independent-reviewer", "second-reviewer", "third-reviewer"}, verifier);
        const auto* metric = restored.knowledge_source("sensor-a");
        assert(metric != nullptr);
        assert(metric->calibration_observations == 3);
        assert(std::abs(metric->empirical_accuracy - (2.0 / 3.0)) < 1e-12);
        assert(metric->observations == 2);
        assert(std::abs(metric->reliability - observation_quality) < 1e-12);
        const auto restored_assessment = restored.knowledge_assessment("temperature");
        assert(restored_assessment.has_value());
        assert(restored_assessment->status == KnowledgeStatus::disputed);
        assert(restored_assessment->evidence_weight > 0.7);
        assert(!restored.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false, "test-attestation:independent-reviewer"));
    }

    {
        // Without the host trust configuration, replay must fail closed rather
        // than accepting evaluator names persisted in the journal.
        Brain untrusted_restore(journal);
        const auto* metric = untrusted_restore.knowledge_source("sensor-a");
        assert(metric != nullptr);
        assert(metric->calibration_observations == 0);
        assert(!untrusted_restore.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", true));
    }

    std::filesystem::remove(journal, error);
    return 0;
}
