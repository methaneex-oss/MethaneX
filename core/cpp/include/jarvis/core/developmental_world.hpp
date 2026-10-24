#pragma once

#include "event.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <limits>
#include <optional>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace jarvis::core {

// General-purpose world mechanics for developmental learning. The world owns
// physical/task state and consequences; it never writes to Brain memory,
// beliefs, strategies, predictions, or decisions.
struct DevelopmentalWorldTransition {
    double consequence{0.0};
    Attributes state_updates;
    std::vector<std::string> events;
    bool terminal{false};
};

struct DevelopmentalWorldAction {
    std::string name;
    double resource_cost{0.0};
    std::function<bool(const Attributes&)> available;
    std::function<std::optional<DevelopmentalWorldTransition>(
        const Attributes&, std::mt19937_64&)> transition;
};

struct DevelopmentalWorldTick {
    Attributes state_updates;
    std::vector<std::string> events;
    bool terminal{false};
};

struct DevelopmentalWorldConfig {
    std::string task;
    std::string context;
    Attributes initial_state;
    double initial_resources{100.0};
    std::uint64_t random_seed{1};
    std::uint64_t max_steps{1000};
    // Optional partial-observation boundary. The transition function still
    // receives true world state; the brain only receives this filtered view.
    std::function<Attributes(const Attributes&)> observation_filter;
    // Exogenous world changes (weather, moving objects, outages, other actors)
    // occur after an accepted action and are driven by the world's seeded RNG.
    std::function<DevelopmentalWorldTick(const Attributes&, std::mt19937_64&)> dynamics;
};

struct DevelopmentalWorldObservation {
    Event event;
    double resources_remaining{0.0};
    std::uint64_t episode{0};
    std::uint64_t step{0};
    bool terminal{false};
};

struct DevelopmentalWorldStep {
    std::string action;
    bool attempted{false};
    bool executed{false};
    bool observed{false};
    bool terminal{false};
    std::optional<double> consequence;
    double resources_before{0.0};
    double resources_after{0.0};
    std::uint64_t episode{0};
    std::uint64_t step{0};
    Attributes state_before;
    Attributes state_after;
    std::vector<std::string> events;
    std::string reason;
};

class DevelopmentalWorld {
public:
    explicit DevelopmentalWorld(DevelopmentalWorldConfig config)
        : config_(std::move(config)), state_(config_.initial_state),
          resources_(config_.initial_resources), random_(config_.random_seed) {
        if (config_.task.empty()) config_.task = "developmental-task";
        if (config_.context.empty()) config_.context = config_.task;
        if (!std::isfinite(config_.initial_resources) || config_.initial_resources < 0.0)
            resources_ = 0.0;
        if (config_.max_steps == 0) config_.max_steps = 1;
    }

    bool add_action(DevelopmentalWorldAction action) {
        if (action.name.empty() || !action.transition ||
            !std::isfinite(action.resource_cost) || action.resource_cost < 0.0 ||
            action_index_.contains(action.name)) return false;
        action_index_.emplace(action.name, actions_.size());
        actions_.push_back(std::move(action));
        return true;
    }

    DevelopmentalWorldObservation observe() const {
        Attributes visible = config_.observation_filter
            ? config_.observation_filter(state_) : state_;
        visible.insert_or_assign("task", config_.task);
        visible.insert_or_assign("context", config_.context);
        visible.insert_or_assign("world_step", static_cast<std::int64_t>(step_));
        visible.insert_or_assign("world_episode", static_cast<std::int64_t>(episode_));
        visible.insert_or_assign("resources_remaining", resources_);
        visible.insert_or_assign("world_terminal", terminal_);
        return {Event{step_, 0, "developmental_world", "observation", std::move(visible)},
                resources_, episode_, step_, terminal_};
    }

    std::vector<std::string> available_actions() const {
        std::vector<std::string> result;
        if (terminal_) return result;
        for (const auto& action : actions_) {
            if (action.resource_cost > resources_) continue;
            if (!action_is_available(action, state_)) continue;
            result.push_back(action.name);
        }
        return result;
    }

