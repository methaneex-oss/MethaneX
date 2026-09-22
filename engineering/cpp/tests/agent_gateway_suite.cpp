#include "jarvis/engineering/agent_gateway.hpp"

#include <cassert>
#include <string>
#include <utility>

using namespace jarvis::engineering;

namespace {

class ChatAgent final : public EngineeringAgent, public ConversationalEngineeringAgent {
public:
    explicit ChatAgent(std::string id) : id_(std::move(id)) {}

    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            id_, id_, "test", "chat fixture",
            {"engineering.chat"}, {"conversation.send"}, {}, {},
            0.0, 1.0, AgentRisk::low, AgentAvailability::available, true};
    }

    AgentResult execute(const EngineeringTask& task) override {
        return {true, id_, task.id, "ok", {}, {}};
    }

    AgentConversationResponse converse(
        const AgentConversationRequest& request) override {
        last_context_ = request.context;
        return {true, request.session_id, id_, "reply:" + request.message,
                {{"conversation.response", "true"}}, "ok"};
    }

    const std::string& last_context() const noexcept { return last_context_; }

private:
    std::string id_;
    std::string last_context_;
};

} // namespace

int main() {
    AgentMessageBus bus;
    std::size_t queries = 0;
    const auto observer = bus.register_agent(
        "user",
        [&](const AgentMessage& message) {
            if (message.type == AgentMessageType::query) ++queries;
        });
    assert(observer.accepted);

    ChatAgent architect("architect");
    EngineeringAgentGateway gateway(&bus, 8);
    assert(gateway.register_agent(architect));
    assert(gateway.open_session("session-1", "user"));

    const auto first = gateway.send(
        "session-1", "architect", "Inspect the architecture.");
    assert(first.accepted);
    assert(first.response == "reply:Inspect the architecture.");

    const auto second = gateway.send(
        "session-1", "architect", "Now explain the main risk.",
        "Focus on concurrency.");
    assert(second.accepted);
    assert(architect.last_context().find("Inspect the architecture.") != std::string::npos);
    assert(architect.last_context().find("Focus on concurrency.") != std::string::npos);
    assert(queries == 2);

    assert(gateway.close_session("session-1"));
    assert(gateway.active_sessions() == 0);
    return 0;
}
