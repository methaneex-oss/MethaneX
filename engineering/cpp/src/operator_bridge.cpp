#include "jarvis/engineering/operator_bridge.hpp"

#include <algorithm>
#include <utility>

namespace jarvis::engineering {

AgentOperatorBridge::AgentOperatorBridge(
    AgentMessageBus& bus,
    std::string operator_id,
    std::string run_id,
    std::string workspace_id,
    AgentOperatorBridgePolicy policy)
    : policy_(std::move(policy)),
      conversation_(
          bus,
          std::move(operator_id),
          std::move(run_id),
          std::move(workspace_id),
          [this](const std::string& sender,
                 const std::string& recipient,
                 AgentMessageType type) {
              if (sender != operator_id()) return false;
              if (!allows(type)) return false;
              return !policy_.authorize || policy_.authorize(sender, recipient, type);
          },
          AgentConversationPolicy{policy_.maximum_pending_messages}) {}

bool AgentOperatorBridge::connected() const noexcept { return conversation_.connected(); }
const std::string& AgentOperatorBridge::operator_id() const noexcept {
    return conversation_.participant_id();
}
const std::string& AgentOperatorBridge::run_id() const noexcept {
    return conversation_.run_id();
}
const std::string& AgentOperatorBridge::workspace_id() const noexcept {
    return conversation_.workspace_id();
}

MessageBusResult AgentOperatorBridge::send(const AgentOperatorMessage& message) {
    if (!connected()) return {false, 0, "operator bridge is not connected"};
    if (message.recipient_id.empty() || message.correlation_id.empty()) {
        return {false, 0, "recipient and correlation id are required"};
    }
    if (!allows(message.type)) return {false, 0, "operator message type is not permitted"};
    return conversation_.send(
        message.recipient_id,
        message.correlation_id,
        message.type,
        message.payload);
}

MessageBusResult AgentOperatorBridge::send_to_agent(
    const std::string& agent_id,
    const std::string& correlation_id,
    const std::string& payload,
    AgentMessageType type) {
    return send({agent_id, correlation_id, type, payload});
}

std::vector<AgentMessage> AgentOperatorBridge::receive() { return conversation_.receive(); }
std::size_t AgentOperatorBridge::pending() const noexcept { return conversation_.pending(); }

bool AgentOperatorBridge::allows(AgentMessageType type) const noexcept {
    return std::find(policy_.allowed_message_types.begin(),
                     policy_.allowed_message_types.end(), type) !=
           policy_.allowed_message_types.end();
}

} // namespace jarvis::engineering
