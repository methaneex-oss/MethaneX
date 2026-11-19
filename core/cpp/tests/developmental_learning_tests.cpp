#include "jarvis/core/developmental_learning.hpp"

#include <cassert>
#include <cmath>

using namespace jarvis::core;

int main() {
    DevelopmentalLearning learning;

    // No domain rule exists initially.
    assert(learning.best_strategy("unseen_context") == nullptr);

    // Repeated experience creates a learned association rather than a hard-coded one.
    learning.observe_association("object_a", "outcome_b", LearningSignal{0.8, -0.6, 0.9, 1.0});
    learning.observe_association("object_a", "outcome_b", LearningSignal{0.1, 0.5, 0.5, 0.1});
    const auto associations = learning.associations();
    assert(associations.size() == 1);
    assert(associations.front().observations == 2);

    // Experience can cause a strategy to become preferred without encoding the action itself.
    learning.observe_strategy("context", "strategy_a", LearningSignal{0.0, 0.9, 0.8, 0.2});
    learning.observe_strategy("context", "strategy_b", LearningSignal{0.8, -0.5, 0.9, 0.9});
    const auto* first = learning.best_strategy("context");
    assert(first != nullptr);
    const std::string initially_preferred = first->action;

    // More successful experience can change the preferred strategy.
    const std::string alternative = initially_preferred == "strategy_a" ? "strategy_b" : "strategy_a";
    for (int i = 0; i < 12; ++i) {
        learning.observe_strategy("context", alternative, LearningSignal{0.0, 1.0, 0.9, 0.1});
    }
    const auto* second = learning.best_strategy("context");
    assert(second != nullptr);
    assert(second->action == alternative);
    assert(second->uses >= 12);
    assert(std::isfinite(second->value));

    // Consolidation is selective and bounded rather than unconditional deletion.
    learning.consolidate(0.01);
    assert(!learning.associations().empty());
    assert(!learning.strategies().empty());

    return 0;
}
