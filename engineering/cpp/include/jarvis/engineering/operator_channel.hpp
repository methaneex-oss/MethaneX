#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct OperatorMessage {
    std::string message_id;
    std::string correlation_id;
    std::string recipient_id;
    AgentMessageType type{AgentMessageType::request};
    std::string payload;
};

struct OperatorChannelResult {
    bool accepted{false};
    std::uint64_t sequence{0};
    std::string reason;
};

class OperatorChannel {
public:
    OperatorChannel(
        AgentMessageBus& bus,
        std::string session_id,
        std::string run_id,
        std::string workspace_id,
        std::size_t maximum_pending_messages = 256);

    bool connected() const noexcept;
    const std::string& session_id() const noexcept;

    OperatorChannelResult send(const OperatorMessage& message);
    std::vector<AgentMessage> receive();
    std::size_t pending() const noexcept;

private:
    AgentCommunicationEndpoint endpoint_;
};

} // namespace jarvis::engineering
