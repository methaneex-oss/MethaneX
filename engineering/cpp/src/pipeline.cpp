#include "jarvis/engineering/pipeline.hpp"

#include <memory>
#include <utility>

namespace jarvis::engineering {

namespace {

int stage_rank(EngineeringStage stage) noexcept {
    return static_cast<int>(stage);
}

std::string stage_name(EngineeringStage stage) {
    switch (stage) {
    case EngineeringStage::implementation: return "implementation";
    case EngineeringStage::review: return "review";
    case EngineeringStage::verification: return "verification";
    }
    return "unknown";
}

} // namespace

EngineeringAgent* EngineeringPipeline::find_agent(
    const std::vector<EngineeringAgent*>& agents,
    const std::string& agent_id) noexcept {
    for (auto* agent : agents) {
        if (agent != nullptr && agent->descriptor().id == agent_id) return agent;
    }
    return nullptr;
}

EngineeringRunResult EngineeringPipeline::run(
    std::string run_id,
    const std::vector<EngineeringStageTask>& stages,
    const std::vector<EngineeringAgent*>& agents,
    const EngineeringAuthorizer& authorizer,
    EngineeringExecutionBoundary& boundary,
    EngineeringWorkspace* workspace,
    bool select_agents,
    EngineeringRunPolicy policy,
    AgentMessageBus* message_bus) const {
    EngineeringRunResult run_result;
    run_result.run_id = std::move(run_id);
    run_result.context.run_id = run_result.run_id;

    if (run_result.run_id.empty() || stages.empty() || policy.max_attempts_per_stage == 0) {
        run_result.reason = "invalid engineering run";
        return run_result;
    }

    if (workspace != nullptr) {
        const std::string workspace_id = "engineering-run-" + run_result.run_id;
        if (!workspace->open(workspace_id, "engineering/" + run_result.run_id).accepted) {
            run_result.reason = "engineering workspace open failed";
            return run_result;
        }
        run_result.context.workspace_id = workspace_id;
    }

    const auto close_workspace = [&]() {
        if (workspace != nullptr) {
            workspace->close("engineering-run-" + run_result.run_id);
        }
    };

    EngineeringStage previous_stage = EngineeringStage::implementation;
    bool first_stage = true;
    EngineeringCoordinator coordinator;
    std::vector<std::unique_ptr<AgentCommunicationEndpoint>> communication_endpoints;
    if (message_bus != nullptr) {
        communication_endpoints.reserve(agents.size());
        const std::string communication_workspace = run_result.context.workspace_id;
        for (auto* agent : agents) {
            if (agent == nullptr) continue;
            communication_endpoints.push_back(std::make_unique<AgentCommunicationEndpoint>(
                *message_bus,
                agent->descriptor().id,
                run_result.run_id,
                communication_workspace));
        }
    }

    const auto endpoint_for = [&](const std::string& agent_id) -> AgentCommunicationEndpoint* {
        for (const auto& endpoint : communication_endpoints) {
            if (endpoint->registered() && endpoint->agent_id() == agent_id) {
                return endpoint.get();
            }
        }
        return nullptr;
    };

    for (const auto& stage : stages) {
        if (!valid_task(stage.task) || (!select_agents && stage.agent_id.empty())) {
            run_result.reason = "invalid engineering stage";
            close_workspace();
            return run_result;
        }

        if (!first_stage && stage_rank(stage.stage) < stage_rank(previous_stage)) {
            run_result.reason = "engineering stages out of order";
            close_workspace();
            return run_result;
        }
        previous_stage = stage.stage;
        first_stage = false;

        AgentResult result;
        bool accepted = false;
        for (std::size_t attempt = 1; attempt <= policy.max_attempts_per_stage; ++attempt) {
            auto task = stage.task;
            if (workspace != nullptr) {
                task.workspace_id = "engineering-run-" + run_result.run_id;
                task.manage_workspace = false;
            }
            task.prior_stage_artifacts = run_result.context.artifacts;
            task.prior_stage_evidence = run_result.context.evidence;

            AgentCommunicationEndpoint* endpoint = nullptr;
            if (message_bus != nullptr && !select_agents) {
                endpoint = endpoint_for(stage.agent_id);
                task.communication = endpoint;
                if (endpoint != nullptr) {
                    task.incoming_messages = endpoint->drain();
                }
            }

            if (select_agents) {
                result = coordinator.dispatch_selected(task, agents, authorizer, boundary);
            } else {
                auto* agent = find_agent(agents, stage.agent_id);
                if (agent == nullptr) {
                    result = AgentResult{false, stage.agent_id, task.id,
                                         "engineering agent not found", {}, {}};
                } else {
                    result = coordinator.dispatch(task, *agent, authorizer, boundary);
                }
            }

            run_result.artifacts.insert(
                run_result.artifacts.end(), result.artifacts.begin(), result.artifacts.end());
            run_result.stages.push_back(EngineeringStageResult{stage.stage, result, attempt});
            run_result.context.stages.push_back(EngineeringStageFeedback{
                run_result.context.stages.size(), std::to_string(static_cast<int>(stage.stage)), result});
            run_result.context.artifacts.insert(
                run_result.context.artifacts.end(), result.artifacts.begin(), result.artifacts.end());
            run_result.context.evidence.insert(
                run_result.context.evidence.end(), result.evidence.begin(), result.evidence.end());

            if (result.accepted) {
                accepted = true;
                break;
            }

            if (!policy.retry_rejected_stages || attempt == policy.max_attempts_per_stage) break;
        }

        if (!accepted) {
            run_result.status = EngineeringRunStatus::failed;
            run_result.reason = result.reason.empty() ? "engineering stage failed" : result.reason;
            close_workspace();
            return run_result;
        }

        // Publish a normalized stage result so downstream agents can communicate
        // through the same provider-neutral channel without the pipeline knowing
        // anything about their vendors or model providers.
        if (message_bus != nullptr && !select_agents) {
            const auto sender = endpoint_for(stage.agent_id);
            if (sender != nullptr) {
                for (const auto& next_stage : stages) {
                    if (&next_stage == &stage) continue;
                    if (stage_rank(next_stage.stage) <= stage_rank(stage.stage)) continue;
                    const auto recipient = endpoint_for(next_stage.agent_id);
                    if (recipient == nullptr) continue;
                    const std::string payload =
                        "stage=" + stage_name(stage.stage) +
                        ";accepted=true;task=" + result.task_id +
                        ";artifacts=" + std::to_string(result.artifacts.size()) +
                        ";evidence=" + std::to_string(result.evidence.size());
                    sender->send(
                        "stage-result-" + result.task_id + "-" + std::to_string(run_result.stages.size()),
                        recipient->agent_id(),
                        result.task_id,
                        AgentMessageType::result,
                        payload);
                    break;
                }
            }
        }
    }

    if (workspace != nullptr) {
        const auto committed = workspace->commit(
            "engineering-run-" + run_result.run_id,
            "engineering: " + run_result.run_id);
        if (!committed.accepted) {
            run_result.status = EngineeringRunStatus::failed;
            run_result.reason = committed.reason.empty() ? "engineering workspace commit failed"
                                                         : committed.reason;
            run_result.artifacts.insert(
                run_result.artifacts.end(), committed.artifacts.begin(), committed.artifacts.end());
            close_workspace();
            return run_result;
        }
        run_result.artifacts.insert(
            run_result.artifacts.end(), committed.artifacts.begin(), committed.artifacts.end());
        run_result.context.artifacts.insert(
            run_result.context.artifacts.end(), committed.artifacts.begin(), committed.artifacts.end());
    }

    close_workspace();
    run_result.status = EngineeringRunStatus::completed;
    run_result.reason = "engineering pipeline completed";
    return run_result;
}

} // namespace jarvis::engineering
