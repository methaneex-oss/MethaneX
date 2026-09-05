#include "jarvis/core/cognitive_runtime.hpp"

#include <algorithm>
#include <cmath>
#include <exception>
#include <utility>

namespace jarvis::core {
namespace {

double finite_priority(double value) noexcept {
    return std::isfinite(value) ? value : 0.0;
}

} // namespace

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
            if (worker_.joinable()) {
                // The worker can only become non-running after reaching this point.
                // Joining here prevents a finished worker from being left joinable.
            } else {
                return;
            }
        } else {
            stopping_ = true;
        }
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

bool CognitiveRuntime::submit(CognitiveCycleInput input, double priority) {
    {
        std::lock_guard lock(mutex_);
        if (!running_ || stopping_ || config_.input_capacity == 0 ||
            inputs_.size() >= config_.input_capacity) {
            ++metrics_.rejected;
            return false;
        }

        WorkItem item{std::move(input), finite_priority(priority), ++next_sequence_};
        const auto position = std::find_if(inputs_.begin(), inputs_.end(),
            [&](const WorkItem& queued) { return item.priority > queued.priority; });
        inputs_.insert(position, std::move(item));
        ++metrics_.accepted;
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

CognitiveRuntimeMetrics CognitiveRuntime::metrics() const {
    std::lock_guard lock(mutex_);
    return metrics_;
}

void CognitiveRuntime::worker_loop() {
    for (;;) {
        WorkItem item;
        {
            std::unique_lock lock(mutex_);
            condition_.wait(lock, [this] {
                return stopping_ || !inputs_.empty();
            });

            if (inputs_.empty() && stopping_) {
                break;
            }

            item = std::move(inputs_.front());
            inputs_.pop_front();
        }

        try {
            auto result = cycle_.run(item.input);

            std::lock_guard lock(mutex_);
            if (config_.result_capacity != 0) {
                if (results_.size() >= config_.result_capacity) {
                    results_.pop_front();
                    ++metrics_.dropped_results;
                }
                results_.push_back(std::move(result));
            }
            ++metrics_.processed;
        } catch (const std::exception&) {
            std::lock_guard lock(mutex_);
            ++metrics_.processed;
        } catch (...) {
            std::lock_guard lock(mutex_);
            ++metrics_.processed;
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
