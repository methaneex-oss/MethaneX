#include "jarvis/engineering/model_agent.hpp"
#include "jarvis/engineering/pipeline.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

namespace {

class ImplementationModel final : public EngineeringModelProvider {
public:
    ModelDescriptor descriptor() const override {
        return {"implementation-model", "test", "codegen", {"source"}, 0.1, 1.0};
    }

    ModelResponse generate(const ModelRequest&) override {
        return {ModelProviderStatus::succeeded, "test", "codegen", "implemented",
                {{"src/change.cpp", "int answer = 42;"}}, {}, {}};
    }
};

class ReviewModel final : public EngineeringModelProvider {
public:
    ModelDescriptor descriptor() const override {
        return {"review-model", "test", "review", {"report"}, 0.1, 1.0};
    }

    ModelResponse generate(const ModelRequest& request) override {
        saw_handoff = request.context.find("incoming.message=agent.implementation") != std::string::npos &&
                      request.context.find("stage=implementation;accepted=true") != std::string::npos;
        return {ModelProviderStatus::succeeded, "test", "review", "reviewed",
                {{"review/report.txt", saw_handoff ? "handoff received" : "handoff missing"}}, {}, {}};
    }

    bool saw_handoff{false};
};

class Authorizer final : public EngineeringAuthorizer {
public:
    bool authorize(const EngineeringTask&, const AgentDescriptor&) const override { return true; }
};

} // namespace

int main() {
    InMemoryEngineeringWorkspace workspace;
    ImplementationModel implementation_model;
    ReviewModel review_model;

    ModelBackedEngineeringAgent implementation(
        AgentDescriptor{"agent.implementation", "Implementation Agent", "test", "writes source",
                        {"code.implementation"}, {"workspace.write"}, {"source"}, {"source"},
                        0.1, 1.0, AgentRisk::low, AgentAvailability::available, true},
        implementation_model, workspace);
    ModelBackedEngineeringAgent review(
        AgentDescriptor{"agent.review", "Review Agent", "test", "reviews source",
                        {"code.review"}, {"workspace.read"}, {"source"}, {"report"},
                        0.1, 1.0, AgentRisk::low, AgentAvailability::available, true},
        review_model, workspace);

    const EngineeringTask implementation_task{
        "implement", "implement change", {"code.implementation"}, {"workspace.write"},
        {"source"}, {"source"}, AgentRisk::low, 1.0};
    const EngineeringTask review_task{
        "review", "review implementation", {"code.review"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0};

    AgentMessageBus bus;
    EngineeringPipeline pipeline;
    DirectExecutionBoundary boundary;
    Authorizer authorizer;

    const auto result = pipeline.run(
        "handoff-1",
        {{EngineeringStage::implementation, implementation_task, "agent.implementation"},
         {EngineeringStage::review, review_task, "agent.review"}},
        {&implementation, &review}, authorizer, boundary, &workspace, false, {}, &bus);

    assert(result.status == EngineeringRunStatus::completed);
    assert(result.stages.size() == 2);
    assert(review_model.saw_handoff);
    return 0;
}
