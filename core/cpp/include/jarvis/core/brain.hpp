#pragma once

#include "event.hpp"
#include "memory.hpp"
#include "world_model.hpp"
#include "cognition.hpp"
#include "causal_model.hpp"
#include "decision.hpp"

#include <cstdint>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace jarvis::core {

struct BrainState {
    std::uint64_t cycle{0};
    std::uint64_t events_seen{0};
    double novelty{0.0};
};

class Brain {
public:
    Observation observe(Event event);
    std::vector<Belief> beliefs() const;
    Prediction predict(std::string key, Scalar value, double confidence);
    bool resolve_prediction(const std::string& key, const Scalar& actual);
    std::vector<std::pair<std::string, Scalar>> simulate(const std::vector<Belief>& assumptions) const;
    std::vector<Decision> choose(const std::vector<CandidateAction>& actions) const;
    const WorldModel& world() const noexcept { return world_; }
    const Memory& memory() const noexcept { return memory_; }
    BrainState state() const;

private:
    static double compute_novelty(const Event& event, const std::vector<Event>& history);

    mutable std::shared_mutex mutex_;
    BrainState state_{};
    WorldModel world_{};
    Memory memory_{};
    std::unordered_map<std::string, Belief> beliefs_;
    std::unordered_map<std::string, Prediction> predictions_;
    CausalModel causal_{};
    DecisionEngine decision_{};
};

} // namespace jarvis::core
