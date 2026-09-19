#include "jarvis/core/process_isolation.hpp"

#include <cassert>
#include <chrono>

#if defined(__unix__) || defined(__APPLE__)
int main() {
    using namespace jarvis::core;

    ProcessIsolationBackend backend(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{500}, 1024},
        64 * 1024 * 1024,
        2,
        1024 * 1024});

    const auto ok = backend.run({"/bin/sh", {"-c", "printf isolated"}, ""});
    assert(ok.started);
    assert(ok.isolated);
    assert(ok.completed);
    assert(ok.exit_code == 0);
    assert(ok.output == "isolated");

    const auto limited = backend.run({"/bin/sh", {"-c", "printf 123456789"}, ""});
    assert(limited.started);
    assert(limited.isolated);
    assert(limited.output_limited);
    assert(!limited.completed);

    const auto timed = backend.run({"/bin/sh", {"-c", "sleep 2"}, ""});
    assert(timed.started);
    assert(timed.isolated);
    assert(timed.timed_out);
    assert(!timed.completed);

    // Strict optional features fail closed when the host cannot enforce them.
    ProcessIsolationBackend strict(ProcessIsolationLimits{
        SandboxLimits{std::chrono::milliseconds{500}, 1024},
        true, false, false, true, 64 * 1024 * 1024, 2, 1024 * 1024});
    const auto strict_result = strict.run({"/bin/sh", {"-c", "printf strict"}, ""});
#if defined(__linux__)
    if (strict_result.completed) assert(strict_result.isolated);
    else assert(strict_result.exit_code == 125 || strict_result.error == "required isolation feature unavailable");
#else
    assert(!strict_result.completed);
#endif
    return 0;
}
#else
int main() {
    using namespace jarvis::core;
    ProcessIsolationBackend backend;
    const auto result = backend.run({"unsupported", {}, ""});
    assert(!result.started);
    assert(!result.isolated);
    return 0;
}
#endif
