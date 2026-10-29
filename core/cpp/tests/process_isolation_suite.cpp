#include "jarvis/core/process_isolation.hpp"

#include <cassert>
#include <chrono>
#include <string>

#if defined(__unix__) || defined(__APPLE__)
#include <filesystem>
#include <fstream>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
int main() {
    using namespace jarvis::core;
    ProcessIsolationBackend backend(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{500}, 1024}, false, false, false, true, false,
        256 * 1024 * 1024, 2, 1024 * 1024});
    const auto ok = backend.run({"/bin/sh", {"-c", "printf isolated"}, ""});
    assert(ok.started && ok.isolated && ok.completed && ok.exit_code == 0);
    assert(ok.output == "isolated");

    // Regression: a relative executable must not be re-resolved after chdir.
    const auto suffix = std::to_string(static_cast<long long>(::getpid()));
    const auto executable_name = ".jarvis-evaluator-" + suffix;
    const auto original = std::filesystem::current_path() / executable_name;
    const auto alternate = std::filesystem::temp_directory_path() /
                           ("jarvis-evaluator-shadow-" + suffix);
    std::filesystem::create_directory(alternate);
    {
        std::ofstream first(original);
        first << "#!/bin/sh\\necho original\\n";
        std::ofstream second(alternate / executable_name);
        second << "#!/bin/sh\\necho shadow\\n";
    }
    assert(::chmod(original.c_str(), 0700) == 0);
    assert(::chmod((alternate / executable_name).c_str(), 0700) == 0);
    const auto path_identity = backend.run(
        {"./" + executable_name, {}, alternate.string()});
    assert(path_identity.completed && path_identity.output == "original\\n");
    std::filesystem::remove(original);
    std::filesystem::remove_all(alternate);

    // An unrelated parent descriptor must not be visible in the child.
#if defined(__linux__)
    const int inherited_fd = ::open("/dev/null", O_RDONLY);
    assert(inherited_fd >= 3);
    const auto fd_check = backend.run({"/bin/sh",
        {"-c", "test ! -e /proc/self/fd/" + std::to_string(inherited_fd)}, ""});
    ::close(inherited_fd);
    assert(fd_check.completed);

    // Socket creation filters do not stop read/write on an already-connected
    // inherited descriptor; the descriptor itself must be closed.
    int sockets[2] = {-1, -1};
    assert(::socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == 0);
    const auto socket_check = backend.run({"/bin/sh",
        {"-c", "printf leak >&" + std::to_string(sockets[1])}, ""});
    ::close(sockets[0]);
    ::close(sockets[1]);
    assert(socket_check.started && socket_check.isolated && !socket_check.completed);
#endif
    const auto limited = backend.run({"/bin/sh", {"-c", "head -c 2048 /dev/zero"}, ""});
    assert(limited.started && limited.isolated && limited.output_limited && !limited.completed);
    const auto timed = backend.run({"/bin/sh", {"-c", "sleep 2"}, ""});
    assert(timed.started && timed.isolated && timed.timed_out && !timed.completed);
    ProcessIsolationBackend strict(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{500}, 1024}, true, false, false, true, false,
        256 * 1024 * 1024, 2, 1024 * 1024});
    const auto strict_result = strict.run({"/bin/sh", {"-c", "printf strict"}, ""});
#if defined(__linux__)
    if (!strict_result.completed)
        assert(strict_result.exit_code == 125 || strict_result.error == "required isolation feature unavailable");
#else
    assert(!strict_result.completed);
#endif
#if defined(__linux__)
    ProcessIsolationBackend no_network(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{500}, 1024}, false, false, false, true, true,
        256 * 1024 * 1024, 2, 1024 * 1024});
    const auto network = no_network.run({"/bin/sh", {"-c", "python3 -c 'import socket; socket.socket()'"}, ""});
    assert(network.started && network.isolated && !network.completed);
#endif
    return 0;
}
#else
int main() {
    using namespace jarvis::core;
    ProcessIsolationBackend backend;
    const auto result = backend.run({"unsupported", {}, ""});
    assert(!result.started && !result.isolated);
    return 0;
}
#endif
