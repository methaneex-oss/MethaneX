#include "jarvis/engineering/model_agent.hpp"

#include <cassert>
#include <string>
#include <vector>

using namespace jarvis::engineering;

namespace {

class FakeModel final : public EngineeringModelProvider {
public:
    ModelResponse response;
    ModelRequest last_request;

    ModelDescriptor descriptor() const override {
        return {"fake", "test", "coder", {"source"}, 0.1, 0.9};
    }

    ModelResponse generate(const ModelRequest& request) override {
        last_request = request;
        return response;
    }
};

class FakeWorkspace final : public EngineeringWorkspace {
public:
    bool closed{false};
    std::vector<std::string> writes;

    WorkspaceResult open(std::string_view id, std::string_view branch) override {
        return {true, std::string(id), std::string(branch), {}};
    }

    WorkspaceResult write_file(std::string_view id, std::string_view path,
                               std::string_view content, std::string_view digest) override {
        writes.push_back(std::string(path) + ":" + std::string(content));
        assert(!digest.empty());
        return {true, std::string(id), {}, {AgentArtifact{"workspace.file", std::string(path), std::string(digest)}}};
    }

    WorkspaceResult record_file(std::string_view, std::string_view, std::string_view) override {
        return {true, {}, {}, {}};
    }

    WorkspaceResult commit(std::string_view id, std::string_view) override {
        return {true, std::string(id), {}, {AgentArtifact{"git.commit", "commit-1", "commit-1"}}};
    }

    bool close(std::string_view) override {
        closed = true;
        return true;
    }
};

EngineeringTask task() {
    return {"task-1", "implement feature", {"code"}, {}, {}, {"source"}, AgentRisk::high, 1.0};
}

} // namespace

int main() {
    FakeModel model;
    FakeWorkspace workspace;
    AgentDescriptor descriptor{"agent-1", "model agent", "test", "model-backed",
                               {"code-generation"}, {}, {}, {"source"}, 0.1, 0.9,
                               AgentRisk::medium, AgentAvailability::available, false};

    model.response = {ModelProviderStatus::succeeded, "test", "coder", "done",
                      {{"src/example.cpp", "int answer() { return 42; }"}}, {}, {}};
    ModelBackedEngineeringAgent agent(descriptor, model, workspace);
    AgentMessageBus bus;
    AgentCommunicationEndpoint sender(bus, "agent-1", "run-1", "");
    AgentCommunicationEndpoint peer(bus, "peer", "run-1", "");
    assert(sender.registered());
    assert(peer.registered());

    assert(peer.send("inbound-1", "agent-1", "task-1",
                     AgentMessageType::feedback, "review says inspect edge case").accepted);
    auto communication_task = task();
    communication_task.communication = &sender;
    communication_task.communication_targets = {"peer"};

    const auto result = agent.execute(communication_task);
    assert(result.accepted);
    assert(workspace.writes.size() == 1);
    assert(workspace.closed);
    assert(!result.artifacts.empty());
    assert(model.last_request.context.find("incoming.message=peer|task-1|review says inspect edge case") != std::string::npos);
    assert(peer.pending() == 2);

    model.response.file_changes.front().path = "../escape.cpp";
    const auto rejected = agent.execute(task());
    assert(!rejected.accepted);
    assert(rejected.reason == "unsafe model file path");

    model.response.file_changes.front().path = "src/example.cpp";
    model.response.file_changes.front().content = std::string(1024 * 1024, 'x');
    const auto oversized = agent.execute(task());
    assert(!oversized.accepted);
    assert(oversized.reason == "model output limit exceeded");
    return 0;
}
