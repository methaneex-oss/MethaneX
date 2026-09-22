#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::engineering {

enum class ConversationActor : std::uint8_t {
    user,
    assistant
};

struct ConversationMessage {
    std::string message_id;
    std::string run_id;
    std::string workspace_id;
    std::string sender_id;
    std::string recipient_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::query};
    std::string payload;
    std::uint64_t sequence{0};
};

class DirectAgentConversation {
public:
    DirectAgentConversation(
        AgentMessageBus& bus,
        std::string run_id,
        std::string workspace_id,
        std::size_t maximum_pending_messages = 256);

    bool ready() const noexcept;

    MessageBusResult send_user(
        std::string message_id,
        std::string agent_id,
        std::string correlation_id,
        std::string payload);

    MessageBusResult send_assistant(
        std::string message_id,
        std::string agent_id,
        std::string correlation_id,
        std::string payload);

    std::vector<ConversationMessage> drain_user();
    std::vector<ConversationMessage> drain_assistant();

private:
    static ConversationMessage to_conversation_message(const AgentMessage& message);

    AgentMessageBus& bus_;
    AgentCommunicationEndpoint user_endpoint_;
    AgentCommunicationEndpoint assistant_endpoint_;
};

} // namespace jarvis::engineering
