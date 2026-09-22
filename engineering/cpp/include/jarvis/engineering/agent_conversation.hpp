#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::engineering {

inline constexpr std::string_view kHumanConversationEndpoint = "human";

enum class ConversationRole : std::uint8_t {
    human,
    agent
};

struct ConversationMessage {
    std::string message_id;
    std::string conversation_id;
    std::string sender_id;
    std::string recipient_id;
    ConversationRole role{ConversationRole::human};
    AgentMessageType type{AgentMessageType::query};
    std::string content;
};

struct ConversationResult {
    bool accepted{false};
    std::string message_id;
    std::string reason;
};

class AgentConversationBridge {
public:
    AgentConversationBridge(
        AgentMessageBus& bus,
        std::string conversation_id,
        std::string run_id,
        std::string workspace_id,
        std::size_t maximum_pending_messages = 256);

    ~AgentConversationBridge();

    AgentConversationBridge(const AgentConversationBridge&) = delete;
    AgentConversationBridge& operator=(const AgentConversationBridge&) = delete;

    bool registered() const noexcept;
    const std::string& conversation_id() const noexcept;

    ConversationResult send_to_agent(
        std::string message_id,
        std::string agent_id,
        std::string content,
        AgentMessageType type = AgentMessageType::query);

    std::vector<ConversationMessage> receive_from_agents();
    std::size_t pending() const noexcept;

private:
    void receive(const AgentMessage& message);

    AgentMessageBus& bus_;
    std::string conversation_id_;
    std::string run_id_;
    std::string workspace_id_;
    std::size_t maximum_pending_messages_;
    mutable std::mutex mutex_;
    std::deque<ConversationMessage> pending_messages_;
    bool registered_{false};
};

} // namespace jarvis::engineering
