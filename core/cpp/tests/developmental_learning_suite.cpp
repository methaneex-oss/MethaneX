#include "jarvis/core/developmental_learning.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

int main() {
    DevelopmentalLearning learning;

    learning.observe_strategy("context", "action_a", LearningSignal{0.0, 1.0, 0.8, 0.2});
    learning.observe_strategy("context", "action_b", LearningSignal{1.0, -1.0, 0.8, 0.2});

    const auto* best = learning.best_strategy("context");
    assert(best != nullptr);
    assert(best->action == "action_a");
    assert(best->value > 0.0);

    learning.observe_association("a", "b", LearningSignal{0.0, 1.0, 1.0, 1.0});
    learning.observe_association("a", "b", LearningSignal{1.0, -1.0, 1.0, 1.0});

    const auto associations = learning.associations();
    assert(associations.size() == 1);
    assert(associations.front().observations == 2);
    assert(std::isfinite(associations.front().strength));

    learning.consolidate(0.05);
    std::cout << "developmental learning suite passed\n";
    return 0;
}
