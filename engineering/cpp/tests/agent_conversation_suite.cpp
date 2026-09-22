#include "jarvis/engineering/agent_conversation.hpp"

#include <cassert>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    AgentConversationBridge human(bus, "conversation-1", "run-1", "workspace-1");
    assert(human.registered());

    AgentCommunicationEndpoint agent(bus, "builder", "run-1", "workspace-1");
    assert(agent.registered());

    const auto sent = human.send_to_agent("human-1", "builder", "Inspect the failing build.");
    assert(sent.accepted);

    const auto requests = agent.drain();
    assert(requests.size() == 1);
    assert(requests.front().sender_id == "human");
    assert(requests.front().recipient_id == "builder");
    assert(requests.front().payload == "Inspect the failing build.");
    assert(requests.front().correlation_id == "conversation-1");

    const auto replied = agent.send(
        "agent-1", "human", "human-1", AgentMessageType::result,
        "Build failure isolated to the test target.");
    assert(replied.accepted);

    const auto responses = human.receive_from_agents();
    assert(responses.size() == 1);
    assert(responses.front().role == ConversationRole::agent);
    assert(responses.front().sender_id == "builder");
    assert(responses.front().content == "Build failure isolated to the test target.");
    assert(human.pending() == 0);

    return 0;
}
