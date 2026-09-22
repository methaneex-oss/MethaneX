#pragma once

#include "message_bus.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::engineering {

class EngineeringAgentConversation {
public:
    EngineeringAgentConversation(
        AgentMessageBus& bus,
        std::string run_id,
        std::string workspace_id = {},
        std::string operator_id = "operator",
        std::string assistant_id = "assistant",
        std::size_t maximum_pending_messages = 256);

    bool ready() const noexcept;

    MessageBusResult send_from_operator(
        std::string agent_id,
        std::string correlation_id,
        std::string content);

    MessageBusResult send_from_assistant(
        std::string agent_id,
        std::string correlation_id,
        std::string content);

    std::vector<AgentMessage> drain_operator();
    std::vector<AgentMessage> drain_assistant();

    const std::string& operator_id() const noexcept;
    const std::string& assistant_id() const noexcept;

private:
    AgentCommunicationEndpoint operator_endpoint_;
    AgentCommunicationEndpoint assistant_endpoint_;
};

} // namespace jarvis::engineering
