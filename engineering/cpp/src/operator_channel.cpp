#include "jarvis/engineering/operator_channel.hpp"

#include <utility>

namespace jarvis::engineering {

OperatorChannel::OperatorChannel(AgentMessageBus& bus, std::string operator_id,
                                 std::size_t maximum_pending_messages)
    : bus_(bus),
      operator_id_(std::move(operator_id)),
      endpoint_(bus_, operator_id_, "", "", maximum_pending_messages) {}

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

std::vector<MessageBusResult> OperatorChannel::send_to_agents(
    const std::vector<std::string>& agent_ids,
    const std::string& run_id,
    const std::string& workspace_id,
    const std::string& correlation_id,
    AgentMessageType type,
    const std::string& payload) {
    std::vector<MessageBusResult> results;
    results.reserve(agent_ids.size());
    for (const auto& agent_id : agent_ids) {
        results.push_back(send_to_agent(agent_id, run_id, workspace_id,
                                        correlation_id, type, payload));
    }
    return results;
}

std::vector<AgentMessage> OperatorChannel::drain_from_agents() {
    return endpoint_.drain();
}

std::size_t OperatorChannel::pending() const noexcept {
    return endpoint_.pending();
}

} // namespace jarvis::engineering
