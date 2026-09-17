#include "jarvis/core/evolution_sandbox.hpp"

#include <cmath>
#include <utility>

namespace jarvis::core {

EvolutionSandbox::EvolutionSandbox(SandboxLimits limits) : limits_(limits) {
    if (limits_.timeout.count() <= 0) limits_.timeout = std::chrono::milliseconds{1000};
    if (limits_.max_output_bytes == 0) limits_.max_output_bytes = 64 * 1024;
}

SandboxResult EvolutionSandbox::run(const EvolutionProposal& proposal,
                                    const CandidateExecutor& executor) const noexcept {
    SandboxResult result;
    if (proposal.key.empty() || !std::isfinite(proposal.proposed) || !executor) {
        result.error = "invalid candidate execution request";
        return result;
    }

    try {
        result = executor(proposal, limits_);
        if (!result.isolated) {
            result.completed = false;
            result.error = "candidate executor did not prove isolation";
        } else if (!std::isfinite(result.fitness)) {
            result.completed = false;
            result.error = "executor returned non-finite fitness";
        }
    } catch (...) {
        result.started = true;
        result.completed = false;
        result.error = "candidate executor failed";
    }
    return result;
}

} // namespace jarvis::core
