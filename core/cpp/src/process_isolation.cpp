#include "jarvis/core/process_isolation.hpp"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstring>
#include <string>
#include <cstdlib>

#if defined(__unix__) || defined(__APPLE__)
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#if defined(__linux__)
#include <sched.h>
#include <sys/prctl.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <sys/syscall.h>
#endif
#endif

namespace jarvis::core {

#if defined(__linux__)
namespace {

bool install_network_syscall_block() noexcept {
    const sock_filter filter[] = {
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, arch)),
#if defined(__x86_64__)
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, AUDIT_ARCH_X86_64, 1, 0),
#elif defined(__aarch64__)
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, AUDIT_ARCH_AARCH64, 1, 0),
#else
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
#endif
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, nr)),
#ifdef __NR_socket
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_socket, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_socketpair
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_socketpair, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_connect
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_connect, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_bind
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_bind, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_listen
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_listen, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_accept
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_accept, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_accept4
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_accept4, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_sendto
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_sendto, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_sendmsg
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_sendmsg, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_recvfrom
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_recvfrom, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
#ifdef __NR_recvmsg
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_recvmsg, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | EPERM),
#endif
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
    };
    const sock_fprog program{static_cast<unsigned short>(sizeof(filter) / sizeof(filter[0])),
                             const_cast<sock_filter*>(filter)};
    return prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &program, 0, 0) == 0;
}

} // namespace
#endif

ProcessIsolationBackend::ProcessIsolationBackend(ProcessIsolationLimits limits) : limits_(limits) {
    if (limits_.sandbox.timeout.count() <= 0) limits_.sandbox.timeout = std::chrono::milliseconds{1000};
    if (limits_.sandbox.max_output_bytes == 0) limits_.sandbox.max_output_bytes = 64 * 1024;
    if (limits_.max_memory_bytes == 0) limits_.max_memory_bytes = 256 * 1024 * 1024;
    if (limits_.max_cpu_seconds == 0) limits_.max_cpu_seconds = 2;
    if (limits_.max_file_bytes == 0) limits_.max_file_bytes = 16 * 1024 * 1024;
}

