#include "jarvis/engineering/agent.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::engineering {

bool valid_descriptor(const AgentDescriptor& descriptor) noexcept {
    return !descriptor.id.empty() &&
           !descriptor.name.empty() &&
           std::isfinite(descriptor.estimated_cost) &&
           descriptor.estimated_cost >= 0.0 &&
           std::isfinite(descriptor.reliability) &&
           descriptor.reliability >= 0.0 &&
           descriptor.reliability <= 1.0;
}

bool valid_task(const EngineeringTask& task) noexcept {
    return !task.id.empty() &&
           !task.objective.empty() &&
           !task.required_capabilities.empty() &&
           std::all_of(task.required_capabilities.begin(), task.required_capabilities.end(),
                       [](const std::string& value) { return !value.empty(); }) &&
           std::isfinite(task.maximum_cost) &&
           task.maximum_cost >= 0.0;
}

} // namespace jarvis::engineering
