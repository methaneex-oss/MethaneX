#include "jarvis/core/attention.hpp"
#include "jarvis/core/attention_state.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

namespace {

Event event_with_urgency(double urgency) {
    return Event{0, 1, "test", "event", {{"urgency", urgency}}};
}

void test_salience_is_feature_driven() {
    AttentionModel model;
    const auto low = model.score(event_with_urgency(0.0), 0.0, 1.0);
    const auto high = model.score(event_with_urgency(1.0), 1.0, 0.0);
    assert(high.salience > low.salience);
    assert(high.uncertainty > low.uncertainty);
    assert(high.urgency > low.urgency);
}

void test_policy_adapts_from_feedback() {
    AttentionModel model;
    const auto signal = model.score(event_with_urgency(1.0), 1.0, 0.0);
    const auto before = model.policy();
    model.reinforce(signal, 1.0);
    const auto after = model.policy();
    assert(after.novelty_weight >= before.novelty_weight);
    assert(after.uncertainty_weight >= before.uncertainty_weight);
    assert(after.urgency_weight >= before.urgency_weight);
}

void test_attention_state_ranks_and_learns() {
    AttentionState state;
    state.ingest(AttentionSignal{"routine", 0.2, 0.1, 0.1, 0.0}, 1);
    state.ingest(AttentionSignal{"critical", 0.9, 0.8, 0.7, 1.0}, 2);
    const auto focused = state.focus(1);
    assert(focused.size() == 1);
    assert(focused.front().key == "critical");
    const auto* context = state.get("critical");
    assert(context != nullptr);
    assert(context->observations == 1);
    const double before = context->priority;
    state.reinforce("critical", 1.0);
    assert(state.get("critical")->priority >= before);
    state.suppress("critical", 1.0);
    assert(state.get("critical")->priority <= 1.0);
}

} // namespace

int main() {
    test_salience_is_feature_driven();
    test_policy_adapts_from_feedback();
    test_attention_state_ranks_and_learns();
    std::cout << "attention_architecture_suite: PASS\n";
    return 0;
}
