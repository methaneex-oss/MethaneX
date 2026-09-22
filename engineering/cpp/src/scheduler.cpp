#include "jarvis/engineering/scheduler.hpp"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace jarvis::engineering {

namespace {

bool contains(const std::vector<std::string>& values, const std::string& value) {
    return std::find(values.begin(), values.end(), value) != values.end();
}

EngineeringAgent* find_agent(
    const std::vector<EngineeringAgent*>& agents,
    const std::string& id) noexcept {
    for (auto* agent : agents) {
        if (agent != nullptr && agent->descriptor().id == id) return agent;
    }
    return nullptr;
}

} // namespace

bool EngineeringScheduler::disjoint_workspace_files(
    const EngineeringStageTask& left,
    const EngineeringStageTask& right) noexcept {
    if (left.task.workspace_files.empty() || right.task.workspace_files.empty()) return false;
    for (const auto& file : left.task.workspace_files) {
        if (contains(right.task.workspace_files, file)) return false;
    }
    return true;
}

EngineeringSchedule EngineeringScheduler::plan(
    const std::vector<EngineeringStageTask>& stages,
    const std::vector<EngineeringAgent*>& agents) const {
    EngineeringSchedule schedule;
    if (stages.empty()) {
        schedule.reason = "no engineering stages";
        return schedule;
    }

    std::unordered_map<std::string, std::size_t> by_id;
    by_id.reserve(stages.size());
    for (std::size_t i = 0; i < stages.size(); ++i) {
        if (!valid_task(stages[i].task) || stages[i].task.id.empty()) {
            schedule.reason = "invalid engineering stage task";
            return schedule;
        }
        if (!by_id.emplace(stages[i].task.id, i).second) {
            schedule.reason = "duplicate engineering task id";
            return schedule;
        }
        std::unordered_set<std::string> seen_dependencies;
        for (const auto& dependency_id : stages[i].task.dependencies) {
            if (dependency_id.empty() || !seen_dependencies.insert(dependency_id).second) {
                schedule.reason = "invalid or duplicate engineering dependency";
                return schedule;
            }
        }
        if (!stages[i].agent_id.empty() && find_agent(agents, stages[i].agent_id) == nullptr) {
            schedule.reason = "engineering stage agent not found";
            return schedule;
        }
    }

    std::vector<std::vector<std::size_t>> dependents(stages.size());
    std::vector<std::size_t> indegree(stages.size(), 0);
    for (std::size_t i = 0; i < stages.size(); ++i) {
        for (const auto& dependency_id : stages[i].task.dependencies) {
            const auto it = by_id.find(dependency_id);
            if (it == by_id.end()) {
                schedule.reason = "engineering stage dependency not found";
                return schedule;
            }
            if (it->second == i) {
                schedule.reason = "engineering stage cannot depend on itself";
                return schedule;
            }
            dependents[it->second].push_back(i);
            ++indegree[i];
        }
    }

    std::vector<bool> scheduled(stages.size(), false);
    std::size_t remaining = stages.size();
    while (remaining > 0) {
        EngineeringScheduleWave wave;
        for (std::size_t i = 0; i < stages.size(); ++i) {
            if (!scheduled[i] && indegree[i] == 0) wave.stage_indices.push_back(i);
        }
        if (wave.stage_indices.empty()) {
            schedule.reason = "engineering stage dependency cycle detected";
            schedule.waves.clear();
            return schedule;
        }

        wave.parallel_safe = wave.stage_indices.size() > 1;
        if (wave.parallel_safe) {
            for (std::size_t a = 0; a < wave.stage_indices.size() && wave.parallel_safe; ++a) {
                const auto left = wave.stage_indices[a];
                const auto* left_agent = find_agent(agents, stages[left].agent_id);
                if (left_agent == nullptr || !left_agent->descriptor().supports_concurrency) {
                    wave.parallel_safe = false;
                    wave.reason = "one or more agents do not support concurrency";
                    break;
                }

                for (std::size_t b = a + 1; b < wave.stage_indices.size(); ++b) {
                    const auto right = wave.stage_indices[b];
                    const auto* right_agent = find_agent(agents, stages[right].agent_id);
                    if (right_agent == nullptr ||
                        !right_agent->descriptor().supports_concurrency ||
                        !disjoint_workspace_files(stages[left], stages[right])) {
                        wave.parallel_safe = false;
                        wave.reason =
                            "concurrent stages require concurrency support and disjoint workspace files";
                        break;
                    }
                }
            }
        } else {
            wave.reason = "single ready stage";
        }

        for (const auto index : wave.stage_indices) {
            scheduled[index] = true;
            --remaining;
            for (const auto dependent : dependents[index]) --indegree[dependent];
        }
        schedule.waves.push_back(std::move(wave));
    }

    schedule.status = EngineeringScheduleStatus::valid;
    schedule.reason = "engineering schedule planned";
    return schedule;
}

