#pragma once

#include "agent_conversation.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::engineering {

struct OperatorGatewayPolicy {
    std::size_t maximum_pending_messages{256};
};

class EngineeringOperatorGateway {
public:
    using Authorization = AgentConversation::Authorization;

    EngineeringOperatorGateway(
        AgentMessageBus& bus,
        std::string operator_id,
        std::string run_id,
        std::string workspace_id,
        Authorization authorization = {},
        OperatorGatewayPolicy policy = {});

    bool connected() const noexcept;
    const std::string& operator_id() const noexcept;
    const std::string& run_id() const noexcept;
    const std::string& workspace_id() const noexcept;

    MessageBusResult send_to(
        const std::string& agent_id,
        const std::string& correlation_id,
        AgentMessageType type,
        const std::string& payload);

    std::vector<AgentMessage> receive();
    std::size_t pending() const noexcept;

private:
    AgentConversation conversation_;
};

} // namespace jarvis::engineering
