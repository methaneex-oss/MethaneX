#pragma once

#include "message_bus.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::engineering {

// Human/operator communication uses the same normalized message fabric as
// agent-to-agent communication. The channel does not interpret intent; it
// only transports addressed messages and exposes an auditable transcript.
class OperatorChannel {
public:
    explicit OperatorChannel(AgentMessageBus& bus,
                             std::string operator_id = "operator",
                             std::size_t maximum_pending_messages = 256);

    MessageBusResult send_to_agent(const std::string& agent_id,
                                   const std::string& run_id,
                                   const std::string& workspace_id,
                                   const std::string& correlation_id,
                                   AgentMessageType type,
                                   const std::string& payload);

    // Sends the same operator instruction to each explicitly supplied agent.
    // There is deliberately no wildcard recipient in the message protocol.
    std::vector<MessageBusResult> send_to_agents(
        const std::vector<std::string>& agent_ids,
        const std::string& run_id,
        const std::string& workspace_id,
        const std::string& correlation_id,
        AgentMessageType type,
        const std::string& payload);

    std::vector<AgentMessage> drain_from_agents();
    std::size_t pending() const noexcept;
    const std::string& operator_id() const noexcept { return operator_id_; }
    bool registered() const noexcept { return endpoint_.registered(); }

private:
    AgentMessageBus& bus_;
    std::string operator_id_;
    std::uint64_t next_message_id_{1};
    AgentCommunicationEndpoint endpoint_;
};

} // namespace jarvis::engineering
