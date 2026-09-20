#include "jarvis/engineering/worker.hpp"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
#include <stdexcept>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>
#include <vector>

namespace jarvis::engineering {
namespace {

bool set_nonblocking(int fd) {
    const int flags = ::fcntl(fd, F_GETFL, 0);
    return flags >= 0 && ::fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 0;
}

void close_fd(int& fd) {
    if (fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}

void append_capped(std::string& destination, const char* data, std::size_t size,
                   std::size_t limit, bool& truncated) {
    const auto remaining = destination.size() < limit ? limit - destination.size() : 0;
    const auto accepted = std::min(size, remaining);
    destination.append(data, accepted);
    if (accepted != size) {
        truncated = true;
    }
}

void drain_fd(int& fd, std::string& destination, std::size_t limit, bool& truncated) {
    char buffer[8192];
    for (;;) {
        const auto count = ::read(fd, buffer, sizeof(buffer));
        if (count > 0) {
            append_capped(destination, buffer, static_cast<std::size_t>(count), limit, truncated);
            continue;
        }
        if (count == 0 || (count < 0 && errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK)) {
            close_fd(fd);
        }
        return;
    }
}

} // namespace

WorkerResponse ProcessWorkerLauncher::operator()(const WorkerRequest& request) const {
#if defined(_WIN32)
    (void)request;
    return {WorkerExit::rejected, -1, {}, {},
            "real process worker is not implemented on Windows"};
#else
    if (request.executable.empty()) {
        return {WorkerExit::rejected, -1, {}, {}, "worker executable is empty"};
    }
    if (request.limits.timeout.count() <= 0) {
        return {WorkerExit::rejected, -1, {}, {}, "worker timeout must be positive"};
    }
    if (request.limits.max_output_bytes == 0) {
        return {WorkerExit::rejected, -1, {}, {}, "worker output limit must be positive"};
    }

    int stdout_pipe[2]{-1, -1};
    int stderr_pipe[2]{-1, -1};
    if (::pipe(stdout_pipe) != 0 || ::pipe(stderr_pipe) != 0) {
        close_fd(stdout_pipe[0]);
        close_fd(stdout_pipe[1]);
        close_fd(stderr_pipe[0]);
        close_fd(stderr_pipe[1]);
        return {WorkerExit::failed, -1, {}, {}, "failed to create worker pipes"};
    }

    const pid_t pid = ::fork();
    if (pid < 0) {
        close_fd(stdout_pipe[0]); close_fd(stdout_pipe[1]);
        close_fd(stderr_pipe[0]); close_fd(stderr_pipe[1]);
        return {WorkerExit::failed, -1, {}, {}, "failed to fork worker"};
    }

    if (pid == 0) {
        ::setpgid(0, 0);
        ::close(stdout_pipe[0]);
        ::close(stderr_pipe[0]);

        if (::dup2(stdout_pipe[1], STDOUT_FILENO) < 0 ||
            ::dup2(stderr_pipe[1], STDERR_FILENO) < 0) {
            _exit(126);
        }
        ::close(stdout_pipe[1]);
        ::close(stderr_pipe[1]);

        if (!request.working_directory.empty() &&
            ::chdir(request.working_directory.c_str()) != 0) {
            _exit(126);
        }

        std::vector<char*> argv;
        argv.reserve(request.arguments.size() + 2);
        argv.push_back(const_cast<char*>(request.executable.c_str()));
        for (const auto& argument : request.arguments) {
            argv.push_back(const_cast<char*>(argument.c_str()));
        }
        argv.push_back(nullptr);

        ::execvp(request.executable.c_str(), argv.data());
        _exit(127);
    }

    ::close(stdout_pipe[1]);
    ::close(stderr_pipe[1]);
    int stdout_fd = stdout_pipe[0];
    int stderr_fd = stderr_pipe[0];

    if (!set_nonblocking(stdout_fd) || !set_nonblocking(stderr_fd)) {
        ::kill(-pid, SIGKILL);
        ::kill(pid, SIGKILL);
        close_fd(stdout_fd);
        close_fd(stderr_fd);
        int status = 0;
        (void)::waitpid(pid, &status, 0);
        return {WorkerExit::failed, -1, {}, {}, "failed to configure worker pipes"};
    }

    std::string stdout_text;
    std::string stderr_text;
    bool stdout_truncated = false;
    bool stderr_truncated = false;
    bool timed_out = false;
    int status = 0;
    bool exited = false;
    const auto deadline = std::chrono::steady_clock::now() + request.limits.timeout;

    while (stdout_fd >= 0 || stderr_fd >= 0 || !exited) {
        drain_fd(stdout_fd, stdout_text, request.limits.max_output_bytes, stdout_truncated);
        drain_fd(stderr_fd, stderr_text, request.limits.max_output_bytes, stderr_truncated);

        if (!exited) {
            const auto wait_result = ::waitpid(pid, &status, WNOHANG);
            if (wait_result == pid) {
                exited = true;
            } else if (wait_result < 0 && errno != EINTR) {
                ::kill(-pid, SIGKILL);
                ::kill(pid, SIGKILL);
                (void)::waitpid(pid, &status, 0);
                exited = true;
                close_fd(stdout_fd);
                close_fd(stderr_fd);
                return {WorkerExit::failed, -1, std::move(stdout_text), std::move(stderr_text),
                        "waitpid failed"};
            }
        }

        if (!exited && std::chrono::steady_clock::now() >= deadline) {
            timed_out = true;
            ::kill(-pid, SIGKILL);
            ::kill(pid, SIGKILL);
            (void)::waitpid(pid, &status, 0);
            exited = true;
        }

        if (stdout_fd < 0 && stderr_fd < 0 && exited) {
            break;
        }

        fd_set read_set;
        FD_ZERO(&read_set);
        int max_fd = -1;
        if (stdout_fd >= 0) {
            FD_SET(stdout_fd, &read_set);
            max_fd = std::max(max_fd, stdout_fd);
        }
        if (stderr_fd >= 0) {
            FD_SET(stderr_fd, &read_set);
            max_fd = std::max(max_fd, stderr_fd);
        }

        timeval wait_time{0, 20000};
        if (max_fd >= 0) {
            (void)::select(max_fd + 1, &read_set, nullptr, nullptr, &wait_time);
        } else {
            ::usleep(20000);
        }
    }

    close_fd(stdout_fd);
    close_fd(stderr_fd);

    if (timed_out) {
        return {WorkerExit::timed_out, -1, std::move(stdout_text), std::move(stderr_text),
                "worker timed out"};
    }

    if (stdout_truncated || stderr_truncated) {
        return {WorkerExit::failed,
                WIFEXITED(status) ? WEXITSTATUS(status) : -1,
                std::move(stdout_text), std::move(stderr_text),
                "worker output exceeded configured limit"};
    }

    if (!WIFEXITED(status)) {
        return {WorkerExit::failed, -1, std::move(stdout_text), std::move(stderr_text),
                "worker terminated by signal"};
    }

    const int exit_code = WEXITSTATUS(status);
    if (exit_code != 0) {
        return {WorkerExit::failed, exit_code, std::move(stdout_text), std::move(stderr_text),
                "worker exited with non-zero status"};
    }

    return {WorkerExit::completed, 0, std::move(stdout_text), std::move(stderr_text), {}};
#endif
}

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
