#include "jarvis/engineering/coordinator.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::engineering {

namespace {

bool contains_all(const std::vector<std::string>& available,
                  const std::vector<std::string>& required) noexcept {
    return std::all_of(required.begin(), required.end(), [&](const std::string& item) {
        return std::find(available.begin(), available.end(), item) != available.end();
    });
}

} // namespace

int EngineeringCoordinator::risk_rank(AgentRisk risk) noexcept {
    return static_cast<int>(risk);
}

bool EngineeringCoordinator::satisfies_permissions(
    const AgentDescriptor& agent,
    const EngineeringTask& task) noexcept {
    return contains_all(agent.permissions, task.required_permissions);
}

bool EngineeringCoordinator::satisfies_artifacts(
    const AgentDescriptor& agent,
    const EngineeringTask& task) noexcept {
    return contains_all(agent.input_artifacts, task.input_artifacts) &&
           contains_all(agent.output_artifacts, task.expected_artifacts);
}

std::vector<AgentCandidate> EngineeringCoordinator::discover(
    const EngineeringTask& task,
    const std::vector<AgentDescriptor>& agents) const {
    std::vector<AgentCandidate> result;
    if (!valid_task(task)) return result;

    for (const auto& agent : agents) {
        const bool capabilities = contains_all(agent.capabilities, task.required_capabilities);
        const bool permissions = satisfies_permissions(agent, task);
        const bool artifacts = satisfies_artifacts(agent, task);
        const bool availability = agent.availability != AgentAvailability::unavailable;
        const bool risk = risk_rank(agent.risk) <= risk_rank(task.maximum_risk);
        const bool cost = agent.estimated_cost <= task.maximum_cost;
        result.push_back(AgentCandidate{agent, 0.0,
                                        capabilities && permissions && artifacts &&
                                        availability && risk && cost});
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
        candidate.score = candidate.agent.reliability * availability /
                          (1.0 + candidate.agent.estimated_cost);
    }
    std::stable_sort(result.begin(), result.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.eligible != rhs.eligible) return lhs.eligible > rhs.eligible;
        return lhs.score > rhs.score;
    });
    return result;
}

AgentResult EngineeringCoordinator::dispatch(
    const EngineeringTask& task,
    EngineeringAgent& agent) const {
    const auto descriptor = agent.descriptor();
    if (!valid_task(task) || !valid_descriptor(descriptor)) {
        return AgentResult{false, descriptor.id, task.id, "invalid task or agent descriptor", {}, {}};
    }

    const auto candidates = discover(task, {descriptor});
    if (candidates.empty() || !candidates.front().eligible) {
        return AgentResult{false, descriptor.id, task.id, "agent is not eligible for task", {}, {}};
    }

    return agent.execute(task);
}

} // namespace jarvis::engineering
