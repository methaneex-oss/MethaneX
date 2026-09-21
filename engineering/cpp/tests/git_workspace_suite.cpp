#include "jarvis/engineering/git_workspace.hpp"

#include <cassert>
#include <string>
#include <unordered_map>

using namespace jarvis::engineering;

namespace {

class FakeGit final : public GitWorkspaceDriver {
public:
    bool create_branch(std::string_view branch, std::string_view base_ref) override {
        created_branch = std::string(branch);
        created_base = std::string(base_ref);
        return allow_branch;
    }

    bool write_file(std::string_view branch, std::string_view path,
                    std::string_view content) override {
        recorded_branch = std::string(branch);
        recorded_path = std::string(path);
        recorded_content = std::string(content);
        files[std::string(path)] = std::string(content);
        return allow_file;
    }

    bool read_file(std::string_view branch, std::string_view path,
                   std::string& content) override {
        read_branch = std::string(branch);
        const auto it = files.find(std::string(path));
        if (it == files.end()) return false;
        content = it->second;
        return allow_read;
    }

    bool commit(std::string_view branch, std::string_view message,
                std::string& commit_id) override {
        committed_branch = std::string(branch);
        committed_message = std::string(message);
        if (!allow_commit) return false;
        commit_id = "abc123";
        return true;
    }

    bool close_branch(std::string_view branch) override {
        closed_branch = std::string(branch);
        return allow_close;
    }

    bool allow_branch{true};
    bool allow_file{true};
    bool allow_read{true};
    bool allow_commit{true};
    bool allow_close{true};
    std::string created_branch, created_base;
    std::string recorded_branch, recorded_path, recorded_content;
    std::string read_branch;
    std::string committed_branch, committed_message;
    std::string closed_branch;
    std::unordered_map<std::string, std::string> files;
};

} // namespace

int main() {
    FakeGit git;
    GitEngineeringWorkspace workspace(git);

    const auto opened = workspace.open("run-1", "agent/run-1");
    assert(opened.accepted);
    assert(git.created_branch == "agent/run-1");
    assert(git.created_base == "main");

    const auto file = workspace.write_file("run-1", "src/change.cpp", "int x = 1;", "digest-1");
    assert(file.accepted);
    assert(git.recorded_branch == "agent/run-1");
    assert(git.recorded_path == "src/change.cpp");
    assert(git.recorded_content == "int x = 1;");

    const auto read = workspace.read_file("run-1", "src/change.cpp");
    assert(read.accepted);
    assert(read.content == "int x = 1;");
    assert(git.read_branch == "agent/run-1");

    const auto metadata = workspace.record_file("run-1", "src/change.cpp", "digest-1");
    assert(metadata.accepted);

    const auto commit = workspace.commit("run-1", "agent change");
    assert(commit.accepted);
    assert(commit.artifacts.size() == 1);
    assert(commit.artifacts.front().location == "abc123");

    assert(workspace.close("run-1"));
    assert(git.closed_branch == "agent/run-1");

    FakeGit denied;
    denied.allow_file = false;
    GitEngineeringWorkspace denied_workspace(denied);
    assert(denied_workspace.open("run-2", "agent/run-2").accepted);
    assert(!denied_workspace.write_file("run-2", "src/a.cpp", "int a;", "digest").accepted);
    assert(!denied_workspace.commit("run-2", "should fail").accepted);

    FakeGit no_branch;
    no_branch.allow_branch = false;
    GitEngineeringWorkspace unavailable(no_branch);
    assert(!unavailable.open("run-3", "agent/run-3").accepted);
    return 0;
}
