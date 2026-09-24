#include "jarvis/engineering/agent.hpp"
#include <algorithm>
#include <cmath>
namespace jarvis::engineering {
bool valid_descriptor(const AgentDescriptor& d) noexcept { return !d.id.empty() && !d.name.empty() && std::isfinite(d.estimated_cost) && d.estimated_cost >= 0.0 && std::isfinite(d.reliability) && d.reliability >= 0.0 && d.reliability <= 1.0; }
bool valid_task(const EngineeringTask& t) noexcept { return !t.id.empty() && !t.objective.empty() && !t.required_capabilities.empty() && std::all_of(t.required_capabilities.begin(), t.required_capabilities.end(), [](const auto& v){return !v.empty();}) && std::isfinite(t.maximum_cost) && t.maximum_cost >= 0.0; }
} // namespace jarvis::engineering
