#include "jarvis/engineering/agent_console.hpp"

#include <algorithm>
#include <utility>

namespace jarvis::engineering {

bool InMemoryAgentConsole::send(AgentConsoleMessage message) {
    if (message.id.empty() || message.run_id.empty() ||
        message.sender.empty() || message.recipient.empty()) {
        return false;
    }

    std::lock_guard lock(mutex_);
    messages_.push_back(std::move(message));
    return true;
}

std::vector<AgentConsoleMessage> InMemoryAgentConsole::receive(
    const std::string& recipient,
    const std::string& run_id) {
    std::vector<AgentConsoleMessage> result;
    std::lock_guard lock(mutex_);

    auto it = messages_.begin();
    while (it != messages_.end()) {
        if (it->recipient == recipient && it->run_id == run_id) {
            result.push_back(std::move(*it));
            it = messages_.erase(it);
        } else {
            ++it;
        }
    }
    return result;
}

bool AgentConversation::send(AgentConsoleMessageKind kind, std::string body) {
    return console_.send(AgentConsoleMessage{
        .id = sender_ + ":" + agent_id_ + ":" + std::to_string(body.size()),
        .run_id = run_id_,
        .sender = sender_,
        .recipient = agent_id_,
        .kind = kind,
        .body = std::move(body),
    });
}

std::vector<AgentConsoleMessage> AgentConversation::receive() {
    return console_.receive(sender_, run_id_);
}

} // namespace jarvis::engineering
