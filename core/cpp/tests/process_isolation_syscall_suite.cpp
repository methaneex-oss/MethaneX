#include "jarvis/core/process_isolation.hpp"

#include <cassert>

#if defined(__linux__)
#include <cerrno>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    using namespace jarvis::core;
    ProcessIsolationBackend backend(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{1000}, 4096},
        false, false, false, true, true,
        64 * 1024 * 1024, 2, 1024 * 1024});
    const auto result = backend.run({"/bin/sh", {"-c", "python3 -c 'import socket; s=socket.socket(); print(\"UNEXPECTED\")'"}, ""});
    assert(result.started);
    assert(result.isolated);
    assert(!result.completed);
    return 0;
}
#else
int main() { return 0; }
#endif
