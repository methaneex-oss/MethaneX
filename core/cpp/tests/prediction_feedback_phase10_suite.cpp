#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <vector>

using namespace jarvis::core;

int main() {
    const auto path = std::filesystem::temp_directory_path() / "jarvis_phase10_prediction_feedback.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);

    Brain brain(path);

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
        assert(!brain.resolve_prediction(prediction.created_sequence, Scalar{30.0}));
    }
    for (const auto sequence : real_prediction_sequences) {
        bool found = false;
        for (const auto& current : brain.snapshot().predictions) {
            if (current.created_sequence == sequence) {
                assert(current.resolved);
                assert(std::isfinite(current.error));
                assert(current.error > 0.0);
                assert(current.error < 1.0);
                found = true;
                break;
            }
        }
        assert(found);
    }
    const auto* real_metric = brain.learning_metric("real_temperature");
    assert(real_metric != nullptr);
    assert(real_metric->observations == real_prediction_sequences.size());
    const auto real_prediction = brain.predict("real_temperature", Scalar{20.0}, 0.7);
    const auto real_value = std::get_if<double>(&real_prediction.predicted);
    assert(real_value != nullptr);
    assert(*real_value > 20.0);
    assert(*real_value < 30.0);

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
    const auto after_restart = restored.predict("real_temperature", Scalar{20.0}, 0.7);
    const auto after_restart_value = std::get_if<double>(&after_restart.predicted);
    assert(after_restart_value != nullptr);
    assert(*after_restart_value > 20.0);
    assert(*after_restart_value < 30.0);

    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    return 0;
}