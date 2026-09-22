#include "jarvis/engineering/operator_console.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    AgentMessageBus bus;
    bool authorized = true;

    EngineeringOperatorConsole console(
        bus, "operator", "run-1", "workspace-1",
        [&](const std::string& sender, const std::string& recipient, AgentMessageType type) {
            return authorized && sender == "operator" && recipient == "builder" &&
                   type == AgentMessageType::request;
        });

    std::vector<AgentMessage> received;
    const auto registration = bus.register_agent("builder", [&](const AgentMessage& message) {
        received.push_back(message);
    });
    assert(registration.accepted);
    assert(console.connected());

    const auto sent = console.send({
        "operator-request-1", "task-1", "builder", AgentMessageType::request,
        "Implement the requested engineering task."});
    assert(sent.accepted);
    assert(received.size() == 1);
    assert(received.front().sender_id == "operator");
    assert(received.front().recipient_id == "builder");
    assert(received.front().correlation_id == "task-1");

    authorized = false;
    const auto denied = console.send({
        "operator-request-2", "task-2", "builder", AgentMessageType::request,
        "This must be denied."});
    assert(!denied.accepted);

    const auto invalid = console.send({
        "operator-status", "task-3", "builder", AgentMessageType::status,
        "Status"});
    assert(!invalid.accepted);

    return 0;
}
