#include "jarvis/core/affective_learning.hpp"
#include "jarvis/core/brain.hpp"
#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <vector>

using namespace jarvis::core;

int main() {
    AffectiveLearningModel learner;
    const auto initial = learner.appraisal();
    const AffectiveSignal signal{0.8, 0.9, 0.8, 0.9, 0.7, 0.2};
    const auto modulated = learner.modulate(signal);
    assert(modulated.prediction_error >= 0.0 && modulated.prediction_error <= 1.0);
    assert(modulated.outcome >= -1.0 && modulated.outcome <= 1.0);
    AffectiveState before{}; AffectiveState after{}; after.valence = -0.5;
    learner.learn(signal, before, after, -0.9);
    const auto learned = learner.appraisal();
    assert(learner.updates() == 1);
    assert(std::isfinite(learned.error_weight));
    assert(learned.error_weight >= 0.0 && learned.error_weight <= 2.0);
    assert(learned.uncertainty_weight >= 0.0 && learned.uncertainty_weight <= 2.0);
    assert(learned.error_weight != initial.error_weight || learned.uncertainty_weight != initial.uncertainty_weight);
    assert(learner.calibration().observations == 1);
    assert(learner.calibration().mean_absolute_error > 0.0);
    assert(learner.calibration().learning_rate_scale > 1.0);

    const auto path = std::filesystem::temp_directory_path() / "jarvis_affective_decision_suite.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);
    assert(brain.create_goal(Goal{"g", "developmental affect test", 0.9, 0.0, 0, 0, GoalStatus::active, {}, {}}));
    assert(brain.update_goal_progress("g", 0.9));

    const std::vector<CandidateAction> actions{
        CandidateAction{"safe", 0.4, 0.6, 0.1, 1.0, 0.1, 0.1, 0.2},
        CandidateAction{"risky", 0.8, 0.9, 0.8, 0.2, 0.1, 0.8, 0.8}};

    const auto affect_before_cycle = brain.affective_state();
    assert(brain.affective_learning_updates() > 0);

    const CandidateAction probe{"probe", 0.0, 1.0, 0.2, 1.0, 0.0, 0.0, 0.0};
    const auto score_before_experience = brain.choose_with_affect({probe}).front().score;
    const auto attention_before_experience = brain.attention_policy();
    for (int i = 0; i < 8; ++i) {
        brain.observe(Event{
            0, 0, "developmental_test", "observation",
            {{"novelty", 0.8}, {"salience", 0.8}, {"outcome", -1.0}, {"confidence", 0.2}, {"prediction_error", 0.8}}});
    }
    const auto score_after_experience = brain.choose_with_affect({probe}).front().score;
    const auto attention_after_experience = brain.attention_policy();
    assert(std::isfinite(score_before_experience));
    assert(std::isfinite(score_after_experience));
    assert(std::abs(score_after_experience - score_before_experience) > 1e-9);
    assert(std::abs(attention_after_experience.internal_activation_weight - attention_before_experience.internal_activation_weight) > 1e-12);

    const auto calibration = brain.affective_calibration();
    assert(calibration.observations == brain.affective_learning_updates());
    assert(calibration.mean_absolute_error >= 0.0 && calibration.mean_absolute_error <= 1.0);
    assert(calibration.learning_rate_scale >= 0.50 && calibration.learning_rate_scale <= 1.50);

    CognitiveCycle cycle(brain);
    const CognitiveCycleInput input{
        Event{0, 0, "test", "observation", {{"novelty", 0.6}, {"salience", 0.8}}},
        actions,
        std::string{"g"},
        1,
        8,
        8,
        1.0,
        0.2,
        {}};
    const auto result = cycle.run(input);
    assert(result.status == CognitiveCycleStatus::completed);
    assert(result.context.decision_context.valence == result.context.affective_state.valence);
    assert(result.context.decision_context.arousal == result.context.affective_state.arousal);
    assert(result.context.decision_context.stability == result.context.affective_state.stability);
    assert(!result.context.decisions.empty());
    assert(std::isfinite(affect_before_cycle.valence));

    // The learned appraisal/state, calibration and adaptive attention policy are reconstructed from persistent experience.
    const auto learned_appraisal = brain.affective_appraisal();
    const auto learned_calibration = brain.affective_calibration();
    const auto learned_updates = brain.affective_learning_updates();
    const auto learned_attention = brain.attention_policy();
    Brain replayed(path);
    const auto replayed_appraisal = replayed.affective_appraisal();
    const auto replayed_calibration = replayed.affective_calibration();
    const auto replayed_state = replayed.affective_state();
    const auto replayed_attention = replayed.attention_policy();
    assert(replayed.affective_learning_updates() == learned_updates);
    assert(std::abs(replayed_appraisal.error_weight - learned_appraisal.error_weight) < 1e-12);
    assert(std::abs(replayed_appraisal.uncertainty_weight - learned_appraisal.uncertainty_weight) < 1e-12);
    assert(std::abs(replayed_calibration.mean_absolute_error - learned_calibration.mean_absolute_error) < 1e-12);
    assert(std::abs(replayed_calibration.learning_rate_scale - learned_calibration.learning_rate_scale) < 1e-12);
    assert(replayed_calibration.observations == learned_calibration.observations);
    assert(std::abs(replayed_state.valence - brain.affective_state().valence) < 1e-12);
    assert(std::abs(replayed_state.tension - brain.affective_state().tension) < 1e-12);
    assert(std::abs(replayed_attention.internal_activation_weight - learned_attention.internal_activation_weight) < 1e-12);
    assert(std::abs(replayed_attention.uncertainty_weight - learned_attention.uncertainty_weight) < 1e-12);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    std::cout << "affective_decision_learning_suite: PASS\n";
    return 0;
}
