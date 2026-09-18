#pragma once

#include "jarvis/core/evolution_experiment.hpp"

#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

struct EvolutionSchedulePolicy {
    std::chrono::milliseconds minimum_interval{1000};
    std::size_t max_trials_per_cycle{8};
    bool require_idle_system{true};
};

struct EvolutionScheduleDecision {
    bool allowed{false};
    std::string reason;
    std::size_t trial_budget{0};
};

class EvolutionScheduler {
public:
    explicit EvolutionScheduler(EvolutionSchedulePolicy policy = {});
    EvolutionScheduleDecision evaluate(std::chrono::steady_clock::time_point now,
                                       std::chrono::steady_clock::time_point last_run,
                                       bool system_idle) const noexcept;
private:
    EvolutionSchedulePolicy policy_;
};

} // namespace jarvis::core
