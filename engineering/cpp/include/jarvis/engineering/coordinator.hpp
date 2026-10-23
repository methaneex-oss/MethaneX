#pragma once
#include "agent.hpp"
#include "execution.hpp"
#include <cstdint>
#include <vector>
namespace jarvis::engineering {
class EngineeringTaskLedger;
struct AgentCandidate { AgentDescriptor agent; double score{0.0}; bool eligible{false}; };
class EngineeringCoordinator {
public:
 std::vector<AgentCandidate> discover(const EngineeringTask&, const std::vector<AgentDescriptor>&) const;
 std::vector<AgentCandidate> rank(const EngineeringTask&, const std::vector<AgentDescriptor>&) const;
 AgentResult dispatch(const EngineeringTask&, EngineeringAgent&, const EngineeringAuthorizer&, EngineeringExecutionBoundary&) const;
 AgentResult dispatch_tracked(const std::string& task_id, EngineeringAgent&,
     const EngineeringAuthorizer&, EngineeringExecutionBoundary&, EngineeringTaskLedger&,
     std::uint64_t expected_version, const std::string& base_revision) const;
private:
 static int risk_rank(AgentRisk) noexcept;
 static bool satisfies_permissions(const AgentDescriptor&, const EngineeringTask&) noexcept;
 static bool satisfies_artifacts(const AgentDescriptor&, const EngineeringTask&) noexcept;
};
} // namespace jarvis::engineering
