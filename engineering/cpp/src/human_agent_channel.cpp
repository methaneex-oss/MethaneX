#include "jarvis/engineering/human_agent_channel.hpp"

#include <utility>

namespace jarvis::engineering {

HumanAgentChannel::HumanAgentChannel(
    AgentMessageBus& bus,
    std::string human_id,
    std::string session_id,
    std::string workspace_id,
    std::size_t maximum_pending_messages)
    : endpoint_(
          bus,
          human_id,
          session_id,
          std::move(workspace_id),
          maximum_pending_messages),
      human_id_(std::move(human_id)),
      session_id_(std::move(session_id)) {}

bool HumanAgentChannel::connected() const noexcept {
    return endpoint_.registered();
}

const std::string& HumanAgentChannel::human_id() const noexcept {
    return human_id_;
}

const std::string& HumanAgentChannel::session_id() const noexcept {
    return session_id_;
}

MessageBusResult HumanAgentChannel::send_to_agent(
    std::string message_id,
    std::string correlation_id,
    std::string recipient_agent_id,
    std::string text) {
    return endpoint_.send(
        std::move(message_id),
        std::move(recipient_agent_id),
        std::move(correlation_id),
        AgentMessageType::request,
        std::move(text));
}

std::vector<AgentMessage> HumanAgentChannel::receive_from_agents() {
    return endpoint_.drain();
}

} // namespace jarvis::engineering
