#pragma once

#include "agent.hpp"
#include "pipeline.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::engineering {

enum class EngineeringScheduleStatus : std::uint8_t {
    valid,
    invalid
};

struct EngineeringScheduleWave {
    std::vector<std::size_t> stage_indices;
    bool parallel_safe{false};
    std::string reason;
};

struct EngineeringSchedule {
    EngineeringScheduleStatus status{EngineeringScheduleStatus::invalid};
    std::string reason;
    std::vector<EngineeringScheduleWave> waves;
};

enum class EngineeringNodeStatus : std::uint8_t {
    pending,
    completed,
    rejected,
    blocked
};

struct EngineeringNodeResult {
    std::size_t stage_index{0};
    EngineeringNodeStatus status{EngineeringNodeStatus::blocked};
    AgentResult result;
    std::vector<std::string> blocking_dependencies;
};

struct EngineeringScheduleResult {
    bool accepted{false};
    std::string reason;
    std::vector<EngineeringNodeResult> nodes;
};

class EngineeringScheduler {
public:
    EngineeringSchedule plan(
        const std::vector<EngineeringStageTask>& stages,
        const std::vector<EngineeringAgent*>& agents) const;

    EngineeringScheduleResult execute(
        const std::vector<EngineeringStageTask>& stages,
        const std::vector<EngineeringAgent*>& agents,
        const EngineeringAuthorizer& authorizer,
        EngineeringExecutionBoundary& boundary) const;

private:
    static bool disjoint_workspace_files(
        const EngineeringStageTask& left,
        const EngineeringStageTask& right) noexcept;
};

} // namespace jarvis::engineering
