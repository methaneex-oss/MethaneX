#pragma once

#include "agent_charter.hpp"
#include "execution.hpp"
#include "human_agent_channel.hpp"

namespace jarvis::engineering {

class DirectAgentSession {
public:
    DirectAgentSession(
        EngineeringAgent& agent,
        const EngineeringAuthorizer& authorizer,
        EngineeringExecutionBoundary& boundary,
        AgentMessageBus& bus,
        std::string human_id,
        std::string session_id,
        std::string workspace_id = {});

    bool connected() const noexcept;
    const AgentDescriptor& agent_descriptor() const noexcept;
    AgentCharter charter() const;

    AgentResult ask(
        std::string task_id,
        std::string message);

    std::vector<AgentMessage> drain_messages();

private:
    EngineeringAgent& agent_;
    const EngineeringAuthorizer& authorizer_;
    EngineeringExecutionBoundary& boundary_;
    std::string workspace_id_;
    HumanAgentChannel human_;
};

} // namespace jarvis::engineering
