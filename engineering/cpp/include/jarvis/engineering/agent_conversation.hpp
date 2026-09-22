#pragma once

#include "message_bus.hpp"

#include <functional>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct AgentConversationPolicy {
    std::size_t maximum_pending_messages{256};
};

class AgentConversation {
public:
    using Authorization = std::function<bool(
        const std::string& sender_id,
        const std::string& recipient_id,
        AgentMessageType type)>;

    AgentConversation(
        AgentMessageBus& bus,
        std::string participant_id,
        std::string run_id,
        std::string workspace_id,
        Authorization authorization = {},
        AgentConversationPolicy policy = {});

    ~AgentConversation();
    AgentConversation(const AgentConversation&) = delete;
    AgentConversation& operator=(const AgentConversation&) = delete;

    bool connected() const noexcept;
    const std::string& participant_id() const noexcept;
    const std::string& run_id() const noexcept;
    const std::string& workspace_id() const noexcept;

    MessageBusResult send(
        const std::string& recipient_id,
        const std::string& correlation_id,
        AgentMessageType type,
        const std::string& payload);

    std::vector<AgentMessage> receive();
    std::size_t pending() const noexcept;

private:
    AgentCommunicationEndpoint endpoint_;
    Authorization authorization_;
};

} // namespace jarvis::engineering
