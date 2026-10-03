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

    // Affective significance is a continuous learning modifier, not an
    // emotion-to-action rule. With identical evidence, stronger internal
    // significance produces a larger initial update.
    DevelopmentalLearning low_affect;
    DevelopmentalLearning high_affect;
    const LearningSignal low{0.2, 0.6, 0.4, 0.3, 0.0};
    const LearningSignal high{0.2, 0.6, 0.4, 0.3, 1.0};
    low_affect.observe_association("experience", "outcome", low);
    high_affect.observe_association("experience", "outcome", high);

    const auto low_associations = low_affect.associations();
    const auto high_associations = high_affect.associations();
    assert(low_associations.size() == 1);
    assert(high_associations.size() == 1);
    assert(std::abs(high_associations.front().strength) >
           std::abs(low_associations.front().strength));

    low_affect.observe_strategy("context", "action", low);
    high_affect.observe_strategy("context", "action", high);
    assert(high_affect.best_strategy("context") != nullptr);
    assert(low_affect.best_strategy("context") != nullptr);
    assert(high_affect.best_strategy("context")->confidence >
           low_affect.best_strategy("context")->confidence);

    learning.consolidate(0.05);
    std::cout << "developmental learning suite passed\n";
    return 0;
}
