#pragma once

#include "workspace.hpp"

#include <string>
#include <string_view>

namespace jarvis::engineering {

// Provider-neutral boundary for real Git-backed workspaces. Implementations own
// authentication and transport; the engineering layer only expresses the
// operations and validates their lifecycle.
class GitWorkspaceDriver {
public:
    virtual ~GitWorkspaceDriver() = default;
    virtual bool create_branch(std::string_view branch,
                               std::string_view base_ref) = 0;
    virtual bool record_file(std::string_view branch,
                             std::string_view path,
                             std::string_view content) = 0;
    virtual bool commit(std::string_view branch,
                        std::string_view message,
                        std::string& commit_id) = 0;
    virtual bool close_branch(std::string_view branch) = 0;
};

class GitEngineeringWorkspace final : public EngineeringWorkspace {
public:
    explicit GitEngineeringWorkspace(GitWorkspaceDriver& driver) noexcept
        : driver_(driver) {}

    WorkspaceResult open(std::string_view workspace_id,
                         std::string_view branch) override;
    WorkspaceResult record_file(std::string_view workspace_id,
                                std::string_view path,
                                std::string_view digest) override;
    WorkspaceResult commit(std::string_view workspace_id,
                           std::string_view message) override;
    bool close(std::string_view workspace_id) override;

private:
    struct State {
        std::string branch;
        bool open{false};
        bool has_changes{false};
    };

    GitWorkspaceDriver& driver_;
    std::unordered_map<std::string, State> workspaces_;
};

} // namespace jarvis::engineering
