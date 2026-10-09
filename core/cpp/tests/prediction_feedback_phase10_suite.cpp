#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <limits>
#include <vector>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_phase10_prediction_feedback.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);

    // Invalid numeric values must not become journal events or adaptation evidence.
    const auto invalid_prediction = brain.predict("invalid_numeric", Scalar{42.0}, 0.8);
    assert(invalid_prediction.created_sequence != 0);
    assert(!brain.resolve_prediction(invalid_prediction.created_sequence,
                                     Scalar{std::numeric_limits<double>::quiet_NaN()}));
    assert(!brain.resolve_prediction(invalid_prediction.created_sequence,
                                     Scalar{std::numeric_limits<double>::infinity()}));
    bool invalid_target_still_unresolved = false;
    for (const auto& current : brain.snapshot().predictions) {
        if (current.created_sequence == invalid_prediction.created_sequence) {
            invalid_target_still_unresolved = !current.resolved;
            break;
        }
    }
    assert(invalid_target_still_unresolved);
    assert(brain.learning_metric("invalid_numeric") == nullptr);
    assert(!brain.resolve_prediction(invalid_prediction.created_sequence, Scalar{43.0}));
    const auto* valid_metric_after_recovery = brain.learning_metric("invalid_numeric");
    assert(valid_metric_after_recovery != nullptr);
    assert(valid_metric_after_recovery->observations == 1);

    // Non-finite predictions are rejected before journal append.
    const auto snapshot_before_invalid_prediction = brain.snapshot().predictions.size();
    assert(brain.predict("invalid_forecast",
                         Scalar{std::numeric_limits<double>::quiet_NaN()}, 0.8).key.empty());
    assert(brain.predict("invalid_forecast",
                         Scalar{std::numeric_limits<double>::infinity()}, 0.8).key.empty());
    assert(brain.snapshot().predictions.size() == snapshot_before_invalid_prediction);

    // Integer forecasts must receive the same learned calibration as doubles.
    const auto integer_prediction = brain.predict("integer_temperature", Scalar{std::int64_t{20}}, 0.8);
    assert(integer_prediction.created_sequence != 0);
    assert(!brain.resolve_prediction(integer_prediction.created_sequence, Scalar{std::int64_t{30}}));
    const auto calibrated_integer = brain.predict("integer_temperature", Scalar{std::int64_t{20}}, 0.8);
    const auto integer_value = std::get_if<std::int64_t>(&calibrated_integer.predicted);
    assert(integer_value != nullptr);
    assert(*integer_value > 20 && *integer_value < 30);

    const auto contextual_integer = brain.predict_with_context("contextual_integer_temperature", Scalar{std::int64_t{20}}, 0.8, 0.5, 2);
    assert(contextual_integer.created_sequence != 0);
    assert(!brain.resolve_prediction(contextual_integer.created_sequence, Scalar{std::int64_t{30}}));
    const auto calibrated_contextual_integer = brain.predict_with_context("contextual_integer_temperature", Scalar{std::int64_t{20}}, 0.8, 0.5, 2);
    const auto contextual_integer_value = std::get_if<std::int64_t>(&calibrated_contextual_integer.predicted);
    assert(contextual_integer_value != nullptr);
    assert(*contextual_integer_value > 20 && *contextual_integer_value < 30);

    // A numeric prediction mismatch is surprise, not evidence of positive utility.
    const auto affect_semantics_path =
        std::filesystem::temp_directory_path() / "jarvis_prediction_affect_semantics.bin";
    std::filesystem::remove(affect_semantics_path, ec);
    std::filesystem::remove(affect_semantics_path.string() + ".meta", ec);
    {
        Brain affect_semantics(affect_semantics_path);
        const auto predicted = affect_semantics.predict("temperature", Scalar{20.0}, 0.8);
        assert(predicted.created_sequence != 0);
        assert(!affect_semantics.resolve_prediction(predicted.created_sequence, Scalar{30.0}));
        assert(affect_semantics.affective_state().valence < 0.0);
        Brain affect_replay(affect_semantics_path);
        assert(std::abs(affect_replay.affective_state().valence -
                        affect_semantics.affective_state().valence) < 1e-12);
    }
    std::filesystem::remove(affect_semantics_path, ec);
    std::filesystem::remove(affect_semantics_path.string() + ".meta", ec);

    // Build an experience-derived concept from repeated co-change, then ensure
    // its provenance survives journal replay and can still receive outcome feedback.
    brain.observe(Event{0, 1, "sensor", "observation", {{"alpha", false}, {"beta", false}, {"context_one", false}, {"context_two", false}}});
    brain.observe(Event{0, 2, "sensor", "observation", {{"alpha", true}, {"beta", true}, {"context_one", true}, {"context_two", true}}});
    brain.observe(Event{0, 3, "sensor", "observation", {{"alpha", false}, {"beta", false}, {"context_one", false}, {"context_two", false}}});
    brain.observe(Event{0, 4, "sensor", "observation", {{"alpha", true}, {"beta", true}, {"context_one", true}, {"context_two", true}}});
    const auto contextual_prediction = brain.predict_with_context("alpha", 1.0, 0.2, 0.5, 2);
    assert(!contextual_prediction.context.concept_members.empty());
    assert(contextual_prediction.context.evidence_strength > 0.0);
    const double learned_context_confidence = contextual_prediction.confidence;
    assert(learned_context_confidence > 0.2);

    brain.observe(Event{0, 5, "sensor", "observation",
                         {{"alpha", false}, {"beta", false},
                          {"context_one", false}, {"context_two", false},
                          {"gamma", false}}});
    brain.observe(Event{0, 6, "sensor", "observation",
                         {{"alpha", false}, {"beta", false},
                          {"context_one", true}, {"context_two", true},
                          {"gamma", true}}});
    const auto generalized = brain.generalized_concepts("gamma", 0.5, 2, 0.5);
    bool matched_learned_pattern = false;
    for (const auto& match : generalized) {
        if (match.concept_members == contextual_prediction.context.concept_members &&
            match.matched_contexts.size() >= 2 &&
            match.similarity >= 0.5 &&
            match.evidence_strength > 0.0) {
            matched_learned_pattern = true;
            break;
        }
    }
    assert(matched_learned_pattern);
    assert(brain.resolve_prediction("alpha", 1.0));

    // A duplicate outcome event must not mutate affect after its prediction has
    // already been resolved; replay validation must precede affective appraisal.
    const auto affect_before_duplicate = brain.affective_state();
    brain.observe(Event{0, 0, "test", "prediction_outcome",
        {{"key", std::string("alpha")},
         {"prediction_sequence", static_cast<std::int64_t>(contextual_prediction.created_sequence)},
         {"actual", Scalar{1.0}},
         {"error", 0.0},
         {"salience", 0.5},
         {"novelty", 0.1}}});
    const auto affect_after_duplicate = brain.affective_state();
    assert(affect_after_duplicate.updates == affect_before_duplicate.updates);
    assert(std::abs(affect_after_duplicate.valence - affect_before_duplicate.valence) < 1e-12);
    assert(std::abs(affect_after_duplicate.arousal - affect_before_duplicate.arousal) < 1e-12);

    // A sequence/key mismatch is invalid feedback too; it cannot resolve another
    // prediction or alter affect before the identity check.
    const auto affect_before_mismatch = brain.affective_state();
    brain.observe(Event{0, 0, "test", "prediction_outcome",
        {{"key", std::string("not-alpha")},
         {"prediction_sequence", static_cast<std::int64_t>(contextual_prediction.created_sequence)},
         {"actual", Scalar{0.5}},
         {"error", 0.5},
         {"salience", 0.5},
         {"novelty", 0.1}}});
    const auto affect_after_mismatch = brain.affective_state();
    assert(affect_after_mismatch.updates == affect_before_mismatch.updates);
    assert(std::abs(affect_after_mismatch.valence - affect_before_mismatch.valence) < 1e-12);

    Brain restored_context(path);
    bool provenance_restored = false;
    for (const auto& current : restored_context.snapshot().predictions) {
        if (current.key == "alpha" && current.created_sequence == contextual_prediction.created_sequence) {
            provenance_restored = current.context.concept_members == contextual_prediction.context.concept_members &&
                                  current.context.evidence_strength == contextual_prediction.context.evidence_strength &&
                                  current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(provenance_restored);

    // Real-valued predictions must learn in their native scale; adaptation must not
    // silently collapse values such as temperature into a normalized [0,1] range.
    std::vector<std::uint64_t> real_prediction_sequences;
    for (int i = 0; i < 6; ++i) {
        const auto prediction = brain.predict("real_temperature", Scalar{20.0}, 0.7);
        assert(prediction.created_sequence != 0);
        real_prediction_sequences.push_back(prediction.created_sequence);
        const auto affect_before_feedback = brain.affective_state();
        assert(!brain.resolve_prediction(prediction.created_sequence, Scalar{30.0}));
        const auto affect_after_feedback = brain.affective_state();
        assert(affect_after_feedback.updates == affect_before_feedback.updates + 1);
    }
    for (const auto sequence : real_prediction_sequences) {
        bool found = false;
        for (const auto& current : brain.snapshot().predictions) {
            if (current.created_sequence == sequence) {
                assert(current.resolved);
                assert(std::isfinite(current.error));
                assert(current.error > 0.0);
                assert(current.error < 1.0);
                assert(std::abs(current.error - (1.0 / 3.0)) < 1e-12);
                found = true;
                break;
            }
        }
        assert(found);
    }
    const auto* real_metric = brain.learning_metric("real_temperature");
    assert(real_metric != nullptr);
    assert(real_metric->observations == real_prediction_sequences.size());

    // Numeric scalar types share numeric error semantics: a floating prediction
    // of 20.0 is correct when the observed value is the integer 20.
    const auto mixed_numeric_prediction =
        brain.predict("mixed_numeric_outcome", Scalar{20.0}, 0.8);
    assert(mixed_numeric_prediction.created_sequence != 0);
    assert(brain.resolve_prediction(mixed_numeric_prediction.created_sequence,
                                   Scalar{std::int64_t{20}}));
    const auto* mixed_numeric_metric = brain.learning_metric("mixed_numeric_outcome");
    assert(mixed_numeric_metric != nullptr);
    assert(mixed_numeric_metric->observations == 1);

    // Integer-valued predictions must also update numeric adaptation.
    const auto integer_prediction =
        brain.predict("integer_outcome", Scalar{std::int64_t{20}}, 0.8);
    assert(integer_prediction.created_sequence != 0);
    assert(!brain.resolve_prediction(integer_prediction.created_sequence,
                                     Scalar{std::int64_t{30}}));
    const auto* integer_metric = brain.learning_metric("integer_outcome");
    assert(integer_metric != nullptr);
    assert(integer_metric->observations == 1);
    assert(std::abs(integer_metric->mean_error - (1.0 / 3.0)) < 1e-12);
    assert(std::abs(integer_metric->estimate - 30.0) < 1e-12);

    // Categorical outcomes still train association and attention systems even
    // when numeric adaptation cannot be applied.
    const auto categorical_prediction =
        brain.predict("door_state", Scalar{std::string("closed")}, 0.8);
    assert(categorical_prediction.created_sequence != 0);
    assert(!brain.resolve_prediction(categorical_prediction.created_sequence,
                                     Scalar{std::string("open")}));
    bool categorical_association_learned = false;
    for (const auto& association : brain.developmental_associations()) {
        if (association.left == "door_state" &&
            association.right == "prediction_outcome" &&
            association.observations == 1) {
            categorical_association_learned = true;
            break;
        }
    }
    assert(categorical_association_learned);

    // Invalid numeric outcomes must not enter the journal or mutate any learning
    // subsystem; the prediction remains available for a later valid observation.
    const auto invalid_outcome_prediction =
        brain.predict("invalid_outcome_guard", Scalar{25.0}, 0.8);
    assert(invalid_outcome_prediction.created_sequence != 0);
    const auto affect_before_invalid = brain.affective_state();
    const auto invalid_actual = std::numeric_limits<double>::quiet_NaN();
    assert(!brain.resolve_prediction(invalid_outcome_prediction.created_sequence,
                                     Scalar{invalid_actual}));
    const auto affect_after_invalid = brain.affective_state();
    assert(affect_after_invalid.updates == affect_before_invalid.updates);
    bool invalid_prediction_still_unresolved = false;
    for (const auto& current : brain.snapshot().predictions) {
        if (current.created_sequence == invalid_outcome_prediction.created_sequence) {
            invalid_prediction_still_unresolved = !current.resolved;
            break;
        }
    }
    assert(invalid_prediction_still_unresolved);
    assert(brain.learning_metric("invalid_outcome_guard") == nullptr);

    // Infinity is invalid for the same reason as NaN: neither is an observed
    // consequence, and rejection must leave the prediction available.
    const auto affect_before_infinity = brain.affective_state();
    assert(!brain.resolve_prediction(
        invalid_outcome_prediction.created_sequence,
        Scalar{std::numeric_limits<double>::infinity()}));
    assert(brain.affective_state().updates == affect_before_infinity.updates);
    bool unresolved_after_infinity = false;
    for (const auto& current : brain.snapshot().predictions) {
        if (current.created_sequence == invalid_outcome_prediction.created_sequence) {
            unresolved_after_infinity = !current.resolved;
            break;
        }
    }
    assert(unresolved_after_infinity);
    assert(brain.learning_metric("invalid_outcome_guard") == nullptr);

    // A later valid observation can still resolve the same prediction.
    assert(!brain.resolve_prediction(invalid_outcome_prediction.created_sequence,
                                     Scalar{30.0}));
    const auto* valid_after_invalid_metric = brain.learning_metric("invalid_outcome_guard");
    assert(valid_after_invalid_metric != nullptr);
    assert(valid_after_invalid_metric->observations == 1);

    const auto prediction_count_before_invalid_input = brain.snapshot().predictions.size();
    const auto invalid_predicted_value = std::numeric_limits<double>::infinity();
    const auto invalid_plain_prediction =
        brain.predict("invalid_prediction_guard", Scalar{invalid_predicted_value}, 0.8);
    assert(invalid_plain_prediction.key.empty());
    const auto invalid_contextual_prediction =
        brain.predict_with_context("invalid_contextual_prediction_guard",
                                   Scalar{invalid_predicted_value}, 0.8);
    assert(invalid_contextual_prediction.key.empty());
    assert(brain.snapshot().predictions.size() == prediction_count_before_invalid_input);

    // NaN confidence and contextual thresholds must be rejected before they
    // can contaminate confidence calibration or journal replay.
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const auto nan_confidence_prediction = brain.predict("nan_confidence_guard", Scalar{10.0}, nan);
    assert(nan_confidence_prediction.key.empty());
    const auto nan_context_confidence_prediction =
        brain.predict_with_context("nan_context_confidence_guard", Scalar{10.0}, nan);
    assert(nan_context_confidence_prediction.key.empty());
    const auto nan_threshold_prediction =
        brain.predict_with_context("nan_threshold_guard", Scalar{10.0}, 0.8, nan, 2);
    assert(nan_threshold_prediction.key.empty());
    assert(brain.snapshot().predictions.size() == prediction_count_before_invalid_input);
    assert(brain.learning_metric("nan_confidence_guard") == nullptr);
    assert(brain.learning_metric("nan_context_confidence_guard") == nullptr);
    assert(brain.learning_metric("nan_threshold_guard") == nullptr);

    const auto real_prediction = brain.predict("real_temperature", Scalar{20.0}, 0.7);
    const auto real_value = std::get_if<double>(&real_prediction.predicted);
    assert(real_value != nullptr);
    assert(*real_value > 20.0);
    assert(*real_value < 30.0);

    // Convex interpolation must remain finite even when finite inputs have
    // opposite signs near the floating-point range limit.
    const double extreme = -std::numeric_limits<double>::max();
    const auto extreme_prediction = brain.predict("real_temperature", Scalar{extreme}, 0.7);
    const auto extreme_value = std::get_if<double>(&extreme_prediction.predicted);
    assert(extreme_value != nullptr);
    assert(std::isfinite(*extreme_value));
    const auto extreme_contextual = brain.predict_with_context(
        "real_temperature", Scalar{extreme}, 0.7, 0.5, 2);
    const auto extreme_contextual_value = std::get_if<double>(&extreme_contextual.predicted);
    assert(extreme_contextual_value != nullptr);
    assert(std::isfinite(*extreme_contextual_value));

    // Prediction feedback must update the developmental model and remain available to later cognition.
    const Goal learned_goal{"prediction-driven-goal", "Test prediction-driven adaptation", 0.8};
    assert(brain.create_goal(learned_goal));
    assert(brain.activate_goal(learned_goal.id));
    for (int i = 0; i < 8; ++i) {
        const auto predicted = brain.predict("policy_temperature", Scalar{20.0}, 0.8);
        assert(predicted.created_sequence != 0);
        assert(!brain.resolve_prediction(predicted.created_sequence, Scalar{30.0}));
    }
    CognitiveCycle learned_cycle(brain);
    CognitiveCycleInput learned_input;
    learned_input.goal_id = learned_goal.id;
    learned_input.developmental_context = "policy_temperature";
    learned_input.planning_horizon = 1;
    learned_input.resource_budget = 10.0;
    learned_input.candidate_actions = {
        CandidateAction{"hold", 0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0},
        CandidateAction{"adjust", 0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0},
    };
    const auto learned_result = learned_cycle.run(learned_input);
    assert(learned_result.status == CognitiveCycleStatus::completed);
    assert(!learned_result.context.decisions.empty());
    const auto learned_associations = brain.developmental_associations();
    bool prediction_association_exists = false;
    for (const auto& association : learned_associations) {
        if (association.left == "policy_temperature" &&
            association.right == "prediction_outcome" &&
            association.observations >= 8) {
            // Surprise is learning relevance, not positive task utility.
            assert(association.observations == 8);
            assert(std::abs(association.strength) < 1e-12);
            prediction_association_exists = true;
            break;
        }
    }
    assert(prediction_association_exists);

    // Stable semantic prediction keys must accumulate learning across separate
    // experiences. The key identifies the variable; each prediction event keeps
    // its own journal sequence, while adaptation remains keyed by the variable.
    const auto first_prediction = brain.predict("temperature", Scalar{30.0}, 0.8);
    assert(first_prediction.key == "temperature");
    assert(!brain.resolve_prediction("temperature", Scalar{32.0}));
    const auto* metric_after_first = brain.learning_metric("temperature");
    assert(metric_after_first != nullptr);
    assert(metric_after_first->observations == 1);

    const auto second_prediction = brain.predict("temperature", Scalar{31.0}, 0.8);
    assert(second_prediction.key == "temperature");
    assert(second_prediction.created_sequence != first_prediction.created_sequence);
    assert(!second_prediction.resolved);
    assert(brain.resolve_prediction("temperature", Scalar{31.0}));
    const auto* metric_after_second = brain.learning_metric("temperature");
    assert(metric_after_second != nullptr);
    assert(metric_after_second->observations == 2);

    // Two unresolved predictions for the same semantic key must coexist. Their
    // journal identities are distinct and neither prediction may overwrite the other.
    const auto concurrent_first = brain.predict("pressure", Scalar{100.0}, 0.8);
    const auto concurrent_second = brain.predict("pressure", Scalar{110.0}, 0.8);
    assert(concurrent_first.created_sequence != 0);
    assert(concurrent_second.created_sequence != 0);
    assert(concurrent_first.created_sequence != concurrent_second.created_sequence);
    std::size_t pressure_instances = 0;
    for (const auto& current : brain.snapshot().predictions) {
        if (current.key == "pressure" &&
            (current.created_sequence == concurrent_first.created_sequence ||
             current.created_sequence == concurrent_second.created_sequence)) {
            ++pressure_instances;
        }
    }
    assert(pressure_instances == 2);
    assert(!brain.resolve_prediction("pressure", Scalar{111.0}));
    std::size_t unresolved_pressure_instances = 0;
    for (const auto& current : brain.snapshot().predictions) {
        if (current.key == "pressure" &&
            (current.created_sequence == concurrent_first.created_sequence ||
             current.created_sequence == concurrent_second.created_sequence) &&
            !current.resolved) {
            ++unresolved_pressure_instances;
        }
    }
    assert(unresolved_pressure_instances == 1);

    Goal goal;
    goal.id = "stabilize";
    goal.description = "Stabilize the observed system";
    goal.priority = 1.0;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    brain.observe(Event{0, 1, "sensor", "observation", {{"temperature", 20.0}, {"fan", false}}});
    brain.observe(Event{0, 2, "sensor", "observation", {{"temperature", 30.0}, {"fan", true}}});

    CognitiveCycle cycle(brain);
    CognitiveCycleInput input;
    input.observation = Event{0, 3, "sensor", "observation", {{"temperature", 30.0}, {"fan", true}}};
    input.goal_id = goal.id;
    input.planning_horizon = 1;
    input.candidate_actions = {
        CandidateAction{"stabilize", 0.9, 0.8, 0.1, 1.0, 1.0, 0.0, 0.8},
    };
    input.resource_budget = 2.0;

    const auto result = cycle.run(input);
    assert(result.status == CognitiveCycleStatus::completed);
    assert(!result.context.causal_links.empty());
    assert(!result.context.predictions.empty());

    const auto& prediction = result.context.predictions.front();
    assert(!prediction.key.empty());
    assert(prediction.created_sequence != 0);
    assert(!prediction.resolved);
    assert(prediction.confidence >= 0.0 && prediction.confidence <= 1.0);

    const auto feedback = cycle.process_outcome(prediction.key, prediction.predicted);
    assert(feedback.prediction_resolved);

    const auto predictions = brain.snapshot().predictions;
    bool resolved = false;
    for (const auto& current : predictions) {
        if (current.key == prediction.key) {
            resolved = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(resolved);

    const auto live_affect = brain.affective_state();
    const auto live_attention = brain.attention();

    Brain restored(path);
    bool persisted = false;
    for (const auto& current : restored.snapshot().predictions) {
        if (current.key == prediction.key) {
            persisted = current.resolved && current.error == 0.0;
            break;
        }
    }
    assert(persisted);

    const auto* restored_real_metric = restored.learning_metric("real_temperature");
    assert(restored_real_metric != nullptr);
    assert(restored_real_metric->observations == real_prediction_sequences.size());
    assert(std::abs(restored_real_metric->estimate - 30.0) < 1e-12);
    const auto* restored_policy_metric = restored.learning_metric("policy_temperature");
    assert(restored_policy_metric != nullptr);
    assert(restored_policy_metric->observations == 8);
    bool policy_association_replayed = false;
    for (const auto& association : restored.developmental_associations()) {
        if (association.left == "policy_temperature" &&
            association.right == "prediction_outcome") {
            assert(association.observations == 8);
            assert(std::abs(association.strength) < 1e-12);
            policy_association_replayed = true;
            break;
        }
    }
    assert(policy_association_replayed);
    const auto restored_policy_prediction =
        restored.predict("policy_temperature", Scalar{20.0}, 0.8);
    const auto restored_policy_value =
        std::get_if<double>(&restored_policy_prediction.predicted);
    assert(restored_policy_value != nullptr);
    assert(*restored_policy_value > 20.0);
    assert(*restored_policy_value < 30.0);
    const auto restored_affect = restored.affective_state();
    const auto restored_attention = restored.attention();
    assert(restored_affect.updates == live_affect.updates);
    assert(std::abs(restored_affect.valence - live_affect.valence) < 1e-12);
    assert(std::abs(restored_affect.arousal - live_affect.arousal) < 1e-12);
    assert(std::abs(restored_affect.uncertainty - live_affect.uncertainty) < 1e-12);
    assert(std::abs(restored_affect.tension - live_affect.tension) < 1e-12);
    assert(std::abs(restored_affect.stability - live_affect.stability) < 1e-12);
    assert(std::abs(restored_attention.salience - live_attention.salience) < 1e-12);
    assert(std::abs(restored_attention.novelty - live_attention.novelty) < 1e-12);
    assert(std::abs(restored_attention.uncertainty - live_attention.uncertainty) < 1e-12);
    const auto after_restart = restored.predict("real_temperature", Scalar{20.0}, 0.7);
    const auto after_restart_value = std::get_if<double>(&after_restart.predicted);
    assert(after_restart_value != nullptr);
    assert(*after_restart_value > 20.0);
    assert(*after_restart_value < 30.0);

    const auto restored_integer = restored.predict(
        "integer_temperature", Scalar{std::int64_t{20}}, 0.8);
    const auto restored_integer_value = std::get_if<std::int64_t>(&restored_integer.predicted);
    assert(restored_integer_value != nullptr);
    assert(*restored_integer_value > 20 && *restored_integer_value < 30);
    const auto restored_contextual_integer = restored.predict_with_context(
        "contextual_integer_temperature", Scalar{std::int64_t{20}}, 0.8, 0.5, 2);
    const auto restored_contextual_integer_value =
        std::get_if<std::int64_t>(&restored_contextual_integer.predicted);
    assert(restored_contextual_integer_value != nullptr);
    assert(*restored_contextual_integer_value > 20 && *restored_contextual_integer_value < 30);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}