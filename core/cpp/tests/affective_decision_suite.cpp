#include "jarvis/core/decision.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

int main() {
    DecisionEngine engine;
    CandidateAction reversible{"reversible", 0.4, 0.2, 0.2, 1.0, 0.1, 0.1, 0.4};
    CandidateAction irreversible{"irreversible", 0.4, 0.2, 0.2, 0.1, 0.1, 0.1, 0.4};
    const std::vector<CandidateAction> actions{reversible, irreversible};

    DecisionContext stable{};
    stable.uncertainty = 0.2;
    stable.stability = 1.0;
    stable.valence = 0.5;
    const auto stable_rank = engine.decide(actions, stable);
    assert(stable_rank.size() == 2);

    DecisionContext unstable = stable;
    unstable.valence = -0.8;
    unstable.affective_uncertainty = 0.9;
    unstable.arousal = 0.9;
    unstable.tension = 0.9;
    unstable.stability = 0.1;
    const auto unstable_rank = engine.decide(actions, unstable);
    assert(unstable_rank.size() == 2);
    assert(std::isfinite(unstable_rank.front().score));
    assert(unstable_rank.front().action.name == "reversible");

    // Affective state changes appraisal; it does not bypass decision policy.
    DecisionContext positive = unstable;
    positive.valence = 0.9;
    positive.tension = 0.0;
    positive.affective_uncertainty = 0.0;
    positive.stability = 1.0;
    const auto positive_rank = engine.decide(actions, positive);
    assert(positive_rank.size() == 2);
    assert(std::isfinite(positive_rank.front().score));

    std::cout << "affective_decision_suite: PASS\n";
    return 0;
}
