#include "jarvis/engineering/execution.hpp"

namespace jarvis::engineering {

AgentResult DirectExecutionBoundary::run(
    const EngineeringTask& task,
    EngineeringAgent& agent) {
    return agent.execute(task);
}

} // namespace jarvis::engineering
