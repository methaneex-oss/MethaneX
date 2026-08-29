#include "jarvis/core/brain.hpp"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

static Event event(std::uint64_t seq, std::string source, std::string kind,
                   std::string topic, double value) {
    return Event{seq, seq, std::move(source), std::move(kind),
                 {{"topic", Scalar{std::move(topic)}}, {"value", Scalar{value}}}};
}

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis_brain_deep_suite";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);
    const auto journal = root / "continuity.bin";

    {
        Brain first(journal);
        const auto observed = first.observe(event(0, "test", "observation", "persistent", 42.0));
        assert(observed.event.sequence == 1);
        assert(first.memory().size() == 1);
        assert(first.memory().next_sequence() == 2);
        const auto snap = first.snapshot();
        assert(snap.state.events_seen == 1);
        assert(!snap.beliefs.empty());
    }
    {
        Brain restarted(journal);
        assert(restarted.memory().size() == 1);
        const auto latest = restarted.memory().latest();
        assert(latest.has_value());
        assert(latest->kind == "observation");
        assert(restarted.memory().next_sequence() == 2);
        assert(restarted.state().events_seen == 1);
        assert(!restarted.beliefs().empty());
    }

    Brain brain(root / "main.bin");

    // Memory sequence normalization is tested through Memory's public API;
    // Brain intentionally exposes memory as read-only to preserve invariants.
    Memory sequence_memory(256, root / "sequence.bin");
    assert(sequence_memory.append(event(100, "sequence", "manual", "sequence", 1.0)) == 100);
    assert(sequence_memory.append(event(1, "sequence", "manual", "sequence", 2.0)) == 101);
    const auto ordered = sequence_memory.all();
    assert(ordered.size() == 2);
    assert(ordered[0].sequence == 100 && ordered[1].sequence == 101);
    assert(sequence_memory.next_sequence() == 102);

    assert(brain.learn(Evidence{"", "", Scalar{}, -5.0}) == 0.0);
    assert(brain.predict("", Scalar{1.0}, 2.0).key.empty());
    assert(!brain.resolve_prediction("missing", Scalar{1.0}));
    assert(!brain.isolate(""));
    assert(!brain.recover("", 2.0));
    const auto before_invalid = brain.state().events_seen;
    const auto empty_observation = brain.observe(Event{0, 0, "", "", {}});
    assert(empty_observation.novelty == 0.0);
    assert(brain.state().events_seen == before_invalid + 1);

    for (int i = 0; i < 20; ++i) {
        brain.observe(event(0, "memory", "observation",
                            i % 2 ? "target" : "noise", static_cast<double>(i + 1)));
    }
    const auto recalled = brain.memory().recall(
        Attributes{{"topic", Scalar{std::string("target")}}}, 3);
    assert(recalled.size() == 3);
    assert(recalled.front().data.at("topic") == Scalar{std::string("target")});
    assert(brain.memory().recent(0).size() <= 256);
    assert(brain.memory().recent(2).size() == 2);
    assert(brain.memory().by_kind("observation", 2).size() == 2);
    assert(brain.memory().by_source("memory", 2).size() == 2);

    const auto learned = brain.learn(Evidence{"trusted", "temperature", Scalar{25.0}, 0.9});
    assert(learned >= 0.0 && learned <= 1.0);
    assert(brain.knowledge_source("trusted") != nullptr);
    const auto causal_before = brain.causal_links().size();
    brain.observe(event(0, "sensor", "observation", "temperature", 26.0));
    const auto beliefs = brain.beliefs();
    assert(!beliefs.empty());
    (void)brain.simulate(beliefs);
    assert(brain.causal_links().size() >= causal_before);

    const std::vector<CandidateAction> actions{
        {"safe", 0.9, 0.9, 0.05, 0.9},
        {"risky", 0.95, 0.2, 0.9, 0.8}
    };
    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(!brain.plan(actions, 4).steps.empty());
    (void)brain.reflect();
    (void)brain.attention();
    (void)brain.threat();

    brain.observe(Event{0, 0, "memory", "observation",
                        {{"health", Scalar{0.2}}, {"mode", Scalar{std::string("degraded")}}}});
    assert(brain.isolate("memory"));
    assert(!brain.recovery_options().empty());
    assert(brain.recover("memory", 1.0));

    brain.observe_capability("test-capability", 2.0, -1.0);
    assert(brain.isolate_capability("test-capability"));
    assert(brain.restore_capability("test-capability", 2.0, -1.0));

    brain.register_evolution_parameter("latency", 1.0);
    for (int i = 0; i < 6; ++i) brain.observe_evolution_fitness("latency", 0.8 + 0.02 * i);
    const auto proposals = brain.evolution_options();
    assert(!proposals.empty());
    const auto proposal = proposals.front();
    assert(brain.adopt_evolution(proposal));
    assert(brain.rollback_evolution(proposal.key));
    assert(!brain.adopt_evolution(EvolutionProposal{}));
    assert(!brain.rollback_evolution(""));

    brain.predict("deep.prediction", Scalar{10.0}, 2.0);
    assert(!brain.resolve_prediction("deep.prediction", Scalar{11.0}));
    assert(!brain.resolve_prediction("deep.prediction", Scalar{11.0}));
    brain.predict("correct.prediction", Scalar{10.0}, -1.0);
    assert(brain.resolve_prediction("correct.prediction", Scalar{10.0}));
    assert(brain.learning_confidence("deep.prediction") >= 0.0);
    assert(brain.learning_confidence("deep.prediction") <= 1.0);

    constexpr int workers = 16;
    constexpr int per_worker = 100;
    const auto before_events = brain.state().events_seen;
    std::vector<std::thread> threads;
    for (int w = 0; w < workers; ++w) {
        threads.emplace_back([&brain]() {
            for (int i = 0; i < per_worker; ++i) {
                brain.observe(event(0, "stress", "observation", "concurrent", 0.5));
            }
        });
    }
    for (auto& t : threads) t.join();
    assert(brain.state().events_seen >= before_events + static_cast<std::uint64_t>(workers * per_worker));

    const auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        brain.observe(event(0, "benchmark", "observation", "load", 0.25));
    }
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start).count();
    assert(elapsed >= 0);
    assert(brain.state().cycle > 0);

    const auto corrupt = root / "corrupt.bin";
    {
        Memory writer(256, corrupt);
        assert(writer.append(event(0, "recovery", "observation", "valid", 1.0)) == 1);
        assert(writer.append(event(0, "recovery", "observation", "valid", 2.0)) == 2);
    }
    {
        std::ofstream out(corrupt, std::ios::binary | std::ios::app);
        const char bytes[] = {0x7f, 0x45, 0x4c, 0x46, 0x00, 0x01, 0x02};
        out.write(bytes, sizeof(bytes));
    }
    Memory recovered_memory(256, corrupt);
    assert(recovered_memory.size() == 2);
    assert(recovered_memory.next_sequence() == 3);
    assert(recovered_memory.append(event(0, "recovery", "observation", "after", 3.0)) == 3);
    assert(recovered_memory.size() == 3);

    std::filesystem::remove_all(root, ec);
    return 0;
}
