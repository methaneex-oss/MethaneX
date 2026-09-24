#include "jarvis/engineering/agent_console.hpp"

namespace jarvis::engineering {

AgentConsole::AgentConsole(AgentMessageBus& bus,
                           std::string operator_id,
                           std::string run_id,
                           std::string workspace_id,
                           std::size_t maximum_pending_messages)
    : endpoint_(bus, std::move(operator_id), std::move(run_id),
                std::move(workspace_id), maximum_pending_messages) {}

bool AgentConsole::connected() const noexcept { return endpoint_.registered(); }

const std::string& AgentConsole::operator_id() const noexcept {
    return endpoint_.agent_id();
}

const std::string& AgentConsole::run_id() const noexcept {
    return endpoint_.run_id();
}

const std::string& AgentConsole::workspace_id() const noexcept {
    return endpoint_.workspace_id();
}

MessageBusResult AgentConsole::send_to_agent(
    std::string message_id,
    std::string agent_id,
    std::string correlation_id,
    AgentMessageType type,
    std::string payload) {
    return endpoint_.send(std::move(message_id), std::move(agent_id),
                          std::move(correlation_id), type, std::move(payload));
}

MessageBusResult AgentConsole::broadcast(
    std::string message_id,
    const std::vector<std::string>& agent_ids,
    std::string correlation_id,
    AgentMessageType type,
    std::string payload) {
    MessageBusResult last{true, 0, {}};
    for (const auto& agent_id : agent_ids) {
        last = send_to_agent(message_id, agent_id, correlation_id, type, payload);
        if (!last.accepted) return last;
    }
    return last;
}

std::vector<AgentConsoleMessage> AgentConsole::receive() {
    const auto messages = endpoint_.drain();
    std::vector<AgentConsoleMessage> result;
    result.reserve(messages.size());
    for (const auto& message : messages) {
        result.push_back({message.message_id, message.sender_id,
                          message.recipient_id, message.correlation_id,
                          message.type, message.payload, message.sequence});
    }
    return result;
}

std::size_t AgentConsole::pending() const noexcept { return endpoint_.pending(); }

} // namespace jarvis::engineering
