#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::engineering {

struct AgentChatRequest {
    std::string message_id;
    std::string run_id;
    std::string workspace_id;
    std::string agent_id;
    std::string correlation_id;
    std::string text;
};

struct AgentChatResponse {
    bool accepted{false};
    std::string message_id;
    std::string sender_id;
    std::string recipient_id;
    std::string correlation_id;
    std::string text;
    std::uint64_t sequence{0};
    std::string reason;
};

struct AgentChatConfig {
    std::string participant_id{"human"};
    std::size_t maximum_message_bytes{64 * 1024};
    std::size_t maximum_pending_messages{256};
};

class EngineeringAgentChat {
public:
    EngineeringAgentChat(
        AgentMessageBus& bus,
        std::string run_id,
        std::string workspace_id,
        AgentChatConfig config = {});

    bool connected() const noexcept;
    const std::string& participant_id() const noexcept;

    AgentChatResponse send(const AgentChatRequest& request);
    std::vector<AgentChatResponse> receive();

private:
    AgentMessageBus& bus_;
    std::string run_id_;
    std::string workspace_id_;
    AgentChatConfig config_;
    AgentCommunicationEndpoint endpoint_;
};

} // namespace jarvis::engineering
