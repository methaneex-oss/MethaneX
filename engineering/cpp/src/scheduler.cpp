#include "jarvis/engineering/scheduler.hpp"

#include <algorithm>
#include <unordered_map>

namespace jarvis::engineering {

namespace {

bool contains(const std::vector<std::string>& values, const std::string& value) {
    return std::find(values.begin(), values.end(), value) != values.end();
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
        if (stages[i].agent_id.empty()) continue;
        bool found = false;
        for (auto* agent : agents) {
            if (agent != nullptr && agent->descriptor().id == stages[i].agent_id) {
                found = true;
                break;
            }
        }
        if (!found) {
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
                const EngineeringAgent* left_agent = nullptr;
                for (auto* agent : agents) {
                    if (agent != nullptr && agent->descriptor().id == stages[left].agent_id) {
                        left_agent = agent;
                        break;
                    }
                }
                if (left_agent == nullptr || !left_agent->descriptor().supports_concurrency) {
                    wave.parallel_safe = false;
                    wave.reason = "one or more agents do not support concurrency";
                    break;
                }

                for (std::size_t b = a + 1; b < wave.stage_indices.size(); ++b) {
                    const auto right = wave.stage_indices[b];
                    const EngineeringAgent* right_agent = nullptr;
                    for (auto* agent : agents) {
                        if (agent != nullptr && agent->descriptor().id == stages[right].agent_id) {
                            right_agent = agent;
                            break;
                        }
                    }
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

} // namespace jarvis::engineering
