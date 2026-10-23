#pragma once
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace jarvis::engineering {
enum class AgentMessageType : std::uint8_t { request, artifact, review, feedback, status, query, result, error };
struct AgentMessage { std::string message_id; std::uint64_t sequence{0}; std::string run_id; std::string workspace_id; std::string sender_id; std::string recipient_id; std::string correlation_id; AgentMessageType type{AgentMessageType::status}; std::string payload; };
struct MessageBusResult { bool accepted{false}; std::uint64_t sequence{0}; std::string reason; };
// Return false when the receiver cannot accept the message; the bus propagates
// backpressure instead of reporting delivery that silently lost work.
using AgentMessageHandler = std::function<bool(const AgentMessage&)>;
struct MessageBusConfig {
    std::size_t maximum_payload_bytes{64 * 1024};
    // Bounded idempotency window: accepted retries are acknowledged without
    // redelivery while their IDs remain in this recent-message history.
    std::size_t maximum_deduplication_entries{65536};
};
class AgentMessageBus {
public:
    explicit AgentMessageBus(MessageBusConfig config = {});
    MessageBusResult register_agent(std::string, AgentMessageHandler);
    MessageBusResult unregister_agent(const std::string&);
    MessageBusResult send(AgentMessage);
    std::size_t registered_agents() const noexcept;
private:
    struct Subscriber { AgentMessageHandler handler; };
    MessageBusConfig config_;
    mutable std::mutex mutex_;
    std::unordered_map<std::string, Subscriber> subscribers_;
    // Accepted IDs are retained in bounded FIFO order. In-flight IDs prevent
    // simultaneous retries from invoking a receiver twice.
    std::unordered_map<std::string, AgentMessage> accepted_messages_;
    std::deque<std::string> accepted_order_;
    std::unordered_set<std::string> in_flight_messages_;
    std::uint64_t next_sequence_{1};
    bool valid_message(const AgentMessage&) const noexcept;
    static std::string delivery_key(const AgentMessage&);
    static bool same_content(const AgentMessage&, const AgentMessage&) noexcept;
};
class AgentCommunicationEndpoint { public: AgentCommunicationEndpoint(AgentMessageBus&,std::string,std::string,std::string,std::size_t=256); ~AgentCommunicationEndpoint(); AgentCommunicationEndpoint(const AgentCommunicationEndpoint&)=delete; AgentCommunicationEndpoint& operator=(const AgentCommunicationEndpoint&)=delete; bool registered() const noexcept; const std::string& agent_id() const noexcept; const std::string& run_id() const noexcept; const std::string& workspace_id() const noexcept; MessageBusResult send(std::string,std::string,std::string,AgentMessageType,std::string); std::vector<AgentMessage> drain(); std::size_t pending() const noexcept; private: struct State{mutable std::mutex mutex;std::deque<AgentMessage> pending_messages;std::size_t maximum_pending_messages{256};bool accepting{true};}; static bool receive(const std::shared_ptr<State>&,const AgentMessage&,const std::string&,const std::string&); AgentMessageBus& bus_; std::string agent_id_,run_id_,workspace_id_; std::shared_ptr<State> state_; bool registered_{false}; };
} // namespace jarvis::engineering
