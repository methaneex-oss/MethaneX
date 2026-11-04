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

CognitiveWorkspace make_workspace(const CognitiveCycleResult& result, const Brain& brain) {
    CognitiveWorkspace workspace;
    workspace.observation = result.context.observation;
    workspace.memories = result.context.memories;
    workspace.beliefs = result.context.beliefs;
    workspace.causal_links = result.context.causal_links;
    workspace.predictions = result.context.predictions;
    workspace.reasoning = result.context.reasoning;
    workspace.goals = result.context.eligible_goals;
    if (!result.context.selected_goal.id.empty()) workspace.selected_goal = result.context.selected_goal;
    workspace.plan = result.context.plan;
    workspace.decision_context = result.context.decision_context;
    workspace.decisions = result.context.decisions;
    workspace.action_assessments = result.context.action_assessments;

    const auto intent = brain.intent();
    if (!intent.id.empty()) {
        workspace.intent = intent;
        workspace.strategy = brain.strategy();
    }
    workspace.reflection = result.context.reflection;
    return workspace;
}

} // namespace

CognitiveRuntime::CognitiveRuntime(Brain& brain, CognitiveRuntimeConfig config)
    : brain_(brain), config_(config), cycle_(brain), trigger_(config_.trigger) {}

CognitiveRuntime::~CognitiveRuntime() { stop(); }

bool CognitiveRuntime::start() {
    std::lock_guard lock(mutex_);
    if (running_) return false;
    stopping_ = false;
    running_ = true;
    worker_ = std::thread(&CognitiveRuntime::worker_loop, this);
    return true;
}

void CognitiveRuntime::stop() {
    {
        std::lock_guard lock(mutex_);
        if (!running_ && !worker_.joinable()) return;
        stopping_ = true;
    }
    condition_.notify_one();
    if (worker_.joinable()) worker_.join();
}

bool CognitiveRuntime::running() const {
    std::lock_guard lock(mutex_);
    return running_;
}

bool CognitiveRuntime::submit(CognitiveCycleInput input, double priority) {
    return enqueue(std::move(input), finite_priority(priority));
}

bool CognitiveRuntime::submit(CognitiveCycleInput input, const CognitiveTriggerSignals& signals) {
    const auto decision = trigger_.evaluate(signals);
    if (!decision.should_cognize) {
        std::lock_guard lock(mutex_);
        ++metrics_.trigger_rejected;
        return false;
    }
    return enqueue(std::move(input), decision.priority);
}

bool CognitiveRuntime::submit_feedback(CognitiveFeedback feedback) {
    const bool has_prediction = !feedback.prediction_key.empty();
    const bool has_evidence = feedback.evidence.has_value() && !feedback.evidence->key.empty();
    if (!has_prediction && !has_evidence) {
        std::lock_guard lock(mutex_);
        ++metrics_.feedback_rejected;
        return false;
    }

    {
        std::lock_guard lock(mutex_);
        if (!running_ || stopping_ || config_.feedback_capacity == 0 ||
            feedback_.size() >= config_.feedback_capacity) {
            ++metrics_.feedback_rejected;
            return false;
        }
        feedback_.push_back(std::move(feedback));
        ++metrics_.feedback_accepted;
    }
    condition_.notify_one();
    return true;
}

bool CognitiveRuntime::enqueue(CognitiveCycleInput input, double priority) {
    {
        std::lock_guard lock(mutex_);
        if (!running_ || stopping_ || config_.input_capacity == 0 || inputs_.size() >= config_.input_capacity) {
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
    if (results_.empty()) return std::nullopt;
    auto result = std::move(results_.front());
    results_.pop_front();
    return result;
}

std::size_t CognitiveRuntime::pending_inputs() const {
    std::lock_guard lock(mutex_);
    return inputs_.size();
}

std::size_t CognitiveRuntime::pending_feedback() const {
    std::lock_guard lock(mutex_);
    return feedback_.size();
}

std::size_t CognitiveRuntime::pending_results() const {
    std::lock_guard lock(mutex_);
    return results_.size();
}

CognitiveRuntimeMetrics CognitiveRuntime::metrics() const {
    std::lock_guard lock(mutex_);
    return metrics_;
}

CognitiveWorkspace CognitiveRuntime::workspace() const { return workspace_.snapshot(); }

void CognitiveRuntime::process_feedback(CognitiveFeedback feedback) {
    try {
        (void)cycle_.process_outcome(
            feedback.prediction_key.empty()
                ? std::nullopt
                : std::optional<std::string>{feedback.prediction_key},
            feedback.actual,
            feedback.evidence);
    } catch (...) {
        // Feedback is an internal learning path. A malformed or failing outcome
        // must not terminate the continuous cognitive worker.
    }

    std::lock_guard lock(mutex_);
    ++metrics_.feedback_processed;
}

void CognitiveRuntime::worker_loop() {
    for (;;) {
        WorkItem item;
        std::optional<CognitiveFeedback> feedback;

        {
            std::unique_lock lock(mutex_);
            condition_.wait(lock, [this] {
                return stopping_ || !feedback_.empty() || !inputs_.empty();
            });

            if (feedback_.empty() && inputs_.empty() && stopping_) {
                break;
            }

            // Outcome feedback is consumed before queued cognitive work so that
            // learning from a completed prediction can influence the next cycle.
            if (!feedback_.empty()) {
                feedback = std::move(feedback_.front());
                feedback_.pop_front();
            } else {
                item = std::move(inputs_.front());
                inputs_.pop_front();
            }
        }

        if (feedback.has_value()) {
            process_feedback(std::move(*feedback));
            continue;
        }

        try {
            auto result = cycle_.run(item.input);
            auto workspace = make_workspace(result, brain_);
            workspace.cycle = brain_.state().cycle;
            workspace_.replace(std::move(workspace));

            std::lock_guard lock(mutex_);
            if (config_.result_capacity != 0) {
                if (results_.size() >= config_.result_capacity) {
                    results_.pop_front();
                    ++metrics_.dropped_results;
                }
                results_.push_back(std::move(result));
            }
            ++metrics_.processed;
        } catch (const std::exception& error) {
            CognitiveCycleResult result;
            result.status = CognitiveCycleStatus::failed;
            result.error = error.what();
            std::lock_guard lock(mutex_);
            if (config_.result_capacity != 0) {
                if (results_.size() >= config_.result_capacity) {
                    results_.pop_front();
                    ++metrics_.dropped_results;
                }
                results_.push_back(std::move(result));
            }
            ++metrics_.processed;
        } catch (...) {
            CognitiveCycleResult result;
            result.status = CognitiveCycleStatus::failed;
            result.error = "unknown_cognitive_runtime_failure";
            std::lock_guard lock(mutex_);
            if (config_.result_capacity != 0) {
                if (results_.size() >= config_.result_capacity) {
                    results_.pop_front();
                    ++metrics_.dropped_results;
                }
                results_.push_back(std::move(result));
            }
            ++metrics_.processed;
        }
    }

    std::lock_guard lock(mutex_);
    if (!config_.drain_on_stop) {
        inputs_.clear();
        feedback_.clear();
    }
    running_ = false;
    stopping_ = false;
}

} // namespace jarvis::core
