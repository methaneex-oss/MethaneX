#include "jarvis/engineering/model_assessment_agent.hpp"

#include <cassert>
#include <string>
#include <vector>

using namespace jarvis::engineering;

namespace {

class FakeModel final : public EngineeringModelProvider {
public:
    ModelDescriptor descriptor() const override {
        return {"review-model", "test", "assessment", {"report"}, 0.1, 1.0};
    }

    ModelResponse generate(const ModelRequest& request) override {
        ++calls;
        last_context = request.context;
        return {ModelProviderStatus::succeeded, "test", "assessment",
                "no blocking findings", {}, {{"model.test", "ok"}}, {}};
    }

    int calls{0};
    std::string last_context;
};

} // namespace

int main() {
    InMemoryEngineeringWorkspace workspace;
    assert(workspace.open("run-1", "agent/run-1").accepted);
    assert(workspace.write_file("run-1", "src/change.cpp", "int x = 1;", "digest").accepted);

    FakeModel model;
    const AgentDescriptor review_descriptor{
        "agent.review", "Review Agent", "test", "reviews source",
        {"code.review"}, {"workspace.read"}, {"source"}, {"report"},
        0.1, 1.0, AgentRisk::low, AgentAvailability::available, true};

    ModelAssessmentAgent review(review_descriptor, model, workspace);
    const EngineeringTask review_task{
        "review-1", "review implementation", {"code.review"}, {"workspace.read"},
        {"source"}, {"report"}, AgentRisk::low, 1.0,
        "run-1", false, {"src/change.cpp"}};

    const auto result = review.execute(review_task);
    assert(result.accepted);
    assert(model.calls == 1);
    assert(model.last_context.find("src/change.cpp") != std::string::npos);
    assert(model.last_context.find("int x = 1;") != std::string::npos);
    assert(result.evidence.size() == 4);

    class MutatingModel final : public EngineeringModelProvider {
    public:
        ModelDescriptor descriptor() const override {
            return {"mutating", "test", "assessment", {"report"}, 0.1, 1.0};
        }
        ModelResponse generate(const ModelRequest&) override {
            return {ModelProviderStatus::succeeded, "test", "assessment", "bad",
                    {{"src/bad.cpp", "mutation"}}, {}, {}};
        }
    } mutating;

    ModelAssessmentAgent verification(
        AgentDescriptor{"agent.verification", "Verification Agent", "test", "verifies source",
                        {"code.verification"}, {"workspace.read"}, {"source"}, {"report"},
                        0.1, 1.0, AgentRisk::low, AgentAvailability::available, true},
        mutating, workspace);

    auto verification_task = review_task;
    verification_task.id = "verify-1";
    verification_task.objective = "verify implementation";
    verification_task.required_capabilities = {"code.verification"};

    const auto rejected = verification.execute(verification_task);
    assert(!rejected.accepted);
    assert(rejected.reason == "assessment provider attempted workspace mutation");

    const auto missing = review.execute(
        EngineeringTask{"missing", "review missing", {"code.review"}, {"workspace.read"},
                        {"source"}, {"report"}, AgentRisk::low, 1.0,
                        "run-1", false, {"src/missing.cpp"}});
    assert(!missing.accepted);
    return 0;
}
