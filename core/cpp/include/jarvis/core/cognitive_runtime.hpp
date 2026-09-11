#pragma once

#include "cognitive_cycle.hpp"

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
    bool drain_on_stop{true};
};

struct CognitiveRuntimeMetrics {
    std::uint64_t accepted{0};
    std::uint64_t rejected{0};
    std::uint64_t processed{0};
    std::uint64_t dropped_results{0};
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

    // Priority is supplied by the producer/cognitive layer. Higher values run first;
    // equal priorities remain FIFO. No phrase-to-behavior mapping is embedded here.
    bool submit(CognitiveCycleInput input, double priority = 0.0);
    std::optional<CognitiveCycleResult> poll_result();
    std::size_t pending_inputs() const;
    std::size_t pending_results() const;
    CognitiveRuntimeMetrics metrics() const;

private:
    struct WorkItem {
        CognitiveCycleInput input;
        double priority{0.0};
        std::uint64_t sequence{0};
    };

    void worker_loop();

    Brain& brain_;
    CognitiveRuntimeConfig config_;
    CognitiveCycle cycle_;

    mutable std::mutex mutex_;
    std::condition_variable condition_;
    std::deque<WorkItem> inputs_;
    std::deque<CognitiveCycleResult> results_;
    CognitiveRuntimeMetrics metrics_{};
    std::thread worker_;
    std::uint64_t next_sequence_{0};
    bool running_{false};
    bool stopping_{false};
};

} // namespace jarvis::core
