#include "jarvis/engineering/agent_conversation.hpp"

#include <utility>

namespace jarvis::engineering {

AgentConversation::AgentConversation(
    AgentMessageBus& bus,
    std::string participant_id,
    std::string run_id,
    std::string workspace_id,
    Authorization authorization,
    AgentConversationPolicy policy)
    : endpoint_(bus,
                 std::move(participant_id),
                 std::move(run_id),
                 std::move(workspace_id),
                 policy.maximum_pending_messages),
      authorization_(std::move(authorization)) {}

AgentConversation::~AgentConversation() = default;

bool AgentConversation::connected() const noexcept {
    return endpoint_.registered();
}

const std::string& AgentConversation::participant_id() const noexcept {
    return endpoint_.agent_id();
}

const std::string& AgentConversation::run_id() const noexcept {
    return endpoint_.agent_id();
}

MessageBusResult AgentConversation::send(
    const std::string& recipient_id,
    const std::string& correlation_id,
    AgentMessageType type,
    const std::string& payload) {
    if (!connected()) {
        return {false, 0, "conversation is not connected"};
    }
    if (authorization_ && !authorization_(participant_id(), recipient_id, type)) {
        return {false, 0, "conversation authorization denied"};
    }
    return endpoint_.send(
        participant_id() + ":" + correlation_id,
        recipient_id,
        correlation_id,
        type,
        payload);
}

std::vector<AgentMessage> AgentConversation::receive() {
    return endpoint_.drain();
}

std::size_t AgentConversation::pending() const noexcept {
    return endpoint_.pending();
}

} // namespace jarvis::engineering
