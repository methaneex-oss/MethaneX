#include "jarvis/engineering/worker.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <string>
#include <thread>

using namespace jarvis::engineering;

namespace {

AgentDescriptor descriptor() {
    return AgentDescriptor{
        "agent.worker", "Worker", "test", "fixture",
        {"code.implement"}, {"workspace.write"},
        {}, {"patch"}, 0.5, 0.9, AgentRisk::medium,
        AgentAvailability::available, false};
}

EngineeringTask task() {
    return EngineeringTask{
        "task-1", "implement requested change",
        {"code.implement"}, {"workspace.write"},
        {}, {"patch"}, AgentRisk::medium, 1.0};
}

} // namespace

int main() {
    bool launched = false;
    WorkerBackedAgent injected{
        descriptor(),
        [&](const WorkerRequest& request) {
            launched = true;
            assert(request.task.id == "task-1");
            assert(request.limits.timeout.count() > 0);
            return WorkerResponse{WorkerExit::completed, 0, "changed files", "", ""};
        }};

    const auto result = injected.execute(task());
    assert(launched);
    assert(result.accepted);
    assert(result.agent_id == descriptor().id);
    assert(result.task_id == "task-1");
    assert(result.evidence.size() == 1);

    WorkerBackedAgent failed{
        descriptor(),
        [](const WorkerRequest&) {
            return WorkerResponse{WorkerExit::timed_out, -1, "", "", "worker timed out"};
        }};

    const auto injected_timeout = failed.execute(task());
    assert(!injected_timeout.accepted);
    assert(injected_timeout.reason == "worker timed out");

#if !defined(_WIN32)
    const auto fixture = std::filesystem::temp_directory_path() / "jarvis-engineering-worker-fixture";
    std::filesystem::create_directories(fixture);

    ProcessWorkerLauncher launcher;

    WorkerRequest echo;
    echo.task = task();
    echo.executable = "/bin/sh";
    echo.working_directory = fixture.string();
    echo.arguments = {"-c", "printf 'stdout-ok'; printf 'stderr-ok' >&2"};
    echo.limits.timeout = std::chrono::seconds(2);
    echo.limits.max_output_bytes = 1024;

    const auto completed = launcher(echo);
    assert(completed.exit == WorkerExit::completed);
    assert(completed.exit_code == 0);
    assert(completed.stdout_text == "stdout-ok");
    assert(completed.stderr_text == "stderr-ok");

    WorkerRequest nonzero = echo;
    nonzero.arguments = {"-c", "printf 'bad'; exit 7"};
    const auto failed_process = launcher(nonzero);
    assert(failed_process.exit == WorkerExit::failed);
    assert(failed_process.exit_code == 7);
    assert(failed_process.stdout_text == "bad");

    WorkerRequest timeout_request = echo;
    timeout_request.arguments = {"-c", "sleep 2"};
    timeout_request.limits.timeout = std::chrono::milliseconds(100);
    const auto timed_out = launcher(timeout_request);
    assert(timed_out.exit == WorkerExit::timed_out);

    WorkerRequest output = echo;
    output.arguments = {"-c", "printf '0123456789'"};
    output.limits.max_output_bytes = 4;
    const auto too_large = launcher(output);
    assert(too_large.exit == WorkerExit::failed);
    assert(too_large.stdout_text == "0123");

    WorkerRequest bad_directory = echo;
    bad_directory.working_directory = (fixture / "does-not-exist").string();
    const auto bad_cwd = launcher(bad_directory);
    assert(bad_cwd.exit == WorkerExit::failed);
    assert(bad_cwd.exit_code == 126);

    std::filesystem::remove_all(fixture);
#endif

    return 0;
}
