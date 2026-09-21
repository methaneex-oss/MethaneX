#include "jarvis/engineering/pipeline.hpp"

namespace jarvis::engineering {

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
    EngineeringExecutionBoundary& boundary) const {
    EngineeringRunResult run_result;
    run_result.run_id = std::move(run_id);

    if (run_result.run_id.empty() || stages.empty()) {
        run_result.reason = "invalid engineering run";
        return run_result;
    }

    EngineeringCoordinator coordinator;
    for (const auto& stage : stages) {
        if (!valid_task(stage.task) || stage.agent_id.empty()) {
            run_result.reason = "invalid engineering stage";
            return run_result;
        }

        auto* agent = find_agent(agents, stage.agent_id);
        if (agent == nullptr) {
            run_result.reason = "engineering agent not found";
            return run_result;
        }

        auto result = coordinator.dispatch(stage.task, *agent, authorizer, boundary);
        run_result.stages.push_back(EngineeringStageResult{stage.stage, result});

        if (!result.accepted) {
            run_result.status = EngineeringRunStatus::failed;
            run_result.reason = result.reason.empty() ? "engineering stage failed" : result.reason;
            return run_result;
        }
    }

    run_result.status = EngineeringRunStatus::completed;
    run_result.reason = "engineering pipeline completed";
    return run_result;
}

} // namespace jarvis::engineering
