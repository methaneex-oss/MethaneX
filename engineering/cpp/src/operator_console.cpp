#include "jarvis/engineering/operator_console.hpp"

#include <utility>

namespace jarvis::engineering {

EngineeringOperatorEndpoint::EngineeringOperatorEndpoint(
    AgentMessageBus& bus,
    std::string operator_id,
    std::string run_id,
    std::string workspace_id,
    std::size_t maximum_pending_messages)
    : endpoint_(bus,
                std::move(operator_id),
                std::move(run_id),
                std::move(workspace_id),
                maximum_pending_messages) {}

bool EngineeringOperatorEndpoint::registered() const noexcept {
    return endpoint_.registered();
}

const std::string& EngineeringOperatorEndpoint::operator_id() const noexcept {
    return endpoint_.agent_id();
}

MessageBusResult EngineeringOperatorEndpoint::send(
    const std::string& agent_id,
    const std::string& message_id,
    const std::string& correlation_id,
    AgentMessageType type,
    const std::string& payload) {
    return endpoint_.send(
        message_id, agent_id, correlation_id, type, payload);
}

MessageBusResult EngineeringOperatorEndpoint::ask(
    const std::string& agent_id,
    const std::string& message_id,
    const std::string& correlation_id,
    const std::string& payload) {
    return send(agent_id, message_id, correlation_id,
                AgentMessageType::request, payload);
}

std::vector<AgentMessage> EngineeringOperatorEndpoint::drain() {
    return endpoint_.drain();
}

std::size_t EngineeringOperatorEndpoint::pending() const noexcept {
    return endpoint_.pending();
}

} // namespace jarvis::engineering
