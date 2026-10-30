#include "jarvis/core/brain.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
bool check(bool value, const char* message) {
    if (!value) std::cerr << "source feedback failure: " << message << '\n';
    return value;
}
}

int main() {
    const auto path = std::filesystem::temp_directory_path() /
                      "jarvis_source_feedback_journal_suite.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    std::vector<std::uint64_t> claims;
    {
        Brain brain(path);
        for (std::int64_t value : {20, 21, 22}) {
            const auto observation = brain.observe(Event{
                0, 0, "weather_sensor", "observation",
                {{"temperature", Scalar{value}}}});
            if (!check(observation.event.sequence != 0, "observation persisted")) return 1;
            claims.push_back(observation.event.sequence);
        }

        if (!check(!brain.record_knowledge_source_feedback(
                       claims[0], "temperature", Scalar{20}, "weather_sensor", true),
                   "source cannot evaluate its own claim")) return 1;
        if (!check(!brain.record_knowledge_source_feedback(
                       claims[0], "temperature", Scalar{999}, "independent_auditor", true),
                   "mismatched value is rejected before journaling")) return 1;
        if (!check(brain.memory().by_kind("knowledge_source_feedback").empty(),
                   "rejected feedback did not enter the journal")) return 1;

        if (!check(brain.record_knowledge_source_feedback(
                       claims[0], "temperature", Scalar{20}, "independent_auditor", true),
                   "valid adjudicated feedback is accepted")) return 1;
        if (!check(!brain.record_knowledge_source_feedback(
                       claims[0], "temperature", Scalar{20}, "independent_auditor", false),
                   "duplicate evaluator feedback is rejected")) return 1;
        if (!check(brain.record_knowledge_source_feedback(
                       claims[1], "temperature", Scalar{21}, "independent_auditor", false),
                   "distinct claim can receive separate adjudication")) return 1;
        if (!check(brain.record_knowledge_source_feedback(
                       claims[2], "temperature", Scalar{22}, "independent_auditor", true),
                   "third independent outcome is accepted")) return 1;

        const auto* metric = brain.knowledge_source("weather_sensor");
        if (!check(metric != nullptr && metric->calibration_observations == 3,
                   "calibration counts accepted adjudications only")) return 1;
        if (!check(metric->empirical_accuracy > 0.0 && metric->empirical_accuracy < 1.0,
                   "calibration tracks mixed correctness outcomes")) return 1;
        if (!check(brain.memory().by_kind("knowledge_source_feedback").size() == 3,
                   "only valid unique feedback events are journaled")) return 1;
    }

    {
        Brain restored(path);
        const auto* metric = restored.knowledge_source("weather_sensor");
        if (!check(metric != nullptr && metric->calibration_observations == 3,
                   "calibration is reconstructed from journal after restart")) return 1;
        if (!check(metric->empirical_accuracy > 0.0 && metric->empirical_accuracy < 1.0,
                   "replayed calibration retains correctness history")) return 1;
        if (!check(!restored.record_knowledge_source_feedback(
                       claims[0], "temperature", Scalar{20}, "independent_auditor", true),
                   "duplicate remains rejected after fresh-process replay")) return 1;
    }

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "source feedback journal integration passed\n";
    return 0;
}
