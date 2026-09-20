#include "jarvis/engineering/agent.hpp"

#include <cassert>

using namespace jarvis::engineering;

namespace {

class TestAgent final : public EngineeringAgent {
public:
    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            "agent.test", "Test Agent", "test", "deterministic fixture",
            {"code.edit", "code.review"}, {"workspace.read"},
            {"source"}, {"patch", "report"}, 0.0, 1.0, AgentRisk::low,
            AgentAvailability::available, false};
    }

    AgentResult execute(const EngineeringTask& task) override {
        return AgentResult{true, descriptor().id, task.id, "executed", {}, {{"test", "verified"} }};
    }
};

} // namespace

int main() {
    TestAgent agent;
    const auto descriptor = agent.descriptor();
    assert(valid_descriptor(descriptor));

    EngineeringTask task{
        "task-1", "review a change",
        {"code.review"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0};
    assert(valid_task(task));

    const auto result = agent.execute(task);
    assert(result.accepted);
    assert(result.task_id == task.id);
    assert(result.evidence.size() == 1);
    return 0;
}
