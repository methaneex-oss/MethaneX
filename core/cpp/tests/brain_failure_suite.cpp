#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

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

    // A middle-record failure must not destroy the original journal. The
    // active journal recovers to the verified prefix, while the full corrupt
    // file is retained for forensic/manual recovery.
    const auto middle_path = root / "middle" / "continuity.bin";
    std::filesystem::create_directories(middle_path.parent_path(), ec);
    {
        Memory journal(32, middle_path);
        assert(journal.append(Event{0, 0, "journal-test", "first-record", {}}) == 1);
        assert(journal.append(Event{0, 0, "journal-test", "middle-record", {}}) == 2);
        assert(journal.append(Event{0, 0, "journal-test", "last-record", {}}) == 3);
    }
    std::vector<char> original;
    {
        std::ifstream in(middle_path, std::ios::binary);
        original.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    }
    const std::string marker = "middle-record";
    const auto marker_it = std::search(original.begin(), original.end(),
                                       marker.begin(), marker.end());
    assert(marker_it != original.end());
    const auto marker_offset = static_cast<std::size_t>(marker_it - original.begin());
    assert(marker_offset >= sizeof(std::uint64_t));
    const std::uint64_t invalid_length = (1ULL << 30) + 1;
    std::memcpy(original.data() + marker_offset - sizeof(invalid_length),
                &invalid_length, sizeof(invalid_length));
    {
        std::ofstream out(middle_path, std::ios::binary | std::ios::trunc);
        out.write(original.data(), static_cast<std::streamsize>(original.size()));
        assert(out.good());
    }

    const auto backup_path = std::filesystem::path(middle_path.string() + ".recovery-backup");
    {
        Memory recovered_middle(32, middle_path);
        assert(recovered_middle.size() == 1);
        assert(recovered_middle.next_sequence() == 2);
        assert(std::filesystem::exists(backup_path));
        assert(std::filesystem::file_size(backup_path) == original.size());

        std::vector<char> backup;
        std::ifstream in(backup_path, std::ios::binary);
        backup.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
        assert(backup == original);

        assert(recovered_middle.append(
            Event{0, 0, "journal-test", "after-recovery", {}}) == 2);
    }
    {
        Memory restarted_middle(32, middle_path);
        assert(restarted_middle.size() == 2);
        const auto all = restarted_middle.all();
        assert(all[0].kind == "first-record");
        assert(all[1].kind == "after-recovery");
        assert(restarted_middle.next_sequence() == 3);
    }

    std::filesystem::remove_all(root, ec);
    return 0;
}
