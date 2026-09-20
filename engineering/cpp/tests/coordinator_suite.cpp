#include "jarvis/engineering/coordinator.hpp"

#include <cassert>

using namespace jarvis::engineering;

namespace {

class TestAgent final : public EngineeringAgent {
public:
    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            "agent.review", "Review Agent", "test", "fixture",
            {"code.review"}, {"workspace.read"},
            {"source"}, {"report"}, 0.2, 0.9, AgentRisk::low,
            AgentAvailability::available, true};
    }

    AgentResult execute(const EngineeringTask& task) override {
        return AgentResult{true, descriptor().id, task.id, "executed", {}, {{"ci", "pending"}}};
    }
};

} // namespace

int main() {
    TestAgent agent;
    EngineeringCoordinator coordinator;

    EngineeringTask task{
        "review-1", "review source",
        {"code.review"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0};

    const auto candidates = coordinator.discover(task, {agent.descriptor()});
    assert(candidates.size() == 1);
    assert(candidates.front().eligible);

    const auto ranked = coordinator.rank(task, {agent.descriptor()});
    assert(ranked.size() == 1);
    assert(ranked.front().eligible);
    assert(ranked.front().score > 0.0);

    const auto result = coordinator.dispatch(task, agent);
    assert(result.accepted);
    assert(result.agent_id == "agent.review");

    EngineeringTask impossible = task;
    impossible.required_capabilities = {"security.audit"};
    assert(!coordinator.discover(impossible, {agent.descriptor()}).front().eligible);
    return 0;
}
