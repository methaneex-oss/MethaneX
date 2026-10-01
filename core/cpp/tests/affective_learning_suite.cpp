#include "jarvis/core/affective_learning.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

int main() {
    AffectiveStateModel state;
    AffectiveLearningModel learner;
    const auto before = state.state();
    const AffectiveSignal signal{0.9, 0.1, 0.8, 0.9, 0.1, 0.9};
    const auto after = state.update(signal);
    const auto initial = learner.appraisal();

    for (int i = 0; i < 20; ++i) learner.learn(signal, before, after, 1.0);

    const auto learned = learner.appraisal();
    assert(learner.updates() == 20);
    assert(std::isfinite(learned.uncertainty_weight));
    assert(std::isfinite(learned.tension_error_weight));
    assert(learned.uncertainty_weight != initial.uncertainty_weight ||
           learned.tension_error_weight != initial.tension_error_weight);
    assert(learned.uncertainty_weight >= 0.0 && learned.uncertainty_weight <= 2.0);
    assert(learned.tension_error_weight >= 0.0 && learned.tension_error_weight <= 2.0);

    std::cout << "affective_learning_suite: PASS\n";
    return 0;
}
