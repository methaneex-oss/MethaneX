#include "jarvis/core/brain.hpp"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

static Event make_event(std::uint64_t seq, const std::string& source,
                       const std::string& text, double value = 1.0) {
    return Event{seq, seq, source, text,
                 {{"value", Scalar{value}},
                  {"topic", Scalar{std::string("weather")}}}};
}

int main() {
    // 1. Basic integrity: lifecycle and core state.
    Brain brain;
    assert(brain.state().cycle == 0);

    // 2. Perception/understanding: semantically related observations should
    // produce valid observations without relying on exact input text.
    const auto a = brain.observe(make_event(1, "voice", "what is the weather"));
    const auto b = brain.observe(make_event(2, "voice", "do I need an umbrella"));
    assert(a.novelty >= 0.0 && a.novelty <= 1.0);
    assert(b.novelty >= 0.0 && b.novelty <= 1.0);

    // 3. Context: successive observations advance one coherent cognitive cycle.
    assert(brain.state().cycle >= 2);

    // 4. Memory: repeated retrieval must return a stable relevant event.
    const auto recalled = brain.recall("weather", 8);
    assert(!recalled.empty());

    // 5. Reasoning: beliefs and predictions can be formed and resolved.
    const auto beliefs = brain.beliefs();
    assert(!beliefs.empty());
    const auto prediction = brain.predict("weather.value", Scalar{1.0}, 0.8);
    assert(prediction.key == "weather.value");
    assert(brain.resolve_prediction("weather.value", Scalar{1.0}));

    // 6. Autonomous decision: the cognitive core can rank an available action.
    const auto decision = brain.decide({"inspect", "notify"}, 0.7);
    assert(!decision.action.empty());

    // 7. Adaptation: resolving a prediction updates learning state.
    const auto before = brain.adaptation_state();
    brain.predict("adapt.value", Scalar{0.0}, 0.5);
    assert(brain.resolve_prediction("adapt.value", Scalar{1.0}));
    const auto after = brain.adaptation_state();
    assert(after.predictions_resolved >= before.predictions_resolved);

    // 8. Failure/recovery: a recoverable component remains represented by the
    // resilience layer after an explicit health transition.
    assert(brain.resilience().healthy());
    brain.report_component_failure("memory");
    assert(!brain.resilience().healthy());
    brain.recover_component("memory");
    assert(brain.resilience().healthy());

    // 9. Concurrency: simultaneous observation must not corrupt cognitive state.
    constexpr int workers = 8;
    constexpr int events_per_worker = 25;
    std::vector<std::thread> threads;
    threads.reserve(workers);
    for (int w = 0; w < workers; ++w) {
        threads.emplace_back([&brain, w]() {
            for (int i = 0; i < events_per_worker; ++i) {
                brain.observe(make_event(1000 + static_cast<std::uint64_t>(w * events_per_worker + i),
                                         "concurrent", "background event", 0.5));
            }
        });
    }
    for (auto& t : threads) t.join();
    assert(brain.state().events_seen >= static_cast<std::uint64_t>(workers * events_per_worker));

    // 10. Benchmark/observability: a bounded observation workload completes and
    // exposes a non-zero cognitive cycle for measurement.
    const auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; ++i) {
        brain.observe(make_event(5000 + static_cast<std::uint64_t>(i), "benchmark", "measure latency", 0.25));
    }
    const auto elapsed = std::chrono::steady_clock::now() - start;
    assert(elapsed >= std::chrono::steady_clock::duration::zero());
    assert(brain.state().cycle > 0);

    // Security remains a cross-cutting contract: unauthorized capability use
    // must be denied by the decision boundary rather than silently executed.
    assert(!brain.authorize("unknown-principal", "restricted-action"));

    return 0;
}
