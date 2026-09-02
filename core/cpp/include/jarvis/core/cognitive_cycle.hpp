#pragma once

#include "brain.hpp"
#include "reasoning.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace jarvis::core {

enum class CognitiveCycleStatus : std::uint8_t {
    completed,
    no_goal,
    no_action,
    invalid_goal,
};

struct CognitiveCycleInput {
    Event observation;
    std::vector<CandidateAction> candidate_actions;
    std::optional<std::string> goal_id;
    std::size_t planning_horizon{1};
    std::size_t memory_limit{8};
    std::size_t reasoning_steps{8};
};

struct CognitiveCycleContext {
    Observation observation;
    std::vector<MemoryRecord> memories;
    std::vector<Belief> beliefs;
    std::vector<CausalLink> causal_links;
    ReasoningResult reasoning;
    std::vector<Goal> eligible_goals;
    Goal selected_goal;
    Plan plan;
    std::vector<Decision> decisions;
    Reflection reflection;
};

struct CognitiveCycleResult {
    CognitiveCycleStatus status{CognitiveCycleStatus::no_goal};
    CognitiveCycleContext context;
};

class CognitiveCycle {
public:
    explicit CognitiveCycle(Brain& brain) noexcept : brain_(brain) {}

    CognitiveCycleResult run(const CognitiveCycleInput& input) const;

    double learn_from_outcome(const Evidence& evidence) const;
    bool resolve_prediction(const std::string& key, const Scalar& actual) const;

private:
    std::optional<Goal> select_goal(const CognitiveCycleInput& input,
                                    const std::vector<Goal>& eligible) const;

    Brain& brain_;
};

} // namespace jarvis::core
