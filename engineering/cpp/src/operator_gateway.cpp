#include "jarvis/engineering/operator_gateway.hpp"

#include <algorithm>

namespace jarvis::engineering {

OperatorGateway::OperatorGateway(
    AgentMessageBus& bus,
    std::string operator_id,
    std::string run_id,
    std::string workspace_id,
    OperatorGatewayPolicy policy)
    : bus_(bus),
      endpoint_(bus_, std::move(operator_id), std::move(run_id),
                std::move(workspace_id)),
      policy_(std::move(policy)) {}

OperatorGateway::~OperatorGateway() = default;

bool OperatorGateway::connected() const noexcept {
    return endpoint_.registered();
}

const std::string& OperatorGateway::operator_id() const noexcept {
    return endpoint_.agent_id();
}

const std::string& OperatorGateway::run_id() const noexcept {
    return endpoint_.run_id();
}

const std::string& OperatorGateway::workspace_id() const noexcept {
    return endpoint_.workspace_id();
}

OperatorGatewayResult OperatorGateway::send_to_agent(
    const OperatorMessage& message,
    const std::string& agent_id) {
    if (agent_id.empty()) return {false, "recipient is required", 0};
    if (!valid_message(message, policy_.maximum_message_bytes)) {
        return {false, "invalid operator message", 0};
    }
    if (policy_.authorize && !policy_.authorize(message, agent_id)) {
        return {false, "operator authorization denied", 0};
    }

    const auto result = endpoint_.send(
        message.message_id, agent_id, message.correlation_id,
        message.type, message.payload);
    return {result.accepted, result.reason, result.sequence};
}

OperatorGatewayResult OperatorGateway::broadcast(
    const OperatorMessage& message,
    const std::vector<std::string>& agent_ids) {
    if (!policy_.allow_broadcast) {
        return {false, "operator broadcast is disabled", 0};
    }
    if (!valid_message(message, policy_.maximum_message_bytes)) {
        return {false, "invalid operator message", 0};
    }

    OperatorGatewayResult final_result{true, "broadcast completed", 0};
    for (const auto& agent_id : agent_ids) {
        const auto result = send_to_agent(message, agent_id);
        if (!result.accepted) {
            final_result.accepted = false;
            final_result.reason = result.reason;
            return final_result;
        }
        final_result.sequence = result.sequence;
    }
    return final_result;
}

std::vector<AgentMessage> OperatorGateway::receive() {
    return endpoint_.drain();
}

std::size_t OperatorGateway::pending() const noexcept {
    return endpoint_.pending();
}

bool OperatorGateway::valid_message(
    const OperatorMessage& message,
    std::size_t maximum_bytes) noexcept {
    return !message.message_id.empty() &&
           !message.payload.empty() &&
           message.payload.size() <= maximum_bytes;
}

} // namespace jarvis::engineering
