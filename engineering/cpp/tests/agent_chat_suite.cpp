#include "jarvis/engineering/agent_chat.hpp"

#include <cassert>
#include <string>
#include <vector>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;

    EngineeringAgentChat human(
        bus,
        "run-1",
        "workspace-1",
        AgentChatConfig{"human", 4096, 8});

    assert(human.connected());

    std::vector<AgentMessage> received;
    const auto registered = bus.register_agent(
        "architect",
        [&](const AgentMessage& message) { received.push_back(message); });
    assert(registered.accepted);

    const auto sent = human.send({
        "human-1",
        "run-1",
        "workspace-1",
        "architect",
        "conversation-1",
        "Explain the current architecture and identify the next engineering task."});
    assert(sent.accepted);
    assert(received.size() == 1);
    assert(received.front().sender_id == "human");
    assert(received.front().recipient_id == "architect");
    assert(received.front().type == AgentMessageType::query);
    assert(received.front().payload.find("current architecture") != std::string::npos);

    const auto wrong_scope = human.send({
        "human-2",
        "other-run",
        "workspace-1",
        "architect",
        "conversation-1",
        "should be rejected"});
    assert(!wrong_scope.accepted);

    const auto reply = bus.send({
        "architect-1",
        0,
        "run-1",
        "workspace-1",
        "architect",
        "human",
        "conversation-1",
        AgentMessageType::result,
        "Architecture review complete; next task is scheduler integration."});
    assert(reply.accepted);

    const auto responses = human.receive();
    assert(responses.size() == 1);
    assert(responses.front().sender_id == "architect");
    assert(responses.front().recipient_id == "human");
    assert(responses.front().correlation_id == "conversation-1");
    assert(responses.front().text.find("scheduler integration") != std::string::npos);

    const auto oversized = human.send({
        "human-3",
        "run-1",
        "workspace-1",
        "architect",
        "conversation-1",
        std::string(4097, 'x')});
    assert(!oversized.accepted);

    return 0;
}
