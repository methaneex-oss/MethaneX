#include "jarvis/engineering/direct_agent_session.hpp"

#include <utility>

namespace jarvis::engineering {

DirectAgentSession::DirectAgentSession(
    EngineeringAgent& agent,
    const EngineeringAuthorizer& authorizer,
    EngineeringExecutionBoundary& boundary,
    AgentMessageBus& bus,
    std::string human_id,
    std::string session_id,
    std::string workspace_id)
    : agent_(agent),
      authorizer_(authorizer),
      boundary_(boundary),
      workspace_id_(std::move(workspace_id)),
      human_(
          bus,
          std::move(human_id),
          std::move(session_id),
          workspace_id_) {}

bool DirectAgentSession::connected() const noexcept {
    return human_.connected();
}

const AgentDescriptor& DirectAgentSession::agent_descriptor() const noexcept {
    return agent_.descriptor();
}

AgentCharter DirectAgentSession::charter() const {
    return default_engineering_charter(agent_.descriptor());
}

AgentResult DirectAgentSession::ask(
    std::string task_id,
    std::string message) {
    if (!connected() || task_id.empty() || message.empty()) {
        return {
            false,
            agent_.descriptor().id,
            std::move(task_id),
            "invalid direct agent session request",
            {},
            {}};
    }

    const auto request = human_.send_to_agent(
        "human-" + task_id,
        task_id,
        agent_.descriptor().id,
        message);
    if (!request.accepted) {
        return {
            false,
            agent_.descriptor().id,
            std::move(task_id),
            request.reason,
            {},
            {}};
    }

    AgentCommunicationEndpoint agent_endpoint(
        *reinterpret_cast<AgentMessageBus*>(nullptr),
        "",
        "",
        "");
    (void)agent_endpoint;

    EngineeringTask task{
        std::move(task_id),
        std::move(message),
        {"engineering"},
        {},
        {},
        {},
        AgentRisk::low,
        0.0};
    task.workspace_id = workspace_id_;
    task.manage_workspace = false;

    return EngineeringCoordinator{}.dispatch(
        task, agent_, authorizer_, boundary_);
}

std::vector<AgentMessage> DirectAgentSession::drain_messages() {
    return human_.receive_from_agents();
}

} // namespace jarvis::engineering
