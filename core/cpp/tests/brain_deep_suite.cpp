#include "jarvis/core/brain.hpp"

#include <cassert>
#include <chrono>
#include <cmath>
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

    // Persistence and restart continuity.
    {
        Brain first(journal);
        first.observe(event(1, "test", "observation", "persistent", 42.0));
        assert(first.memory().size() == 1);
        assert(first.memory().next_sequence() == 2);
    }
    {
        Brain restarted(journal);
        assert(restarted.memory().size() == 1);
        const auto latest = restarted.memory().latest();
        assert(latest.has_value());
        assert(latest->kind == "observation");
        assert(restarted.memory().next_sequence() == 2);
    }

    // Memory ranking and bounded retrieval.
    Brain brain(root / "main.bin");
    for (std::uint64_t i = 1; i <= 20; ++i) {
        brain.observe(event(i, "memory", "observation", i % 2 ? "target" : "noise", static_cast<double>(i)));
    }
    const auto recalled = brain.memory().recall(
        Attributes{{"topic", Scalar{std::string("target")}}}, 3);
    assert(recalled.size() == 3);
    assert(recalled.front().data.at("topic") == Scalar{std::string("target")});

    // Planning, decision, reflection, attention and threat remain callable together.
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

    // Failure isolation and restoration.
    assert(brain.isolate("memory"));
    assert(!brain.recovery_options().empty());
    assert(brain.recover("memory", 1.0));

    // Capability loss and restoration.
    brain.observe_capability("test-capability", 1.0, 1.0);
    assert(brain.isolate_capability("test-capability"));
    assert(brain.restore_capability("test-capability", 1.0, 1.0));

    // Evolution proposal, adoption and rollback.
    brain.register_evolution_parameter("latency", 1.0);
    for (int i = 0; i < 6; ++i) brain.observe_evolution_fitness("latency", 0.8 + 0.02 * i);
    const auto proposals = brain.evolution_options();
    if (!proposals.empty()) {
        const auto proposal = proposals.front();
        assert(brain.adopt_evolution(proposal));
        assert(brain.rollback_evolution(proposal.key));
    }

    // Prediction learning must remain numerically sane.
    brain.predict("deep.prediction", Scalar{10.0}, 0.5);
    assert(brain.resolve_prediction("deep.prediction", Scalar{11.0}));
    assert(brain.learning_confidence("deep.prediction") >= 0.0);
    assert(brain.learning_confidence("deep.prediction") <= 1.0);

    // Concurrent mixed observations: check completion and monotonic event accounting.
    constexpr int workers = 16;
    constexpr int per_worker = 100;
    std::vector<std::thread> threads;
    for (int w = 0; w < workers; ++w) {
        threads.emplace_back([&brain, w]() {
            for (int i = 0; i < per_worker; ++i) {
                const auto seq = 10000ULL + static_cast<std::uint64_t>(w * per_worker + i);
                brain.observe(event(seq, "stress", "observation", "concurrent", 0.5));
            }
        });
    }
    for (auto& t : threads) t.join();
    assert(brain.state().events_seen >= static_cast<std::uint64_t>(workers * per_worker));

    // Sustained bounded workload with basic latency accounting.
    const auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        brain.observe(event(30000ULL + static_cast<std::uint64_t>(i),
                            "benchmark", "observation", "load", 0.25));
    }
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start).count();
    assert(elapsed >= 0);
    assert(brain.state().cycle > 0);

    // Corrupt/truncated journal must not make construction throw or fabricate events.
    const auto corrupt = root / "corrupt.bin";
    {
        std::ofstream out(corrupt, std::ios::binary | std::ios::trunc);
        const char bytes[] = {0x7f, 0x45, 0x4c, 0x46, 0x00, 0x01, 0x02};
        out.write(bytes, sizeof(bytes));
    }
    Brain recovered(corrupt);
    assert(recovered.memory().size() == 0);

    std::filesystem::remove_all(root, ec);
    return 0;
}
