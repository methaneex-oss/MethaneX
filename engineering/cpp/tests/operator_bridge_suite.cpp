#include "jarvis/engineering/operator_bridge.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    AgentConversation agent(
        bus, "builder", "run-operator", "workspace-operator",
        [](const std::string& sender, const std::string& recipient, AgentMessageType) {
            return sender == "builder" && recipient == "operator";
        });
    assert(agent.connected());

    OperatorBridge operator_bridge(
        bus, "operator", "run-operator", "workspace-operator",
        [](const std::string& sender, const std::string& recipient, AgentMessageType) {
            return sender == "operator" && recipient == "builder";
        });
    assert(operator_bridge.connected());
    assert(operator_bridge.operator_id() == "operator");
    assert(operator_bridge.run_id() == "run-operator");
    assert(operator_bridge.workspace_id() == "workspace-operator");

    const auto request = operator_bridge.send({
        "builder", "task-1", AgentMessageType::request, "Implement the requested change."
    });
    assert(request.accepted);

    const auto requests = agent.receive();
    assert(requests.size() == 1);
    assert(requests.front().sender_id == "operator");
    assert(requests.front().recipient_id == "builder");
    assert(requests.front().correlation_id == "task-1");

    const auto response = agent.send(
        "operator", "task-1", AgentMessageType::result, "Implementation result is ready.");
    assert(response.accepted);

    const auto responses = operator_bridge.receive();
    assert(responses.size() == 1);
    assert(responses.front().sender_id == "builder");
    assert(responses.front().recipient_id == "operator");
    assert(responses.front().correlation_id == "task-1");
    assert(responses.front().payload == "Implementation result is ready.");

    const auto denied = operator_bridge.send({
        "other-agent", "task-2", AgentMessageType::request, "unauthorized"
    });
    assert(!denied.accepted);
    return 0;
}
