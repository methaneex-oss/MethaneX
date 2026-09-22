#include "jarvis/engineering/human_agent_channel.hpp"

#include <cassert>
#include <string>
#include <vector>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    std::vector<AgentMessage> received;

    AgentCommunicationEndpoint agent(
        bus, "architect", "session-1", "workspace-1");
    assert(agent.registered());

    HumanAgentChannel human(
        bus, "human:user", "session-1", "workspace-1");
    assert(human.connected());

    const auto sent = human.send_to_agent(
        "human-msg-1", "chat-1", "architect",
        "Review the current architecture and report conflicts.");
    assert(sent.accepted);

    const auto requests = agent.drain();
    assert(requests.size() == 1);
    assert(requests[0].sender_id == "human:user");
    assert(requests[0].recipient_id == "architect");
    assert(requests[0].type == AgentMessageType::request);
    assert(requests[0].payload.find("Review") != std::string::npos);

    const auto reply = agent.send(
        "agent-msg-1", "human:user", "chat-1",
        AgentMessageType::result,
        "Architecture reviewed; no blocking conflict found.");
    assert(reply.accepted);

    const auto responses = human.receive_from_agents();
    assert(responses.size() == 1);
    assert(responses[0].sender_id == "architect");
    assert(responses[0].recipient_id == "human:user");
    assert(responses[0].correlation_id == "chat-1");
    assert(responses[0].type == AgentMessageType::result);

    const auto cross_session = human.send_to_agent(
        "human-msg-2", "chat-2", "architect",
        "This must not cross a different session.");
    assert(cross_session.accepted);
    const auto ignored = AgentCommunicationEndpoint(
        bus, "other-human", "session-2", "workspace-1");
    (void)ignored;

    return 0;
}
