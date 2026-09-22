#include "jarvis/engineering/operator_channel.hpp"

#include <utility>

namespace jarvis::engineering {

OperatorControlChannel::OperatorControlChannel(
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

OperatorControlChannel::~OperatorControlChannel() {
    if (connected_) {
        bus_.unregister_agent(operator_id_);
    }
}

bool OperatorControlChannel::connected() const noexcept { return connected_; }

const std::string& OperatorControlChannel::operator_id() const noexcept {
    return operator_id_;
}

MessageBusResult OperatorControlChannel::send(const OperatorMessage& message) {
    if (!connected_) {
        return {false, 0, "operator channel is not connected"};
    }
    if (message.message_id.empty() || message.correlation_id.empty() ||
        message.recipient_id.empty()) {
        return {false, 0, "invalid operator message"};
    }

    return bus_.send(AgentMessage{
        message.message_id,
        0,
        run_id_,
        workspace_id_,
        operator_id_,
        message.recipient_id,
        message.correlation_id,
        message.type,
        message.payload});
}

MessageBusResult OperatorControlChannel::broadcast(
    const std::vector<std::string>& recipients,
    std::string message_id,
    std::string correlation_id,
    AgentMessageType type,
    std::string payload) {
    if (!connected_ || recipients.empty() || message_id.empty() ||
        correlation_id.empty()) {
        return {false, 0, "invalid operator broadcast"};
    }

    MessageBusResult last{true, 0, "broadcast delivered"};
    for (const auto& recipient : recipients) {
        if (recipient.empty()) {
            return {false, last.sequence, "broadcast contains empty recipient"};
        }
        last = send(OperatorMessage{
            message_id,
            correlation_id,
            recipient,
            type,
            payload});
        if (!last.accepted) {
            return last;
        }
    }
    return last;
}

std::vector<AgentMessage> OperatorControlChannel::receive() {
    std::lock_guard lock(mutex_);
    std::vector<AgentMessage> result;
    result.reserve(pending_messages_.size());
    while (!pending_messages_.empty()) {
        result.push_back(std::move(pending_messages_.front()));
        pending_messages_.pop_front();
    }
    return result;
}

std::size_t OperatorControlChannel::pending() const noexcept {
    std::lock_guard lock(mutex_);
    return pending_messages_.size();
}

void OperatorControlChannel::receive_message(const AgentMessage& message) {
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

} // namespace jarvis::engineering
