#pragma once

#include "coordinator.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::engineering {

enum class EngineeringStage : std::uint8_t {
    implementation,
    review,
    verification
};

struct EngineeringStageTask {
    EngineeringStage stage{EngineeringStage::implementation};
    EngineeringTask task;
    std::string agent_id;
};

enum class EngineeringRunStatus : std::uint8_t {
    completed,
    rejected,
    failed
};

struct EngineeringStageResult {
    EngineeringStage stage{EngineeringStage::implementation};
    AgentResult result;
};

struct EngineeringRunResult {
    EngineeringRunStatus status{EngineeringRunStatus::failed};
    std::string run_id;
    std::string reason;
    std::vector<EngineeringStageResult> stages;
};

class EngineeringPipeline {
public:
    EngineeringRunResult run(
        std::string run_id,
        const std::vector<EngineeringStageTask>& stages,
        const std::vector<EngineeringAgent*>& agents,
        const EngineeringAuthorizer& authorizer,
        EngineeringExecutionBoundary& boundary) const;

private:
    static EngineeringAgent* find_agent(
        const std::vector<EngineeringAgent*>& agents,
        const std::string& agent_id) noexcept;
};

} // namespace jarvis::engineering
