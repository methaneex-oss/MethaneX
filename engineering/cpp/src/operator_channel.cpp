#include "jarvis/engineering/operator_channel.hpp"

#include <string>

namespace jarvis::engineering {

OperatorChannel::OperatorChannel(AgentMessageBus& bus, std::string operator_id)
    : bus_(bus), operator_id_(std::move(operator_id)) {}

MessageBusResult OperatorChannel::send_to_agent(
    const std::string& agent_id,
    const std::string& run_id,
    const std::string& workspace_id,
    const std::string& correlation_id,
    AgentMessageType type,
    const std::string& payload) {
    return bus_.send(AgentMessage{
        "operator-" + std::to_string(next_message_id_++), 0,
        run_id, workspace_id, operator_id_, agent_id, correlation_id,
        type, payload});
}

MessageBusResult OperatorChannel::broadcast(
    const std::string& run_id,
    const std::string& workspace_id,
    const std::string& correlation_id,
    AgentMessageType type,
    const std::string& payload) {
    return bus_.send(AgentMessage{
        "operator-" + std::to_string(next_message_id_++), 0,
        run_id, workspace_id, operator_id_, "*", correlation_id,
        type, payload});
}

std::vector<AgentMessage> OperatorChannel::drain_from_agents() {
    // Operator messages are subscribed through a reserved endpoint. Keeping
    // transport concerns in AgentMessageBus prevents a second communication
    // protocol from emerging solely for humans.
    return {};
}

} // namespace jarvis::engineering
