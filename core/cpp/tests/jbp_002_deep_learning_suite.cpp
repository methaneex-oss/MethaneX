#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

using namespace jarvis::core;

namespace {
Attributes state_for(const std::vector<std::string>& keys,
                     const std::vector<bool>& state) {
    Attributes attributes;
    for (std::size_t i = 0; i < keys.size(); ++i)
        attributes.emplace(keys[i], Scalar{state[i]});
    return attributes;
}

void observe_state(Brain& brain, std::uint64_t sequence,
                   const std::vector<std::string>& keys,
                   const std::vector<bool>& state) {
    const auto result = brain.observe(Event{
        0, sequence, "jbp-002-generated-environment", "observation",
        state_for(keys, state)});
    assert(result.event.sequence != 0);
}
} // namespace

int main() {
    // The generated identifiers intentionally have no domain semantics. The
    // evaluator knows the chain; the brain only receives observations.
    constexpr std::size_t relation_count = 7;
    std::vector<std::string> keys;
    keys.reserve(relation_count);
    for (std::size_t i = 0; i < relation_count; ++i)
        keys.push_back("generated_entity_" + std::to_string(4100 + i * 37));

    const auto root = std::filesystem::temp_directory_path() /
                      "jarvis_jbp_002_deep_association";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);
    const auto journal = root / "brain-journal.bin";

    std::vector<bool> state(relation_count, false);
    {
        Brain brain(journal);
        observe_state(brain, 1, keys, state);

        // Train a multi-hop relational chain through incremental experience.
        // Each transition changes only a neighboring pair. No final answer,
        // chain length, or expected retrieval result is passed to Brain.
        std::uint64_t sequence = 2;
        for (std::size_t edge = 0; edge + 1 < relation_count; ++edge) {
            state[edge] = !state[edge];
            state[edge + 1] = !state[edge + 1];
            observe_state(brain, sequence++, keys, state);
        }

        const auto learned = brain.contextual_associations(keys.front(), 8, 0.0);
        const auto reaches_end = std::find_if(
            learned.begin(), learned.end(),
            [&](const AssociationInference& inference) {
                return inference.key == keys.back() &&
                       inference.hops >= relation_count - 1;
            });
        assert(reaches_end != learned.end());
        assert(reaches_end->strength > 0.0);

        // Add contradictory experience to one interior relationship. The
        // learner should record contradictory evidence instead of silently
        // erasing its history. This is a bounded revision probe, not a claim
        // that every inferred conclusion must reverse immediately.
        const auto before_contradiction = brain.associations();
        assert(!before_contradiction.empty());
        state[1] = !state[1];
        state[2] = !state[2];
        observe_state(brain, sequence++, keys, state);
        const auto after_contradiction = brain.associations();
        assert(after_contradiction.size() >= before_contradiction.size());
        const bool tracked_counterevidence = std::any_of(
            after_contradiction.begin(), after_contradiction.end(),
            [](const Association& association) {
                return association.contradictory_observations > 0;
            });
        assert(tracked_counterevidence);
    }

    // Reconstruct a fresh Brain instance from the journal. This checks the
    // persisted association graph, not just an in-memory model object.
    {
        Brain restored(journal);
        const auto learned_after_restart =
            restored.contextual_associations(keys.front(), 8, 0.0);
        const auto reaches_end = std::find_if(
            learned_after_restart.begin(), learned_after_restart.end(),
            [&](const AssociationInference& inference) {
                return inference.key == keys.back() &&
                       inference.hops >= relation_count - 1;
            });
        assert(reaches_end != learned_after_restart.end());
        assert(reaches_end->strength > 0.0);
        std::cout << "JBP-002 stage=multi_hop_acquisition status=PASS"
                  << " relation_count=" << relation_count
                  << " inferred_hops=" << reaches_end->hops << '\n';
        std::cout << "JBP-002 stage=restart_persistence status=PASS"
                  << " restored_chain_endpoint=true\n";
        std::cout << "JBP-002 stage=counterevidence status=PASS"
                  << " contradictory_evidence_recorded=true\n";
    }

    std::filesystem::remove_all(root, ec);
    return 0;
}
