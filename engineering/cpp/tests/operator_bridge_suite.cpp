#include "jarvis/engineering/operator_bridge.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    AgentCommunicationEndpoint agent(
        bus, "builder", "run-operator", "workspace-operator");
    assert(agent.registered());

    AgentOperatorBridge bridge(
        bus,
        "operator",
        "run-operator",
        "workspace-operator",
        AgentOperatorBridgePolicy{
            16,
            {AgentMessageType::request, AgentMessageType::query,
             AgentMessageType::feedback, AgentMessageType::result},
            [](const std::string& sender, const std::string& recipient, AgentMessageType) {
                return sender == "operator" && recipient == "builder";
            }});

    assert(bridge.connected());
    assert(bridge.operator_id() == "operator");

    const auto sent = bridge.send_to_agent(
        "builder", "task-1", "Implement the requested change.");
    assert(sent.accepted);

    const auto messages = agent.drain();
    assert(messages.size() == 1);
    assert(messages.front().sender_id == "operator");
    assert(messages.front().recipient_id == "builder");
    assert(messages.front().correlation_id == "task-1");

    const auto denied = bridge.send_to_agent(
        "builder", "task-2", "execute", AgentMessageType::status);
    assert(!denied.accepted);

    const auto response = agent.send(
        "agent-response", "operator", "task-1", AgentMessageType::result,
        "Implementation complete.");
    assert(response.accepted);

    const auto received = bridge.receive();
    assert(received.size() == 1);
    assert(received.front().sender_id == "builder");
    assert(received.front().correlation_id == "task-1");
    assert(received.front().payload == "Implementation complete.");

    return 0;
}
