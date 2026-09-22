#pragma once

#include "message_bus.hpp"

#include <deque>
#include <mutex>
#include <string>
#include <vector>

namespace jarvis::engineering {

// Human/operator communication uses the same normalized message fabric as
// agent-to-agent communication. The channel does not interpret intent; it
// only transports addressed messages and exposes an auditable transcript.
class OperatorChannel {
public:
    explicit OperatorChannel(AgentMessageBus& bus,
                             std::string operator_id = "operator");

    MessageBusResult send_to_agent(const std::string& agent_id,
                                   const std::string& run_id,
                                   const std::string& workspace_id,
                                   const std::string& correlation_id,
                                   AgentMessageType type,
                                   const std::string& payload);

    MessageBusResult broadcast(const std::string& run_id,
                               const std::string& workspace_id,
                               const std::string& correlation_id,
                               AgentMessageType type,
                               const std::string& payload);

    std::vector<AgentMessage> drain_from_agents();
    const std::string& operator_id() const noexcept { return operator_id_; }

private:
    AgentMessageBus& bus_;
    std::string operator_id_;
    std::uint64_t next_message_id_{1};
};

} // namespace jarvis::engineering
