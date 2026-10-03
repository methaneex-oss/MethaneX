#include "jarvis/core/affective_learning.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

int main() {
    AffectiveLearningModel learner;
    const auto initial = learner.appraisal();

    const AffectiveOutcomeEvidence expected_failure{
        0.8, -0.7, -1.0, -0.7, 0.9, 0.7, 0.9, 0.4, 0.8};
    for (int i = 0; i < 20; ++i) learner.learn(expected_failure);

    const auto learned = learner.appraisal();
    assert(learner.updates() == 20);
    assert(std::isfinite(learned.outcome_weight));
    assert(std::isfinite(learned.error_weight));
    assert(std::isfinite(learned.tension_error_weight));
    assert(learned.error_weight != initial.error_weight ||
           learned.tension_error_weight != initial.tension_error_weight);
    assert(learned.error_weight >= 0.0 && learned.error_weight <= 2.0);
    assert(learned.tension_error_weight >= 0.0 && learned.tension_error_weight <= 2.0);

    // Learned appraisal must actually modulate future evidence. A changing
    // parameter that never reaches the affective state is not developmental
    // influence; this checks the causal connection directly.
    const AffectiveSignal probe{0.7, 0.8, 0.6, 0.9, 0.5, 0.8};
    const auto modulated = learner.modulate(probe);
    assert(modulated.outcome != probe.outcome ||
           modulated.prediction_error != probe.prediction_error ||
           modulated.novelty != probe.novelty ||
           modulated.salience != probe.salience ||
           modulated.uncertainty != probe.uncertainty);

    AffectiveLearningModel repeated_success;
    const auto success_initial = repeated_success.appraisal();
    const AffectiveOutcomeEvidence expected_success{
        0.8, 0.75, -0.05, 0.75, 0.05, 0.1, 0.8, 0.1, 0.95};
    for (int i = 0; i < 20; ++i) repeated_success.learn(expected_success);
    const auto success_learned = repeated_success.appraisal();

    // Different consequence histories must produce different learned appraisal,
    // rather than merely incrementing a counter.
    assert(success_learned.error_weight != learned.error_weight ||
           success_learned.tension_error_weight != learned.tension_error_weight);
    assert(success_learned.error_weight != success_initial.error_weight ||
           success_learned.outcome_weight != success_initial.outcome_weight);

    // Explicit outcome evidence is the primary learning path. The legacy adapter
    // remains covered for persisted callers during the transition.
    AffectiveStateModel state;
    const auto before = state.state();
    const AffectiveSignal signal{0.9, 0.1, 0.8, 0.9, 0.1, 0.9};
    const auto after = state.update(signal);
    AffectiveLearningModel legacy;
    legacy.learn(signal, before, after, 1.0);
    assert(legacy.updates() == 1);

    std::cout << "affective_learning_suite: PASS\n";
    return 0;
}
