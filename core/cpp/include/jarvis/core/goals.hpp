#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

enum class GoalStatus {
    pending,
    active,
    completed,
    abandoned
};

struct Goal {
    std::string id;
    std::string description;
    double priority{0.0};
    double progress{0.0};
    std::uint64_t created_cycle{0};
    std::uint64_t deadline_cycle{0};
    GoalStatus status{GoalStatus::pending};
    std::vector<std::string> prerequisites;
    std::vector<std::string> subgoals;
};

class GoalModel {
public:
    bool create(Goal goal);
    bool activate(const std::string& id);
    bool update_progress(const std::string& id, double progress);
    bool complete(const std::string& id);
    bool abandon(const std::string& id);
    bool set_priority(const std::string& id, double priority);

    std::vector<Goal> eligible(std::uint64_t cycle) const;
    std::vector<Goal> all() const;
    const Goal* get(const std::string& id) const noexcept;

private:
    std::vector<Goal> goals_;
};

} // namespace jarvis::core
