#pragma once

#include "message_bus.hpp"

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace jarvis::engineering {

// Human-facing bridge to the same agent message bus used for agent-to-agent
// communication. It deliberately carries opaque payloads: interpretation
// remains the responsibility of the receiving agent/cognitive layer.
struct AgentConsoleMessage {
    std::string message_id;
    std::uint64_t sequence{0};
    std::string run_id;
    std::string workspace_id;
    std::string sender_id;
    std::string recipient_id;
    AgentMessageType type{AgentMessageType::query};
    std::string payload;
};

class AgentConsole {
public:
    AgentConsole(AgentMessageBus& bus,
                 std::string console_id = "human",
                 std::size_t maximum_pending_messages = 256);
    ~AgentConsole();

    AgentConsole(const AgentConsole&) = delete;
    AgentConsole& operator=(const AgentConsole&) = delete;

    bool registered() const noexcept;
    const std::string& console_id() const noexcept;

    MessageBusResult send(const std::string& recipient_id,
                          const std::string& run_id,
                          const std::string& workspace_id,
                          AgentMessageType type,
                          const std::string& payload,
                          const std::string& correlation_id = {});

    std::vector<AgentConsoleMessage> receive();
    std::size_t pending() const noexcept;

private:
    static void receive_message(const std::shared_ptr<struct State>& state,
                                const AgentMessage& message,
                                const std::string& console_id);

    AgentMessageBus& bus_;
    std::string console_id_;
    struct State {
        mutable std::mutex mutex;
        std::vector<AgentConsoleMessage> pending;
        std::size_t maximum_pending_messages{256};
        bool accepting{true};
    };
    std::shared_ptr<State> state_;
    bool registered_{false};
};

} // namespace jarvis::engineering
