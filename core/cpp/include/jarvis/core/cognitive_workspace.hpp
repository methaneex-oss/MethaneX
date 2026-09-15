#pragma once

#include "action_model.hpp"
#include "cognition.hpp"
#include "event.hpp"
#include "reasoning.hpp"

#include <cstdint>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

namespace jarvis::core {

struct CognitiveWorkspace {
    std::uint64_t cycle{0};
    std::optional<Observation> observation;
    std::vector<MemoryRecord> memories;
    std::vector<Belief> beliefs;
    std::vector<CausalLink> causal_links;
    std::vector<Prediction> predictions;
    ReasoningResult reasoning;
    std::vector<Goal> goals;
    std::optional<Goal> selected_goal;
    Plan plan;
    DecisionContext decision_context;
    std::vector<Decision> decisions;
    std::vector<ActionAssessment> action_assessments;
    std::optional<Intent> intent;
    std::optional<StrategyContext> strategy;
    Reflection reflection;
};

class CognitiveWorkspaceStore {
public:
    CognitiveWorkspace snapshot() const;
    void replace(CognitiveWorkspace workspace);
    void clear();

private:
    mutable std::mutex mutex_;
    CognitiveWorkspace workspace_{};
};

} // namespace jarvis::core
