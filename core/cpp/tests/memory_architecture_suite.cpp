#include "jarvis/core/memory.hpp"

#include <cassert>
#include <filesystem>
#include <string>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_memory_phase4.bin";
    const auto metadata_path = std::filesystem::path(path.string() + ".meta");
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(metadata_path, ec);

    Memory memory(3, path);
    const auto a = memory.append(Event{0, 1, "sensor", "observation", {{"topic", std::string("temperature")}}});
    const auto b = memory.append(Event{0, 2, "brain", "learning", {{"topic", std::string("physics")}, {"reliability", 0.9}}});
    const auto c = memory.append(Event{0, 3, "agent", "action", {{"topic", std::string("navigation")}}});
    assert(a == 1 && b == 2 && c == 3);
    assert(memory.size() == 3);

    const auto ranked = memory.recall_ranked({{"topic", std::string("physics")}}, 2);
    assert(!ranked.empty());
    assert(ranked.front().event.sequence == b);
    assert(ranked.front().confidence > 0.8);

    assert(memory.promote(a, MemoryTier::Semantic, 0.95, 0.8));
    assert(memory.promote(b, MemoryTier::Semantic, 0.9, 0.9));
    assert(memory.promote(c, MemoryTier::Procedural, 0.8, 0.8));
    assert(memory.tier_of(Event{0, 0, "", "learning", {}}) == MemoryTier::Semantic);
    assert(memory.tier_of(Event{0, 0, "", "action", {}}) == MemoryTier::Procedural);
    assert(memory.salient(2, MemoryTier::Semantic).size() == 2);

    const auto working = memory.append(Event{0, 4, "sensor", "transient", {{"topic", std::string("noise")}}});
    assert(working == 4);
    assert(memory.promote(working, MemoryTier::Working, 0.4, 0.4));
    assert(memory.working_size() == 1);
    assert(memory.forget_working(0));
    assert(memory.working_size() == 0);

    Memory restored(3, path);
    assert(restored.size() == 4);
    assert(restored.next_sequence() == 5);
    assert(restored.recent(2).size() == 2);
    assert(restored.by_kind("learning", 1).size() == 1);

    const auto restored_semantic = restored.salient(2, MemoryTier::Semantic);
    assert(restored_semantic.size() == 2);
    assert(restored_semantic[0].event.sequence == a);
    assert(restored_semantic[0].salience == 0.95);
    assert(restored_semantic[0].confidence == 0.8);
    assert(restored.tier_of(Event{0, 0, "", "learning", {}}) == MemoryTier::Semantic);
    assert(restored.tier_of(Event{0, 0, "", "action", {}}) == MemoryTier::Procedural);
    assert(restored.working_size() == 0);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(metadata_path, ec);
    return 0;
}
