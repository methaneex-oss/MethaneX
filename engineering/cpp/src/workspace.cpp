#include "jarvis/engineering/workspace.hpp"

namespace jarvis::engineering {

WorkspaceResult InMemoryEngineeringWorkspace::open(std::string_view workspace_id,
                                                   std::string_view branch) {
    if (workspace_id.empty() || branch.empty() || workspaces_.contains(std::string(workspace_id))) {
        return {false, std::string(workspace_id), "invalid or duplicate workspace", {}};
    }
    workspaces_.emplace(std::string(workspace_id), WorkspaceState{std::string(branch), {}, true});
    return {true, std::string(workspace_id), {}, {}};
}

WorkspaceResult InMemoryEngineeringWorkspace::write_file(std::string_view workspace_id,
                                                         std::string_view path,
                                                         std::string_view content,
                                                         std::string_view digest) {
    if (content.empty()) {
        return {false, std::string(workspace_id), "empty file content", {}};
    }
    return record_file(workspace_id, path, digest);
}

WorkspaceResult InMemoryEngineeringWorkspace::record_file(std::string_view workspace_id,
                                                          std::string_view path,
                                                          std::string_view digest) {
    const auto it = workspaces_.find(std::string(workspace_id));
    if (it == workspaces_.end() || !it->second.open || path.empty() || digest.empty()) {
        return {false, std::string(workspace_id), "workspace unavailable or invalid file", {}};
    }
    it->second.files.push_back(AgentArtifact{"workspace.file", std::string(path), std::string(digest)});
    return {true, std::string(workspace_id), {}, {it->second.files.back()}};
}

WorkspaceResult InMemoryEngineeringWorkspace::commit(std::string_view workspace_id,
                                                     std::string_view message) {
    const auto it = workspaces_.find(std::string(workspace_id));
    if (it == workspaces_.end() || !it->second.open || message.empty() || it->second.files.empty()) {
        return {false, std::string(workspace_id), "workspace unavailable or nothing to commit", {}};
    }
    return {true, std::string(workspace_id), {},
            {AgentArtifact{"git.commit", it->second.branch, std::string(message)}}};
}

bool InMemoryEngineeringWorkspace::close(std::string_view workspace_id) {
    const auto it = workspaces_.find(std::string(workspace_id));
    if (it == workspaces_.end() || !it->second.open) return false;
    it->second.open = false;
    return true;
}

} // namespace jarvis::engineering
