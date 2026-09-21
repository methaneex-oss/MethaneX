#pragma once

#include "agent.hpp"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace jarvis::engineering {

struct WorkspaceResult {
    bool accepted{false};
    std::string workspace_id;
    std::string reason;
    std::vector<AgentArtifact> artifacts;
};

class EngineeringWorkspace {
public:
    virtual ~EngineeringWorkspace() = default;
    virtual WorkspaceResult open(std::string_view workspace_id,
                                 std::string_view branch) = 0;
    virtual WorkspaceResult record_file(std::string_view workspace_id,
                                        std::string_view path,
                                        std::string_view digest) = 0;
    virtual WorkspaceResult commit(std::string_view workspace_id,
                                   std::string_view message) = 0;
    virtual bool close(std::string_view workspace_id) = 0;
};

class InMemoryEngineeringWorkspace final : public EngineeringWorkspace {
public:
    WorkspaceResult open(std::string_view workspace_id,
                         std::string_view branch) override;
    WorkspaceResult record_file(std::string_view workspace_id,
                                std::string_view path,
                                std::string_view digest) override;
    WorkspaceResult commit(std::string_view workspace_id,
                           std::string_view message) override;
    bool close(std::string_view workspace_id) override;

private:
    struct WorkspaceState {
        std::string branch;
        std::vector<AgentArtifact> files;
        bool open{true};
    };

    std::unordered_map<std::string, WorkspaceState> workspaces_;
};

} // namespace jarvis::engineering
