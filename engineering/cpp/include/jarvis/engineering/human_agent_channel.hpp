#pragma once

#include "message_bus.hpp"

#include <string>
#include <vector>

namespace jarvis::engineering {

struct HumanAgentMessage {
    std::string message_id;
    std::string correlation_id;
    std::string recipient_agent_id;
    std::string text;
};

class HumanAgentChannel {
public:
    HumanAgentChannel(
        AgentMessageBus& bus,
        std::string human_id,
        std::string session_id,
        std::string workspace_id = {},
        std::size_t maximum_pending_messages = 256);

    bool connected() const noexcept;
    const std::string& human_id() const noexcept;
    const std::string& session_id() const noexcept;

    MessageBusResult send_to_agent(
        std::string message_id,
        std::string correlation_id,
        std::string recipient_agent_id,
        std::string text);

    std::vector<AgentMessage> receive_from_agents();

private:
    AgentCommunicationEndpoint endpoint_;
    std::string human_id_;
    std::string session_id_;
};

} // namespace jarvis::engineering
