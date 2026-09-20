#include "jarvis/engineering/worker.hpp"

#include <utility>

namespace jarvis::engineering {

WorkerBackedAgent::WorkerBackedAgent(AgentDescriptor descriptor, WorkerLauncher launcher)
    : descriptor_(std::move(descriptor)), launcher_(std::move(launcher)) {}

AgentDescriptor WorkerBackedAgent::descriptor() const {
    return descriptor_;
}

AgentResult WorkerBackedAgent::execute(const EngineeringTask& task) {
    if (!launcher_ || !valid_task(task) || !valid_descriptor(descriptor_)) {
        return AgentResult{false, descriptor_.id, task.id,
                           "invalid task, descriptor, or worker launcher", {}, {}};
    }

    WorkerRequest request;
    request.task = task;
    const auto response = launcher_(request);

    if (response.exit != WorkerExit::completed || response.exit_code != 0) {
        AgentResult result{
            false, descriptor_.id, task.id,
            response.error.empty() ? "worker execution failed" : response.error,
            {}, {}};
        if (!response.stdout_text.empty())
            result.evidence.push_back({"worker.stdout", response.stdout_text});
        if (!response.stderr_text.empty())
            result.evidence.push_back({"worker.stderr", response.stderr_text});
        return result;
    }

    AgentResult result{true, descriptor_.id, task.id, "worker completed", {}, {}};
    if (!response.stdout_text.empty())
        result.evidence.push_back({"worker.stdout", response.stdout_text});
    if (!response.stderr_text.empty())
        result.evidence.push_back({"worker.stderr", response.stderr_text});
    return result;
}

} // namespace jarvis::engineering
