#include "jarvis/engineering/message_bus.hpp"

#include <utility>

namespace jarvis::engineering {

AgentMessageBus::AgentMessageBus(MessageBusConfig config) : config_(config) {}

bool AgentMessageBus::valid_message(const AgentMessage& message) const noexcept {
    return !message.run_id.empty() && !message.sender_id.empty() &&
           !message.recipient_id.empty() && !message.message_id.empty() &&
           !message.correlation_id.empty() &&
           message.payload.size() <= config_.maximum_payload_bytes;
}

MessageBusResult AgentMessageBus::register_agent(std::string agent_id, AgentMessageHandler handler) {
    if (agent_id.empty() || !handler) return {false, 0, "invalid agent registration"};
    std::lock_guard lock(mutex_);
    if (subscribers_.contains(agent_id)) return {false, 0, "agent already registered"};
    subscribers_.emplace(std::move(agent_id), Subscriber{std::move(handler)});
    return {true, 0, "agent registered"};
}

MessageBusResult AgentMessageBus::unregister_agent(const std::string& agent_id) {
    if (agent_id.empty()) return {false, 0, "invalid agent id"};
    std::lock_guard lock(mutex_);
    if (subscribers_.erase(agent_id) == 0) return {false, 0, "agent not registered"};
    return {true, 0, "agent unregistered"};
}

MessageBusResult AgentMessageBus::send(AgentMessage message) {
    AgentMessageHandler handler;
    {
        std::lock_guard lock(mutex_);
        if (!valid_message(message)) return {false, 0, "invalid message"};
        const auto it = subscribers_.find(message.recipient_id);
        if (it == subscribers_.end()) return {false, 0, "recipient not registered"};
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
    AgentMessageBus& bus, std::string agent_id, std::string run_id,
    std::string workspace_id, std::size_t maximum_pending_messages)
    : bus_(bus), agent_id_(std::move(agent_id)), run_id_(std::move(run_id)),
      workspace_id_(std::move(workspace_id)), state_(std::make_shared<State>()) {
    state_->maximum_pending_messages = maximum_pending_messages;
    // An empty run id is a deliberate receive-only wildcard used by the
    // operator endpoint. Normal agent endpoints must provide a run id.
    if (agent_id_.empty() || maximum_pending_messages == 0) {
        state_->accepting = false;
        return;
    }

    const auto state = state_;
    const auto run_id_copy = run_id_;
    const auto workspace_id_copy = workspace_id_;
    const auto result = bus_.register_agent(
        agent_id_, [state, run_id_copy, workspace_id_copy](const AgentMessage& message) {
            AgentCommunicationEndpoint::receive(
                state, message, run_id_copy, workspace_id_copy);
        });
    registered_ = result.accepted;
    if (!registered_) state_->accepting = false;
}

AgentCommunicationEndpoint::~AgentCommunicationEndpoint() {
    {
        std::lock_guard lock(state_->mutex);
        state_->accepting = false;
    }
    if (registered_) bus_.unregister_agent(agent_id_);
}

bool AgentCommunicationEndpoint::registered() const noexcept { return registered_; }
const std::string& AgentCommunicationEndpoint::agent_id() const noexcept { return agent_id_; }
const std::string& AgentCommunicationEndpoint::run_id() const noexcept { return run_id_; }
const std::string& AgentCommunicationEndpoint::workspace_id() const noexcept { return workspace_id_; }

MessageBusResult AgentCommunicationEndpoint::send(
    std::string message_id, std::string recipient_id, std::string correlation_id,
    AgentMessageType type, std::string payload) {
    if (!registered_ || run_id_.empty()) {
        return {false, 0, "communication endpoint is receive-only"};
    }
    return bus_.send(AgentMessage{std::move(message_id), 0, run_id_, workspace_id_,
                                  agent_id_, std::move(recipient_id),
                                  std::move(correlation_id), type, std::move(payload)});
}

void AgentCommunicationEndpoint::receive(
    const std::shared_ptr<State>& state, const AgentMessage& message,
    const std::string& run_id, const std::string& workspace_id) {
    if ((!run_id.empty() && message.run_id != run_id) ||
        (!workspace_id.empty() && message.workspace_id != workspace_id)) return;
    std::lock_guard lock(state->mutex);
    if (!state->accepting) return;
    if (state->pending_messages.size() >= state->maximum_pending_messages) {
        state->pending_messages.pop_front();
    }
    state->pending_messages.push_back(message);
}

std::vector<AgentMessage> AgentCommunicationEndpoint::drain() {
    std::lock_guard lock(state_->mutex);
    std::vector<AgentMessage> messages;
    messages.reserve(state_->pending_messages.size());
    while (!state_->pending_messages.empty()) {
        messages.push_back(std::move(state_->pending_messages.front()));
        state_->pending_messages.pop_front();
    }
    return messages;
}

std::size_t AgentCommunicationEndpoint::pending() const noexcept {
    std::lock_guard lock(state_->mutex);
    return state_->pending_messages.size();
}

} // namespace jarvis::engineering
