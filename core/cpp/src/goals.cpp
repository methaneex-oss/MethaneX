#include "jarvis/core/goals.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace jarvis::core {

namespace {
Goal* find_goal(std::vector<Goal>& goals, const std::string& id) noexcept {
    for (auto& goal : goals) if (goal.id == id) return &goal;
    return nullptr;
}
}

bool GoalModel::create(Goal goal) {
    if (goal.id.empty() || goal.description.empty() || !std::isfinite(goal.priority) ||
        !std::isfinite(goal.progress) || goal.progress < 0.0 || goal.progress > 1.0) return false;
    if (get(goal.id) != nullptr) return false;
    goal.priority = std::clamp(goal.priority, 0.0, 1.0);
    goals_.push_back(std::move(goal));
    return true;
}

bool GoalModel::activate(const std::string& id) {
    Goal* goal = find_goal(goals_, id);
    if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false;
    for (const auto& prerequisite : goal->prerequisites) {
        const Goal* dependency = get(prerequisite);
        if (dependency == nullptr || dependency->status != GoalStatus::completed) return false;
    }
    goal->status = GoalStatus::active;
    return true;
}

bool GoalModel::update_progress(const std::string& id, double progress) {
    Goal* goal = find_goal(goals_, id);
    if (goal == nullptr || !std::isfinite(progress) || progress < 0.0 || progress > 1.0 ||
        goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false;
    goal->progress = progress;
    if (progress >= 1.0) goal->status = GoalStatus::completed;
    return true;
}

bool GoalModel::complete(const std::string& id) { return update_progress(id, 1.0); }

bool GoalModel::abandon(const std::string& id) {
    Goal* goal = find_goal(goals_, id);
    if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false;
    goal->status = GoalStatus::abandoned;
    return true;
}

bool GoalModel::set_priority(const std::string& id, double priority) {
    Goal* goal = find_goal(goals_, id);
    if (goal == nullptr || !std::isfinite(priority)) return false;
    goal->priority = std::clamp(priority, 0.0, 1.0);
    return true;
}

std::vector<Goal> GoalModel::eligible(std::uint64_t cycle) const {
    std::vector<Goal> result;
    for (const auto& goal : goals_) {
        if (goal.status != GoalStatus::pending && goal.status != GoalStatus::active) continue;
        if (goal.deadline_cycle != 0 && cycle > goal.deadline_cycle) continue;
        bool ready = true;
        for (const auto& prerequisite : goal.prerequisites) {
            const Goal* dependency = get(prerequisite);
            if (dependency == nullptr || dependency->status != GoalStatus::completed) {
                ready = false;
                break;
            }
        }
        if (ready) result.push_back(goal);
    }
    std::sort(result.begin(), result.end(), [](const Goal& a, const Goal& b) {
        if (a.priority != b.priority) return a.priority > b.priority;
        return a.created_cycle < b.created_cycle;
    });
    return result;
}

std::vector<Goal> GoalModel::all() const { return goals_; }

const Goal* GoalModel::get(const std::string& id) const noexcept {
    for (const auto& goal : goals_) if (goal.id == id) return &goal;
    return nullptr;
}

} // namespace jarvis::core
