#include "jarvis/engineering/operator_channel.hpp"

#include <cassert>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    OperatorControlChannel operator_channel(bus, "operator", "run-1", "workspace-1");
    AgentCommunicationEndpoint agent(bus, "builder", "run-1", "workspace-1");

    assert(operator_channel.connected());
    assert(agent.registered());

    const auto outbound = operator_channel.send({
        "operator-msg-1", "corr-1", "builder", AgentMessageType::request,
        "Implement the requested engineering task."});
    assert(outbound.accepted);

    const auto agent_messages = agent.drain();
    assert(agent_messages.size() == 1);
    assert(agent_messages.front().sender_id == "operator");
    assert(agent_messages.front().recipient_id == "builder");
    assert(agent_messages.front().correlation_id == "corr-1");

    const auto reply = agent.send(
        "builder-msg-1", "operator", "corr-1", AgentMessageType::result,
        "Implementation completed; verification evidence attached.");
    assert(reply.accepted);

    const auto operator_messages = operator_channel.receive();
    assert(operator_messages.size() == 1);
    assert(operator_messages.front().sender_id == "builder");
    assert(operator_messages.front().recipient_id == "operator");
    assert(operator_messages.front().correlation_id == "corr-1");

    const auto invalid = operator_channel.send({
        "", "corr-2", "builder", AgentMessageType::request, "invalid"});
    assert(!invalid.accepted);

    const auto wrong_run = [&]() {
        AgentCommunicationEndpoint other(bus, "other", "run-2", "workspace-1");
        return operator_channel.send({
            "operator-msg-2", "corr-3", "other", AgentMessageType::request, "isolated"});
    }();
    assert(wrong_run.accepted);

    return 0;
}
