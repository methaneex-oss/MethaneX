#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>
#include <string>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_brain_contract.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);

    {
        Brain brain(path);
        Event event{0, 0, "test", "observation", {{"health", Scalar{0.9}}, {"mode", Scalar{std::string("nominal")}}}};
        const auto observation = brain.observe(event);
        assert(observation.event.sequence == 1);
        assert(observation.event.timestamp_ns != 0);
        assert(observation.novelty >= 0.0 && observation.novelty <= 1.0);
        assert(brain.beliefs().size() == 2);

        const auto prediction = brain.predict("test.value", Scalar{0.9}, 0.8);
        assert(prediction.key == "test.value");
        assert(brain.resolve_prediction("test.value", Scalar{0.9}));
        assert(brain.memory().size() == 3);

        const auto reflection = brain.reflect();
        assert(reflection.prediction_accuracy >= 0.0 && reflection.prediction_accuracy <= 1.0);
        assert(reflection.coherence >= 0.0 && reflection.coherence <= 1.0);
    }

    {
        Brain restored(path);
        assert(restored.state().events_seen == 3);
        assert(restored.state().cycle == 3);
        assert(restored.beliefs().size() == 2);
        assert(restored.memory().size() == 3);
        const auto snapshot = restored.snapshot();
        assert(snapshot.state.events_seen == 3);
        assert(snapshot.predictions.size() == 1);
        assert(snapshot.predictions.front().resolved);
    }

    std::filesystem::remove(path, ec);
    return 0;
}
