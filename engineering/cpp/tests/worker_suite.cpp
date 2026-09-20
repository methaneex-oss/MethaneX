#include "jarvis/engineering/worker.hpp"

#include <cassert>

using namespace jarvis::engineering;

int main() {
    AgentDescriptor descriptor{
        "agent.worker", "Worker", "test", "fixture",
        {"code.implement"}, {"workspace.write"},
        {}, {"patch"}, 0.5, 0.9, AgentRisk::medium,
        AgentAvailability::available, false};

    bool launched = false;
    WorkerBackedAgent agent{
        descriptor,
        [&](const WorkerRequest& request) {
            launched = true;
            assert(request.task.id == "task-1");
            assert(request.limits.timeout.count() > 0);
            return WorkerResponse{WorkerExit::completed, 0, "changed files", "", ""};
        }};

    EngineeringTask task{
        "task-1", "implement requested change",
        {"code.implement"}, {"workspace.write"},
        {}, {"patch"}, AgentRisk::medium, 1.0};

    const auto result = agent.execute(task);
    assert(launched);
    assert(result.accepted);
    assert(result.agent_id == descriptor.id);
    assert(result.task_id == task.id);
    assert(result.evidence.size() == 1);

    WorkerBackedAgent failed{
        descriptor,
        [](const WorkerRequest&) {
            return WorkerResponse{WorkerExit::timed_out, -1, "", "", "worker timed out"};
        }};

    const auto timeout = failed.execute(task);
    assert(!timeout.accepted);
    assert(timeout.reason == "worker timed out");
    return 0;
}
