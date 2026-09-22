#include "jarvis/engineering/coordinator.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

class StubAgent final : public EngineeringAgent {
public:
    explicit StubAgent(std::string id) : id_(std::move(id)) {}
    AgentDescriptor descriptor() const override {
        return {id_, id_, "test", "", {"implement"}, {"workspace"}, {}, {"source"}, 0.0, 0.9, AgentRisk::low, AgentAvailability::available, false};
    }
    AgentResult execute(const EngineeringTask& task) override {
        return {true, id_, task.id, "ok", {{"source", id_ + ".cpp", id_}}, {{"stage", id_}}};
    }
private:
    std::string id_;
};

class Allow final : public EngineeringAuthorizer {
public:
    bool authorize(const EngineeringTask&, const AgentDescriptor&) const override { return true; }
};

class Boundary final : public EngineeringExecutionBoundary {
public:
    AgentResult execute(const EngineeringTask& task, EngineeringAgent& agent) override {
        return agent.execute(task);
    }
};

int main() {
    StubAgent first("builder-a");
    StubAgent second("builder-b");
    Allow authorizer;
    Boundary boundary;
    EngineeringCoordinator coordinator;
    EngineeringTask task;
    task.id = "run-1";
    task.objective = "implement capability";
    task.required_capabilities = {"implement"};
    task.required_permissions = {"workspace"};
    task.maximum_cost = 1.0;
    task.expected_artifacts = {"source"};

    const auto plan = coordinator.dispatch_sequence(task, {&first, &second}, authorizer, boundary);
    assert(plan.accepted);
    assert(plan.completed.size() == 2);
    assert(plan.completed[0].result.accepted);
    assert(plan.completed[1].result.accepted);
    return 0;
}
