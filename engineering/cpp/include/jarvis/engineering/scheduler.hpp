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

class EngineeringScheduler {
public:
    EngineeringSchedule plan(
        const std::vector<EngineeringStageTask>& stages,
        const std::vector<EngineeringAgent*>& agents) const;

private:
    static bool disjoint_workspace_files(
        const EngineeringStageTask& left,
        const EngineeringStageTask& right) noexcept;
};

} // namespace jarvis::engineering
