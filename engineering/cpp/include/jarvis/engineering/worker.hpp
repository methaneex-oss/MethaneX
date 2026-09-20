#pragma once

#include "agent.hpp"

#include <chrono>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace jarvis::engineering {

enum class WorkerExit : std::uint8_t {
    completed,
    rejected,
    timed_out,
    failed
};

struct WorkerLimits {
    std::chrono::milliseconds timeout{30000};
    std::size_t max_output_bytes{1024 * 1024};
};

struct WorkerRequest {
    EngineeringTask task;
    std::string executable;
    std::string working_directory;
    std::vector<std::string> arguments;
    WorkerLimits limits{};
};

struct WorkerResponse {
    WorkerExit exit{WorkerExit::failed};
    int exit_code{-1};
    std::string stdout_text;
    std::string stderr_text;
    std::string error;
};

using WorkerLauncher = std::function<WorkerResponse(const WorkerRequest&)>;

class ProcessWorkerLauncher {
public:
    WorkerResponse operator()(const WorkerRequest& request) const;
};

class WorkerBackedAgent final : public EngineeringAgent {
public:
    WorkerBackedAgent(AgentDescriptor descriptor, WorkerLauncher launcher);
    AgentDescriptor descriptor() const override;
    AgentResult execute(const EngineeringTask& task) override;
private:
    AgentDescriptor descriptor_;
    WorkerLauncher launcher_;
};

} // namespace jarvis::engineering
