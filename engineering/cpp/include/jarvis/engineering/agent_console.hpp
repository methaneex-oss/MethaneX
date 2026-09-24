#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct AgentConsoleMessage {
    std::string message_id;
    std::string sender_id;
    std::string recipient_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::status};
    std::string payload;
    std::uint64_t sequence{0};
};

// Explicit operator-facing communication boundary. It does not interpret
// natural language or choose agents; routing remains a capability decision
// outside this class.
class AgentConsole {
public:
    AgentConsole(AgentMessageBus& bus,
                 std::string operator_id,
                 std::string run_id,
                 std::string workspace_id,
                 std::size_t maximum_pending_messages = 256);

    bool connected() const noexcept;
    const std::string& operator_id() const noexcept;
    const std::string& run_id() const noexcept;
    const std::string& workspace_id() const noexcept;

    MessageBusResult send_to_agent(
        std::string message_id,
        std::string agent_id,
        std::string correlation_id,
        AgentMessageType type,
        std::string payload);

    MessageBusResult broadcast(
        std::string message_id,
        const std::vector<std::string>& agent_ids,
        std::string correlation_id,
        AgentMessageType type,
        std::string payload);

    std::vector<AgentConsoleMessage> receive();
    std::size_t pending() const noexcept;

private:
    AgentCommunicationEndpoint endpoint_;
};

} // namespace jarvis::engineering
