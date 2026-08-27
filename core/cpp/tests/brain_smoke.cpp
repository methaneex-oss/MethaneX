#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cstdint>
#include <filesystem>
#include <string>

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_brain_smoke.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);

    {
        jarvis::core::Brain brain(path);
        jarvis::core::Event event{0, 0, "smoke", "observation", {{"temperature", std::int64_t{25}}, {"status", std::string{"stable"}}}};
        const auto observation = brain.observe(event);
        assert(observation.event.sequence == 1);
        assert(observation.event.timestamp_ns != 0);
        assert(brain.beliefs().size() == 2);
        assert(brain.state().events_seen == 1);
        assert(brain.state().cycle == 1);
    }

    {
        jarvis::core::Brain restored(path);
        assert(restored.state().events_seen == 1);
        assert(restored.state().cycle == 1);
        assert(restored.beliefs().size() == 2);
        assert(restored.memory().size() == 1);
    }

    std::filesystem::remove(path, ec);
    return 0;
}
