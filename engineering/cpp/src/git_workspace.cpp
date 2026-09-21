#include "jarvis/engineering/git_workspace.hpp"

namespace jarvis::engineering {

WorkspaceResult GitEngineeringWorkspace::open(std::string_view workspace_id,
                                              std::string_view branch) {
    if (workspace_id.empty() || branch.empty() || workspaces_.contains(std::string(workspace_id))) {
        return {false, std::string(workspace_id), "invalid or duplicate workspace", {}};
    }
    if (!driver_.create_branch(branch, "main")) {
        return {false, std::string(workspace_id), "git branch creation failed", {}};
    }
    workspaces_.emplace(std::string(workspace_id), State{std::string(branch), true, false});
    return {true, std::string(workspace_id), {}, {}};
}

WorkspaceResult GitEngineeringWorkspace::record_file(std::string_view workspace_id,
                                                     std::string_view path,
                                                     std::string_view digest) {
    const auto it = workspaces_.find(std::string(workspace_id));
    if (it == workspaces_.end() || !it->second.open || path.empty() || digest.empty()) {
        return {false, std::string(workspace_id), "workspace unavailable or invalid file", {}};
    }
    if (!driver_.record_file(it->second.branch, path, digest)) {
        return {false, std::string(workspace_id), "git file update failed", {}};
    }
    it->second.has_changes = true;
    return {true, std::string(workspace_id), {},
            {AgentArtifact{"workspace.file", std::string(path), std::string(digest)}}};
}

WorkspaceResult GitEngineeringWorkspace::commit(std::string_view workspace_id,
                                                std::string_view message) {
    const auto it = workspaces_.find(std::string(workspace_id));
    if (it == workspaces_.end() || !it->second.open || message.empty() || !it->second.has_changes) {
        return {false, std::string(workspace_id), "workspace unavailable or nothing to commit", {}};
    }
    std::string commit_id;
    if (!driver_.commit(it->second.branch, message, commit_id) || commit_id.empty()) {
        return {false, std::string(workspace_id), "git commit failed", {}};
    }
    it->second.has_changes = false;
    return {true, std::string(workspace_id), {},
            {AgentArtifact{"git.commit", commit_id, commit_id}}};
}

bool GitEngineeringWorkspace::close(std::string_view workspace_id) {
    const auto it = workspaces_.find(std::string(workspace_id));
    if (it == workspaces_.end() || !it->second.open) return false;
    if (!driver_.close_branch(it->second.branch)) return false;
    it->second.open = false;
    return true;
}

} // namespace jarvis::engineering
