#include "jarvis/core/process_isolation.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

#if defined(__unix__) || defined(__APPLE__)
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main() {
    using namespace jarvis::core;
    ProcessIsolationBackend backend(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{500}, 1024}, false, false, false, true, false,
        64 * 1024 * 1024, 2, 1024 * 1024});
    const auto ok = backend.run({"/bin/sh", {"-c", "printf isolated"}, ""});
    assert(ok.started && ok.isolated && ok.completed && ok.exit_code == 0);
    assert(ok.output == "isolated");

    // A relative executable must keep the identity resolved before chdir.
    const auto suffix = std::to_string(static_cast<long long>(getpid()));
    const auto executable_name = ".jarvis-isolation-evaluator-" + suffix;
    const auto original_executable = std::filesystem::current_path() / executable_name;
    const auto alternate_directory = std::filesystem::temp_directory_path() /
                                     ("jarvis-isolation-shadow-" + suffix);
    std::filesystem::create_directory(alternate_directory);
    {
        std::ofstream original(original_executable);
        original << "#!/bin/sh\nprintf original\\n\n";
        std::ofstream shadow(alternate_directory / executable_name);
        shadow << "#!/bin/sh\nprintf shadow\\n\n";
    }
    assert(::chmod(original_executable.c_str(), 0700) == 0);
    assert(::chmod((alternate_directory / executable_name).c_str(), 0700) == 0);
    const auto path_identity = backend.run(
        {"./" + executable_name, {}, alternate_directory.string()});
    assert(path_identity.completed && path_identity.output == "original\n");
    std::filesystem::remove(original_executable);
    std::filesystem::remove_all(alternate_directory);

#if defined(__linux__)
    // An unrelated descriptor opened by the parent must not reach the child.
    const int inherited_fd = ::open("/dev/null", O_RDONLY);
    assert(inherited_fd >= 3);
    const auto fd_check = backend.run({"/bin/sh",
        {"-c", "test ! -e /proc/self/fd/" + std::to_string(inherited_fd)}, ""});
    ::close(inherited_fd);
    assert(fd_check.completed);
#endif
    const auto limited = backend.run({"/bin/sh", {"-c", "head -c 2048 /dev/zero"}, ""});
    assert(limited.started && limited.isolated && limited.output_limited && !limited.completed);
    const auto timed = backend.run({"/bin/sh", {"-c", "sleep 2"}, ""});
    assert(timed.started && timed.isolated && timed.timed_out && !timed.completed);
    ProcessIsolationBackend strict(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{500}, 1024}, true, false, false, true, false,
        64 * 1024 * 1024, 2, 1024 * 1024});
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
        64 * 1024 * 1024, 2, 1024 * 1024});
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
