#include "jarvis/engineering/agent_gateway.hpp"

#include <cassert>
#include <string>
#include <utility>
#include <vector>

using namespace jarvis::engineering;

namespace {

class ChatAgent final : public EngineeringAgent, public ConversationalEngineeringAgent {
public:
    explicit ChatAgent(std::string id) : id_(std::move(id)) {}

    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            id_, id_, "test", "conversation fixture",
            {"engineering.chat"}, {"conversation.send"}, {}, {},
            0.0, 1.0, AgentRisk::low, AgentAvailability::available, true};
    }

    AgentResult execute(const EngineeringTask& task) override {
        return {true, id_, task.id, "ok", {}, {}};
    }

    AgentConversationResponse converse(
        const AgentConversationRequest& request) override {
        seen_context_ = request.context;
        return {true, request.session_id, id_,
                "ack:" + request.message,
                {{"conversation", "response"}},
                "ok"};
    }

    const std::string& seen_context() const noexcept { return seen_context_; }

private:
    std::string id_;
    std::string seen_context_;
};

class BusObserver final {
public:
    explicit BusObserver(std::vector<AgentMessage>& messages) : messages_(messages) {}

    void receive(const AgentMessage& message) { messages_.push_back(message); }

private:
    std::vector<AgentMessage>& messages_;
};

} // namespace

int main() {
    AgentMessageBus bus;
    std::vector<AgentMessage> messages;
    const auto registered = bus.register_agent(
        "user.observer",
        [&](const AgentMessage& message) { messages.push_back(message); });
    assert(registered.accepted);

    ChatAgent architect("architect");
    ChatAgent reviewer("reviewer");

    EngineeringAgentGateway gateway(&bus, 4);
    assert(gateway.register_agent(architect));
    assert(gateway.register_agent(reviewer));
    assert(!gateway.register_agent(architect));

    assert(gateway.open_session("session-1", "user"));
    assert(!gateway.open_session("session-1", "user"));

    const auto first = gateway.send(
        "session-1", "architect", "Inspect the current architecture.");
    assert(first.accepted);
    assert(first.response == "ack:Inspect the current architecture.");

    const auto second = gateway.send(
        "session-1", "architect", "Now explain the main risk.",
        "Focus on concurrency and workspace isolation.");
    assert(second.accepted);
    assert(second.response == "ack:Now explain the main risk.");
    assert(architect.seen_context().find("Inspect the current architecture.") != std::string::npos);
    assert(architect.seen_context().find("Focus on concurrency and workspace isolation.") != std::string::npos);

    assert(messages.size() == 2);
    assert(messages[0].type == AgentMessageType::query);
    assert(messages[0].recipient_id == "architect");
    assert(messages[1].type == AgentMessageType::query ||
           messages[1].type == AgentMessageType::result);

    const auto missing = gateway.send("session-1", "missing", "hello");
    assert(!missing.accepted);

    assert(gateway.close_session("session-1"));
    assert(gateway.active_sessions() == 0);
    assert(!gateway.close_session("session-1"));

    return 0;
}
