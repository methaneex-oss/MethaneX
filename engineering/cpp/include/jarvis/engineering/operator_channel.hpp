#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <deque>
#include <mutex>
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

class OperatorControlChannel {
public:
    OperatorControlChannel(
        AgentMessageBus& bus,
        std::string operator_id,
        std::string run_id,
        std::string workspace_id,
        std::size_t maximum_pending_messages = 256);

    ~OperatorControlChannel();

    OperatorControlChannel(const OperatorControlChannel&) = delete;
    OperatorControlChannel& operator=(const OperatorControlChannel&) = delete;

    bool connected() const noexcept;
    const std::string& operator_id() const noexcept;

    MessageBusResult send(const OperatorMessage& message);
    MessageBusResult broadcast(
        const std::vector<std::string>& recipients,
        std::string message_id,
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
