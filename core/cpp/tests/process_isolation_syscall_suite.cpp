#include "jarvis/core/process_isolation.hpp"
#include <cassert>
#if defined(__linux__)
int main() {
    using namespace jarvis::core;
    ProcessIsolationBackend backend(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{1000}, 4096}, false, false, false, true, true,
        64 * 1024 * 1024, 2, 1024 * 1024});
    const auto result = backend.run({"/bin/sh", {"-c", "python3 -c 'import socket; socket.socket()'"}, ""});
    assert(result.started && result.isolated && !result.completed);
    return 0;
}
#else
int main() { return 0; }
#endif
