#pragma once
#include "agent.hpp"
#include "execution.hpp"
#include <vector>
namespace jarvis::engineering {
struct AgentCandidate { AgentDescriptor agent; double score{0.0}; bool eligible{false}; };
class EngineeringCoordinator {
public:
 std::vector<AgentCandidate> discover(const EngineeringTask&, const std::vector<AgentDescriptor>&) const;
 std::vector<AgentCandidate> rank(const EngineeringTask&, const std::vector<AgentDescriptor>&) const;
 AgentResult dispatch(const EngineeringTask&, EngineeringAgent&, const EngineeringAuthorizer&, EngineeringExecutionBoundary&) const;
private:
 static int risk_rank(AgentRisk) noexcept;
 static bool satisfies_permissions(const AgentDescriptor&, const EngineeringTask&) noexcept;
 static bool satisfies_artifacts(const AgentDescriptor&, const EngineeringTask&) noexcept;
};
} // namespace jarvis::engineering
