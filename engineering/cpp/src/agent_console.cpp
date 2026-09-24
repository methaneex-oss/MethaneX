#include "jarvis/engineering/agent_console.hpp"

#include <utility>

namespace jarvis::engineering {

AgentConsole::AgentConsole(AgentMessageBus& bus,
                           std::string console_id,
                           std::size_t maximum_pending_messages)
    : bus_(bus),
      console_id_(std::move(console_id)),
      state_(std::make_shared<State>()) {
    state_->maximum_pending_messages = maximum_pending_messages;
    if (console_id_.empty() || maximum_pending_messages == 0) {
        state_->accepting = false;
        return;
    }

    const auto state = state_;
    const auto id = console_id_;
    const auto result = bus_.register_agent(console_id_,
        [state, id](const AgentMessage& message) {
            AgentConsole::receive_message(state, message, id);
        });
    registered_ = result.accepted;
    if (!registered_) state_->accepting = false;
}

AgentConsole::~AgentConsole() {
    {
        std::lock_guard lock(state_->mutex);
        state_->accepting = false;
    }
    if (registered_) bus_.unregister_agent(console_id_);
}

bool AgentConsole::registered() const noexcept { return registered_; }

const std::string& AgentConsole::console_id() const noexcept { return console_id_; }

MessageBusResult AgentConsole::send(const std::string& recipient_id,
                                    const std::string& run_id,
                                    const std::string& workspace_id,
                                    AgentMessageType type,
                                    const std::string& payload,
                                    const std::string& correlation_id) {
    if (!registered_) return {false, 0, "console is not registered"};
    if (run_id.empty() || recipient_id.empty() || correlation_id.empty()) {
        return {false, 0, "run, recipient and correlation id are required"};
    }
    return bus_.send(AgentMessage{
        "human-" + std::to_string(std::hash<std::string>{}(run_id + correlation_id + payload)),
        0,
        run_id,
        workspace_id,
        console_id_,
        recipient_id,
        correlation_id,
        type,
        payload});
}

void AgentConsole::receive_message(const std::shared_ptr<State>& state,
                                   const AgentMessage& message,
                                   const std::string& console_id) {
    if (message.recipient_id != console_id) return;
    std::lock_guard lock(state->mutex);
    if (!state->accepting) return;
    if (state->pending.size() >= state->maximum_pending_messages) state->pending.pop_front();
    state->pending.push_back(AgentConsoleMessage{
        message.message_id,
        message.sequence,
        message.run_id,
        message.workspace_id,
        message.sender_id,
        message.recipient_id,
        message.type,
        message.payload});
}

std::vector<AgentConsoleMessage> AgentConsole::receive() {
    std::lock_guard lock(state_->mutex);
    std::vector<AgentConsoleMessage> result;
    result.reserve(state_->pending.size());
    while (!state_->pending.empty()) {
        result.push_back(std::move(state_->pending.front()));
        state_->pending.pop_front();
    }
    return result;
}

std::size_t AgentConsole::pending() const noexcept {
    std::lock_guard lock(state_->mutex);
    return state_->pending.size();
}

} // namespace jarvis::engineering
