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
    assert(memory.latest_sequence_by_kind("observation") == a);
    assert(memory.latest_sequence_by_kind("learning") == b);
    assert(memory.latest_sequence_by_kind("missing-kind") == 0);

    const auto ranked = memory.recall_ranked({{"topic", std::string("physics")}}, 2);
    assert(!ranked.empty());
    assert(ranked.front().event.sequence == b);
    assert(ranked.front().confidence > 0.8);

    assert(memory.promote(a, MemoryTier::Semantic, 0.95, 0.8));
    assert(memory.promote(b, MemoryTier::Semantic, 0.9, 0.9));
    assert(memory.promote(c, MemoryTier::Procedural, 0.8, 0.8));
    assert(memory.consolidate(a, 1.0, 1.0, 1.0, 0.9));
    const auto consolidated = memory.recall_ranked({{"topic", std::string("temperature")}}, 1);
    assert(consolidated.size() == 1);
    assert(consolidated.front().event.sequence == a);
    assert(consolidated.front().consolidation > 0.0);
    assert(memory.tier_of(Event{0, 0, "", "learning", {}}) == MemoryTier::Semantic);
    assert(memory.tier_of(Event{0, 0, "", "action", {}}) == MemoryTier::Procedural);
    assert(memory.salient(2, MemoryTier::Semantic).size() == 2);

    // Consolidated memories should outrank otherwise equivalent, newer traces.
    const auto old_experience = memory.append(Event{0, 5, "sensor", "experience", {{"topic", std::string("navigation-experience")}}});
    const auto recent_experience = memory.append(Event{0, 6, "sensor", "experience", {{"topic", std::string("navigation-experience")}}});
    assert(old_experience == 4 && recent_experience == 5);
    for (int i = 0; i < 8; ++i)
        assert(memory.consolidate(old_experience, 0.5, 1.0, 1.0, 0.5));
    const auto experience_ranked = memory.recall_ranked({{"topic", std::string("navigation-experience")}}, 2);
    assert(experience_ranked.size() == 2);
    assert(experience_ranked.front().event.sequence == old_experience);

    const auto working = memory.append(Event{0, 4, "sensor", "transient", {{"topic", std::string("noise")}}});
    assert(working == 6);
    assert(memory.promote(working, MemoryTier::Working, 0.4, 0.4));
    assert(memory.working_size() == 1);
    assert(memory.forget_working(0));
    assert(memory.working_size() == 0);
    assert(memory.tier_of(Event{0, 0, "", "transient", {}}) == MemoryTier::Episodic);

    const auto semantic_before_restart = memory.salient(2, MemoryTier::Semantic);
    assert(semantic_before_restart.size() == 2);

    Memory restored(3, path);
    assert(restored.size() == 6);
    assert(restored.latest_sequence_by_kind("observation") == a);
    assert(restored.latest_sequence_by_kind("learning") == b);
    assert(restored.next_sequence() == 7);
    assert(restored.recent(2).size() == 2);
    assert(restored.by_kind("learning", 1).size() == 1);

    const auto restored_semantic = restored.salient(2, MemoryTier::Semantic);
    assert(restored_semantic.size() == 2);
    assert(restored_semantic[0].event.sequence == a);
    // Consolidation evidence can increase salience; persistence must preserve
    // the learned value rather than reverting to the pre-consolidation value.
    assert(restored_semantic[0].salience == 1.0);
    assert(restored_semantic[0].confidence == semantic_before_restart[0].confidence);
    const auto restored_consolidated = restored.recall_ranked({{"topic", std::string("temperature")}}, 1);
    assert(restored_consolidated.size() == 1);
    assert(restored_consolidated.front().consolidation > 0.0);
    assert(restored.tier_of(Event{0, 0, "", "learning", {}}) == MemoryTier::Semantic);
    assert(restored.tier_of(Event{0, 0, "", "action", {}}) == MemoryTier::Procedural);
    assert(restored.working_size() == 0);
    assert(restored.tier_of(Event{0, 0, "", "transient", {}}) == MemoryTier::Episodic);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(metadata_path, ec);

    // Newly appended experience must update the learned tier distribution.
    // Otherwise later experiences of the same kind cannot inherit the learned
    // placement until some unrelated promotion/consolidation rebuilds it.
    const auto learning_path = std::filesystem::temp_directory_path() / "jarvis_memory_learned_tiers.bin";
    const auto learning_metadata_path = std::filesystem::path(learning_path.string() + ".meta");
    std::filesystem::remove(learning_path, ec);
    std::filesystem::remove(learning_metadata_path, ec);
    {
        Memory developmental_memory(8, learning_path);
        const auto first = developmental_memory.append(
            Event{0, 1, "experience", "learned-kind", {{"episode", std::int64_t{1}}}});
        assert(first != 0);
        const auto outcome = developmental_memory.append(
            Event{0, 2, "brain", "action_outcome",
                  {{"action", std::string("calibrate")},
                   {"context", std::string("stabilization")},
                   {"reliability", 0.1},
                   {"evidence_reliability", 0.9}}});
        assert(outcome != 0);
        const auto recalled_outcome = developmental_memory.recall_ranked(
            {{"action", std::string("calibrate")}}, 1, "action_outcome", true);
        assert(recalled_outcome.size() == 1);
        // Operational execution reliability must not drown out reliable
        // evidence about the consequence actually observed.
        assert(recalled_outcome.front().confidence > 0.8);
        assert(developmental_memory.promote(first, MemoryTier::Semantic, 0.9, 0.9));
        const auto second = developmental_memory.append(
            Event{0, 2, "experience", "learned-kind", {{"episode", std::int64_t{2}}}});
        assert(second != 0);
        assert(developmental_memory.latest_sequence_by_kind("learned-kind") == second);
        assert(developmental_memory.latest_sequence_by_kind("action_outcome") == outcome);
        const auto semantic_experiences = developmental_memory.salient(8, MemoryTier::Semantic);
        assert(semantic_experiences.size() == 2);
        assert(semantic_experiences.back().event.sequence == second);
    }
    {
        // Rebuild the learned distribution from journal records if the
        // separately persisted metadata is missing.
        std::filesystem::remove(learning_metadata_path, ec);
        Memory reconstructed_memory(8, learning_path);
        assert(reconstructed_memory.tier_of(
            Event{0, 0, "experience", "learned-kind", {}}) == MemoryTier::Episodic);
        assert(reconstructed_memory.latest_sequence_by_kind("learned-kind") == 3);
        assert(reconstructed_memory.latest_sequence_by_kind("action_outcome") == 2);
    }
    std::filesystem::remove(learning_path, ec);
    std::filesystem::remove(learning_metadata_path, ec);
    return 0;
}
