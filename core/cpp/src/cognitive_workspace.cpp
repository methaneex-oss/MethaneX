#include "jarvis/core/cognitive_workspace.hpp"

namespace jarvis::core {

CognitiveWorkspace CognitiveWorkspaceStore::snapshot() const {
    std::lock_guard lock(mutex_);
    return workspace_;
}

void CognitiveWorkspaceStore::replace(CognitiveWorkspace workspace) {
    std::lock_guard lock(mutex_);
    workspace_ = std::move(workspace);
}

void CognitiveWorkspaceStore::clear() {
    std::lock_guard lock(mutex_);
    workspace_ = {};
}

} // namespace jarvis::core
