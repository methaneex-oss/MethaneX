#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::engineering {

// A user-facing communication boundary. It deliberately speaks only in
// normalized AgentMessage values; it does not decide which agent should act.
class EngineeringOperatorChannel final {
public:
    EngineeringOperatorChannel(
        AgentMessageBus& bus,
        std::string operator_id,
        std::string run_id,
        std::string workspace_id,
        std::size_t maximum_pending_messages = 256);

    ~EngineeringOperatorChannel();

    EngineeringOperatorChannel(const EngineeringOperatorChannel&) = delete;
    EngineeringOperatorChannel& operator=(const EngineeringOperatorChannel&) = delete;

    bool connected() const noexcept;
    const std::string& operator_id() const noexcept;

    MessageBusResult send_to_agent(
        std::string message_id,
        std::string agent_id,
        std::string correlation_id,
        AgentMessageType type,
        std::string payload);

    std::vector<AgentMessage> receive();
    std::size_t pending() const noexcept;

private:
    void receive_message(const AgentMessage& message);

    AgentMessageBus& bus_;
    std::string operator_id_;
    std::string run_id_;
    std::string workspace_id_;
    std::size_t maximum_pending_messages_;
    mutable std::mutex mutex_;
    std::deque<AgentMessage> pending_messages_;
    bool connected_{false};
};

} // namespace jarvis::engineering
