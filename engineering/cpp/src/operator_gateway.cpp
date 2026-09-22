#include "jarvis/engineering/operator_gateway.hpp"

#include <utility>

namespace jarvis::engineering {

EngineeringOperatorGateway::EngineeringOperatorGateway(
    AgentMessageBus& bus,
    std::string operator_id,
    std::string run_id,
    std::string workspace_id,
    Authorization authorization,
    OperatorGatewayPolicy policy)
    : conversation_(
          bus,
          std::move(operator_id),
          std::move(run_id),
          std::move(workspace_id),
          std::move(authorization),
          AgentConversationPolicy{policy.maximum_pending_messages}) {}

bool EngineeringOperatorGateway::connected() const noexcept {
    return conversation_.connected();
}

const std::string& EngineeringOperatorGateway::operator_id() const noexcept {
    return conversation_.participant_id();
}

const std::string& EngineeringOperatorGateway::run_id() const noexcept {
    return conversation_.run_id();
}

const std::string& EngineeringOperatorGateway::workspace_id() const noexcept {
    return conversation_.workspace_id();
}

MessageBusResult EngineeringOperatorGateway::send_to(
    const std::string& agent_id,
    const std::string& correlation_id,
    AgentMessageType type,
    const std::string& payload) {
    return conversation_.send(agent_id, correlation_id, type, payload);
}

std::vector<AgentMessage> EngineeringOperatorGateway::receive() {
    return conversation_.receive();
}

std::size_t EngineeringOperatorGateway::pending() const noexcept {
    return conversation_.pending();
}

} // namespace jarvis::engineering
