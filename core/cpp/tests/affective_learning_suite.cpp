#include "jarvis/core/affective_learning.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace jarvis::core;

int main() {
    AffectiveLearningModel learner;
    const auto initial = learner.appraisal();
    const auto initial_influence = learner.influence_confidence();
    const auto initial_calibration = learner.calibration();

    const AffectiveOutcomeEvidence expected_failure{
        0.8, -0.7, -1.0, -0.7, 0.9, 0.7, 0.9, 0.4, 0.8};
    for (int i = 0; i < 20; ++i) learner.learn(expected_failure);

    const auto learned = learner.appraisal();
    const auto learned_calibration = learner.calibration();
    assert(learner.updates() == 20);
    assert(std::isfinite(learned.outcome_weight));
    assert(std::isfinite(learned.error_weight));
    assert(std::isfinite(learned.tension_error_weight));
    assert(learned.error_weight != initial.error_weight ||
           learned.tension_error_weight != initial.tension_error_weight);
    assert(learned.error_weight >= 0.0 && learned.error_weight <= 2.0);
    assert(learned.tension_error_weight >= 0.0 && learned.tension_error_weight <= 2.0);
    assert(learned_calibration.observations == 20);
    assert(learned_calibration.mean_absolute_error > initial_calibration.mean_absolute_error);
    assert(learned_calibration.learning_rate_scale > initial_calibration.learning_rate_scale);
    assert(learned_calibration.learning_rate_scale >= 0.50 &&
           learned_calibration.learning_rate_scale <= 1.50);

    // Poor calibration must reduce how strongly affective prediction error is
    // trusted by future state updates. This is metacognitive regulation, not a
    // semantic emotion/action rule.
    assert(learner.influence_confidence() < initial_influence);
    assert(learner.influence_confidence() >= 0.0 && learner.influence_confidence() <= 1.0);
    const AffectiveSignal probe{0.7, 0.8, 0.6, 0.9, 0.5, 0.8};
    const auto modulated = learner.modulate(probe);
    assert(modulated.confidence < probe.confidence);
    assert(std::abs(modulated.confidence - learner.influence_confidence() * probe.confidence) < 1e-12);
    assert(std::isfinite(modulated.tension_error));
    assert(modulated.tension_error >= 0.0 && modulated.tension_error <= 1.0);

    // Learned appraisal must actually modulate future evidence.
    assert(modulated.outcome != probe.outcome ||
           modulated.prediction_error != probe.prediction_error ||
           modulated.novelty != probe.novelty ||
           modulated.salience != probe.salience ||
           modulated.uncertainty != probe.uncertainty ||
           modulated.tension_error != probe.tension_error ||
           modulated.confidence != probe.confidence);

    AffectiveLearningModel repeated_success;
    const auto success_initial = repeated_success.appraisal();
    const AffectiveOutcomeEvidence expected_success{
        0.8, 0.75, -0.05, 0.75, 0.05, 0.1, 0.8, 0.1, 0.95};
    for (int i = 0; i < 20; ++i) repeated_success.learn(expected_success);
    const auto success_learned = repeated_success.appraisal();
    assert(success_learned.error_weight != learned.error_weight ||
           success_learned.tension_error_weight != learned.tension_error_weight);
    assert(success_learned.error_weight != success_initial.error_weight ||
           success_learned.outcome_weight != success_initial.outcome_weight);
    assert(repeated_success.influence_confidence() > learner.influence_confidence());

    // Accurate evidence should keep calibration error and learning pressure low.
    AffectiveLearningModel accurate;
    const AffectiveOutcomeEvidence accurate_evidence{
        0.5, 0.5, 0.0, 0.5, 0.0, 0.1, 0.5, 0.1, 0.95};
    for (int i = 0; i < 20; ++i) accurate.learn(accurate_evidence);
    assert(accurate.calibration().mean_absolute_error < learned_calibration.mean_absolute_error);
    assert(accurate.calibration().learning_rate_scale < learned_calibration.learning_rate_scale);
    assert(accurate.influence_confidence() > learner.influence_confidence());

    // The tension-specific learned parameter remains distinct from general
    // prediction-error sensitivity.
    AffectiveLearningModel high_tension;
    for (int i = 0; i < 20; ++i) high_tension.learn(expected_failure);
    const auto high_tension_signal = high_tension.modulate(probe);
    assert(std::isfinite(high_tension_signal.tension_error));
    assert(high_tension_signal.tension_error >= 0.0 && high_tension_signal.tension_error <= 1.0);

    AffectiveStateModel state;
    const auto before = state.state();
    const auto default_after = state.update(probe);
    AffectiveStateModel weighted_state;
    AffectiveAppraisalWeights weights{};
    weights.tension_error_weight = 2.0;
    const auto weighted_after = weighted_state.update(probe, weights);
    assert(weighted_after.tension != default_after.tension);

    // Explicit outcome evidence is the primary learning path. The legacy adapter
    // remains covered for persisted callers during the transition.
    const auto legacy_before = state.state();
    AffectiveLearningModel legacy;
    legacy.learn(probe, before, legacy_before, 1.0);
    assert(legacy.updates() == 1);

    std::cout << "affective_learning_suite: PASS\n";
    return 0;
}
