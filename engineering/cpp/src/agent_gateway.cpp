#include "jarvis/engineering/agent_gateway.hpp"

#include <algorithm>
#include <limits>
#include <utility>

namespace jarvis::engineering {

EngineeringAgentGateway::EngineeringAgentGateway(
    AgentMessageBus* message_bus,
    std::size_t maximum_history_messages)
    : message_bus_(message_bus),
      maximum_history_messages_(maximum_history_messages == 0 ? 1 : maximum_history_messages) {}

bool EngineeringAgentGateway::register_agent(EngineeringAgent& agent) {
    const auto descriptor = agent.descriptor();
    if (!valid_descriptor(descriptor)) return false;

    auto* conversational = dynamic_cast<ConversationalEngineeringAgent*>(&agent);
    if (conversational == nullptr) return false;

    std::lock_guard lock(mutex_);
    return agents_.emplace(
        descriptor.id, RegisteredAgent{&agent, conversational}).second;
}

bool EngineeringAgentGateway::unregister_agent(const std::string& agent_id) {
    std::lock_guard lock(mutex_);
    return agents_.erase(agent_id) != 0;
}

bool EngineeringAgentGateway::open_session(
    std::string session_id,
    std::string user_id) {
    if (session_id.empty() || user_id.empty()) return false;

    std::lock_guard lock(mutex_);
    if (sessions_.contains(session_id)) return false;

    AgentConversationSession session;
    session.session_id = std::move(session_id);
    session.user_id = std::move(user_id);
    session.maximum_history_messages = maximum_history_messages_;
    return sessions_.emplace(session.session_id, std::move(session)).second;
}

std::string EngineeringAgentGateway::build_context(
    const AgentConversationSession& session,
    const std::string& extra_context) const {
    std::string context;
    context.reserve(extra_context.size() + session.history.size() * 64);
    if (!extra_context.empty()) context += extra_context;

    for (const auto& item : session.history) {
        if (!context.empty()) context += "\n";
        context += "conversation." + std::string(item.from_agent ? "agent" : "user") +
                   "=" + item.sender_id + " -> " + item.recipient_id + ": " + item.message;
    }
    return context;
}

AgentConversationResponse EngineeringAgentGateway::send(
    const std::string& session_id,
    const std::string& agent_id,
    std::string message,
    std::string context) {
    if (message.empty()) {
        return {false, session_id, agent_id, {}, {}, "conversation message is empty"};
    }

    RegisteredAgent registered;
    AgentConversationSession session;
    {
        std::lock_guard lock(mutex_);
        const auto session_it = sessions_.find(session_id);
        if (session_it == sessions_.end()) {
            return {false, session_id, agent_id, {}, {}, "conversation session not found"};
        }
        const auto agent_it = agents_.find(agent_id);
        if (agent_it == agents_.end()) {
            return {false, session_id, agent_id, {}, {}, "conversation agent not found"};
        }

        registered = agent_it->second;
        session = session_it->second;
    }

    const std::string sender_id = session.user_id;
    const std::string full_context = build_context(session, context);

    if (message_bus_ != nullptr) {
        message_bus_->send(AgentMessage{
            "conversation-" + session_id + "-" + agent_id + "-query",
            0,
            session_id,
            {},
            sender_id,
            agent_id,
            session_id,
            AgentMessageType::query,
            message});
    }

    AgentConversationRequest request{
        session_id,
        sender_id,
        std::move(message),
        full_context,
        64 * 1024};

    auto response = registered.conversational->converse(request);
    if (response.session_id.empty()) response.session_id = session_id;
    if (response.agent_id.empty()) response.agent_id = agent_id;

    {
        std::lock_guard lock(mutex_);
        const auto session_it = sessions_.find(session_id);
        if (session_it != sessions_.end()) {
            session_it->second.history.push_back(
                {sender_id, agent_id, request.message, false});
            if (response.accepted) {
                session_it->second.history.push_back(
                    {agent_id, sender_id, response.response, true});
            }
            while (session_it->second.history.size() >
                   session_it->second.maximum_history_messages) {
                session_it->second.history.erase(session_it->second.history.begin());
            }
        }
    }

    if (message_bus_ != nullptr) {
        message_bus_->send(AgentMessage{
            "conversation-" + session_id + "-" + agent_id + "-response",
            0,
            session_id,
            {},
            agent_id,
            sender_id,
            session_id,
            response.accepted ? AgentMessageType::result : AgentMessageType::error,
            response.response.empty() ? response.reason : response.response});
    }

    return response;
}

bool EngineeringAgentGateway::close_session(const std::string& session_id) {
    std::lock_guard lock(mutex_);
    return sessions_.erase(session_id) != 0;
}

std::size_t EngineeringAgentGateway::active_sessions() const noexcept {
    std::lock_guard lock(mutex_);
    return sessions_.size();
}

} // namespace jarvis::engineering
