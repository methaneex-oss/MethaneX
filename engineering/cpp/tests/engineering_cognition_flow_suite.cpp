#include "jarvis/engineering/model_agent.hpp"
#include "jarvis/engineering/model_assessment_agent.hpp"
#include "jarvis/engineering/pipeline.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

namespace {

class ImplementationModel final : public EngineeringModelProvider {
public:
    ModelDescriptor descriptor() const override {
        return {"implementation-model", "test", "codegen", {"source"}, 0.2, 0.9};
    }

    ModelResponse generate(const ModelRequest&) override {
        return {ModelProviderStatus::succeeded, "test", "codegen", "implemented",
                {{"src/change.cpp", "int answer = 42;"}}, {}, {}};
    }
};

class AssessmentModel final : public EngineeringModelProvider {
public:
    ModelDescriptor descriptor() const override {
        return {"assessment-model", "test", "review", {"report"}, 0.1, 0.95};
    }

    ModelResponse generate(const ModelRequest& request) override {
        ++calls;
        assert(request.context.find("int answer = 42;") != std::string::npos);
        assert(request.context.find("prior.artifact=workspace.file") != std::string::npos);
        if (calls == 1) {
            return {ModelProviderStatus::failed, "test", "review", "review requires revision",
                    {}, {{"review", "requires_revision"}}, "review requires revision"};
        }
        return {ModelProviderStatus::succeeded, "test", "review",
                "implementation verified", {}, {}, {}};
    }

    int calls{0};
};

class Authorizer final : public EngineeringAuthorizer {
public:
    bool authorize(const EngineeringTask&, const AgentDescriptor&) const override {
        return true;
    }
};

} // namespace

int main() {
    InMemoryEngineeringWorkspace workspace;
    ImplementationModel implementation_model;
    AssessmentModel assessment_model;

    ModelBackedEngineeringAgent implementation(
        AgentDescriptor{"agent.implementation", "Implementation Agent", "test", "writes source",
                        {"code.implementation"}, {"workspace.write"}, {"source"}, {"source"},
                        0.2, 0.9, AgentRisk::low, AgentAvailability::available, true},
        implementation_model, workspace);

    ModelAssessmentAgent review(
        AgentDescriptor{"agent.review", "Review Agent", "test", "reviews source",
                        {"code.review"}, {"workspace.read"}, {"source"}, {"report"},
                        0.1, 0.95, AgentRisk::low, AgentAvailability::available, true},
        assessment_model, workspace);

    const EngineeringTask implementation_task{
        "implement", "implement change", {"code.implementation"}, {"workspace.write"},
        {"source"}, {"source"}, AgentRisk::low, 1.0};

    const EngineeringTask review_task{
        "review", "review implementation", {"code.review"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0, {}, false, {"src/change.cpp"}};

    EngineeringPipeline pipeline;
    DirectExecutionBoundary boundary;
    Authorizer authorizer;

    const auto result = pipeline.run(
        "flow-1",
        {{EngineeringStage::implementation, implementation_task, "agent.implementation"},
         {EngineeringStage::review, review_task, "agent.review"},
         {EngineeringStage::verification, review_task, "agent.review"}},
        {&implementation, &review},
        authorizer,
        boundary,
        &workspace);

    assert(result.status == EngineeringRunStatus::completed);
    assert(result.stages.size() == 4);
    assert(result.stages[1].attempt == 1);
    assert(result.stages[2].attempt == 2);
    assert(result.artifacts.size() == 2);
    assert(assessment_model.calls == 3);
    assert(result.context.stages.size() == 4);
    assert(result.context.artifacts.size() == 2);
    assert(result.context.evidence.size() >= 3);
    assert(result.context.workspace_id == "engineering-run-flow-1");
    return 0;
}
