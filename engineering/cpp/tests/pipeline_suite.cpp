#include "jarvis/engineering/pipeline.hpp"

#include <cassert>

using namespace jarvis::engineering;

namespace {

class StageAgent final : public EngineeringAgent {
public:
    explicit StageAgent(std::string id, std::string capability)
        : id_(std::move(id)), capability_(std::move(capability)) {}

    AgentDescriptor descriptor() const override {
        return AgentDescriptor{
            id_, id_, "test", "pipeline fixture",
            {capability_}, {"workspace.read"},
            {"source"}, {"report"}, 0.1, 1.0, AgentRisk::low,
            AgentAvailability::available, true};
    }

    AgentResult execute(const EngineeringTask& task) override {
        ++calls;
        return AgentResult{true, id_, task.id, "stage completed", {}, {{"stage", id_}}};
    }

    int calls{0};

private:
    std::string id_;
    std::string capability_;
};

class DenyAuthorizer final : public EngineeringAuthorizer {
public:
    bool authorize(const EngineeringTask&, const AgentDescriptor&) const override {
        return false;
    }
};

} // namespace

int main() {
    StageAgent implementation("agent.implementation", "code.implementation");
    StageAgent review("agent.review", "code.review");
    EngineeringPipeline pipeline;
    DirectExecutionBoundary boundary;
    AllowAllAuthorizer allow;

    const EngineeringTask implementation_task{
        "implement-1", "implement change",
        {"code.implementation"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0};
    const EngineeringTask review_task{
        "review-1", "review change",
        {"code.review"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0};

    const auto result = pipeline.run(
        "run-1",
        {
            {EngineeringStage::implementation, implementation_task, implementation.descriptor().id},
            {EngineeringStage::review, review_task, review.descriptor().id}
        },
        {&implementation, &review},
        allow,
        boundary);

    assert(result.status == EngineeringRunStatus::completed);
    assert(result.stages.size() == 2);
    assert(implementation.calls == 1);
    assert(review.calls == 1);

    const auto denied = pipeline.run(
        "run-2",
        {{EngineeringStage::implementation, implementation_task, implementation.descriptor().id}},
        {&implementation},
        DenyAuthorizer{},
        boundary);
    assert(denied.status == EngineeringRunStatus::failed);
    assert(implementation.calls == 1);

    const auto missing = pipeline.run(
        "run-3",
        {{EngineeringStage::implementation, implementation_task, "missing"}},
        {&implementation},
        allow,
        boundary);
    assert(missing.status == EngineeringRunStatus::failed);
    return 0;
}
