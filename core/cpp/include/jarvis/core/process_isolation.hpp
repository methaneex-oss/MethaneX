#pragma once

#include "jarvis/core/evolution_sandbox.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

struct IsolatedCommand {
    std::string executable;
    std::vector<std::string> arguments;
    std::string working_directory;
};

struct IsolatedEvaluationSpec {
    // A local, project-controlled evaluator executable implementing the
    // JARVIS_EVAL_V1 protocol. The same procedure measures baseline and
    // candidate artifacts; stdout must bind each score to all supplied IDs.
    IsolatedCommand evaluator;
    std::string procedure_id;
    std::string baseline_artifact_id;
    std::string candidate_artifact_id;
    double baseline_value{0.0};
    double candidate_value{0.0};
};

struct ProcessIsolationLimits {
    SandboxLimits sandbox;
    // Requested controls must be enforced or execution fails closed. The default
    // evaluator is a trusted local C++ procedure (candidate values are data, not
    // executable artifacts); filesystem chroot isolation remains opt-in because
    // it requires a prepared root filesystem and suitable host privileges.
    bool require_network_isolation{false};
    bool require_filesystem_isolation{false};
    bool require_privilege_drop{true};
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
