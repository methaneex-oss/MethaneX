#include "jarvis/engineering/operator_channel.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    EngineeringOperatorChannel operator_channel(
        bus, "operator:primary", "run-1", "workspace-1");

    assert(operator_channel.connected());

    AgentCommunicationEndpoint agent(
        bus, "builder", "run-1", "workspace-1");
    assert(agent.registered());

    const auto outbound = operator_channel.send_to_agent(
        "msg-1", "builder", "corr-1", AgentMessageType::request,
        "Implement the requested engineering task.");
    assert(outbound.accepted);

    const auto requests = agent.drain();
    assert(requests.size() == 1);
    assert(requests.front().sender_id == "operator:primary");
    assert(requests.front().recipient_id == "builder");
    assert(requests.front().payload == "Implement the requested engineering task.");

    const auto reply = agent.send(
        "msg-2", "operator:primary", "corr-1", AgentMessageType::result,
        "Implementation completed; verification evidence attached.");
    assert(reply.accepted);

    const auto responses = operator_channel.receive();
    assert(responses.size() == 1);
    assert(responses.front().sender_id == "builder");
    assert(responses.front().recipient_id == "operator:primary");
    assert(responses.front().correlation_id == "corr-1");

    EngineeringOperatorChannel isolated(
        bus, "operator:isolated", "run-2", "workspace-2");
    const auto wrong_run = agent.send(
        "msg-3", "operator:isolated", "corr-2", AgentMessageType::result,
        "must not cross run/workspace boundary");
    assert(wrong_run.accepted);
    assert(isolated.pending() == 0);

    return 0;
}
