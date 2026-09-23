#include "jarvis/engineering/operator_console.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    AgentConversation agent(
        bus, "builder", "run-console", "workspace-console",
        [](const std::string& sender, const std::string& recipient, AgentMessageType) {
            return sender == "builder" && recipient == "operator";
        });

    OperatorBridge bridge(
        bus, "operator", "run-console", "workspace-console",
        [](const std::string& sender, const std::string& recipient, AgentMessageType) {
            return sender == "operator" && recipient == "builder";
        });
    OperatorAgentConsole console(bridge);
    assert(console.connected());

    const auto sent = console.send({"builder", "conversation-1", "Work on the current implementation and report the result."});
    assert(sent.accepted);

    const auto requests = agent.receive();
    assert(requests.size() == 1);
    assert(requests.front().payload == "Work on the current implementation and report the result.");

    assert(agent.send("operator", "conversation-1", AgentMessageType::result,
                      "The requested work is complete and verified.").accepted);

    const auto responses = console.receive();
    assert(responses.size() == 1);
    assert(responses.front().sender_id == "builder");
    assert(responses.front().correlation_id == "conversation-1");
    assert(responses.front().payload == "The requested work is complete and verified.");

    return 0;
}
