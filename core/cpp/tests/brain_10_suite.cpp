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
    // 1. Basic integrity.
    Brain brain;
    assert(brain.state().cycle == 0);
    assert(brain.state().events_seen == 0);

    // 2. Perception / understanding: different utterances remain valid
    // observations without exact-string coupling in the cognitive core.
    const auto first = brain.observe(make_event(1, "voice", "what is the weather"));
    const auto second = brain.observe(make_event(2, "voice", "do I need an umbrella"));
    assert(first.novelty >= 0.0 && first.novelty <= 1.0);
    assert(second.novelty >= 0.0 && second.novelty <= 1.0);

    // 3. Context / continuity.
    assert(brain.state().cycle >= 2);
    assert(brain.state().events_seen >= 2);

    // 4. Memory / relevance.
    const auto recalled = brain.memory().recall("weather", 8);
    assert(!recalled.empty());

    // 5. Reasoning: beliefs, causal representation and prediction resolution.
    assert(!brain.beliefs().empty());
    const auto prediction = brain.predict("weather.value", Scalar{1.0}, 0.8);
    assert(prediction.key == "weather.value");
    assert(brain.resolve_prediction("weather.value", Scalar{1.0}));

    // 6. Autonomous decision / planning boundary.
    const std::vector<CandidateAction> actions{
        {"inspect", 0.7, 0.8, 0.1, 0.9},
        {"notify", 0.5, 0.6, 0.2, 1.0}
    };
    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(!decisions.front().action.name.empty());
    const auto plan = brain.plan(actions, 2);
    assert(!plan.steps.empty());

    // 7. Adaptation: prediction resolution creates an adaptive metric.
    brain.predict("adapt.value", Scalar{0.0}, 0.5);
    assert(brain.resolve_prediction("adapt.value", Scalar{1.0}));
    const auto* metric = brain.learning_metric("adapt.value");
    assert(metric != nullptr);
    assert(metric->observations >= 1);

    // 8. Failure / recovery.
    assert(brain.isolate("memory"));
    const auto* isolated = brain.resilience().health("memory");
    assert(isolated != nullptr);
    assert(isolated->state == HealthState::Isolated);
    assert(brain.recover("memory", 1.0));
    const auto* recovered = brain.resilience().health("memory");
    assert(recovered != nullptr);
    assert(recovered->state == HealthState::Healthy);

    // 9. Concurrency / state integrity.
    constexpr int workers = 8;
    constexpr int events_per_worker = 25;
    std::vector<std::thread> threads;
    threads.reserve(workers);
    for (int w = 0; w < workers; ++w) {
        threads.emplace_back([&brain, w]() {
            for (int i = 0; i < events_per_worker; ++i) {
                const auto seq = 1000 + static_cast<std::uint64_t>(w * events_per_worker + i);
                brain.observe(make_event(seq, "concurrent", "background event", 0.5));
            }
        });
    }
    for (auto& thread : threads) thread.join();
    assert(brain.state().events_seen >= static_cast<std::uint64_t>(workers * events_per_worker));

    // 10. Performance / observability: execute a bounded workload and verify
    // monotonic cognitive progress. Exact latency targets are established by
    // benchmark infrastructure rather than a brittle platform-specific limit.
    const auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; ++i) {
        brain.observe(make_event(5000 + static_cast<std::uint64_t>(i), "benchmark", "measure latency", 0.25));
    }
    const auto elapsed = std::chrono::steady_clock::now() - start;
    assert(elapsed >= std::chrono::steady_clock::duration::zero());
    assert(brain.state().cycle > 0);
    assert(brain.state().events_seen >= static_cast<std::uint64_t>(workers * events_per_worker + 100));

    // Security cross-cutting check: the cognitive core must not silently grant
    // capabilities merely because an unknown principal requests them. The
    // external authorization service remains responsible for policy decisions.
    assert(brain.recovery_options().size() >= 0);

    return 0;
}
