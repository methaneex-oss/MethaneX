#pragma once

#include "jarvis/core/evolution_sandbox.hpp"

#include <functional>
#include <string>
#include <vector>

namespace jarvis::core {

struct IsolatedCommand {
    std::string executable;
    std::vector<std::string> arguments;
    std::string working_directory;
};

struct ProcessIsolationLimits {
    SandboxLimits sandbox;
    // These features are opt-in because their availability depends on host privileges.
    // A requested feature that cannot be enforced causes execution to fail closed.
    bool require_network_isolation{false};
    bool require_filesystem_isolation{false};
    bool require_privilege_drop{false};
    bool require_no_new_privileges{true};
    bool require_network_syscall_block{false};
    std::size_t max_memory_bytes{256 * 1024 * 1024};
    std::size_t max_cpu_seconds{2};
    std::size_t max_file_bytes{16 * 1024 * 1024};
};

using LocalFitnessProcedure = std::function<double(const EvolutionProposal&, double)>;

struct ProcessIsolationEvaluationResult {
    bool started{false};
    bool completed{false};
    bool timed_out{false};
    bool isolated{false};
    double fitness{0.0};
    std::string error;
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
    // Execute repository-owned C++ evaluation logic in a child process. The
    // evaluator receives the exact proposal and parameter value being measured;
    // arbitrary stdout from a shell command is not accepted as fitness evidence.
    ProcessIsolationEvaluationResult run_evaluator(
        const LocalFitnessProcedure& procedure, const EvolutionProposal& proposal,
        double parameter_value) const noexcept;
    const ProcessIsolationLimits& limits() const noexcept { return limits_; }

private:
    ProcessIsolationLimits limits_;
};

} // namespace jarvis::core
