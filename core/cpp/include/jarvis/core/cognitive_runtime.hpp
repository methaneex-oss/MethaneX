#pragma once

#include "cognitive_cycle.hpp"
#include "cognitive_trigger.hpp"
#include "cognitive_workspace.hpp"

#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <mutex>
#include <optional>
#include <thread>

namespace jarvis::core {

struct CognitiveRuntimeConfig {
    std::size_t input_capacity{256};
    std::size_t result_capacity{256};
    std::size_t feedback_capacity{256};
    bool drain_on_stop{true};
    CognitiveTriggerConfig trigger{};
};

struct CognitiveRuntimeMetrics {
    std::uint64_t accepted{0};
    std::uint64_t rejected{0};
    std::uint64_t trigger_rejected{0};
    std::uint64_t processed{0};
    std::uint64_t dropped_results{0};
    std::uint64_t feedback_accepted{0};
    std::uint64_t feedback_rejected{0};
    std::uint64_t feedback_processed{0};
};

struct CognitiveFeedback {
    std::string prediction_key;
    Scalar actual;
    std::optional<Evidence> evidence;
};

class CognitiveRuntime {
public:
    CognitiveRuntime(Brain& brain, CognitiveRuntimeConfig config = {});
    ~CognitiveRuntime();

    CognitiveRuntime(const CognitiveRuntime&) = delete;
    CognitiveRuntime& operator=(const CognitiveRuntime&) = delete;

    bool start();
    void stop();
    bool running() const;

    // Direct submission remains available to explicit callers that have already
    // decided cognition should run. Higher priority values run first; equal
    // priorities remain FIFO.
    bool submit(CognitiveCycleInput input, double priority = 0.0);

    // Event-driven submission evaluates normalized upstream cognitive signals.
    // The trigger never interprets event contents or phrases.
    bool submit(CognitiveCycleInput input, const CognitiveTriggerSignals& signals);

    // Feedback closes the runtime-level outcome loop. It can resolve a prediction,
    // assimilate evidence, or do both; it never executes an external action.
    bool submit_feedback(CognitiveFeedback feedback);

    std::optional<CognitiveCycleResult> poll_result();
    std::size_t pending_inputs() const;
    std::size_t pending_feedback() const;
    std::size_t pending_results() const;
    CognitiveRuntimeMetrics metrics() const;
    CognitiveWorkspace workspace() const;

private:
    struct WorkItem {
        CognitiveCycleInput input;
        double priority{0.0};
        std::uint64_t sequence{0};
    };

    bool enqueue(CognitiveCycleInput input, double priority);
    void process_feedback(CognitiveFeedback feedback);
    void worker_loop();

    Brain& brain_;
    CognitiveRuntimeConfig config_;
    CognitiveCycle cycle_;
    CognitiveTriggerPolicy trigger_;
    CognitiveWorkspaceStore workspace_;

    mutable std::mutex mutex_;
    std::condition_variable condition_;
    std::deque<WorkItem> inputs_;
    std::deque<CognitiveFeedback> feedback_;
    std::deque<CognitiveCycleResult> results_;
    CognitiveRuntimeMetrics metrics_{};
    std::thread worker_;
    std::uint64_t next_sequence_{0};
    bool running_{false};
    bool stopping_{false};
};

} // namespace jarvis::core
