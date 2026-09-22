#pragma once

#include "jarvis/engineering/message_bus.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::engineering {

// Human-facing communication boundary. It uses the same message bus as agents,
// so operator messages participate in the same run/workspace/correlation model.
// It does not grant execution authority; normal authorization remains separate.
class EngineeringOperatorEndpoint {
public:
    EngineeringOperatorEndpoint(
        AgentMessageBus& bus,
        std::string operator_id,
        std::string run_id,
        std::string workspace_id,
        std::size_t maximum_pending_messages = 256);

    bool registered() const noexcept;
    const std::string& operator_id() const noexcept;

    MessageBusResult send(
        const std::string& agent_id,
        const std::string& message_id,
        const std::string& correlation_id,
        AgentMessageType type,
        const std::string& payload);

    MessageBusResult ask(
        const std::string& agent_id,
        const std::string& message_id,
        const std::string& correlation_id,
        const std::string& payload);

    std::vector<AgentMessage> drain();
    std::size_t pending() const noexcept;

private:
    AgentCommunicationEndpoint endpoint_;
};

} // namespace jarvis::engineering
