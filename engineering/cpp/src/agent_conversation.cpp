#include "jarvis/engineering/agent_conversation.hpp"

#include <utility>

namespace jarvis::engineering {

AgentConversationBridge::AgentConversationBridge(
    AgentMessageBus& bus,
    std::string conversation_id,
    std::string run_id,
    std::string workspace_id,
    std::size_t maximum_pending_messages)
    : bus_(bus),
      conversation_id_(std::move(conversation_id)),
      run_id_(std::move(run_id)),
      workspace_id_(std::move(workspace_id)),
      maximum_pending_messages_(maximum_pending_messages) {
    if (conversation_id_.empty() || run_id_.empty() || maximum_pending_messages_ == 0) {
        return;
    }

    const auto result = bus_.register_agent(
        std::string{kHumanConversationEndpoint},
        [this](const AgentMessage& message) { receive(message); });
    registered_ = result.accepted;
}

AgentConversationBridge::~AgentConversationBridge() {
    if (registered_) {
        bus_.unregister_agent(std::string{kHumanConversationEndpoint});
    }
}

bool AgentConversationBridge::registered() const noexcept {
    return registered_;
}

const std::string& AgentConversationBridge::conversation_id() const noexcept {
    return conversation_id_;
}

ConversationResult AgentConversationBridge::send_to_agent(
    std::string message_id,
    std::string agent_id,
    std::string content,
    AgentMessageType type) {
    if (!registered_) {
        return {false, std::move(message_id), "conversation bridge is not registered"};
    }
    if (message_id.empty() || agent_id.empty() || content.empty()) {
        return {false, std::move(message_id), "message requires id, recipient and content"};
    }

    const auto result = bus_.send(AgentMessage{
        message_id,
        0,
        run_id_,
        workspace_id_,
        std::string{kHumanConversationEndpoint},
        std::move(agent_id),
        conversation_id_,
        type,
        std::move(content)
    });

    return {result.accepted, std::move(message_id), result.reason};
}

void AgentConversationBridge::receive(const AgentMessage& message) {
    if (message.run_id != run_id_ ||
        (!workspace_id_.empty() && message.workspace_id != workspace_id_) ||
        message.recipient_id != kHumanConversationEndpoint) {
        return;
    }

    std::lock_guard lock(mutex_);
    if (pending_messages_.size() >= maximum_pending_messages_) {
        pending_messages_.pop_front();
    }
    pending_messages_.push_back(ConversationMessage{
        message.message_id,
        message.correlation_id,
        message.sender_id,
        message.recipient_id,
        ConversationRole::agent,
        message.type,
        message.payload
    });
}

std::vector<ConversationMessage> AgentConversationBridge::receive_from_agents() {
    std::lock_guard lock(mutex_);
    std::vector<ConversationMessage> messages;
    messages.reserve(pending_messages_.size());
    while (!pending_messages_.empty()) {
        messages.push_back(std::move(pending_messages_.front()));
        pending_messages_.pop_front();
    }
    return messages;
}

std::size_t AgentConversationBridge::pending() const noexcept {
    std::lock_guard lock(mutex_);
    return pending_messages_.size();
}

} // namespace jarvis::engineering
