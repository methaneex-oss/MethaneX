#include "jarvis/core/cognitive_runtime.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace jarvis::core {
namespace {
double finite_priority(double value) noexcept { return std::isfinite(value) ? value : 0.0; }
}

CognitiveRuntime::CognitiveRuntime(Brain& brain, CognitiveRuntimeConfig config)
    : brain_(brain), cycle_(brain), config_(std::move(config)) {}
CognitiveRuntime::~CognitiveRuntime() { stop(); }
void CognitiveRuntime::start() { std::lock_guard lock(mutex_); if (running_) return; stopping_ = false; running_ = true; worker_ = std::thread([this] { worker_loop(); }); }
void CognitiveRuntime::stop() { { std::lock_guard lock(mutex_); if (!running_) return; stopping_ = true; running_ = false; } condition_.notify_all(); if (worker_.joinable()) worker_.join(); }
bool CognitiveRuntime::running() const { std::lock_guard lock(mutex_); return running_; }
bool CognitiveRuntime::submit(CognitiveCycleInput input, double priority) { return enqueue(std::move(input), finite_priority(priority)); }
bool CognitiveRuntime::submit(CognitiveCycleInput input, const CognitiveTriggerSignals& signals) { const auto decision = trigger_.evaluate(signals); if (!decision.should_cognize) { std::lock_guard lock(mutex_); ++metrics_.trigger_rejected; return false; } return enqueue(std::move(input), decision.priority); }

bool CognitiveRuntime::submit_feedback(CognitiveFeedback feedback) {
    const bool has_prediction = !feedback.prediction_key.empty();
    const bool has_evidence = feedback.evidence.has_value() && !feedback.evidence->key.empty();
    const bool has_goal = feedback.goal_id.has_value() && !feedback.goal_id->empty() && feedback.goal_progress.has_value() && std::isfinite(*feedback.goal_progress);
    if (!has_prediction && !has_evidence && !has_goal) {
        std::lock_guard lock(mutex_); ++metrics_.feedback_rejected; return false;
    }
    if (has_goal) {
        const auto* goal = brain_.goal(*feedback.goal_id);
        if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) {
            std::lock_guard lock(mutex_); ++metrics_.feedback_rejected; return false;
        }
    }
    {
        std::lock_guard lock(mutex_);
        if (!running_ || stopping_ || config_.feedback_capacity == 0 || feedback_.size() >= config_.feedback_capacity) { ++metrics_.feedback_rejected; return false; }
        feedback_.push_back(std::move(feedback)); ++metrics_.feedback_accepted;
    }
    condition_.notify_one(); return true;
}

bool CognitiveRuntime::enqueue(CognitiveCycleInput input, double priority) { { std::lock_guard lock(mutex_); if (!running_ || stopping_ || config_.input_capacity == 0 || inputs_.size() >= config_.input_capacity) { ++metrics_.rejected; return false; } WorkItem item{std::move(input), finite_priority(priority), ++next_sequence_}; const auto position = std::find_if(inputs_.begin(), inputs_.end(), [&](const WorkItem& queued) { return item.priority > queued.priority; }); inputs_.insert(position, std::move(item)); ++metrics_.accepted; } condition_.notify_one(); return true; }
void CognitiveRuntime::process_feedback(CognitiveFeedback feedback) { try { (void)cycle_.process_outcome(feedback.prediction_key.empty() ? std::nullopt : std::optional<std::string>{feedback.prediction_key}, feedback.actual, feedback.evidence, feedback.goal_id, feedback.goal_progress, feedback.goal_confidence); } catch (...) {} std::lock_guard lock(mutex_); ++metrics_.feedback_processed; }
void CognitiveRuntime::execute_actions(CognitiveCycleResult& result) {
    for (const auto& assessment : result.context.action_assessments) {
        if (assessment.disposition != ActionDisposition::execute) continue;
        ActionExecutionResult execution;
        try {
            if (!config_.action_adapter.execute) { execution.action = assessment.action; execution.status = ActionExecutionStatus::rejected; execution.authorized = false; execution.reason = "action_adapter_unavailable"; }
            else execution = brain_.execute_action(assessment, config_.action_adapter.execute, config_.action_adapter.verify, config_.action_adapter.rollback, config_.action_adapter.observe_consequence, config_.action_adapter.authorization);
        } catch (...) { execution.action = assessment.action; execution.status = ActionExecutionStatus::failed; execution.reason = "action_boundary_exception"; }
        result.context.action_execution_results.push_back(execution);
        { std::lock_guard lock(mutex_); ++metrics_.action_attempted; if (execution.status == ActionExecutionStatus::rejected) ++metrics_.action_rejected; else if (execution.status == ActionExecutionStatus::verified) ++metrics_.action_succeeded; else ++metrics_.action_failed; }
        if (const auto evidence = evidence_for_action(execution); evidence.has_value()) (void)submit_feedback(CognitiveFeedback{"", evidence->value, evidence, result.context.selected_goal.id.empty() ? std::nullopt : std::optional<std::string>{result.context.selected_goal.id}, std::nullopt, 0.0});
    }
}

void CognitiveRuntime::publish_result(CognitiveCycleResult result) { auto workspace = make_workspace(result, brain_); workspace.cycle = brain_.state().cycle; workspace_.replace(std::move(workspace)); std::lock_guard lock(mutex_); if (config_.result_capacity != 0) { if (results_.size() >= config_.result_capacity) results_.pop_front(); results_.push_back(std::move(result)); } }
void CognitiveRuntime::worker_loop() { while (true) { WorkItem item; CognitiveFeedback feedback; bool have_input = false; bool have_feedback = false; { std::unique_lock lock(mutex_); condition_.wait(lock, [this] { return stopping_ || !inputs_.empty() || !feedback_.empty(); }); if (stopping_ && inputs_.empty() && feedback_.empty()) break; if (!feedback_.empty()) { feedback = std::move(feedback_.front()); feedback_.pop_front(); have_feedback = true; } else if (!inputs_.empty()) { item = std::move(inputs_.front()); inputs_.pop_front(); have_input = true; } } if (have_feedback) { process_feedback(std::move(feedback)); continue; } if (have_input) { try { auto result = cycle_.run(item.input); execute_actions(result); publish_result(std::move(result)); } catch (...) { std::lock_guard lock(mutex_); ++metrics_.cycles_failed; } } } }

CognitiveRuntimeMetrics CognitiveRuntime::metrics() const { std::lock_guard lock(mutex_); return metrics_; }
std::vector<CognitiveCycleResult> CognitiveRuntime::results() const { std::lock_guard lock(mutex_); return {results_.begin(), results_.end()}; }
CognitiveWorkspace CognitiveRuntime::workspace() const { return workspace_.snapshot(); }

} // namespace jarvis::core
