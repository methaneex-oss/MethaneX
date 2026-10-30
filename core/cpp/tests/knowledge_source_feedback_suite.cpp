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
            {{"temperature", Scalar{20.0}}}});
        claim_sequence = observed.event.sequence;
        assert(claim_sequence != 0);
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
        assert(initial->observations == 1);
        assert(initial->calibration_observations == 0);

        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0}, "sensor-a", true));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{21.0}, "independent-reviewer", true));
        assert(!brain.record_knowledge_source_feedback(
            claim_sequence + 100, "temperature", Scalar{20.0},
            "independent-reviewer", true));

        assert(brain.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
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
        assert(calibrated->calibration_observations == 3);
        assert(std::abs(calibrated->empirical_accuracy - (2.0 / 3.0)) < 1e-12);
        assert(calibrated->observations == 1);
        assert(std::abs(calibrated->reliability - observation_quality) < 1e-12);
    }

    {
        Brain restored(journal);
        const auto* metric = restored.knowledge_source("sensor-a");
        assert(metric != nullptr);
        assert(metric->calibration_observations == 3);
        assert(std::abs(metric->empirical_accuracy - (2.0 / 3.0)) < 1e-12);
        assert(metric->observations == 1);
        assert(std::abs(metric->reliability - observation_quality) < 1e-12);
        assert(!restored.record_knowledge_source_feedback(
            claim_sequence, "temperature", Scalar{20.0},
            "independent-reviewer", false));
    }

    std::filesystem::remove(journal, error);
    return 0;
}
