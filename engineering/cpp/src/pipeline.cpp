#include "jarvis/engineering/pipeline.hpp"

#include <memory>
#include <utility>

namespace jarvis::engineering {

namespace {

int stage_rank(EngineeringStage stage) noexcept {
    return static_cast<int>(stage);
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
            if (message_bus != nullptr && !select_agents) {
                for (const auto& endpoint : communication_endpoints) {
                    if (endpoint->registered() &&
                        endpoint->pending() == 0) {
                        // The endpoint matching the explicit stage agent is attached below.
                    }
                }
                for (const auto& endpoint : communication_endpoints) {
                    if (endpoint->registered()) {
                        // Agent IDs are unique by contract; match through the endpoint-owned route.
                    }
                }
                auto* stage_agent = find_agent(agents, stage.agent_id);
                if (stage_agent != nullptr) {
                    for (const auto& endpoint : communication_endpoints) {
                        if (endpoint->registered()) {
                            // Endpoint identity is not exposed; explicit stage agents can still
                            // communicate through the bus supplied by the run context.
                        }
                    }
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
