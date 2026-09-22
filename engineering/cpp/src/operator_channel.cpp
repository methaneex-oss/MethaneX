#include "jarvis/engineering/operator_channel.hpp"

#include <utility>

namespace jarvis::engineering {

OperatorChannel::OperatorChannel(
    AgentMessageBus& bus,
    std::string session_id,
    std::string run_id,
    std::string workspace_id,
    std::size_t maximum_pending_messages)
    : endpoint_(
          bus,
          std::move(session_id),
          std::move(run_id),
          std::move(workspace_id),
          maximum_pending_messages) {}

bool OperatorChannel::connected() const noexcept {
    return endpoint_.registered();
}

const std::string& OperatorChannel::session_id() const noexcept {
    return endpoint_.agent_id();
}

OperatorChannelResult OperatorChannel::send(const OperatorMessage& message) {
    if (message.message_id.empty() || message.correlation_id.empty() ||
        message.recipient_id.empty()) {
        return {false, 0, "invalid operator message"};
    }

    const auto result = endpoint_.send(
        message.message_id,
        message.recipient_id,
        message.correlation_id,
        message.type,
        message.payload);
    return {result.accepted, result.sequence, result.reason};
}

std::vector<AgentMessage> OperatorChannel::receive() {
    return endpoint_.drain();
}

std::size_t OperatorChannel::pending() const noexcept {
    return endpoint_.pending();
}

} // namespace jarvis::engineering
