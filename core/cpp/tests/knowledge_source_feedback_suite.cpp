#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <string>

using namespace jarvis::core;

namespace {
std::string feedback_attestation(std::uint64_t sequence, const std::string& key,
                                 double value, const std::string& evaluator,
                                 bool correct) {
    return "feedback-v1:" + std::to_string(sequence) + ":" + evaluator + ":" +
           key + ":" + std::to_string(value) + ":" + (correct ? "1" : "0");
}
}

int main() {
    const auto journal = std::filesystem::temp_directory_path() /
                         "jarvis_knowledge_source_feedback.bin";
    std::error_code error;
    std::filesystem::remove(journal, error);

    const KnowledgeFeedbackVerifier verifier =
        [](const KnowledgeFeedbackRequest& request) {
            const auto* value = std::get_if<double>(&request.value);
            return value != nullptr &&
                request.attestation == feedback_attestation(
                    request.claim_sequence, request.key, *value,
                    request.evaluator, request.correct);
        };
    const KnowledgeProvenanceVerifier provenance_verifier =
        [](const KnowledgeProvenanceRequest& request) {
            return request.attestation == "source-origin:" + request.source + ":" +
                       request.provenance_id;
        };
    std::uint64_t claim_sequence = 0;
    std::uint64_t humidity_sequence = 0;
    std::uint64_t pressure_sequence = 0;
    std::uint64_t wind_sequence = 0;
    std::uint64_t voltage_sequence = 0;
    double observation_quality = 0.0;
    {
        Brain brain(journal,
            {"independent-reviewer", "second-reviewer", "third-reviewer", "sensor-a"},
            verifier, provenance_verifier);
        const auto observed = brain.observe(Event{0, 0, "sensor-a", "observation",
            {{"temperature", Scalar{20.0}}, {"reliability", Scalar{0.99}},
             {"provenance_id", Scalar{std::string("origin-a")}},
             {"provenance_attestation", Scalar{std::string("source-origin:sensor-a:origin-a")}}}});
        claim_sequence = observed.event.sequence;
        assert(claim_sequence != 0);
        humidity_sequence = brain.observe(Event{0, 0, "sensor-a", "observation",
            {{"humidity", Scalar{50.0}}, {"reliability", Scalar{0.99}},
             {"provenance_id", Scalar{std::string("origin-a")}},
             {"provenance_attestation", Scalar{std::string("source-origin:sensor-a:origin-a")}}}}).event.sequence;
        pressure_sequence = brain.observe(Event{0, 0, "sensor-a", "observation",
            {{"pressure", Scalar{1013.0}}, {"reliability", Scalar{0.99}},
             {"provenance_id", Scalar{std::string("origin-a")}},
             {"provenance_attestation", Scalar{std::string("source-origin:sensor-a:origin-a")}}}}).event.sequence;
        wind_sequence = brain.observe(Event{0, 0, "sensor-a", "observation",
            {{"wind", Scalar{5.0}}, {"reliability", Scalar{0.99}},
             {"provenance_id", Scalar{std::string("origin-a")}},
             {"provenance_attestation", Scalar{std::string("source-origin:sensor-a:origin-a")}}}}).event.sequence;
        voltage_sequence = brain.observe(Event{0, 0, "sensor-a", "observation",
            {{"voltage", Scalar{230.0}}, {"reliability", Scalar{0.99}},
             {"provenance_id", Scalar{std::string("origin-a")}},
             {"provenance_attestation", Scalar{std::string("source-origin:sensor-a:origin-a")}}}}).event.sequence;
        assert(humidity_sequence != 0 && pressure_sequence != 0 &&
               wind_sequence != 0 && voltage_sequence != 0);
        assert(brain.observe(Event{0, 0, "sensor-b", "observation",
            {{"temperature", Scalar{25.0}},
             {"provenance_id", Scalar{std::string("origin-b")}},
             {"provenance_attestation", Scalar{std::string("source-origin:sensor-b:origin-b")}}}}).event.sequence != 0);

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
        assert(baseline_assessment->supporting_origins == 1);
        assert(baseline_assessment->conflicting_origins == 1);
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
        assert(initial->observations == 5);
        assert(initial->calibration_observations == 0);

        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0}, "sensor-a", true,
            feedback_attestation(claim_sequence, "temperature", 20.0, "sensor-a", true)));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0}, "untrusted-reviewer", true,
            feedback_attestation(claim_sequence, "temperature", 20.0, "untrusted-reviewer", true)));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{21.0}, "independent-reviewer", true,
            feedback_attestation(claim_sequence, "temperature", 21.0, "independent-reviewer", true)));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "reliability", Scalar{0.99}, "independent-reviewer", true,
            feedback_attestation(claim_sequence, "reliability", 0.99, "independent-reviewer", true)));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence + 100, "temperature", Scalar{20.0},
            "independent-reviewer", true, feedback_attestation(claim_sequence + 100, "temperature", 20.0, "independent-reviewer", true)));

        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", true, feedback_attestation(claim_sequence, "temperature", 20.0, "independent-reviewer", true)));
        assert(brain.record_knowledge_source_feedback(
            humidity_sequence, "humidity", Scalar{50.0},
            "independent-reviewer", true, feedback_attestation(humidity_sequence, "humidity", 50.0, "independent-reviewer", true)));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false, feedback_attestation(claim_sequence, "temperature", 20.0, "independent-reviewer", false)));
        // Different trusted evaluators cannot multiply calibration evidence
        // for one claim or turn disagreement into two independent outcomes.
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "second-reviewer", false, feedback_attestation(claim_sequence, "temperature", 20.0, "second-reviewer", false)));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "third-reviewer", true, feedback_attestation(claim_sequence, "temperature", 20.0, "third-reviewer", true)));
        assert(brain.record_knowledge_source_feedback(
            pressure_sequence, "pressure", Scalar{1013.0},
            "second-reviewer", false, feedback_attestation(pressure_sequence, "pressure", 1013.0, "second-reviewer", false)));
        assert(brain.record_knowledge_source_feedback(
            wind_sequence, "wind", Scalar{5.0},
            "third-reviewer", true, feedback_attestation(wind_sequence, "wind", 5.0, "third-reviewer", true)));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false, "forged-attestation"));

        const auto* calibrated = brain.knowledge_source("sensor-a");
        assert(calibrated != nullptr);
        assert(calibrated->calibration_observations == 4);
        assert(std::abs(calibrated->empirical_accuracy - 0.75) < 1e-12);
        assert(calibrated->observations == 5);
        assert(std::abs(calibrated->reliability - observation_quality) < 1e-12);
        const auto calibrated_assessment = brain.knowledge_assessment("temperature");
        assert(calibrated_assessment.has_value());
        assert(calibrated_assessment->status == KnowledgeStatus::disputed);
        assert(calibrated_assessment->supporting_origins == 1);
        assert(calibrated_assessment->evidence_weight > baseline_weight);
    }

    // Simulate offline journal tampering through the storage abstraction,
    // not through a mutable accessor on a live Brain. The live Brain API must
    // remain the only in-process route for mutating its journal.
    {
        Memory journal_tamper(256, journal);
        Event forged_journal_feedback{0, 0, "independent-reviewer",
            "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(claim_sequence)}},
             {"claim_source", Scalar{std::string("sensor-a")}},
             {"claim_key", Scalar{std::string("temperature")}},
             {"claim_value", Scalar{20.0}},
             {"evaluator", Scalar{std::string("independent-reviewer")}},
             {"correct", Scalar{false}},
             {"attestation", Scalar{feedback_attestation(
                 claim_sequence, "temperature", 20.0, "independent-reviewer", true)}}}};
        assert(journal_tamper.append(forged_journal_feedback) != 0);

        Event conflicting_duplicate{0, 0, "second-reviewer",
            "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(claim_sequence)}},
             {"claim_source", Scalar{std::string("sensor-a")}},
             {"claim_key", Scalar{std::string("temperature")}},
             {"claim_value", Scalar{20.0}},
             {"evaluator", Scalar{std::string("second-reviewer")}},
             {"correct", Scalar{false}},
             {"attestation", Scalar{feedback_attestation(
                 claim_sequence, "temperature", 20.0, "second-reviewer", false)}}}};
        assert(journal_tamper.append(conflicting_duplicate) != 0);

        Event invalid_duplicate{0, 0, "second-reviewer",
            "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(voltage_sequence)}},
             {"claim_source", Scalar{std::string("sensor-a")}},
             {"claim_key", Scalar{std::string("voltage")}},
             {"claim_value", Scalar{230.0}},
             {"evaluator", Scalar{std::string("second-reviewer")}},
             {"correct", Scalar{false}},
             {"attestation", Scalar{std::string("invalid-attestation")}}}};
        assert(journal_tamper.append(invalid_duplicate) != 0);
    }

    {
        Brain restored(journal,
            {"independent-reviewer", "second-reviewer", "third-reviewer", "sensor-a"},
            verifier, provenance_verifier);
        // A forged raw record with a copied evaluator name must not poison
        // the legitimate API's duplicate check after restart.
        assert(restored.record_knowledge_source_feedback(
            voltage_sequence, "voltage", Scalar{230.0}, "second-reviewer", true,
            feedback_attestation(voltage_sequence, "voltage", 230.0, "second-reviewer", true)));
        const auto* metric = restored.knowledge_source("sensor-a");
        assert(metric != nullptr);
        assert(metric->calibration_observations == 4);
        assert(std::abs(metric->empirical_accuracy - 0.75) < 1e-12);
        assert(metric->observations == 5);
        assert(std::abs(metric->reliability - observation_quality) < 1e-12);
        const auto restored_assessment = restored.knowledge_assessment("temperature");
        assert(restored_assessment.has_value());
        assert(restored_assessment->status == KnowledgeStatus::disputed);
        assert(restored_assessment->supporting_origins == 1);
        assert(restored_assessment->evidence_weight > baseline_weight);
        assert(!restored.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false, feedback_attestation(claim_sequence, "temperature", 20.0, "independent-reviewer", false)));
    }

    {
        // Without the host trust configuration, replay must fail closed rather
        // than accepting evaluator names persisted in the journal.
        Brain untrusted_restore(journal);
        const auto* metric = untrusted_restore.knowledge_source("sensor-a");
        assert(metric != nullptr);
        assert(metric->calibration_observations == 0);
        const auto untrusted_assessment =
            untrusted_restore.knowledge_assessment("temperature");
        assert(untrusted_assessment.has_value());
        assert(untrusted_assessment->supporting_origins == 0);
        assert(std::abs(untrusted_assessment->evidence_weight) < 1e-12);
        assert(untrusted_assessment->unverified_evidence_weight > 0.7);
        assert(!untrusted_restore.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", true));
    }

    std::filesystem::remove(journal, error);

    // Missing observation-quality metadata is neutral, not the old fixed 0.7
    // boost. Explicit evidence reliability takes precedence over compatibility
    // reliability, which takes precedence over perceptual confidence.
    const auto quality_journal = std::filesystem::temp_directory_path() /
                                 "jarvis_knowledge_observation_quality.bin";
    std::filesystem::remove(quality_journal, error);
    {
        Brain quality(quality_journal);
        quality.observe(Event{0, 0, "explicit-quality", "observation",
            {{"explicit_quality_fact", Scalar{true}},
             {"evidence_reliability", Scalar{0.6}},
             {"reliability", Scalar{0.99}},
             {"confidence", Scalar{0.95}}}});
        quality.observe(Event{0, 0, "legacy-quality", "observation",
            {{"legacy_quality_fact", Scalar{true}},
             {"reliability", Scalar{0.4}},
             {"confidence", Scalar{0.9}}}});
        quality.observe(Event{0, 0, "confidence-quality", "observation",
            {{"confidence_quality_fact", Scalar{true}},
             {"confidence", Scalar{0.3}}}});
        quality.observe(Event{0, 0, "missing-quality", "observation",
            {{"missing_quality_fact", Scalar{true}}}});
        assert(std::abs(quality.knowledge_source("explicit-quality")->reliability - 0.6) < 1e-12);
        assert(std::abs(quality.knowledge_source("legacy-quality")->reliability - 0.4) < 1e-12);
        assert(std::abs(quality.knowledge_source("confidence-quality")->reliability - 0.3) < 1e-12);
        assert(std::abs(quality.knowledge_source("missing-quality")->reliability - 0.5) < 1e-12);
    }
    {
        Brain quality_restored(quality_journal);
        assert(std::abs(quality_restored.knowledge_source("missing-quality")->reliability - 0.5) < 1e-12);
    }
    std::filesystem::remove(quality_journal, error);

    // Distinct source names sharing one host-verified origin count as one
    // evidence origin. A separate verified origin is required for corroboration.
    const auto provenance_journal = std::filesystem::temp_directory_path() /
                                    "jarvis_knowledge_provenance.bin";
    std::filesystem::remove(provenance_journal, error);
    const KnowledgeProvenanceVerifier provenance_verifier =
        [](const KnowledgeProvenanceRequest& request) {
            return request.value == Scalar{std::string("present")} &&
                request.attestation == "signed-origin:" + request.source + ":" +
                    request.key + ":" + request.provenance_id;
        };
    {
        Brain provenance(provenance_journal, {}, {}, provenance_verifier);
        const auto malformed_before = provenance.memory().all().size();
        const auto malformed = provenance.observe(Event{0, 0, "sensor-malformed",
            "observation", {{"device_state", Scalar{std::string("present")}},
                            {"provenance_attestation", Scalar{std::string("orphaned")}}}});
        assert(malformed.event.sequence == 0);
        assert(provenance.memory().all().size() == malformed_before);

        provenance.observe(Event{0, 0, "sensor-a", "observation",
            {{"device_state", Scalar{std::string("present")}},
             {"provenance_id", Scalar{std::string("shared-origin")}},
             {"provenance_attestation", Scalar{std::string(
                 "signed-origin:sensor-a:device_state:shared-origin")}}}});
        provenance.observe(Event{0, 0, "sensor-b", "observation",
            {{"device_state", Scalar{std::string("present")}},
             {"provenance_id", Scalar{std::string("shared-origin")}},
             {"provenance_attestation", Scalar{std::string(
                 "signed-origin:sensor-b:device_state:shared-origin")}}}});
        auto assessment = provenance.knowledge_assessment("device_state");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::provisional);
        assert(assessment->supporting_sources == 2);
        assert(assessment->supporting_origins == 1);
        assert(std::abs(assessment->evidence_weight - 0.5) < 1e-12);

        provenance.observe(Event{0, 0, "sensor-c", "observation",
            {{"device_state", Scalar{std::string("present")}},
             {"evidence_reliability", Scalar{0.7}},
             {"provenance_id", Scalar{std::string("independent-origin")}},
             {"provenance_attestation", Scalar{std::string(
                 "signed-origin:sensor-c:device_state:independent-origin")}}}});
        assessment = provenance.knowledge_assessment("device_state");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::corroborated);
        assert(assessment->supporting_sources == 3);
        assert(assessment->supporting_origins == 2);
        assert(std::abs(assessment->evidence_weight - 1.2) < 1e-12);
        assert(!provenance.knowledge_assessment("provenance_id").has_value());
        assert(!provenance.knowledge_assessment("provenance_attestation").has_value());

        // An invalid origin attestation is retained as unknown-origin evidence,
        // but cannot add an independent origin.
        provenance.observe(Event{0, 0, "sensor-forged", "observation",
            {{"unverified_state", Scalar{std::string("present")}},
             {"provenance_id", Scalar{std::string("invented-origin")}},
             {"provenance_attestation", Scalar{std::string("forged")}}}});
        provenance.observe(Event{0, 0, "sensor-forged-two", "observation",
            {{"unverified_state", Scalar{std::string("present")}},
             {"provenance_id", Scalar{std::string("another-invented-origin")}},
             {"provenance_attestation", Scalar{std::string("forged")}}}});
        const auto unverified = provenance.knowledge_assessment("unverified_state");
        assert(unverified.has_value());
        assert(unverified->status == KnowledgeStatus::provisional);
        assert(unverified->supporting_sources == 2);
        assert(unverified->supporting_origins == 0);
    }
    {
        Brain provenance_restored(provenance_journal, {}, {}, provenance_verifier);
        const auto assessment = provenance_restored.knowledge_assessment("device_state");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::corroborated);
        assert(assessment->supporting_origins == 2);
    }
    {
        // Without the host verifier, persisted origin labels are not trusted.
        Brain provenance_untrusted_restore(provenance_journal);
        const auto assessment = provenance_untrusted_restore.knowledge_assessment("device_state");
        assert(assessment.has_value());
        assert(assessment->status == KnowledgeStatus::provisional);
        assert(assessment->supporting_sources == 3);
        assert(assessment->supporting_origins == 0);
    }
    std::filesystem::remove(provenance_journal, error);

    // Conflicting authenticated adjudications are rejected regardless of
    // journal insertion order. This journal records false first, then true.
    const auto reverse_journal = std::filesystem::temp_directory_path() /
                                 "jarvis_knowledge_feedback_reverse_order.bin";
    std::filesystem::remove(reverse_journal, error);
    {
        Brain reverse(reverse_journal, {"reviewer"}, verifier);
        const auto claim = reverse.observe(Event{0, 0, "sensor-reverse", "observation",
            {{"pressure", Scalar{10.0}}}});
        assert(claim.event.sequence != 0);
        Event first_false{0, 0, "reviewer", "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(claim.event.sequence)}},
             {"claim_source", Scalar{std::string("sensor-reverse")}},
             {"claim_key", Scalar{std::string("pressure")}},
             {"claim_value", Scalar{10.0}},
             {"evaluator", Scalar{std::string("reviewer")}},
             {"correct", Scalar{false}},
             {"attestation", Scalar{feedback_attestation(
                 claim.event.sequence, "pressure", 10.0, "reviewer", false)}}}};
        Event second_true{0, 0, "reviewer", "knowledge_source_feedback",
            {{"claim_sequence", Scalar{static_cast<std::int64_t>(claim.event.sequence)}},
             {"claim_source", Scalar{std::string("sensor-reverse")}},
             {"claim_key", Scalar{std::string("pressure")}},
             {"claim_value", Scalar{10.0}},
             {"evaluator", Scalar{std::string("reviewer")}},
             {"correct", Scalar{true}},
             {"attestation", Scalar{feedback_attestation(
                 claim.event.sequence, "pressure", 10.0, "reviewer", true)}}}};
        assert(reverse.memory().append(first_false) != 0);
        assert(reverse.memory().append(second_true) != 0);
    }
    {
        Brain reverse_restored(reverse_journal, {"reviewer"}, verifier);
        const auto* metric = reverse_restored.knowledge_source("sensor-reverse");
        assert(metric != nullptr);
        assert(metric->calibration_observations == 0);
    }
    std::filesystem::remove(reverse_journal, error);

    return 0;
}
