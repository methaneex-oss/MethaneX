#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct Goal {
    std::string id;
    std::string description;
    double priority{0.0};
    double progress{0.0};
    bool active{true};
    std::uint64_t created_sequence{0};
    std::uint64_t updated_sequence{0};
};

class GoalModel {
public:
    bool upsert(Goal goal);
    bool update_progress(const std::string& id, double progress, std::uint64_t sequence);
    bool complete(const std::string& id, std::uint64_t sequence);
    bool remove(const std::string& id);
    const Goal* get(const std::string& id) const noexcept;
    std::vector<Goal> active() const;
    std::vector<Goal> all() const;

private:
    std::vector<Goal> goals_;
};

} // namespace jarvis::core
