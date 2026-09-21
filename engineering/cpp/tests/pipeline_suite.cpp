#include "jarvis/engineering/pipeline.hpp"

#include <cassert>
#include <string>
#include <utility>
#include <vector>

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

class SharedWorkspace final : public EngineeringWorkspace {
public:
    WorkspaceResult open(std::string_view id, std::string_view branch) override {
        ++opens;
        opened_id = std::string(id);
        opened_branch = std::string(branch);
        return {true, opened_id, opened_branch, {}};
    }

    WorkspaceResult write_file(std::string_view id, std::string_view path,
                               std::string_view, std::string_view digest) override {
        ++writes;
        assert(id == opened_id);
        assert(!path.empty());
        assert(!digest.empty());
        return {true, std::string(id), {}, {AgentArtifact{"workspace.file", std::string(path), std::string(digest)}}};
    }

    WorkspaceResult record_file(std::string_view, std::string_view, std::string_view) override {
        return {true, {}, {}, {}};
    }

    WorkspaceResult commit(std::string_view id, std::string_view message) override {
        ++commits;
        assert(id == opened_id);
        assert(!message.empty());
        return {true, std::string(id), {}, {AgentArtifact{"git.commit", "commit-1", "commit-1"}}};
    }

    bool close(std::string_view id) override {
        ++closes;
        assert(id == opened_id);
        return true;
    }

    int opens{0};
    int writes{0};
    int commits{0};
    int closes{0};
    std::string opened_id;
    std::string opened_branch;
};

EngineeringTask task(std::string id, std::string capability) {
    return {std::move(id), "implement change", {std::move(capability)}, {"workspace.read"},
            {"source"}, {"report"}, AgentRisk::low, 1.0};
}

} // namespace

int main() {
    StageAgent implementation("agent.implementation", "code.implementation");
    StageAgent review("agent.review", "code.review");
    EngineeringPipeline pipeline;
    DirectExecutionBoundary boundary;
    AllowAllAuthorizer allow;

    const auto implementation_task = task("implement-1", "code.implementation");
    const auto review_task = task("review-1", "code.review");

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

    SharedWorkspace shared;
    const auto shared_result = pipeline.run(
        "run-shared",
        {{EngineeringStage::implementation, implementation_task, implementation.descriptor().id},
         {EngineeringStage::verification, review_task, review.descriptor().id}},
        {&implementation, &review},
        allow,
        boundary,
        &shared);

    assert(shared_result.status == EngineeringRunStatus::completed);
    assert(shared.opens == 1);
    assert(shared.commits == 1);
    assert(shared.closes == 1);
    assert(shared.writes == 0);
    assert(shared_result.artifacts.size() == 1);
    assert(implementation.calls == 2);
    assert(review.calls == 2);

    const auto selected_result = pipeline.run(
        "run-selected",
        {{EngineeringStage::implementation, implementation_task, ""},
         {EngineeringStage::review, review_task, ""}},
        {&review, &implementation},
        allow,
        boundary,
        nullptr,
        true);
    assert(selected_result.status == EngineeringRunStatus::completed);
    assert(selected_result.stages.size() == 2);
    assert(implementation.calls == 3);
    assert(review.calls == 3);

    const auto out_of_order = pipeline.run(
        "run-order",
        {{EngineeringStage::review, review_task, review.descriptor().id},
         {EngineeringStage::implementation, implementation_task, implementation.descriptor().id}},
        {&implementation, &review},
        allow,
        boundary);
    assert(out_of_order.status == EngineeringRunStatus::failed);
    assert(out_of_order.reason == "engineering stages out of order");

    const auto denied = pipeline.run(
        "run-2",
        {{EngineeringStage::implementation, implementation_task, implementation.descriptor().id}},
        {&implementation},
        DenyAuthorizer{},
        boundary);
    assert(denied.status == EngineeringRunStatus::failed);
    assert(implementation.calls == 3);

    const auto missing = pipeline.run(
        "run-3",
        {{EngineeringStage::implementation, implementation_task, "missing"}},
        {&implementation},
        allow,
        boundary);
    assert(missing.status == EngineeringRunStatus::failed);
    return 0;
}
