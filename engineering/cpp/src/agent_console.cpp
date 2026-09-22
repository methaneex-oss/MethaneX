#include "jarvis/engineering/agent_console.hpp"

#include <utility>

namespace jarvis::engineering {

AgentConsole::AgentConsole(AgentMessageBus& bus, std::string operator_id)
    : bus_(bus), operator_id_(std::move(operator_id)) {
    bus_.register_agent(operator_id_, [this](const AgentMessage& message) {
        if (message.recipient_id != operator_id_) return;
        std::lock_guard lock(mutex_);
        inbox_.push_back({message.message_id, message.run_id, message.workspace_id,
                          message.sender_id, message.recipient_id,
                          message.correlation_id, message.type, message.payload});
    });
}

AgentConsole::~AgentConsole() {
    bus_.unregister_agent(operator_id_);
}

MessageBusResult AgentConsole::send(
    std::string run_id,
    std::string workspace_id,
    std::string recipient_id,
    AgentMessageType type,
    std::string payload,
    std::string correlation_id) {
    std::string message_id;
    {
        std::lock_guard lock(mutex_);
        message_id = operator_id_ + ":" + std::to_string(next_message_id_++);
    }
    return bus_.send({std::move(message_id), 0, std::move(run_id),
                      std::move(workspace_id), operator_id_, std::move(recipient_id),
                      std::move(correlation_id), type, std::move(payload)});
}

std::vector<AgentConsoleMessage> AgentConsole::drain(const std::string& run_id) {
    std::lock_guard lock(mutex_);
    if (run_id.empty()) {
        auto messages = std::move(inbox_);
        inbox_.clear();
        return messages;
    }

    std::vector<AgentConsoleMessage> selected;
    std::vector<AgentConsoleMessage> remaining;
    selected.reserve(inbox_.size());
    remaining.reserve(inbox_.size());
    for (auto& message : inbox_) {
        if (message.run_id == run_id) selected.push_back(std::move(message));
        else remaining.push_back(std::move(message));
    }
    inbox_ = std::move(remaining);
    return selected;
}

} // namespace jarvis::engineering
