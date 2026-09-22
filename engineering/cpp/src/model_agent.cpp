#include "jarvis/engineering/model_agent.hpp"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <utility>

namespace jarvis::engineering {

namespace {

std::uint64_t fnv1a(std::string_view value) noexcept {
    std::uint64_t hash = 14695981039346656037ULL;
    for (const unsigned char byte : value) {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
    return hash;
}

} // namespace

ModelBackedEngineeringAgent::ModelBackedEngineeringAgent(
    AgentDescriptor descriptor,
    EngineeringModelProvider& provider,
    EngineeringWorkspace& workspace) noexcept
    : descriptor_(std::move(descriptor)),
      provider_(provider),
      workspace_(workspace) {}

AgentDescriptor ModelBackedEngineeringAgent::descriptor() const {
    return descriptor_;
}

bool ModelBackedEngineeringAgent::safe_relative_path(std::string_view path) noexcept {
    if (path.empty() || path.front() == '/' || path.front() == '\\') {
        return false;
    }
    if (path.find(':') != std::string_view::npos) {
        return false;
    }

    std::size_t start = 0;
    while (start < path.size()) {
        const std::size_t end = path.find_first_of("/\\", start);
        const auto part = path.substr(start, end == std::string_view::npos ? path.size() - start
                                                                            : end - start);
        if (part.empty() || part == "." || part == "..") {
            return false;
        }
        if (end == std::string_view::npos) {
            break;
        }
        start = end + 1;
    }
    return true;
}

std::string ModelBackedEngineeringAgent::digest(std::string_view content) {
    return std::to_string(fnv1a(content));
}

std::size_t ModelBackedEngineeringAgent::response_bytes(const ModelResponse& response) noexcept {
    std::size_t total = response.output.size();
    for (const auto& change : response.file_changes) {
        if (change.path.size() > std::numeric_limits<std::size_t>::max() - change.content.size()) {
            return std::numeric_limits<std::size_t>::max();
        }
        const std::size_t change_bytes = change.path.size() + change.content.size();
        if (total > std::numeric_limits<std::size_t>::max() - change_bytes) {
            return std::numeric_limits<std::size_t>::max();
        }
        total += change_bytes;
    }
    return total;
}

ModelBackedEngineeringAgent::ModelBackedEngineeringAgent(
    ModelBackedEngineeringAgent&&) noexcept = default;

AgentResult ModelBackedEngineeringAgent::execute(const EngineeringTask& task) {
    const auto model = provider_.descriptor();
    if (!valid_model_descriptor(model) || !valid_task(task)) {
        return {false, descriptor_.id, task.id, "invalid model, agent, or task", {}, {}};
    }

    std::string context = "engineering task: " + task.id +
        (task.workspace_id.empty() ? std::string{} : " workspace: " + task.workspace_id);
    for (const auto& artifact : task.prior_stage_artifacts) {
        context += "\nprior.artifact=" + artifact.type + "|" + artifact.location + "|" + artifact.digest;
    }
    for (const auto& evidence : task.prior_stage_evidence) {
        context += "\nprior.evidence=" + evidence.kind + "|" + evidence.value;
    }
    for (const auto& message : task.incoming_messages) {
        context += "\nincoming.message=" + message.sender_id + "|" +
                   message.correlation_id + "|" + message.payload;
    }
    if (task.communication != nullptr) {
        for (const auto& message : task.communication->drain()) {
            context += "\nincoming.message=" + message.sender_id + "|" +
                       message.correlation_id + "|" + message.payload;
        }
        for (const auto& target : task.communication_targets) {
            task.communication->send(
                "task-" + task.id + "-started-" + target,
                target,
                task.id,
                AgentMessageType::status,
                "task started");
        }
    }

    ModelRequest request{
        task.objective,
        std::move(context),
        task.expected_artifacts,
        1024 * 1024
    };
    if (!valid_model_request(request)) {
        return {false, descriptor_.id, task.id, "invalid model request", {}, {}};
    }

    const auto response = provider_.generate(request);
    if (response.status != ModelProviderStatus::succeeded) {
        if (task.communication != nullptr) {
            for (const auto& target : task.communication_targets) {
                task.communication->send(
                    "task-" + task.id + "-failed-" + target,
                    target,
                    task.id,
                    AgentMessageType::error,
                    response.reason.empty() ? "model generation failed" : response.reason);
            }
        }
        return {false, descriptor_.id, task.id,
                response.reason.empty() ? "model generation failed" : response.reason,
                {}, response.evidence};
    }
    if (response_bytes(response) > request.maximum_output_bytes) {
        return {false, descriptor_.id, task.id, "model output limit exceeded", {}, response.evidence};
    }

    const bool owns_workspace = task.manage_workspace;
    const std::string workspace_id = task.workspace_id.empty()
        ? "engineering-" + task.id
        : task.workspace_id;

    if (owns_workspace) {
        const auto opened = workspace_.open(workspace_id, "agent/" + task.id);
        if (!opened.accepted) {
            return {false, descriptor_.id, task.id, opened.reason, opened.artifacts, response.evidence};
        }
    }

    std::vector<AgentArtifact> artifacts;
    for (const auto& change : response.file_changes) {
        if (!safe_relative_path(change.path)) {
            if (owns_workspace) workspace_.close(workspace_id);
            return {false, descriptor_.id, task.id, "unsafe model file path", artifacts, response.evidence};
        }
        const auto written = workspace_.write_file(
            workspace_id, change.path, change.content, digest(change.content));
        if (!written.accepted) {
            if (owns_workspace) workspace_.close(workspace_id);
            return {false, descriptor_.id, task.id, written.reason, artifacts, response.evidence};
        }
        artifacts.insert(artifacts.end(), written.artifacts.begin(), written.artifacts.end());
    }

    if (response.file_changes.empty()) {
        if (owns_workspace) workspace_.close(workspace_id);
        return {false, descriptor_.id, task.id, "model produced no file changes", artifacts, response.evidence};
    }

    if (owns_workspace) {
        const auto committed = workspace_.commit(workspace_id, "engineering: " + task.objective);
        if (!committed.accepted) {
            workspace_.close(workspace_id);
            return {false, descriptor_.id, task.id, committed.reason, artifacts, response.evidence};
        }
        artifacts.insert(artifacts.end(), committed.artifacts.begin(), committed.artifacts.end());

        if (!workspace_.close(workspace_id)) {
            return {false, descriptor_.id, task.id, "workspace close failed", artifacts, response.evidence};
        }
    }

    if (task.communication != nullptr) {
        for (const auto& target : task.communication_targets) {
            task.communication->send(
                "task-" + task.id + "-completed-" + target,
                target,
                task.id,
                AgentMessageType::result,
                "task completed with " + std::to_string(artifacts.size()) + " artifacts");
        }
    }

    auto evidence = response.evidence;
    evidence.push_back({"model.provider", model.provider});
    evidence.push_back({"model.id", model.id});
    evidence.push_back({"model.model", model.model});
    if (!task.workspace_id.empty()) {
        evidence.push_back({"workspace.id", task.workspace_id});
    }
    return {true, descriptor_.id, task.id, "model-backed engineering task completed",
            artifacts, evidence};
}

} // namespace jarvis::engineering
