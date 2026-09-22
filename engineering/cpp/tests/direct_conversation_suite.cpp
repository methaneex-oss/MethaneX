#include "jarvis/engineering/direct_conversation.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    AgentCommunicationEndpoint builder(bus, "builder", "run-1", "workspace-1");
    DirectAgentConversation conversation(bus, "run-1", "workspace-1");

    assert(conversation.ready());
    assert(builder.registered());

    auto user_send = conversation.send_user(
        "user-1", "builder", "task-1", "Implement the requested change.");
    assert(user_send.accepted);

    auto received = builder.drain();
    assert(received.size() == 1);
    assert(received.front().sender_id == "human");
    assert(received.front().payload == "Implement the requested change.");

    auto agent_reply = builder.send(
        "builder-1", "human", "task-1", AgentMessageType::result,
        "Implementation result is ready.");
    assert(agent_reply.accepted);

    auto user_replies = conversation.drain_user();
    assert(user_replies.size() == 1);
    assert(user_replies.front().sender_id == "builder");
    assert(user_replies.front().correlation_id == "task-1");

    auto assistant_send = conversation.send_assistant(
        "assistant-1", "builder", "task-2", "Review the implementation.");
    assert(assistant_send.accepted);

    received = builder.drain();
    assert(received.size() == 1);
    assert(received.front().sender_id == "assistant");
    assert(received.front().correlation_id == "task-2");

    auto assistant_reply = builder.send(
        "builder-2", "assistant", "task-2", AgentMessageType::review,
        "Review completed.");
    assert(assistant_reply.accepted);

    auto assistant_replies = conversation.drain_assistant();
    assert(assistant_replies.size() == 1);
    assert(assistant_replies.front().sender_id == "builder");
    assert(assistant_replies.front().payload == "Review completed.");

    return 0;
}
