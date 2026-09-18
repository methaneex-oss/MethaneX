#include "jarvis/core/evolution_learning.hpp"
#include <cassert>
#include <cmath>
using namespace jarvis::core;
int main() {
    EvolutionHistory history;
    assert(history.append({"exp-a","p",EvolutionRecordAction::Rejected,ExperimentOutcome::Degraded,0.8,0.6,0.95,0}));
    assert(history.append({"exp-b","p",EvolutionRecordAction::RolledBack,ExperimentOutcome::Degraded,0.9,0.7,0.95,0}));
    assert(history.append({"exp-c","other",EvolutionRecordAction::Rejected,ExperimentOutcome::Neutral,0.5,0.5,0.95,0}));
    const auto insight=EvolutionLearning::analyze_failures("p",history);
    assert(insight.failures==2 && insight.rollbacks==1);
    assert(insight.average_failed_gain < 0.0);
    assert(insight.caution > 0.0 && insight.caution <= 1.0);
    return 0;
}
