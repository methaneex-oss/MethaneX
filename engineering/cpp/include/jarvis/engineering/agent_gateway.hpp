#pragma once

#include "agent_conversation.hpp"
#include "message_bus.hpp"

#include <cstddef>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::engineering {

struct AgentConversationMessage {
    std::string sender_id;
    std::string recipient_id;
    std::string message;
    bool from_agent{false};
};

struct AgentConversationSession {
    std::string session_id;
    std::string user_id;
    std::size_t maximum_history_messages{32};
    std::vector<AgentConversationMessage> history;
};

class EngineeringAgentGateway {
public:
    explicit EngineeringAgentGateway(
        AgentMessageBus* message_bus = nullptr,
        std::size_t maximum_history_messages = 32);

    bool register_agent(EngineeringAgent& agent);
    bool unregister_agent(const std::string& agent_id);

    bool open_session(
        std::string session_id,
        std::string user_id);

    AgentConversationResponse send(
        const std::string& session_id,
        const std::string& agent_id,
        std::string message,
        std::string context = {});

    bool close_session(const std::string& session_id);
    std::size_t active_sessions() const noexcept;

private:
    struct RegisteredAgent {
        EngineeringAgent* agent{nullptr};
        ConversationalEngineeringAgent* conversational{nullptr};
    };

    std::string build_context(
        const AgentConversationSession& session,
        const std::string& extra_context) const;

    AgentMessageBus* message_bus_{nullptr};
    std::size_t maximum_history_messages_{32};
    mutable std::mutex mutex_;
    std::unordered_map<std::string, RegisteredAgent> agents_;
    std::unordered_map<std::string, AgentConversationSession> sessions_;
};

} // namespace jarvis::engineering