EngineeringScheduleResult EngineeringScheduler::execute(
    const std::vector<EngineeringStageTask>& stages,
    const std::vector<EngineeringAgent*>& agents,
    const EngineeringAuthorizer& authorizer,
    EngineeringExecutionBoundary& boundary) const {
    EngineeringScheduleResult result;
    const auto schedule = plan(stages, agents);
    if (schedule.status != EngineeringScheduleStatus::valid) {
        result.reason = schedule.reason;
        return result;
    }

    std::vector<EngineeringStageTask> tasks = stages;
    std::vector<EngineeringNodeStatus> statuses(
        tasks.size(), EngineeringNodeStatus::pending);
    std::unordered_map<std::string, std::size_t> by_id;
    by_id.reserve(tasks.size());
    for (std::size_t i = 0; i < tasks.size(); ++i) by_id.emplace(tasks[i].task.id, i);

    for (const auto& wave : schedule.waves) {
        for (const auto index : wave.stage_indices) {
            std::vector<std::string> blockers;
            for (const auto& dependency_id : tasks[index].task.dependencies) {
                const auto dependency_index = by_id.at(dependency_id);
                if (statuses[dependency_index] != EngineeringNodeStatus::completed) {
                    blockers.push_back(dependency_id);
                }
            }

            if (!blockers.empty()) {
                statuses[index] = EngineeringNodeStatus::blocked;
                result.nodes.push_back(
                    {index, EngineeringNodeStatus::blocked, {}, std::move(blockers)});
                continue;
            }

            EngineeringAgent* agent = nullptr;
            if (!tasks[index].agent_id.empty()) {
                agent = find_agent(agents, tasks[index].agent_id);
            }
            AgentResult dispatch_result;
            if (agent != nullptr) {
                dispatch_result = EngineeringCoordinator{}.dispatch(
                    tasks[index].task, *agent, authorizer, boundary);
            } else {
                dispatch_result = EngineeringCoordinator{}.dispatch_selected(
                    tasks[index].task, agents, authorizer, boundary);
            }

            const auto node_status = dispatch_result.accepted
                ? EngineeringNodeStatus::completed
                : EngineeringNodeStatus::rejected;
            statuses[index] = node_status;
            result.nodes.push_back(
                {index, node_status, dispatch_result, {}});

            if (dispatch_result.accepted) {
                for (const auto& artifact : dispatch_result.artifacts) {
                    tasks[index].task.prior_stage_artifacts.push_back(artifact);
                }
                for (const auto& evidence : dispatch_result.evidence) {
                    tasks[index].task.prior_stage_evidence.push_back(evidence);
                }
                for (std::size_t dependent = 0; dependent < tasks.size(); ++dependent) {
                    if (!contains(tasks[dependent].task.dependencies, tasks[index].task.id)) {
                        continue;
                    }
                    tasks[dependent].task.prior_stage_artifacts.insert(
                        tasks[dependent].task.prior_stage_artifacts.end(),
                        dispatch_result.artifacts.begin(),
                        dispatch_result.artifacts.end());
                    tasks[dependent].task.prior_stage_evidence.insert(
                        tasks[dependent].task.prior_stage_evidence.end(),
                        dispatch_result.evidence.begin(),
                        dispatch_result.evidence.end());
                }
            }
        }
    }

    result.accepted = std::all_of(
        statuses.begin(), statuses.end(),
        [](const auto status) { return status == EngineeringNodeStatus::completed; });
    result.reason = result.accepted
        ? "engineering schedule executed"
        : "engineering schedule did not complete all nodes";
    return result;
}

} // namespace jarvis::engineering
