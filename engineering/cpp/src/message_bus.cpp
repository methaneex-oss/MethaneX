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

} // namespace jarvis::engineering
