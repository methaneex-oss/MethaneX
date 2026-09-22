#include "jarvis/engineering/operator_gateway.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus({128});
    AgentCommunicationEndpoint builder(bus, "builder", "run-operator", "workspace-1");
    AgentCommunicationEndpoint reviewer(bus, "reviewer", "run-operator", "workspace-1");
    assert(builder.registered());
    assert(reviewer.registered());

    OperatorGateway operator_gateway(bus, "operator", "run-operator", "workspace-1");
    assert(operator_gateway.connected());
    assert(operator_gateway.run_id() == "run-operator");
    assert(operator_gateway.workspace_id() == "workspace-1");

    const OperatorMessage request{
        "operator-1", "task-1", AgentMessageType::request, "Review the current implementation."};
    const auto sent = operator_gateway.send_to_agent(request, "reviewer");
    assert(sent.accepted);
    assert(reviewer.pending() == 1);

    const auto received = reviewer.drain();
    assert(received.size() == 1);
    assert(received.front().sender_id == "operator");
    assert(received.front().recipient_id == "reviewer");
    assert(received.front().payload == request.payload);

    const auto response = reviewer.send(
        "review-1", "operator", "task-1", AgentMessageType::result, "Review complete.");
    assert(response.accepted);

    const auto operator_messages = operator_gateway.receive();
    assert(operator_messages.size() == 1);
    assert(operator_messages.front().sender_id == "reviewer");
    assert(operator_messages.front().correlation_id == "task-1");

    OperatorGatewayPolicy denied_policy;
    denied_policy.authorize = [](const OperatorMessage&, const std::string&) { return false; };
    OperatorGateway denied(bus, "operator-denied", "run-operator", "workspace-1", denied_policy);
    const auto denied_result = denied.send_to_agent(request, "builder");
    assert(!denied_result.accepted);
    assert(builder.pending() == 0);

    OperatorGatewayPolicy broadcast_policy;
    broadcast_policy.allow_broadcast = true;
    OperatorGateway broadcaster(bus, "operator-broadcast", "run-operator", "workspace-1", broadcast_policy);
    const auto broadcast_result = broadcaster.broadcast(
        OperatorMessage{"operator-2", "task-2", AgentMessageType::status, "Work is starting."},
        {"builder", "reviewer"});
    assert(broadcast_result.accepted);
    assert(builder.pending() == 1);
    assert(reviewer.pending() == 1);

    return 0;
}
