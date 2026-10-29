#pragma once

#include "jarvis/core/evolution_sandbox.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

struct IsolatedCommand {
    std::string executable;
    std::vector<std::string> arguments;
    std::string working_directory;
    // Identifier registered by trusted application startup. A caller-supplied
    // identifier alone does not register or authorize an executable.
    std::string evaluation_procedure_id;
    // Pinned fingerprint of the trusted local evaluator executable. The runner
    // compares it to the registered fingerprint before each measurement.
    std::string expected_executable_fingerprint;
};

struct ProcessIsolationLimits {
    SandboxLimits sandbox;
    // The default trusted-evaluation profile requires no-new-privileges and
    // kernel-level network syscall blocking. Network namespaces, chroot-based
    // filesystem isolation, and privilege dropping are optional capabilities;
    // when explicitly required, inability to enforce them fails closed.
    // "isolated" means every property required by this exact policy was applied,
    // not merely that a child process was created.
    bool require_network_isolation{false};
    bool require_filesystem_isolation{false};
    bool require_privilege_drop{false};
    bool require_no_new_privileges{true};
    bool require_network_syscall_block{true};
    std::size_t max_memory_bytes{256 * 1024 * 1024};
    std::size_t max_cpu_seconds{2};
    std::size_t max_file_bytes{16 * 1024 * 1024};
};

struct ProcessIsolationResult {
    bool started{false};
    bool completed{false};
    bool timed_out{false};
    bool output_limited{false};
    bool isolated{false};
    int exit_code{-1};
    std::string output;
    std::string error;
};

class ProcessIsolationBackend {
public:
    explicit ProcessIsolationBackend(ProcessIsolationLimits limits = {});

    ProcessIsolationResult run(const IsolatedCommand& command) const noexcept;
    const ProcessIsolationLimits& limits() const noexcept { return limits_; }

private:
    ProcessIsolationLimits limits_;
};

} // namespace jarvis::core
