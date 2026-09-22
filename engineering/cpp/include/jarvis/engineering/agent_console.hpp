#pragma once

#include "message_bus.hpp"

#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace jarvis::engineering {

// Human-facing communication boundary. It deliberately carries opaque payloads;
// interpretation remains a capability of the selected agent, not this console.
struct AgentConsoleMessage {
    std::string message_id;
    std::string run_id;
    std::string workspace_id;
    std::string sender_id;
    std::string recipient_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::request};
    std::string payload;
};

class AgentConsole {
public:
    explicit AgentConsole(AgentMessageBus& bus, std::string operator_id = "operator");
    ~AgentConsole();

    AgentConsole(const AgentConsole&) = delete;
    AgentConsole& operator=(const AgentConsole&) = delete;

    MessageBusResult send(
        std::string run_id,
        std::string workspace_id,
        std::string recipient_id,
        AgentMessageType type,
        std::string payload,
        std::string correlation_id = {});

    std::vector<AgentConsoleMessage> drain(
        const std::string& run_id = {});

    const std::string& operator_id() const noexcept { return operator_id_; }

private:
    AgentMessageBus& bus_;
    std::string operator_id_;
    mutable std::mutex mutex_;
    std::vector<AgentConsoleMessage> inbox_;
    std::uint64_t next_message_id_{1};
};

} // namespace jarvis::engineering
