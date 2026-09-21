#include "jarvis/engineering/message_bus.hpp"

#include <utility>

namespace jarvis::engineering {

AgentMessageBus::AgentMessageBus(MessageBusConfig config)
    : config_(config) {}

bool AgentMessageBus::valid_message(const AgentMessage& message) const noexcept {
    return !message.run_id.empty() &&
           !message.sender_id.empty() &&
           !message.recipient_id.empty() &&
           !message.message_id.empty() &&
           !message.correlation_id.empty() &&
           message.payload.size() <= config_.maximum_payload_bytes;
}

MessageBusResult AgentMessageBus::register_agent(
    std::string agent_id,
    AgentMessageHandler handler) {
    if (agent_id.empty() || !handler) {
        return {false, 0, "invalid agent registration"};
    }

    std::lock_guard lock(mutex_);
    if (subscribers_.contains(agent_id)) {
        return {false, 0, "agent already registered"};
    }

    subscribers_.emplace(
        std::move(agent_id),
        Subscriber{std::move(handler)});
    return {true, 0, "agent registered"};
}

MessageBusResult AgentMessageBus::unregister_agent(const std::string& agent_id) {
    if (agent_id.empty()) {
        return {false, 0, "invalid agent id"};
    }

    std::lock_guard lock(mutex_);
    if (subscribers_.erase(agent_id) == 0) {
        return {false, 0, "agent not registered"};
    }
    return {true, 0, "agent unregistered"};
}

MessageBusResult AgentMessageBus::send(AgentMessage message) {
    AgentMessageHandler handler;
    {
        std::lock_guard lock(mutex_);
        if (!valid_message(message)) {
            return {false, 0, "invalid message"};
        }
        const auto it = subscribers_.find(message.recipient_id);
        if (it == subscribers_.end()) {
            return {false, 0, "recipient not registered"};
        }

        message.sequence = next_sequence_++;
        handler = it->second.handler;
    }

    handler(message);
    return {true, message.sequence, "message delivered"};
}

std::size_t AgentMessageBus::registered_agents() const noexcept {
    std::lock_guard lock(mutex_);
    return subscribers_.size();
}


AgentCommunicationEndpoint::AgentCommunicationEndpoint(
    AgentMessageBus& bus,
    std::string agent_id,
    std::string run_id,
    std::string workspace_id,
    std::size_t maximum_pending_messages)
    : bus_(bus),
      agent_id_(std::move(agent_id)),
      run_id_(std::move(run_id)),
      workspace_id_(std::move(workspace_id)),
      maximum_pending_messages_(maximum_pending_messages) {
    if (agent_id_.empty() || run_id_.empty() ||
        maximum_pending_messages_ == 0) {
        return;
    }

    const auto result = bus_.register_agent(
        agent_id_,
        [this](const AgentMessage& message) { receive(message); });
    registered_ = result.accepted;
}

AgentCommunicationEndpoint::~AgentCommunicationEndpoint() {
    if (registered_) {
        bus_.unregister_agent(agent_id_);
    }
}

bool AgentCommunicationEndpoint::registered() const noexcept {
    return registered_;
}

const std::string& AgentCommunicationEndpoint::agent_id() const noexcept {
    return agent_id_;
}

MessageBusResult AgentCommunicationEndpoint::send(
    std::string message_id,
    std::string recipient_id,
    std::string correlation_id,
    AgentMessageType type,
    std::string payload) {
    if (!registered_) {
        return {false, 0, "communication endpoint is not registered"};
    }

    AgentMessage message{
        std::move(message_id),
        0,
        run_id_,
        workspace_id_,
        agent_id_,
        std::move(recipient_id),
        std::move(correlation_id),
        type,
        std::move(payload)
    };
    return bus_.send(std::move(message));
}

void AgentCommunicationEndpoint::receive(const AgentMessage& message) {
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

std::vector<AgentMessage> AgentCommunicationEndpoint::drain() {
    std::lock_guard lock(mutex_);
    std::vector<AgentMessage> messages;
    messages.reserve(pending_messages_.size());
    while (!pending_messages_.empty()) {
        messages.push_back(std::move(pending_messages_.front()));
        pending_messages_.pop_front();
    }
    return messages;
}

std::size_t AgentCommunicationEndpoint::pending() const noexcept {
    std::lock_guard lock(mutex_);
    return pending_messages_.size();
}

} // namespace jarvis::engineering
