#pragma once

#include "agent.hpp"
#include "execution.hpp"

#include <vector>

namespace jarvis::engineering {

struct AgentCandidate {
    AgentDescriptor agent;
    double score{0.0};
    bool eligible{false};
};

class EngineeringCoordinator {
public:
    std::vector<AgentCandidate> discover(
        const EngineeringTask& task,
        const std::vector<AgentDescriptor>& agents) const;

    std::vector<AgentCandidate> rank(
        const EngineeringTask& task,
        const std::vector<AgentDescriptor>& agents) const;

    AgentResult dispatch(
        const EngineeringTask& task,
        EngineeringAgent& agent,
        const EngineeringAuthorizer& authorizer,
        EngineeringExecutionBoundary& boundary) const;

    AgentResult dispatch_selected(
        const EngineeringTask& task,
        const std::vector<EngineeringAgent*>& agents,
        const EngineeringAuthorizer& authorizer,
        EngineeringExecutionBoundary& boundary) const;

private:
    static int risk_rank(AgentRisk risk) noexcept;
    static bool satisfies_permissions(
        const AgentDescriptor& agent,
        const EngineeringTask& task) noexcept;
    static bool satisfies_artifacts(
        const AgentDescriptor& agent,
        const EngineeringTask& task) noexcept;
};

} // namespace jarvis::engineering
