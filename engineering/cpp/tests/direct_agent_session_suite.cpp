#include "jarvis/engineering/direct_agent_session.hpp"

#include <cassert>
#include <string>
#include <utility>

using namespace jarvis::engineering;

namespace {

class InteractiveAgent final : public EngineeringAgent {
public:
    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            "architect", "Architect", "test", "architecture agent",
            {"architecture"}, {"workspace.read"}, {"source"}, {"report"},
            0.1, 0.9, AgentRisk::low, AgentAvailability::available, false};
    }

    AgentResult execute(const EngineeringTask& task) override {
        assert(task.communication != nullptr);
        const auto messages = task.communication->drain();
        assert(messages.size() == 1);
        assert(messages[0].type == AgentMessageType::request);
        assert(messages[0].payload == task.objective);
        return {
            true, descriptor().id, task.id, "direct response",
            {{"report", "memory/direct", "digest"}},
            {{"interactive", "handled"}}};
    }
};

} // namespace

int main() {
    InteractiveAgent agent;
    AllowAllAuthorizer authorizer;
    DirectExecutionBoundary boundary;
    AgentMessageBus bus;

    DirectAgentSession session(
        agent,
        authorizer,
        boundary,
        bus,
        "human:user",
        "session-42");

    assert(session.connected());
    assert(session.agent_descriptor().id == "architect");

    const auto charter = session.charter();
    assert(!charter.mission.empty());
    assert(!charter.forbidden_operations.empty());
    assert(!charter.preserved_contracts.empty());
    assert(!charter.mandatory_tests.empty());
    assert(!charter.completion_requirements.empty());

    const auto result = session.ask(
        "task-42",
        "Explain the current architecture and identify any contract conflict.");
    assert(result.accepted);
    assert(result.reason == "direct response");

    const auto responses = session.drain_messages();
    assert(responses.size() == 1);
    assert(responses[0].sender_id == "architect");
    assert(responses[0].type == AgentMessageType::result);
    assert(responses[0].correlation_id == "task-42");

    return 0;
}
