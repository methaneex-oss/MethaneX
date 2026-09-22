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

class CommunicatingAgent final : public EngineeringAgent {
public:
    CommunicatingAgent(std::string id, std::string capability, std::string expected_sender)
        : id_(std::move(id)), capability_(std::move(capability)),
          expected_sender_(std::move(expected_sender)) {}

    AgentDescriptor descriptor() const override {
        return AgentDescriptor{id_, id_, "test", "communication fixture",
            {capability_}, {"workspace.read"}, {"source"}, {"report"}, 0.1, 1.0,
            AgentRisk::low, AgentAvailability::available, true};
    }

    AgentResult execute(const EngineeringTask& task) override {
        ++calls;
        if (communication_required_) {
            assert(task.communication != nullptr);
            const auto messages = task.communication->drain();
            assert(!messages.empty());
            for (const auto& message : messages) {
                if (message.sender_id == expected_sender_ &&
                    message.type == AgentMessageType::result) {
                    saw_peer_result_ = true;
                    break;
                }
            }
            assert(saw_peer_result_);
        }
        return AgentResult{true, id_, task.id, "stage completed",
            {{"report", id_ + ".report", id_}}, {{"stage", id_}}};
    }

    void require_peer_message() noexcept { communication_required_ = true; }
    bool saw_peer_result() const noexcept { return saw_peer_result_; }
    int calls{0};

private:
    std::string id_;
    std::string capability_;
    std::string expected_sender_;
    bool communication_required_{false};
    bool saw_peer_result_{false};
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

    AgentMessageBus bus({4096});
    CommunicatingAgent communicating_implementation(
        "agent.comm-implementation", "code.implementation", "");
    CommunicatingAgent communicating_review(
        "agent.comm-review", "code.review", "agent.comm-implementation");
    communicating_review.require_peer_message();

    const auto communication_result = pipeline.run(
        "run-communication",
        {{EngineeringStage::implementation,
          task("communication-implementation", "code.implementation"),
          communicating_implementation.descriptor().id},
         {EngineeringStage::review,
          task("communication-review", "code.review"),
          communicating_review.descriptor().id}},
        {&communicating_implementation, &communicating_review},
        allow,
        boundary,
        nullptr,
        false,
        {},
        &bus);

    assert(communication_result.status == EngineeringRunStatus::completed);
    assert(communication_result.stages.size() == 2);
    assert(communicating_review.saw_peer_result());
    assert(communicating_implementation.calls == 1);
    assert(communicating_review.calls == 1);

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
