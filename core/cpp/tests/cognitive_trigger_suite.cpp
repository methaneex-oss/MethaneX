#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/cognitive_trigger.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <thread>

using namespace jarvis::core;

namespace {
CognitiveCycleInput make_input() {
    CognitiveCycleInput input;
    input.observation = Event{0, 0, "trigger-test", "observation", {{"value", 1LL}}};
    input.candidate_actions = {CandidateAction{"continue", 1.0, 0.8, 0.1, 1.0}};
    input.planning_horizon = 1;
    input.memory_limit = 4;
    input.reasoning_steps = 4;
    return input;
}
}

int main() {
    CognitiveTriggerPolicy policy;

    assert(!policy.evaluate({0.1, 0.1, 0.1}).should_cognize);
    const auto novelty = policy.evaluate({0.9, 0.1, 0.1});
    assert(novelty.should_cognize);
    assert(novelty.priority > 0.0);

    const auto urgency = policy.evaluate({0.1, 0.9, 0.1});
    assert(urgency.should_cognize);
    const auto uncertainty = policy.evaluate({0.1, 0.1, 0.9});
    assert(uncertainty.should_cognize);

    CognitiveTriggerConfig weighted;
    weighted.novelty_weight = 0.0;
    weighted.urgency_weight = 2.0;
    weighted.uncertainty_weight = 0.0;
    CognitiveTriggerPolicy weighted_policy(weighted);
    assert(weighted_policy.evaluate({0.1, 0.8, 0.1}).priority == 0.8);

    const auto journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_trigger_suite.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    Brain brain(journal);

    CognitiveRuntimeConfig config;
    config.input_capacity = 8;
    config.result_capacity = 8;
    CognitiveRuntime runtime(brain, config);
    assert(runtime.start());

    assert(!runtime.submit(make_input(), {0.1, 0.1, 0.1}));
    assert(runtime.metrics().trigger_rejected == 1);
    assert(runtime.pending_inputs() == 0);

    assert(runtime.submit(make_input(), {0.9, 0.1, 0.1}));
    for (int attempt = 0; attempt < 100 && runtime.pending_results() == 0; ++attempt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(runtime.pending_results() == 1);
    assert(runtime.metrics().accepted == 1);
    assert(runtime.metrics().processed == 1);

    runtime.stop();
    std::filesystem::remove(journal, ec);
    return 0;
}
