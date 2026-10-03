#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace jarvis::core;

namespace {
void remove_journal(const std::filesystem::path& path) {
    std::error_code error;
    std::filesystem::remove(path, error);
    std::filesystem::remove(path.string() + ".meta", error);
}
}

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis_brain_deep_suite";
    std::filesystem::create_directories(root);
    remove_journal(root / "brain.bin");
    remove_journal(root / "action-replay.bin");
    remove_journal(root / "concepts.bin");

    Brain brain(root / "brain.bin");
    brain.observe(Event{0, 0, "test", "observation", {{"temperature", Scalar{20.0}}, {"pressure", Scalar{1.0}}}});
    brain.observe(Event{0, 0, "test", "observation", {{"temperature", Scalar{25.0}}, {"pressure", Scalar{1.0}}}});
    assert(brain.memory().size() == 2);
    assert(brain.beliefs().size() >= 2);
    assert(brain.state().events_seen == 2);

    const auto prediction = brain.predict("temperature", Scalar{30.0}, 0.8);
    assert(prediction.created_sequence != 0);
    const auto cycle = brain.learn_from_prediction("temperature", Scalar{28.0}, 0.5);
    assert(cycle.adaptation.observations >= 1);
    assert(brain.affective_state().updates > 0);

    CandidateAction executable{"test-action", 0.8, 0.8, 0.1, 0.9};
    const auto decisions = brain.choose({executable});
    const auto assessments = brain.assess_actions(decisions);
    assert(!assessments.empty());
    const auto failed_action = brain.execute_action(
        assessments.front(),
        [](const CandidateAction&) { return false; },
        [](const CandidateAction&) { return false; });
    assert(failed_action.authorized);
    assert(!failed_action.executed);
    assert(brain.memory().by_kind("action_outcome", 2).size() == 1);

    const auto action_journal = root / "action-replay.bin";
    AffectiveAppraisal learned_appraisal{};
    {
        Brain first(action_journal);
        const auto local_decisions = first.choose({CandidateAction{"persist-action", 0.9, 0.9, 0.05, 0.9}});
        const auto local_assessments = first.assess_actions(local_decisions);
        assert(!local_assessments.empty());
        auto assessment = local_assessments.front();
        assessment.action.expected_consequence = 0.8;
        const auto prediction_before_action = first.predict("action-surprise", Scalar{0.0}, 0.8);
        assert(prediction_before_action.created_sequence != 0);
        (void)first.learn_from_prediction("action-surprise", Scalar{1.0}, 0.0);
        const auto affect_before_action = first.affective_state();
        const auto attention_before_action = first.attention();
        const auto result = first.execute_action(
            assessment,
            [](const CandidateAction&) { return true; },
            [](const CandidateAction&) { return true; },
            {},
            [](const CandidateAction&) { return -0.7; });
        assert(result.verified);
        assert(result.outcome.observed);
        assert(result.outcome.expected_consequence == 0.8);
        assert(result.outcome.actual_consequence == -0.7);
        assert(first.memory().by_kind("affective_learning", 1).size() == 1);
        assert(first.affective_learning_updates() > 0);
        const auto action_events = first.memory().by_kind("action_outcome", 1);
        assert(action_events.size() == 1);
        const auto action_event_arousal = std::get<double>(action_events.front().data.at("affective_arousal"));
        const auto action_event_tension = std::get<double>(action_events.front().data.at("affective_tension"));
        const auto action_event_salience = std::get<double>(action_events.front().data.at("salience"));
        assert(std::abs(action_event_arousal - affect_before_action.arousal) < 1e-12);
        assert(std::abs(action_event_tension - affect_before_action.tension) < 1e-12);
        const double expected_affective_salience = std::clamp(
            0.70 * attention_before_action.salience +
            0.15 * affect_before_action.arousal +
            0.15 * affect_before_action.tension,
            0.0, 1.0);
        assert(std::abs(action_event_salience - expected_affective_salience) < 1e-12);
        learned_appraisal = first.affective_appraisal();
    }
    {
        Brain restarted(action_journal);
        assert(restarted.memory().by_kind("action_outcome", 1).size() == 1);
        assert(restarted.memory().by_kind("learning", 1).size() == 1);
        assert(restarted.memory().by_kind("affective_learning", 1).size() == 1);
        assert(restarted.knowledge_source("action_executor") != nullptr);
        assert(restarted.affective_learning_updates() == 1);
        const auto restored_appraisal = restarted.affective_appraisal();
        assert(restored_appraisal.error_weight == learned_appraisal.error_weight);
        assert(restored_appraisal.outcome_weight == learned_appraisal.outcome_weight);
        assert(restored_appraisal.novelty_weight == learned_appraisal.novelty_weight);
        assert(restored_appraisal.salience_weight == learned_appraisal.salience_weight);
        assert(restored_appraisal.uncertainty_weight == learned_appraisal.uncertainty_weight);
        assert(restored_appraisal.tension_error_weight == learned_appraisal.tension_error_weight);
    }

    const auto concept_journal = root / "concepts.bin";
    Brain concept_brain(concept_journal);
    concept_brain.observe(Event{0, 0, "experience", "observation", {{"alpha", Scalar{false}}, {"beta", Scalar{false}}, {"context_one", Scalar{false}}, {"context_two", Scalar{false}}}});
    concept_brain.observe(Event{0, 0, "experience", "observation", {{"alpha", Scalar{true}}, {"beta", Scalar{true}}, {"context_one", Scalar{true}}, {"context_two", Scalar{true}}}});
    concept_brain.observe(Event{0, 0, "experience", "observation", {{"alpha", Scalar{false}}, {"beta", Scalar{false}}, {"context_one", Scalar{false}}, {"context_two", Scalar{false}}}});
    concept_brain.observe(Event{0, 0, "experience", "observation", {{"alpha", Scalar{true}}, {"beta", Scalar{true}}, {"context_one", Scalar{true}}, {"context_two", Scalar{true}}}});
    const auto contextual = concept_brain.predict_with_context("alpha", Scalar{1.0}, 0.2, 0.5, 2);
    assert(!contextual.context.concept_members.empty());
    assert(contextual.context.evidence_strength > 0.0);
    concept_brain.observe(Event{0, 0, "experience", "observation", {{"gamma", Scalar{true}}, {"context_one", Scalar{true}}, {"context_two", Scalar{true}}}});

    std::cout << "brain deep suite passed\n";
    return 0;
}
