#include "jarvis/engineering/operator_bridge.hpp"

#include <utility>

namespace jarvis::engineering {

OperatorBridge::OperatorBridge(
    AgentMessageBus& bus,
    std::string operator_id,
    std::string run_id,
    std::string workspace_id,
    AgentConversation::Authorization authorization,
    AgentConversationPolicy policy)
    : bus_(bus),
      conversation_(
          bus,
          std::move(operator_id),
          std::move(run_id),
          std::move(workspace_id),
          std::move(authorization),
          policy) {}

bool OperatorBridge::connected() const noexcept { return conversation_.connected(); }
const std::string& OperatorBridge::operator_id() const noexcept { return conversation_.participant_id(); }
const std::string& OperatorBridge::run_id() const noexcept { return conversation_.run_id(); }
const std::string& OperatorBridge::workspace_id() const noexcept { return conversation_.workspace_id(); }

MessageBusResult OperatorBridge::send(const OperatorMessage& message) {
    return conversation_.send(
        message.recipient_id,
        message.correlation_id,
        message.type,
        message.payload);
}

std::vector<std::string> OperatorBridge::available_agents() const {
    const auto ids = bus_.registered_agent_ids();
    std::vector<std::string> agents;
    agents.reserve(ids.size());
    for (const auto& id : ids) {
        if (id != operator_id()) agents.push_back(id);
    }
    return agents;
}

std::vector<AgentMessage> OperatorBridge::receive() { return conversation_.receive(); }
std::size_t OperatorBridge::pending() const noexcept { return conversation_.pending(); }

} // namespace jarvis::engineering
