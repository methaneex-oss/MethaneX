#include "jarvis/core/goals.hpp"

#include <algorithm>

namespace jarvis::core {

bool GoalModel::upsert(Goal goal) {
    if (goal.id.empty() || goal.description.empty()) return false;
    goal.priority = std::max(0.0, goal.priority);
    goal.progress = std::clamp(goal.progress, 0.0, 1.0);
    const auto it = std::find_if(goals_.begin(), goals_.end(), [&](const Goal& existing) {
        return existing.id == goal.id;
    });
    if (it == goals_.end()) {
        goals_.push_back(std::move(goal));
    } else {
        if (goal.created_sequence == 0) goal.created_sequence = it->created_sequence;
        *it = std::move(goal);
    }
    return true;
}

bool GoalModel::update_progress(const std::string& id, double progress, std::uint64_t sequence) {
    const auto it = std::find_if(goals_.begin(), goals_.end(), [&](const Goal& goal) { return goal.id == id; });
    if (it == goals_.end() || !it->active) return false;
    it->progress = std::clamp(progress, 0.0, 1.0);
    it->updated_sequence = sequence;
    if (it->progress >= 1.0) it->active = false;
    return true;
}

bool GoalModel::complete(const std::string& id, std::uint64_t sequence) {
    return update_progress(id, 1.0, sequence);
}

bool GoalModel::remove(const std::string& id) {
    const auto old_size = goals_.size();
    goals_.erase(std::remove_if(goals_.begin(), goals_.end(), [&](const Goal& goal) { return goal.id == id; }), goals_.end());
    return goals_.size() != old_size;
}

const Goal* GoalModel::get(const std::string& id) const noexcept {
    const auto it = std::find_if(goals_.begin(), goals_.end(), [&](const Goal& goal) { return goal.id == id; });
    return it == goals_.end() ? nullptr : &*it;
}

std::vector<Goal> GoalModel::active() const {
    std::vector<Goal> result;
    for (const auto& goal : goals_) if (goal.active) result.push_back(goal);
    std::sort(result.begin(), result.end(), [](const Goal& a, const Goal& b) {
        if (a.priority != b.priority) return a.priority > b.priority;
        return a.progress < b.progress;
    });
    return result;
}

std::vector<Goal> GoalModel::all() const { return goals_; }

} // namespace jarvis::core
