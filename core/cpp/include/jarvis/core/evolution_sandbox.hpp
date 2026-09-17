#pragma once

#include "jarvis/core/evolution_experiment.hpp"

#include <chrono>
#include <functional>
#include <string>

namespace jarvis::core {

struct SandboxLimits {
    std::chrono::milliseconds timeout{1000};
    std::size_t max_output_bytes{64 * 1024};
};

struct SandboxResult {
    bool started{false};
    bool completed{false};
    bool timed_out{false};
    bool output_limited{false};
    double fitness{0.0};
    std::string error;
};

using CandidateExecutor = std::function<SandboxResult(const EvolutionProposal&, const SandboxLimits&)>;

class EvolutionSandbox {
public:
    explicit EvolutionSandbox(SandboxLimits limits = {});

    SandboxResult run(const EvolutionProposal& proposal, const CandidateExecutor& executor) const noexcept;
    const SandboxLimits& limits() const noexcept { return limits_; }

private:
    SandboxLimits limits_;
};

} // namespace jarvis::core
