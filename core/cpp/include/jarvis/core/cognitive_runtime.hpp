#pragma once

#include "cognitive_cycle.hpp"

#include <condition_variable>
#include <cstddef>
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

class CognitiveRuntime {
public:
    CognitiveRuntime(Brain& brain, CognitiveRuntimeConfig config = {});
    ~CognitiveRuntime();

    CognitiveRuntime(const CognitiveRuntime&) = delete;
    CognitiveRuntime& operator=(const CognitiveRuntime&) = delete;

    bool start();
    void stop();
    bool running() const;

    bool submit(CognitiveCycleInput input);
    std::optional<CognitiveCycleResult> poll_result();
    std::size_t pending_inputs() const;
    std::size_t pending_results() const;

private:
    void worker_loop();

    Brain& brain_;
    CognitiveRuntimeConfig config_;
    CognitiveCycle cycle_;

    mutable std::mutex mutex_;
    std::condition_variable condition_;
    std::deque<CognitiveCycleInput> inputs_;
    std::deque<CognitiveCycleResult> results_;
    std::thread worker_;
    bool running_{false};
    bool stopping_{false};
};

} // namespace jarvis::core
