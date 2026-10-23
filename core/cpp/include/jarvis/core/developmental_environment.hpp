#pragma once

#include "event.hpp"

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <utility>

namespace jarvis::core {

// A small, reusable world model for developmental trials. The brain receives
// observations and consequences, never the environment's transition function.
struct DevelopmentalTransition {
    double consequence{0.0};
    std::optional<Attributes> next_state;
};

struct DevelopmentalStepResult {
    std::string action;
    bool executed{false};
    bool observed{false};
    std::optional<double> consequence;
    std::uint64_t step{0};
};

class DevelopmentalEnvironment {
public:
    using TransitionFunction = std::function<std::optional<DevelopmentalTransition>(
        const std::string&, const Attributes&)>;

    DevelopmentalEnvironment(std::string task, std::string context,
                             Attributes initial_state, TransitionFunction transition)
        : task_(std::move(task)), context_(std::move(context)),
          state_(std::move(initial_state)), transition_(std::move(transition)) {}

    Event observe() const {
        Attributes data = state_;
        data.insert_or_assign("task", task_);
        data.insert_or_assign("context", context_);
        data.insert_or_assign("world_step", static_cast<std::int64_t>(step_));
        return Event{0, 0, "developmental_environment", "observation", std::move(data)};
    }

    // Conditions may change between trials to test adaptation to contradiction.
    void set_context(std::string context) { context_ = std::move(context); }

    void set_state(Attributes state) { state_ = std::move(state); }

    const Attributes& state() const noexcept { return state_; }
    const std::string& context() const noexcept { return context_; }
    std::uint64_t step_count() const noexcept { return step_; }

    DevelopmentalStepResult step(const std::string& action, bool execution_succeeded = true) {
        DevelopmentalStepResult result;
        result.action = action;
        result.executed = execution_succeeded;
        result.step = ++step_;

        // An execution failure is not evidence about the action's consequence.
        if (!execution_succeeded || !transition_) return result;

        const auto transition = transition_(action, state_);
        if (!transition || !std::isfinite(transition->consequence)) return result;

        result.observed = true;
        result.consequence = transition->consequence;
        if (transition->next_state) state_ = *transition->next_state;
        return result;
    }

private:
    std::string task_;
    std::string context_;
    Attributes state_;
    TransitionFunction transition_;
    std::uint64_t step_{0};
};

} // namespace jarvis::core
