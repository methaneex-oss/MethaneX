#include "jarvis/core/cognitive_runtime.hpp"

#include <utility>

namespace jarvis::core {

CognitiveRuntime::CognitiveRuntime(Brain& brain, CognitiveRuntimeConfig config)
    : brain_(brain), config_(config), cycle_(brain) {}

CognitiveRuntime::~CognitiveRuntime() {
    stop();
}

bool CognitiveRuntime::start() {
    std::lock_guard lock(mutex_);
    if (running_) {
        return false;
    }

    stopping_ = false;
    running_ = true;
    worker_ = std::thread(&CognitiveRuntime::worker_loop, this);
    return true;
}

void CognitiveRuntime::stop() {
    {
        std::lock_guard lock(mutex_);
        if (!running_) {
            return;
        }
        stopping_ = true;
    }
    condition_.notify_one();

    if (worker_.joinable()) {
        worker_.join();
    }
}

bool CognitiveRuntime::running() const {
    std::lock_guard lock(mutex_);
    return running_;
}

bool CognitiveRuntime::submit(CognitiveCycleInput input) {
    {
        std::lock_guard lock(mutex_);
        if (!running_ || stopping_ || config_.input_capacity == 0 ||
            inputs_.size() >= config_.input_capacity) {
            return false;
        }
        inputs_.push_back(std::move(input));
    }
    condition_.notify_one();
    return true;
}

std::optional<CognitiveCycleResult> CognitiveRuntime::poll_result() {
    std::lock_guard lock(mutex_);
    if (results_.empty()) {
        return std::nullopt;
    }

    auto result = std::move(results_.front());
    results_.pop_front();
    return result;
}

std::size_t CognitiveRuntime::pending_inputs() const {
    std::lock_guard lock(mutex_);
    return inputs_.size();
}

std::size_t CognitiveRuntime::pending_results() const {
    std::lock_guard lock(mutex_);
    return results_.size();
}

void CognitiveRuntime::worker_loop() {
    for (;;) {
        CognitiveCycleInput input;
        {
            std::unique_lock lock(mutex_);
            condition_.wait(lock, [this] {
                return stopping_ || !inputs_.empty();
            });

            if (inputs_.empty() && stopping_) {
                break;
            }

            input = std::move(inputs_.front());
            inputs_.pop_front();
        }

        auto result = cycle_.run(input);

        {
            std::lock_guard lock(mutex_);
            if (config_.result_capacity != 0) {
                if (results_.size() >= config_.result_capacity) {
                    results_.pop_front();
                }
                results_.push_back(std::move(result));
            }
        }
    }

    std::lock_guard lock(mutex_);
    if (!config_.drain_on_stop) {
        inputs_.clear();
    }
    running_ = false;
    stopping_ = false;
}

} // namespace jarvis::core
