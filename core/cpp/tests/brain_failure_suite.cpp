#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

using namespace jarvis::core;

static Event sample() {
    return Event{0, 0, "failure-test", "observation",
                  {{"topic", Scalar{std::string("failure")}}, {"value", Scalar{1.0}}}};
}

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis_brain_failure_suite";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);

    // A journal whose parent is a regular file must fail closed: no event is
    // acknowledged and cognitive counters must not advance.
    const auto blocked_parent = root / "blocked";
    {
        std::ofstream out(blocked_parent);
        out << "not-a-directory";
    }
    Brain blocked(blocked_parent / "continuity.bin");
    const auto before = blocked.state();
    const auto result = blocked.observe(sample());
    assert(result.event.sequence == 0);
    assert(blocked.state().events_seen == before.events_seen);
    assert(blocked.memory().size() == 0);

    // A healthy journal remains usable after a separate persistence failure.
    const auto healthy_path = root / "healthy" / "continuity.bin";
    Brain healthy(healthy_path);
    const auto first = healthy.observe(sample());
    assert(first.event.sequence == 1);
    assert(healthy.state().events_seen == 1);
    assert(healthy.memory().size() == 1);

    // Corrupt/truncated tails are discarded without fabricating records.
    {
        std::ofstream out(healthy_path, std::ios::binary | std::ios::app);
        const char bad_tail[] = {static_cast<char>(0xff), static_cast<char>(0x00), static_cast<char>(0x7f)};
        out.write(bad_tail, sizeof(bad_tail));
    }
    Brain recovered(healthy_path);
    assert(recovered.memory().size() == 1);
    assert(recovered.memory().next_sequence() == 2);

    std::filesystem::remove_all(root, ec);
    return 0;
}
