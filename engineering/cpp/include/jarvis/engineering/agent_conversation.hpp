#pragma once

#include "message_bus.hpp"

#include <string>
#include <vector>

namespace jarvis::engineering {

enum class EngineeringConversationActor : std::uint8_t {
    operator_user,
    assistant,
    agent
};

struct EngineeringConversationMessage {
    AgentMessage message;
    EngineeringConversationActor sender_type{EngineeringConversationActor::agent};
};

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

    MessageBusResult send_from_agent(
        std::string agent_id,
        std::string recipient_id,
        std::string correlation_id,
        AgentMessageType type,
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
