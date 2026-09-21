#include "jarvis/engineering/model_assessment_agent.hpp"

#include <algorithm>
#include <limits>
#include <string>
#include <string_view>
#include <utility>

namespace jarvis::engineering {

ModelAssessmentAgent::ModelAssessmentAgent(
    AgentDescriptor descriptor,
    EngineeringModelProvider& provider,
    EngineeringWorkspace& workspace) noexcept
    : descriptor_(std::move(descriptor)), provider_(provider), workspace_(workspace) {}

AgentDescriptor ModelAssessmentAgent::descriptor() const {
    return descriptor_;
}

std::size_t ModelAssessmentAgent::context_bytes(const std::string& context) noexcept {
    return context.size();
}

bool ModelAssessmentAgent::safe_relative_path(std::string_view path) noexcept {
    if (path.empty() || path.front() == '/' || path.front() == '\\' ||
        path.find(':') != std::string_view::npos) {
        return false;
    }
    std::size_t start = 0;
    while (start < path.size()) {
        const auto end = path.find_first_of("/\\", start);
        const auto part = path.substr(start, end == std::string_view::npos
                                             ? path.size() - start
                                             : end - start);
        if (part.empty() || part == "." || part == "..") return false;
        if (end == std::string_view::npos) break;
        start = end + 1;
    }
    return true;
}

AgentResult ModelAssessmentAgent::execute(const EngineeringTask& task) {
    const auto model = provider_.descriptor();
    if (!valid_model_descriptor(model) || !valid_task(task)) {
        return {false, descriptor_.id, task.id, "invalid model, agent, or task", {}, {}};
    }
    if (task.workspace_id.empty() || task.workspace_files.empty()) {
        return {false, descriptor_.id, task.id,
                "assessment requires a workspace and explicit files", {}, {}};
    }

    std::string context = "workspace: " + task.workspace_id + "\n";
    constexpr std::size_t max_context = 1024 * 1024;

    for (const auto& path : task.workspace_files) {
        if (!safe_relative_path(path)) {
            return {false, descriptor_.id, task.id, "unsafe workspace file path", {}, {}};
        }
        const auto file = workspace_.read_file(task.workspace_id, path);
        if (!file.accepted) {
            return {false, descriptor_.id, task.id,
                    file.reason.empty() ? "workspace file read failed" : file.reason,
                    {}, {}};
        }
        const std::string header = "\n--- " + path + " ---\n";
        if (context.size() > max_context - header.size() ||
            context.size() + header.size() > max_context - file.content.size()) {
            return {false, descriptor_.id, task.id, "assessment context limit exceeded", {}, {}};
        }
        context += header;
        context += file.content;
    }

    ModelRequest request{
        task.objective,
        std::move(context),
        task.expected_artifacts,
        max_context
    };
    if (!valid_model_request(request) || context_bytes(request.context) > max_context) {
        return {false, descriptor_.id, task.id, "invalid assessment request", {}, {}};
    }

    const auto response = provider_.generate(request);
    if (response.status != ModelProviderStatus::succeeded) {
        return {false, descriptor_.id, task.id,
                response.reason.empty() ? "model assessment failed" : response.reason,
                {}, response.evidence};
    }
    if (!response.file_changes.empty()) {
        return {false, descriptor_.id, task.id,
                "assessment provider attempted workspace mutation", {}, response.evidence};
    }
    if (response.output.empty()) {
        return {false, descriptor_.id, task.id, "assessment produced no evidence", {}, {}};
    }

    auto evidence = response.evidence;
    evidence.push_back({"assessment.output", response.output});
    evidence.push_back({"assessment.model", model.id});
    evidence.push_back({"assessment.provider", model.provider});

    return {true, descriptor_.id, task.id,
            "engineering assessment completed", {}, std::move(evidence)};
}

} // namespace jarvis::engineering
