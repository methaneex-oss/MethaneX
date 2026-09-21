#include "jarvis/engineering/workspace.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    InMemoryEngineeringWorkspace workspace;

    const auto created = workspace.open("run-1", "feat/jarvis-agent/run-1");
    assert(created.accepted);
    assert(created.workspace_id == "run-1");

    const auto inspected = workspace.record_file("run-1", "core/example.cpp", "abc123");
    assert(inspected.accepted);

    const auto artifact = workspace.commit("run-1", "implement candidate");
    assert(artifact.accepted);
    assert(artifact.artifacts.size() == 1);
    assert(artifact.artifacts.front().type == "git.commit");
    assert(artifact.artifacts.front().location == "feat/jarvis-agent/run-1");

    const auto closed = workspace.close("run-1");
    assert(closed);
    assert(!workspace.open("run-1", "feat/jarvis-agent/run-1").accepted);

    const auto unknown = workspace.commit("missing", "should fail");
    assert(!unknown.accepted);
    return 0;
}
