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
    return Event{seq, seq, source, "observation",
                 {{"utterance", Scalar{text}},
                  {"value", Scalar{value}},
                  {"topic", Scalar{std::string("weather")}}}};
}

int main() {
    Brain brain;
    assert(brain.state().cycle == 0);
    assert(brain.state().events_seen == 0);

    const auto first = brain.observe(make_event(1, "voice", "what is the weather"));
    const auto second = brain.observe(make_event(2, "voice", "do I need an umbrella"));
    assert(first.novelty >= 0.0 && first.novelty <= 1.0);
    assert(second.novelty >= 0.0 && second.novelty <= 1.0);

    assert(brain.state().cycle >= 2);
    assert(brain.state().events_seen >= 2);
    assert(brain.memory().latest().has_value());

    const auto recalled = brain.memory().recall(
        Attributes{{"topic", Scalar{std::string("weather")}}}, 8);
    assert(!recalled.empty());

    assert(!brain.beliefs().empty());
    const auto prediction = brain.predict("weather.value", Scalar{1.0}, 0.8);
    assert(prediction.key == "weather.value");
    assert(brain.resolve_prediction("weather.value", Scalar{1.0}));

    const std::vector<CandidateAction> actions{
        {"inspect", 0.7, 0.8, 0.1, 0.9},
        {"notify", 0.5, 0.6, 0.2, 1.0}
    };
    assert(!brain.choose(actions).empty());
    assert(!brain.plan(actions, 4).steps.empty());
    (void)brain.reflect();
    (void)brain.attention();
    (void)brain.threat();

    brain.observe(Event{0, 0, "memory", "observation",
                        {{"health", Scalar{0.2}}, {"mode", Scalar{std::string("degraded")}}}});
    assert(brain.isolate("memory"));
    assert(!brain.recovery_options().empty());
    assert(brain.recover("memory", 1.0));

    brain.observe_capability("test-capability", 1.0, 1.0);
    assert(brain.isolate_capability("test-capability"));
    assert(brain.restore_capability("test-capability", 1.0, 1.0));

    brain.register_evolution_parameter("latency", 0.5);
    for (int i = 0; i < 6; ++i) brain.observe_evolution_fitness("latency", 0.8 + 0.02 * i);
    const auto proposals = brain.evolution_options();
    assert(!proposals.empty());
    const auto proposal = proposals.front();
    assert(proposal.proposed != proposal.current);
    assert(brain.adopt_evolution(proposal));
    assert(brain.rollback_evolution(proposal.key));
    assert(!brain.adopt_evolution(EvolutionProposal{}));
    assert(!brain.rollback_evolution(""));

    assert(!brain.predict("", Scalar{1.0}, 2.0).key.size());
    assert(!brain.resolve_prediction("missing", Scalar{1.0}));

    constexpr int workers = 16;
    constexpr int per_worker = 100;
    const auto before_events = brain.state().events_seen;
    std::vector<std::thread> threads;
    for (int w = 0; w < workers; ++w) {
        threads.emplace_back([&brain]() {
            for (int i = 0; i < per_worker; ++i)
                brain.observe(make_event(0, "stress", "background event", 0.5));
        });
    }
    for (auto& t : threads) t.join();
    assert(brain.state().events_seen >= before_events + static_cast<std::uint64_t>(workers * per_worker));

    const auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i)
        brain.observe(make_event(0, "benchmark", "measure latency", 0.25));
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start).count();
    assert(elapsed >= 0);
    assert(brain.state().cycle > 0);

    assert(!brain.authorize("unknown-principal", "restricted-action"));
    return 0;
}
