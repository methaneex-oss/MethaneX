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
      bus_(bus),
      workspace_id_(std::move(workspace_id)),
      agent_endpoint_id_(agent.descriptor().id + "@" + session_id),
      agent_endpoint_(
          bus_,
          agent_endpoint_id_,
          session_id,
          workspace_id_),
      human_(
          bus_,
          std::move(human_id),
          std::move(session_id),
          workspace_id_) {}#include "jarvis/engineering/direct_agent_session.hpp"

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
      bus_(bus),
      workspace_id_(std::move(workspace_id)),
      agent_endpoint_id_(agent.descriptor().id + "@" + session_id),
      agent_endpoint_(
          bus_,
          agent_endpoint_id_,
          session_id,
          workspace_id_),
      human_(
          bus_,
          std::move(human_id),
          std::move(session_id),
          workspace_id_) {}
