#pragma once

#include "agent_conversation.hpp"

#include <string>
#include <vector>

namespace jarvis::engineering {

// Transport-neutral boundary for a human/operator or supervising interface.
// UI, HTTP, WebSocket, CLI and other transports can adapt to this contract
// without becoming part of the engineering agents themselves.
struct OperatorMessage {
    std::string recipient_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::request};
    std::string payload;
};

class OperatorBridge {
public:
    OperatorBridge(
        AgentMessageBus& bus,
        std::string operator_id,
        std::string run_id,
        std::string workspace_id,
        AgentConversation::Authorization authorization = {},
        AgentConversationPolicy policy = {});

    bool connected() const noexcept;
    const std::string& operator_id() const noexcept;
    const std::string& run_id() const noexcept;
    const std::string& workspace_id() const noexcept;

    MessageBusResult send(const OperatorMessage& message);
    std::vector<AgentMessage> receive();
    std::size_t pending() const noexcept;

private:
    AgentConversation conversation_;
};

} // namespace jarvis::engineering