    DevelopmentalWorldStep step(const std::string& name, bool execution_succeeded = true) {
        DevelopmentalWorldStep result;
        result.action = name;
        result.attempted = true;
        result.resources_before = resources_;
        result.resources_after = resources_;
        result.episode = episode_;
        result.state_before = state_;
        result.state_after = state_;
        result.step = ++step_;

        if (terminal_) {
            result.reason = "world_terminal";
            result.terminal = true;
            return result;
        }
        if (step_ > config_.max_steps) {
            terminal_ = true;
            result.reason = "step_limit_reached";
            result.terminal = true;
            return result;
        }
        if (!execution_succeeded) {
            result.reason = "execution_failed";
            return result;
        }

        const auto found = action_index_.find(name);
        if (found == action_index_.end()) {
            result.reason = "unknown_action";
            return result;
        }
        const auto& action = actions_[found->second];
        if (!action_is_available(action, state_)) {
            result.reason = "action_unavailable_in_current_state";
            return result;
        }
        if (action.resource_cost > resources_) {
            result.reason = "insufficient_resources";
            return result;
        }

        std::optional<DevelopmentalWorldTransition> transition;
        try {
            transition = action.transition(state_, random_);
        } catch (...) {
            result.reason = "transition_failed";
            return result;
        }
        if (!transition || !std::isfinite(transition->consequence)) {
            result.reason = "outcome_unknown";
            return result;
        }

        resources_ = std::max(0.0, resources_ - action.resource_cost);
        for (const auto& [key, value] : transition->state_updates)
            state_.insert_or_assign(key, value);
        result.events = std::move(transition->events);
        terminal_ = transition->terminal;
        if (config_.dynamics && !terminal_) {
            try {
                auto tick = config_.dynamics(state_, random_);
                for (const auto& [key, value] : tick.state_updates)
                    state_.insert_or_assign(key, value);
                result.events.insert(result.events.end(), tick.events.begin(), tick.events.end());
                terminal_ = tick.terminal;
            } catch (...) {
                // The action consequence remains valid; expose the world-model
                // fault as an event instead of silently inventing another outcome.
                result.events.push_back("world_dynamics_failed");
                result.reason = "observed_consequence_world_dynamics_failed";
            }
        }
        terminal_ = terminal_ || step_ >= config_.max_steps;
        result.executed = true;
        result.observed = true;
        result.consequence = transition->consequence;
        result.resources_after = resources_;
        result.state_after = state_;
        result.terminal = terminal_;
        if (result.reason.empty()) result.reason = "observed_consequence";
        return result;
    }

    void set_context(std::string context) {
        if (!context.empty()) config_.context = std::move(context);
    }

    // A reset starts a new episode and resets world state/resources. The random
    // stream deliberately continues, so seeded episodes are reproducible while
    // outcomes can vary across episodes.
    void reset_episode(std::optional<Attributes> state = std::nullopt,
                       std::optional<double> resources = std::nullopt) {
        ++episode_;
        step_ = 0;
        state_ = state ? std::move(*state) : config_.initial_state;
        resources_ = resources && std::isfinite(*resources) && *resources >= 0.0
            ? *resources : config_.initial_resources;
        terminal_ = false;
    }

    const Attributes& true_state() const noexcept { return state_; }
    double resources_remaining() const noexcept { return resources_; }
    std::uint64_t episode() const noexcept { return episode_; }
    std::uint64_t step_count() const noexcept { return step_; }
    bool terminal() const noexcept { return terminal_; }
    const DevelopmentalWorldConfig& config() const noexcept { return config_; }

private:
    static bool action_is_available(const DevelopmentalWorldAction& action,
                                    const Attributes& state) noexcept {
        if (!action.available) return true;
        try {
            return action.available(state);
        } catch (...) {
            // A broken precondition must fail closed: never execute an action
            // when the world cannot establish that it is available.
            return false;
        }
    }

    DevelopmentalWorldConfig config_;
    Attributes state_;
    std::vector<DevelopmentalWorldAction> actions_;
    std::unordered_map<std::string, std::size_t> action_index_;
    double resources_{0.0};
    std::uint64_t episode_{0};
    std::uint64_t step_{0};
    bool terminal_{false};
    std::mt19937_64 random_;
};

} // namespace jarvis::core
