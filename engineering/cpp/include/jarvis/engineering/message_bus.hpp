#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

namespace jarvis::engineering {

enum class AgentMessageType : std::uint8_t {
    request,
    artifact,
    review,
    feedback,
    status,
    query,
    result,
    error
};

struct AgentMessage {
    std::string message_id;
    std::uint64_t sequence{0};
    std::string run_id;
    std::string workspace_id;
    std::string sender_id;
    std::string recipient_id;
    std::string correlation_id;
    AgentMessageType type{AgentMessageType::status};
    std::string payload;
};

struct MessageBusResult {
    bool accepted{false};
    std::uint64_t sequence{0};
    std::string reason;
};

using AgentMessageHandler = std::function<void(const AgentMessage&)>;

struct MessageBusConfig {
    std::size_t maximum_payload_bytes{64 * 1024};
};

class AgentMessageBus {
public:
    explicit AgentMessageBus(MessageBusConfig config = {});

    MessageBusResult register_agent(
        std::string agent_id,
        AgentMessageHandler handler);

    MessageBusResult unregister_agent(const std::string& agent_id);

    MessageBusResult send(AgentMessage message);

    std::size_t registered_agents() const noexcept;

private:
    struct Subscriber {
        AgentMessageHandler handler;
    };

    MessageBusConfig config_;
    mutable std::mutex mutex_;
    std::unordered_map<std::string, Subscriber> subscribers_;
    std::uint64_t next_sequence_{1};

    bool valid_message(const AgentMessage& message) const noexcept;
};

} // namespace jarvis::engineering
