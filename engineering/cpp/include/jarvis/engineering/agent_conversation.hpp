#pragma once

#include "agent.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct AgentConversationRequest {
    std::string session_id;
    std::string sender_id;
    std::string message;
    std::string context;
    std::size_t maximum_output_bytes{64 * 1024};
};

struct AgentConversationResponse {
    bool accepted{false};
    std::string session_id;
    std::string agent_id;
    std::string response;
    std::vector<AgentEvidence> evidence;
    std::string reason;
};

class ConversationalEngineeringAgent {
public:
    virtual ~ConversationalEngineeringAgent() = default;
    virtual AgentConversationResponse converse(
        const AgentConversationRequest& request) = 0;
};

} // namespace jarvis::engineering
