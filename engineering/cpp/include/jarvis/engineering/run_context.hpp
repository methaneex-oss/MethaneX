#pragma once

#include "agent.hpp"

#include <string>
#include <vector>

namespace jarvis::engineering {

struct EngineeringStageFeedback {
    EngineeringStage stage;
    AgentResult result;
};

struct EngineeringRunContext {
    std::string run_id;
    std::string workspace_id;
    std::vector<EngineeringStageFeedback> stages;
    std::vector<AgentArtifact> artifacts;
    std::vector<AgentEvidence> evidence;
};

} // namespace jarvis::engineering