ProcessIsolationResult ProcessIsolationBackend::run(const IsolatedCommand& command) const noexcept {
    ProcessIsolationResult result;
    if (command.executable.empty()) {
        result.error = "empty executable";
        return result;
    }

#if !defined(__unix__) && !defined(__APPLE__)
    result.error = "process isolation backend unsupported on this platform";
    return result;
#else
    int pipe_fds[2] = {-1, -1};
    if (pipe(pipe_fds) != 0) {
        result.error = std::string("pipe failed: ") + std::strerror(errno);
        return result;
    }

    const pid_t pid = fork();
    if (pid < 0) {
        result.error = std::string("fork failed: ") + std::strerror(errno);
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return result;
    }

    if (pid == 0) {
        close(pipe_fds[0]);
        (void)dup2(pipe_fds[1], STDOUT_FILENO);
        (void)dup2(pipe_fds[1], STDERR_FILENO);
        close(pipe_fds[1]);
        (void)setpgid(0, 0);

#if defined(__linux__)
        if (limits_.require_network_isolation && unshare(CLONE_NEWNET) != 0) _exit(125);
        if (limits_.require_no_new_privileges && prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != 0) _exit(125);
        if (limits_.require_network_syscall_block && !install_network_syscall_block()) _exit(125);
#elif defined(__APPLE__)
        if (limits_.require_no_new_privileges) _exit(125);
        if (limits_.require_network_syscall_block) _exit(125);
#endif
#if defined(__unix__) || defined(__APPLE__)
        if (limits_.require_privilege_drop) {
            if (geteuid() == 0) {
                if (setgid(65534) != 0 || setuid(65534) != 0) _exit(125);
            } else if (geteuid() != getuid() || getegid() != getgid()) {
                _exit(125);
            }
        }
#endif
        if (limits_.require_filesystem_isolation) {
#if defined(__unix__) || defined(__APPLE__)
            if (command.working_directory.empty() || geteuid() != 0 || chroot(command.working_directory.c_str()) != 0 || chdir("/") != 0) _exit(125);
#else
            _exit(125);
#endif
        }

        struct rlimit memory_limit{limits_.max_memory_bytes, limits_.max_memory_bytes};
        struct rlimit cpu_limit{limits_.max_cpu_seconds, limits_.max_cpu_seconds};
        struct rlimit file_limit{limits_.max_file_bytes, limits_.max_file_bytes};
        (void)setrlimit(RLIMIT_AS, &memory_limit);
        (void)setrlimit(RLIMIT_CPU, &cpu_limit);
        (void)setrlimit(RLIMIT_FSIZE, &file_limit);

        if (!command.working_directory.empty() && chdir(command.working_directory.c_str()) != 0) _exit(126);

        std::vector<char*> argv;
        argv.reserve(command.arguments.size() + 2);
        argv.push_back(const_cast<char*>(command.executable.c_str()));
        for (const auto& argument : command.arguments) argv.push_back(const_cast<char*>(argument.c_str()));
        argv.push_back(nullptr);
        execvp(command.executable.c_str(), argv.data());
        _exit(127);
    }

    close(pipe_fds[1]);
    result.started = true;
    result.isolated = true;
    const auto deadline = std::chrono::steady_clock::now() + limits_.sandbox.timeout;
    std::string output;
    output.reserve(std::min<std::size_t>(limits_.sandbox.max_output_bytes, 4096));
    bool child_reaped = false;

    for (;;) {
        const auto now = std::chrono::steady_clock::now();
        if (now >= deadline) {
            kill(-pid, SIGKILL);
            kill(pid, SIGKILL);
            result.timed_out = true;
            break;
        }
        struct pollfd descriptor{pipe_fds[0], POLLIN, 0};
        const auto remaining = std::chrono::duration_cast<std::chrono::milliseconds>(deadline - now);
        const int wait_ms = static_cast<int>(std::max<long long>(1, remaining.count()));
        const int poll_result = poll(&descriptor, 1, std::min(wait_ms, 50));
        if (poll_result > 0 && (descriptor.revents & (POLLIN | POLLHUP))) {
            char buffer[4096];
            const ssize_t bytes = read(pipe_fds[0], buffer, sizeof(buffer));
            if (bytes > 0) {
                const std::size_t remaining_output = limits_.sandbox.max_output_bytes > output.size()
                    ? limits_.sandbox.max_output_bytes - output.size() : 0;
                if (static_cast<std::size_t>(bytes) > remaining_output) {
                    output.append(buffer, remaining_output);
                    result.output_limited = true;
                    kill(-pid, SIGKILL);
                    kill(pid, SIGKILL);
                    break;
                }
                output.append(buffer, static_cast<std::size_t>(bytes));
            }
        }
        int status = 0;
        const pid_t waited = waitpid(pid, &status, WNOHANG);
        if (waited == pid) {
            child_reaped = true;
            if (WIFEXITED(status)) result.exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status)) result.exit_code = 128 + WTERMSIG(status);
            break;
        }
        if (waited < 0 && errno != EINTR) break;
    }

    close(pipe_fds[0]);
    if (!child_reaped) {
        int status = 0;
        if (waitpid(pid, &status, 0) == pid) {
            if (WIFEXITED(status)) result.exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status)) result.exit_code = 128 + WTERMSIG(status);
        }
    }
    result.output = std::move(output);
    result.completed = !result.timed_out && !result.output_limited && result.exit_code == 0;
    if (!result.completed && result.exit_code == 125) result.error = "required isolation feature unavailable";
    if (!result.completed && result.error.empty()) {
        if (result.timed_out) result.error = "process timeout";
        else if (result.output_limited) result.error = "process output limit exceeded";
        else result.error = "isolated process failed";
    }
    return result;
#endif
}

} // namespace jarvis::core
