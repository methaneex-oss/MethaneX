#include "jarvis/engineering/operator_channel.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    AgentCommunicationEndpoint agent(bus, "builder", "run-1", "workspace-1");
    OperatorChannel operator_channel(bus, "operator-session", "run-1", "workspace-1");

    assert(agent.registered());
    assert(operator_channel.connected());

    const auto sent = operator_channel.send({
        "operator-msg-1", "corr-1", "builder", AgentMessageType::request,
        "Inspect the current implementation and report the next safe build step."});
    assert(sent.accepted);
    assert(agent.pending() == 1);

    const auto incoming = agent.drain();
    assert(incoming.size() == 1);
    assert(incoming.front().sender_id == "operator-session");
    assert(incoming.front().recipient_id == "builder");
    assert(incoming.front().payload.find("Inspect") != std::string::npos);

    const auto reply = agent.send(
        "builder-reply-1", "operator-session", "corr-1",
        AgentMessageType::result,
        "Implementation inspected; next step is verified integration.");
    assert(reply.accepted);
    assert(operator_channel.pending() == 1);

    const auto replies = operator_channel.receive();
    assert(replies.size() == 1);
    assert(replies.front().correlation_id == "corr-1");
    assert(replies.front().sender_id == "builder");
    assert(replies.front().recipient_id == "operator-session");

    const auto invalid = operator_channel.send({
        "", "corr-2", "builder", AgentMessageType::request, "invalid"});
    assert(!invalid.accepted);

    AgentMessageBus other_bus;
    OperatorChannel isolated(other_bus, "operator-session-2", "run-1", "workspace-1");
    const auto missing = isolated.send({
        "operator-msg-2", "corr-3", "builder", AgentMessageType::request, "not delivered"});
    assert(!missing.accepted);

    return 0;
}
