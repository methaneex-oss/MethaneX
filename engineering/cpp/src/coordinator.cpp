#include "jarvis/engineering/coordinator.hpp"

#include <algorithm>

namespace jarvis::engineering {

namespace {

bool contains_all(const std::vector<std::string>& available,
                  const std::vector<std::string>& required) noexcept {
    return std::all_of(required.begin(), required.end(), [&](const std::string& item) {
        return !item.empty() &&
               std::find(available.begin(), available.end(), item) != available.end();
    });
}

} // namespace

int EngineeringCoordinator::risk_rank(AgentRisk risk) noexcept {
    return static_cast<int>(risk);
}

bool EngineeringCoordinator::satisfies_permissions(
    const AgentDescriptor& agent, const EngineeringTask& task) noexcept {
    return contains_all(agent.permissions, task.required_permissions);
}

bool EngineeringCoordinator::satisfies_artifacts(
    const AgentDescriptor& agent, const EngineeringTask& task) noexcept {
    return contains_all(agent.input_artifacts, task.input_artifacts) &&
           contains_all(agent.output_artifacts, task.expected_artifacts);
}

std::vector<AgentCandidate> EngineeringCoordinator::discover(
    const EngineeringTask& task,
    const std::vector<AgentDescriptor>& agents) const {
    std::vector<AgentCandidate> result;
    if (!valid_task(task)) return result;

    result.reserve(agents.size());
    for (const auto& agent : agents) {
        const bool valid = valid_descriptor(agent);
        const bool eligible =
            valid &&
            contains_all(agent.capabilities, task.required_capabilities) &&
            satisfies_permissions(agent, task) &&
            satisfies_artifacts(agent, task) &&
            agent.availability != AgentAvailability::unavailable &&
            risk_rank(agent.risk) <= risk_rank(task.maximum_risk) &&
            agent.estimated_cost <= task.maximum_cost;
        result.push_back({agent, 0.0, eligible});
    }
    return result;
}

std::vector<AgentCandidate> EngineeringCoordinator::rank(
    const EngineeringTask& task,
    const std::vector<AgentDescriptor>& agents) const {
    auto result = discover(task, agents);
    for (auto& candidate : result) {
        if (!candidate.eligible) continue;
        const double availability =
            candidate.agent.availability == AgentAvailability::available ? 1.0 : 0.5;
        candidate.score =
            candidate.agent.reliability * availability /
            (1.0 + candidate.agent.estimated_cost);
    }

    std::stable_sort(result.begin(), result.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.eligible != rhs.eligible) return lhs.eligible > rhs.eligible;
        if (lhs.score != rhs.score) return lhs.score > rhs.score;
        return lhs.agent.id < rhs.agent.id;
    });
    return result;
}

AgentResult EngineeringCoordinator::dispatch(
    const EngineeringTask& task,
    EngineeringAgent& agent,
    const EngineeringAuthorizer& authorizer,
    EngineeringExecutionBoundary& boundary) const {
    const auto descriptor = agent.descriptor();
    if (!valid_task(task) || !valid_descriptor(descriptor)) {
        return {false, descriptor.id, task.id, "invalid task or agent descriptor", {}, {}};
    }

    const auto candidates = discover(task, {descriptor});
    if (candidates.empty() || !candidates.front().eligible) {
        return {false, descriptor.id, task.id, "agent is not eligible for task", {}, {}};
    }

    if (!authorizer.authorize(task, descriptor)) {
        return {false, descriptor.id, task.id, "execution authorization denied", {}, {}};
    }

    auto result = boundary.run(task, agent);
    if (result.agent_id.empty()) result.agent_id = descriptor.id;
    if (result.task_id.empty()) result.task_id = task.id;
    return result;
}

AgentResult EngineeringCoordinator::dispatch_selected(
    const EngineeringTask& task,
    const std::vector<EngineeringAgent*>& agents,
    const EngineeringAuthorizer& authorizer,
    EngineeringExecutionBoundary& boundary) const {
    if (!valid_task(task)) {
        return {false, {}, task.id, "invalid engineering task", {}, {}};
    }

    std::vector<EngineeringAgent*> valid_agents;
    std::vector<AgentDescriptor> descriptors;
    valid_agents.reserve(agents.size());
    descriptors.reserve(agents.size());
    for (auto* agent : agents) {
        if (agent != nullptr && valid_descriptor(agent->descriptor())) {
            valid_agents.push_back(agent);
            descriptors.push_back(agent->descriptor());
        }
    }

    for (const auto& candidate : rank(task, descriptors)) {
        if (!candidate.eligible) continue;
        const auto selected = std::find_if(
            valid_agents.begin(), valid_agents.end(), [&](auto* agent) {
                return agent->descriptor().id == candidate.agent.id;
            });
        if (selected != valid_agents.end()) {
            return dispatch(task, **selected, authorizer, boundary);
        }
    }

    return {false, {}, task.id, "no eligible engineering agent", {}, {}};
}

AgentDispatchPlan EngineeringCoordinator::dispatch_sequence(
    EngineeringTask task,
    const std::vector<EngineeringAgent*>& agents,
    const EngineeringAuthorizer& authorizer,
    EngineeringExecutionBoundary& boundary) const {
    AgentDispatchPlan plan;
    if (!valid_task(task)) {
        plan.reason = "invalid engineering task";
        return plan;
    }

    std::vector<AgentDescriptor> descriptors;
    descriptors.reserve(agents.size());
    for (auto* agent : agents) {
        if (agent != nullptr && valid_descriptor(agent->descriptor())) {
            descriptors.push_back(agent->descriptor());
        }
    }
    plan.candidates = rank(task, descriptors);

    for (const auto& candidate : plan.candidates) {
        if (!candidate.eligible) continue;
        const auto selected = std::find_if(
            agents.begin(), agents.end(), [&](auto* agent) {
                return agent != nullptr && agent->descriptor().id == candidate.agent.id;
            });
        if (selected == agents.end()) continue;

        auto result = dispatch(task, **selected, authorizer, boundary);
        plan.completed.push_back({candidate.agent.id, result});
        if (!result.accepted) {
            plan.reason = "agent stage failed: " + candidate.agent.id + ": " + result.reason;
            return plan;
        }

        for (const auto& artifact : result.artifacts) {
            task.input_artifacts.push_back(artifact.type);
        }
        task.prior_stage_artifacts.insert(
            task.prior_stage_artifacts.end(), result.artifacts.begin(), result.artifacts.end());
        task.prior_stage_evidence.insert(
            task.prior_stage_evidence.end(), result.evidence.begin(), result.evidence.end());
    }

    plan.accepted = !plan.completed.empty();
    plan.reason = plan.accepted ? "agent sequence completed" : "no eligible agent stage";
    return plan;
}

} // namespace jarvis::engineering
