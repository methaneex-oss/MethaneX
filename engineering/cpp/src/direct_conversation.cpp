#include "jarvis/engineering/direct_conversation.hpp"

#include <utility>

namespace jarvis::engineering {

DirectAgentConversation::DirectAgentConversation(
    AgentMessageBus& bus,
    std::string run_id,
    std::string workspace_id,
    std::size_t maximum_pending_messages)
    : bus_(bus),
      user_endpoint_(bus_, "human", run_id, workspace_id, maximum_pending_messages),
      assistant_endpoint_(bus_, "assistant", std::move(run_id), std::move(workspace_id), maximum_pending_messages) {}

bool DirectAgentConversation::ready() const noexcept {
    return user_endpoint_.registered() && assistant_endpoint_.registered();
}

MessageBusResult DirectAgentConversation::send_user(
    std::string message_id,
    std::string agent_id,
    std::string correlation_id,
    std::string payload) {
    return user_endpoint_.send(
        std::move(message_id), std::move(agent_id), std::move(correlation_id),
        AgentMessageType::query, std::move(payload));
}

MessageBusResult DirectAgentConversation::send_assistant(
    std::string message_id,
    std::string agent_id,
    std::string correlation_id,
    std::string payload) {
    return assistant_endpoint_.send(
        std::move(message_id), std::move(agent_id), std::move(correlation_id),
        AgentMessageType::query, std::move(payload));
}

std::vector<ConversationMessage> DirectAgentConversation::drain_user() {
    std::vector<ConversationMessage> result;
    for (const auto& message : user_endpoint_.drain()) {
        result.push_back(to_conversation_message(message));
    }
    return result;
}

std::vector<ConversationMessage> DirectAgentConversation::drain_assistant() {
    std::vector<ConversationMessage> result;
    for (const auto& message : assistant_endpoint_.drain()) {
        result.push_back(to_conversation_message(message));
    }
    return result;
}

ConversationMessage DirectAgentConversation::to_conversation_message(
    const AgentMessage& message) {
    return {
        message.message_id,
        message.run_id,
        message.workspace_id,
        message.sender_id,
        message.recipient_id,
        message.correlation_id,
        message.type,
        message.payload,
        message.sequence};
}

} // namespace jarvis::engineering
