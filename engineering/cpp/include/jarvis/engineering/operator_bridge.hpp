#pragma once

#include "agent_conversation.hpp"

#include <functional>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct AgentOperatorBridgePolicy {
    std::size_t maximum_pending_messages{256};
    std::vector<AgentMessageType> allowed_message_types{
        AgentMessageType::request,
        AgentMessageType::query,
        AgentMessageType::feedback,
        AgentMessageType::review,
        AgentMessageType::status,
        AgentMessageType::result,
    };
    std::function<bool(const std::string&, const std::string&, AgentMessageType)> authorize{};
};

struct AgentOperatorMessage {
    std::string recipient_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::request};
    std::string payload;
};

class AgentOperatorBridge {
public:
    AgentOperatorBridge(
        AgentMessageBus& bus,
        std::string operator_id,
        std::string run_id,
        std::string workspace_id,
        AgentOperatorBridgePolicy policy = {});

    AgentOperatorBridge(const AgentOperatorBridge&) = delete;
    AgentOperatorBridge& operator=(const AgentOperatorBridge&) = delete;

    bool connected() const noexcept;
    const std::string& operator_id() const noexcept;
    const std::string& run_id() const noexcept;
    const std::string& workspace_id() const noexcept;

    MessageBusResult send(const AgentOperatorMessage& message);
    MessageBusResult send_to_agent(
        const std::string& agent_id,
        const std::string& correlation_id,
        const std::string& payload,
        AgentMessageType type = AgentMessageType::request);

    std::vector<AgentMessage> receive();
    std::size_t pending() const noexcept;

private:
    bool allows(AgentMessageType type) const noexcept;

    AgentConversation conversation_;
    AgentOperatorBridgePolicy policy_;
};

} // namespace jarvis::engineering
