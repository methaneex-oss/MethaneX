#include "jarvis/engineering/coordinator.hpp"
#include "jarvis/engineering/task_ledger.hpp"
#include <exception>
#include <algorithm>
namespace jarvis::engineering {
namespace { bool all(const std::vector<std::string>& a,const std::vector<std::string>& r){return std::all_of(r.begin(),r.end(),[&](const auto& x){return std::find(a.begin(),a.end(),x)!=a.end();});} }
int EngineeringCoordinator::risk_rank(AgentRisk r) noexcept{return static_cast<int>(r);}
bool EngineeringCoordinator::satisfies_permissions(const AgentDescriptor& a,const EngineeringTask& t) noexcept{return all(a.permissions,t.required_permissions);}
bool EngineeringCoordinator::satisfies_artifacts(const AgentDescriptor& a,const EngineeringTask& t) noexcept{return all(a.input_artifacts,t.input_artifacts)&&all(a.output_artifacts,t.expected_artifacts);}
std::vector<AgentCandidate> EngineeringCoordinator::discover(const EngineeringTask& t,const std::vector<AgentDescriptor>& agents) const { std::vector<AgentCandidate> out; if(!valid_task(t)) return out; for(const auto& a:agents){const bool v=valid_descriptor(a); const bool e=v&&all(a.capabilities,t.required_capabilities)&&satisfies_permissions(a,t)&&satisfies_artifacts(a,t)&&a.availability!=AgentAvailability::unavailable&&risk_rank(a.risk)<=risk_rank(t.maximum_risk)&&a.estimated_cost<=t.maximum_cost; out.push_back({a,0.0,e});} return out; }
std::vector<AgentCandidate> EngineeringCoordinator::rank(const EngineeringTask& t,const std::vector<AgentDescriptor>& agents) const {auto out=discover(t,agents); for(auto& c:out) if(c.eligible) c.score=c.agent.reliability*(c.agent.availability==AgentAvailability::available?1.0:0.5)/(1.0+c.agent.estimated_cost); std::stable_sort(out.begin(),out.end(),[](const auto&a,const auto&b){if(a.eligible!=b.eligible)return a.eligible>b.eligible;return a.score>b.score;}); return out;}
AgentResult EngineeringCoordinator::dispatch(const EngineeringTask& t,EngineeringAgent& agent,const EngineeringAuthorizer& auth,EngineeringExecutionBoundary& boundary) const {const auto d=agent.descriptor(); if(!valid_task(t)||!valid_descriptor(d)) return {false,d.id,t.id,"invalid task or agent descriptor",{}, {}}; auto c=discover(t,{d}); if(c.empty()||!c.front().eligible) return {false,d.id,t.id,"agent is not eligible for task",{}, {}}; if(!auth.authorize(t,d)) return {false,d.id,t.id,"execution authorization denied",{}, {}}; auto r=boundary.run(t,agent); if(r.agent_id.empty())r.agent_id=d.id; if(r.task_id.empty())r.task_id=t.id; return r;}

AgentResult EngineeringCoordinator::dispatch_tracked(
    const std::string& task_id, EngineeringAgent& agent,
    const EngineeringAuthorizer& auth, EngineeringExecutionBoundary& boundary,
    EngineeringTaskLedger& ledger, std::uint64_t expected_version,
    const std::string& base_revision) const {
    const auto stored = ledger.get(task_id);
    const auto descriptor = agent.descriptor();
    if (!stored || stored->version != expected_version ||
        stored->status != EngineeringTaskStatus::queued)
        return {false, descriptor.id, task_id, "task is missing, stale, or not queued", {}, {}};

    const auto task = stored->task; // Durable task definition is authoritative.
    if (!valid_task(task) || !valid_descriptor(descriptor))
        return {false, descriptor.id, task.id, "invalid task or agent descriptor", {}, {}};
    const auto candidates = discover(task, {descriptor});
    if (candidates.empty() || !candidates.front().eligible)
        return {false, descriptor.id, task.id, "agent is not eligible for task", {}, {}};
    if (!auth.authorize(task, descriptor))
        return {false, descriptor.id, task.id, "execution authorization denied", {}, {}};
    if (!ledger.claim(task_id, expected_version, descriptor.id, base_revision))
        return {false, descriptor.id, task.id, "task claim lost a concurrency race", {}, {}};

    const auto claimed_version = expected_version + 1;
    if (!ledger.start(task_id, claimed_version, descriptor.id)) {
        ledger.fail(task_id, claimed_version, descriptor.id, "could not enter running state");
        return {false, descriptor.id, task.id, "task start transition failed", {}, {}};
    }
    const auto running_version = claimed_version + 1;
    AgentResult result;
    try {
        result = boundary.run(task, agent);
    } catch (const std::exception& error) {
        const std::string detail = std::string("agent execution threw: ") + error.what();
        if (!ledger.fail(task_id, running_version, descriptor.id, detail))
            return {false, descriptor.id, task.id, detail + "; failure was not durably recorded", {}, {}};
        return {false, descriptor.id, task.id, detail, {}, {}};
    } catch (...) {
        const std::string detail = "agent execution threw a non-standard exception";
        if (!ledger.fail(task_id, running_version, descriptor.id, detail))
            return {false, descriptor.id, task.id, detail + "; failure was not durably recorded", {}, {}};
        return {false, descriptor.id, task.id, detail, {}, {}};
    }
    if (result.agent_id.empty()) result.agent_id = descriptor.id;
    if (result.task_id.empty()) result.task_id = task.id;
    if (result.agent_id != descriptor.id || result.task_id != task.id) {
        const std::string detail = "agent result identity did not match dispatched task";
        ledger.fail(task_id, running_version, descriptor.id, detail, result.evidence);
        return {false, descriptor.id, task.id, detail, result.artifacts, result.evidence};
    }
    if (result.accepted) {
        if (!ledger.complete(task_id, running_version, descriptor.id, result.revision,
                             result.evidence, result.reason)) {
            result.accepted = false;
            result.reason = "execution returned but completion was not durably recorded; reconcile before retrying";
            result.evidence.push_back({"ledger", "completion persistence failed"});
        }
    } else if (!ledger.fail(task_id, running_version, descriptor.id, result.reason,
                            result.evidence)) {
        result.reason += "; failure was not durably recorded";
        result.evidence.push_back({"ledger", "failure persistence failed"});
    }
    return result;
}
} // namespace jarvis::engineering
