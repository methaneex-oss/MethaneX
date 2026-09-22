#include "jarvis/engineering/agent_conversation.hpp"

#include <cassert>
#include <string>
#include <utility>

using namespace jarvis::engineering;

namespace {

class ConversationAgent {
public:
    ConversationAgent(AgentMessageBus& bus, std::string id)
        : endpoint(bus, std::move(id), "run-1", "workspace-1") {}

    void reply() {
        const auto messages = endpoint.drain();
        assert(messages.size() == 2);
        assert(messages[0].type == AgentMessageType::request);
        assert(messages[0].sender_id == "operator");
        assert(messages[1].type == AgentMessageType::request);
        assert(messages[1].sender_id == "assistant");

        const auto sent = endpoint.send(
            "agent-reply-1",
            "operator",
            messages[0].correlation_id,
            AgentMessageType::result,
            "I inspected the requested change.");
        assert(sent.accepted);
    }

private:
    AgentCommunicationEndpoint endpoint;
};

} // namespace

int main() {
    AgentMessageBus bus;
    EngineeringAgentConversation conversation(
        bus, "run-1", "workspace-1", "operator", "assistant");

    assert(conversation.ready());
    ConversationAgent agent(bus, "architect");

    assert(conversation.send_from_operator(
        "architect", "conversation-1",
        "Inspect the architecture and report blockers.").accepted);
    assert(conversation.send_from_assistant(
        "architect", "conversation-2",
        "Also evaluate the next implementation step.").accepted);

    agent.reply();

    const auto operator_messages = conversation.drain_operator();
    assert(operator_messages.size() == 1);
    assert(operator_messages[0].sender_id == "architect");
    assert(operator_messages[0].recipient_id == "operator");
    assert(operator_messages[0].type == AgentMessageType::result);
    assert(operator_messages[0].payload == "I inspected the requested change.");
    assert(operator_messages[0].correlation_id == "conversation-1");

    assert(conversation.drain_assistant().empty());
    return 0;
}
