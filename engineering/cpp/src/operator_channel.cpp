#include "jarvis/engineering/operator_channel.hpp"

#include <utility>

namespace jarvis::engineering {

EngineeringOperatorChannel::EngineeringOperatorChannel(
    AgentMessageBus& bus,
    std::string operator_id,
    std::string run_id,
    std::string workspace_id,
    std::size_t maximum_pending_messages)
    : bus_(bus),
      operator_id_(std::move(operator_id)),
      run_id_(std::move(run_id)),
      workspace_id_(std::move(workspace_id)),
      maximum_pending_messages_(maximum_pending_messages) {
    if (operator_id_.empty() || run_id_.empty() || maximum_pending_messages_ == 0) {
        return;
    }

    const auto result = bus_.register_agent(
        operator_id_,
        [this](const AgentMessage& message) { receive_message(message); });
    connected_ = result.accepted;
}

EngineeringOperatorChannel::~EngineeringOperatorChannel() {
    if (connected_) {
        bus_.unregister_agent(operator_id_);
    }
}

bool EngineeringOperatorChannel::connected() const noexcept {
    return connected_;
}

const std::string& EngineeringOperatorChannel::operator_id() const noexcept {
    return operator_id_;
}

MessageBusResult EngineeringOperatorChannel::send_to_agent(
    std::string message_id,
    std::string agent_id,
    std::string correlation_id,
    AgentMessageType type,
    std::string payload) {
    if (!connected_) {
        return {false, 0, "operator channel is not connected"};
    }
    if (agent_id.empty()) {
        return {false, 0, "agent id is empty"};
    }

    return bus_.send(AgentMessage{
        std::move(message_id),
        0,
        run_id_,
        workspace_id_,
        operator_id_,
        std::move(agent_id),
        std::move(correlation_id),
        type,
        std::move(payload)});
}

void EngineeringOperatorChannel::receive_message(const AgentMessage& message) {
    if (message.run_id != run_id_ ||
        (!workspace_id_.empty() && message.workspace_id != workspace_id_)) {
        return;
    }

    std::lock_guard lock(mutex_);
    if (pending_messages_.size() >= maximum_pending_messages_) {
        pending_messages_.pop_front();
    }
    pending_messages_.push_back(message);
}

std::vector<AgentMessage> EngineeringOperatorChannel::receive() {
    std::lock_guard lock(mutex_);
    std::vector<AgentMessage> messages;
    messages.reserve(pending_messages_.size());
    while (!pending_messages_.empty()) {
        messages.push_back(std::move(pending_messages_.front()));
        pending_messages_.pop_front();
    }
    return messages;
}

std::size_t EngineeringOperatorChannel::pending() const noexcept {
    std::lock_guard lock(mutex_);
    return pending_messages_.size();
}

} // namespace jarvis::engineering
