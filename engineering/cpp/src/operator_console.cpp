#include "jarvis/engineering/operator_console.hpp"

#include <utility>

namespace jarvis::engineering {

EngineeringOperatorConsole::EngineeringOperatorConsole(
    AgentMessageBus& bus,
    std::string operator_id,
    std::string run_id,
    std::string workspace_id,
    Authorization authorization,
    OperatorConsolePolicy policy)
    : endpoint_(bus, std::move(operator_id), std::move(run_id),
                std::move(workspace_id), policy.maximum_pending_messages),
      authorization_(std::move(authorization)),
      policy_(policy) {}

EngineeringOperatorConsole::~EngineeringOperatorConsole() = default;

bool EngineeringOperatorConsole::connected() const noexcept {
    return endpoint_.registered();
}

const std::string& EngineeringOperatorConsole::operator_id() const noexcept {
    return endpoint_.agent_id();
}

const std::string& EngineeringOperatorConsole::run_id() const noexcept {
    return endpoint_.run_id();
}

const std::string& EngineeringOperatorConsole::workspace_id() const noexcept {
    return endpoint_.workspace_id();
}

bool EngineeringOperatorConsole::allowed(AgentMessageType type) const noexcept {
    switch (type) {
    case AgentMessageType::request: return policy_.allow_requests;
    case AgentMessageType::query: return policy_.allow_queries;
    case AgentMessageType::feedback: return policy_.allow_feedback;
    default: return false;
    }
}

MessageBusResult EngineeringOperatorConsole::send(const OperatorMessage& message) {
    if (!connected()) return {false, 0, "operator console is not connected"};
    if (message.recipient_id.empty() || message.correlation_id.empty()) {
        return {false, 0, "recipient and correlation id are required"};
    }
    if (!allowed(message.type)) {
        return {false, 0, "operator message type is not permitted"};
    }
    if (authorization_ && !authorization_(operator_id(), message.recipient_id, message.type)) {
        return {false, 0, "operator authorization denied"};
    }
    const std::string id = message.message_id.empty()
        ? operator_id() + ":" + message.correlation_id
        : message.message_id;
    return endpoint_.send(
        id,
        message.recipient_id,
        message.correlation_id,
        message.type,
        message.payload);
}

std::vector<AgentMessage> EngineeringOperatorConsole::receive() {
    return endpoint_.drain();
}

std::size_t EngineeringOperatorConsole::pending() const noexcept {
    return endpoint_.pending();
}

} // namespace jarvis::engineering
