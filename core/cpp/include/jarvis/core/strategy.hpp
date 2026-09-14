#pragma once

#include "intent.hpp"
#include "planning.hpp"
#include "attention.hpp"

namespace jarvis::core {

struct StrategyContext {
    Intent intent;
    PlanningContext planning;
    double attention{0.0};
};

class StrategyModel {
public:
    StrategyContext formulate(const Intent& intent, const AttentionSignal& attention,
                              double threat, double uncertainty,
                              double resource_budget = 1.0) const;
};

} // namespace jarvis::core
