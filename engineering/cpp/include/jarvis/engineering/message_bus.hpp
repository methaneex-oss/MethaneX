#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

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
    MessageBusResult register_agent(std::string agent_id, AgentMessageHandler handler);
    MessageBusResult unregister_agent(const std::string& agent_id);
    MessageBusResult send(AgentMessage message);
    std::size_t registered_agents() const noexcept;
private:
    struct Subscriber { AgentMessageHandler handler; };
    MessageBusConfig config_;
    mutable std::mutex mutex_;
    std::unordered_map<std::string, Subscriber> subscribers_;
    std::uint64_t next_sequence_{1};
    bool valid_message(const AgentMessage& message) const noexcept;
};

class AgentCommunicationEndpoint {
public:
    AgentCommunicationEndpoint(AgentMessageBus& bus, std::string agent_id,
                               std::string run_id, std::string workspace_id,
                               std::size_t maximum_pending_messages = 256);
    ~AgentCommunicationEndpoint();
    AgentCommunicationEndpoint(const AgentCommunicationEndpoint&) = delete;
    AgentCommunicationEndpoint& operator=(const AgentCommunicationEndpoint&) = delete;
    bool registered() const noexcept;
    const std::string& agent_id() const noexcept;
    const std::string& run_id() const noexcept;
    const std::string& workspace_id() const noexcept;
    MessageBusResult send(std::string message_id, std::string recipient_id,
                          std::string correlation_id, AgentMessageType type,
                          std::string payload);
    std::vector<AgentMessage> drain();
    std::size_t pending() const noexcept;
private:
    struct State {
        mutable std::mutex mutex;
        std::deque<AgentMessage> pending_messages;
        std::size_t maximum_pending_messages{256};
        bool accepting{true};
    };

    static void receive(const std::shared_ptr<State>& state,
                        const AgentMessage& message,
                        const std::string& run_id,
                        const std::string& workspace_id);

    AgentMessageBus& bus_;
    std::string agent_id_;
    std::string run_id_;
    std::string workspace_id_;
    std::shared_ptr<State> state_;
    bool registered_{false};
};

} // namespace jarvis::engineering
