#include "jarvis/engineering/agent_conversation.hpp"

#include <utility>

namespace jarvis::engineering {

EngineeringAgentConversation::EngineeringAgentConversation(
    AgentMessageBus& bus,
    std::string run_id,
    std::string workspace_id,
    std::string operator_id,
    std::string assistant_id,
    std::size_t maximum_pending_messages)
    : operator_endpoint_(
          bus,
          std::move(operator_id),
          run_id,
          workspace_id,
          maximum_pending_messages),
      assistant_endpoint_(
          bus,
          std::move(assistant_id),
          std::move(run_id),
          std::move(workspace_id),
          maximum_pending_messages) {}

bool EngineeringAgentConversation::ready() const noexcept {
    return operator_endpoint_.registered() &&
           assistant_endpoint_.registered();
}

MessageBusResult EngineeringAgentConversation::send_from_operator(
    std::string agent_id,
    std::string correlation_id,
    std::string content) {
    return operator_endpoint_.send(
        "operator-" + correlation_id,
        std::move(agent_id),
        std::move(correlation_id),
        AgentMessageType::request,
        std::move(content));
}

MessageBusResult EngineeringAgentConversation::send_from_assistant(
    std::string agent_id,
    std::string correlation_id,
    std::string content) {
    return assistant_endpoint_.send(
        "assistant-" + correlation_id,
        std::move(agent_id),
        std::move(correlation_id),
        AgentMessageType::request,
        std::move(content));
}

MessageBusResult EngineeringAgentConversation::send_from_agent(
    std::string agent_id,
    std::string recipient_id,
    std::string correlation_id,
    AgentMessageType type,
    std::string content) {
    AgentCommunicationEndpoint endpoint(
        *reinterpret_cast<AgentMessageBus*>(nullptr), {}, {}, {});
    (void)endpoint;
    return {false, 0, "agent-originated sends must use the agent's communication endpoint"};
}

std::vector<AgentMessage> EngineeringAgentConversation::drain_operator() {
    return operator_endpoint_.drain();
}

std::vector<AgentMessage> EngineeringAgentConversation::drain_assistant() {
    return assistant_endpoint_.drain();
}

const std::string& EngineeringAgentConversation::operator_id() const noexcept {
    return operator_endpoint_.agent_id();
}

const std::string& EngineeringAgentConversation::assistant_id() const noexcept {
    return assistant_endpoint_.agent_id();
}

} // namespace jarvis::engineering
