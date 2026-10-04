#include "jarvis/core/brain.hpp"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

static Event event(std::uint64_t seq, std::string source, std::string kind,
                   std::string topic, double value) {
    return Event{seq, seq, std::move(source), std::move(kind),
                 {{"topic", Scalar{std::move(topic)}}, {"value", Scalar{value}}}};
}

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis_brain_deep_suite";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);
    const auto journal = root / "continuity.bin";

    {
        Brain first(journal);
        const auto observed = first.observe(event(0, "test", "observation", "persistent", 42.0));
        assert(observed.event.sequence == 1);
        assert(observed.novelty == 1.0);
        assert(first.memory().size() == 1);
        assert(first.memory().next_sequence() == 2);
        assert(first.create_goal(Goal{"persisted-goal", "survive restart", 0.8, 0.0, 0, 0, GoalStatus::pending, {}, {}}));
        const auto snap = first.snapshot();
        assert(snap.state.events_seen == 2);
        assert(!snap.beliefs.empty());
        assert(!snap.goals.empty());
    }
    {
        Brain restarted(journal);
        assert(restarted.memory().size() == 2);
        const auto latest = restarted.memory().latest();
        assert(latest.has_value());
        assert(latest->kind == "goal_create");
        assert(restarted.memory().next_sequence() == 3);
        assert(restarted.state().events_seen == 2);
        assert(!restarted.beliefs().empty());
        const auto persisted_goal = restarted.goal("persisted-goal");
        assert(persisted_goal != nullptr);
        assert(persisted_goal->created_cycle == 2);
        assert(persisted_goal->priority == 0.8);
    }

    Brain brain(root / "main.bin");

    Memory sequence_memory(256, root / "sequence.bin");
    assert(sequence_memory.append(event(100, "sequence", "manual", "sequence", 1.0)) == 100);
    assert(sequence_memory.append(event(1, "sequence", "manual", "sequence", 2.0)) == 101);
    const auto ordered = sequence_memory.all();
    assert(ordered.size() == 2);
    assert(ordered[0].sequence == 100 && ordered[1].sequence == 101);
    assert(sequence_memory.next_sequence() == 102);

    assert(brain.learn(Evidence{"", "", Scalar{}, -5.0}) == 0.0);
    assert(brain.predict("", Scalar{1.0}, 2.0).key.empty());
    assert(!brain.resolve_prediction("missing", Scalar{1.0}));
    assert(!brain.isolate(""));
    assert(!brain.recover("", 2.0));
    const auto before_invalid = brain.state().events_seen;
    const auto empty_observation = brain.observe(Event{0, 0, "", "", {}});
    assert(empty_observation.novelty == 0.0);
    assert(brain.state().events_seen == before_invalid + 1);

    for (int i = 0; i < 20; ++i) {
        brain.observe(event(0, "memory", "observation", i % 2 ? "target" : "noise", static_cast<double>(i + 1)));
    }
    const auto changed_target = brain.observe(event(0, "memory", "observation", "target", 21.0));
    assert(changed_target.novelty > 0.0 && changed_target.novelty <= 1.0);
    const auto recalled = brain.memory().recall(Attributes{{"topic", Scalar{std::string("target")}}}, 3);
    assert(recalled.size() == 3);
    assert(recalled.front().data.at("topic") == Scalar{std::string("target")});
    assert(brain.memory().recent(0).size() <= 256);
    assert(brain.memory().recent(2).size() == 2);
    assert(brain.memory().by_kind("observation", 2).size() == 2);
    assert(brain.memory().by_source("memory", 2).size() == 2);

    const auto learned = brain.learn(Evidence{"trusted", "temperature", Scalar{25.0}, 0.9});
    assert(learned >= 0.0 && learned <= 1.0);
    assert(brain.knowledge_source("trusted") != nullptr);
    assert(brain.learning_metric("temperature") == nullptr);
    const auto causal_before = brain.causal_links().size();
    brain.observe(event(0, "sensor", "observation", "temperature", 26.0));
    const auto beliefs = brain.beliefs();
    assert(!beliefs.empty());
    (void)brain.simulate(beliefs);
    assert(brain.causal_links().size() >= causal_before);

    const std::vector<CandidateAction> actions{{"safe", 0.9, 0.9, 0.05, 0.9}, {"risky", 0.95, 0.2, 0.9, 0.8}};
    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(!brain.plan(actions, 4).steps.empty());
    const auto assessments = brain.assess_actions(decisions, ActionConstraints{0.5, true});
    assert(!assessments.empty());
    const auto& executable = assessments.front();
    const auto action_result = brain.execute_action(
        executable,
        [](const CandidateAction& action) { return action.name == "safe"; },
        [](const CandidateAction& action) { return action.name == "safe"; });
    assert(action_result.authorized);
    assert(action_result.executed);
    assert(action_result.verified);
    assert(brain.memory().by_kind("action_outcome", 1).size() == 1);
    assert(brain.memory().by_kind("learning", 1).size() == 1);
    (void)brain.reflect();
    (void)brain.attention();
    (void)brain.threat();

    const auto failed_action = brain.execute_action(
        executable,
        [](const CandidateAction&) { return false; },
        [](const CandidateAction&) { return false; });
    assert(failed_action.authorized);
    assert(!failed_action.executed);
    assert(brain.memory().by_kind("action_outcome", 2).size() == 2);

    const auto action_journal = root / "action-replay.bin";
    AffectiveAppraisal learned_appraisal{};
    {
        Brain first(action_journal);
        const auto local_decisions = first.choose({CandidateAction{"persist-action", 0.9, 0.9, 0.05, 0.9}});
        const auto local_assessments = first.assess_actions(local_decisions);
        assert(!local_assessments.empty());
        auto assessment = local_assessments.front();
        assessment.action.expected_consequence = 0.8;
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

    const auto developmental_low = root / "developmental-low.bin";
    const auto developmental_high = root / "developmental-high.bin";
    Brain low_affect(developmental_low);
    Brain high_affect(developmental_high);
    low_affect.observe(Event{0, 0, "neutral", "observation", {{"outcome", Scalar{0.0}}, {"prediction_error", Scalar{0.0}}, {"novelty", Scalar{0.0}}, {"salience", Scalar{0.0}}, {"confidence", Scalar{1.0}}}});
    high_affect.observe(Event{0, 0, "surprise", "observation", {{"outcome", Scalar{-1.0}}, {"prediction_error", Scalar{1.0}}, {"novelty", Scalar{1.0}}, {"salience", Scalar{1.0}}, {"confidence", Scalar{0.0}}}});
    const Event developmental_outcome{
        0, 0, "executor", "action_outcome",
        {{"action", Scalar{std::string("same-action")}},
         {"context", Scalar{std::string("same-context")}},
         {"status", Scalar{static_cast<std::int64_t>(ActionExecutionStatus::verified)}},
         {"reliability", Scalar{0.8}},
         {"observed", Scalar{true}},
         {"consequence_error", Scalar{0.2}},
         {"actual_consequence", Scalar{0.6}},
         {"salience", Scalar{0.5}},
         {"novelty", Scalar{0.4}}}};
    low_affect.observe(developmental_outcome);
    high_affect.observe(developmental_outcome);
    const auto* low_strategy = low_affect.developmental_best_strategy("same-context");
    const auto* high_strategy = high_affect.developmental_best_strategy("same-context");
    assert(low_strategy != nullptr);
    assert(high_strategy != nullptr);
    assert(high_strategy->confidence > low_strategy->confidence);

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
    const auto matches = concept_brain.generalized_concepts("gamma", 0.5, 2, 0.5);
    bool generalized = false;
    for (const auto& match : matches) if (match.concept_members == contextual.context.concept_members && match.matched_contexts.size() >= 2 && match.similarity >= 0.5 && match.evidence_strength > 0.0) { generalized = true; break; }
    assert(generalized);

    const auto prediction_journal = root / "prediction-replay.bin";
    {
        Brain first(prediction_journal);
        const auto prediction = first.predict_with_context("replay.prediction", Scalar{10.0}, 0.3);
        assert(prediction.created_sequence > 0);
        assert(first.resolve_prediction("replay.prediction", Scalar{10.0}));
    }
    {
        Brain restarted(prediction_journal);
        const auto snapshot = restarted.snapshot();
        bool restored = false;
        for (const auto& prediction : snapshot.predictions) if (prediction.key == "replay.prediction") { restored = prediction.resolved && prediction.error == 0.0 && prediction.confidence >= 0.3; break; }
        assert(restored);
    }

    brain.observe(Event{0, 0, "memory", "observation", {{"health", Scalar{0.2}}, {"mode", Scalar{std::string("degraded")}}}});
    assert(brain.isolate("memory")); assert(!brain.recovery_options().empty()); assert(brain.recover("memory", 1.0));
    brain.observe_capability("test-capability", 1.0, 1.0); assert(brain.isolate_capability("test-capability")); assert(brain.restore_capability("test-capability", 1.0, 1.0));
    brain.register_evolution_parameter("latency", 0.5); for (int i = 0; i < 6; ++i) brain.observe_evolution_fitness("latency", 0.8 + 0.02 * i);
    const auto proposals = brain.evolution_options(); assert(!proposals.empty()); const auto proposal = proposals.front(); assert(proposal.proposed != proposal.current); assert(brain.adopt_evolution(proposal)); assert(brain.rollback_evolution(proposal.key)); assert(!brain.adopt_evolution(EvolutionProposal{})); assert(!brain.rollback_evolution(""));
    brain.predict("deep.prediction", Scalar{10.0}, 2.0); assert(!brain.resolve_prediction("deep.prediction", Scalar{11.0})); assert(!brain.resolve_prediction("deep.prediction", Scalar{11.0})); brain.predict("correct.prediction", Scalar{10.0}, -1.0); assert(brain.resolve_prediction("correct.prediction", Scalar{10.0})); assert(brain.learning_confidence("deep.prediction") >= 0.0); assert(brain.learning_confidence("deep.prediction") <= 1.0);

    constexpr int workers = 16; constexpr int per_worker = 100; const auto before_events = brain.state().events_seen; std::vector<std::thread> threads;
    for (int w = 0; w < workers; ++w) threads.emplace_back([&brain]() { for (int i = 0; i < per_worker; ++i) brain.observe(event(0, "stress", "observation", "concurrent", 0.5)); });
    for (auto& t : threads) t.join(); assert(brain.state().events_seen >= before_events + static_cast<std::uint64_t>(workers * per_worker));
    const auto start = std::chrono::steady_clock::now(); for (int i = 0; i < 1000; ++i) brain.observe(event(0, "benchmark", "observation", "load", 0.25)); const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count(); assert(elapsed >= 0); assert(brain.state().cycle > 0);
    const auto corrupt = root / "corrupt.bin"; { Memory writer(256, corrupt); assert(writer.append(event(0, "recovery", "observation", "valid", 1.0)) == 1); assert(writer.append(event(0, "recovery", "observation", "valid", 2.0)) == 2); }
    { std::ofstream out(corrupt, std::ios::binary | std::ios::app); const char bytes[] = {0x7f, 0x45, 0x4c, 0x46, 0x00, 0x01, 0x02}; out.write(bytes, sizeof(bytes)); }
    Memory recovered_memory(256, corrupt); assert(recovered_memory.size() == 2); assert(recovered_memory.next_sequence() == 3); assert(recovered_memory.append(event(0, "recovery", "observation", "after", 3.0)) == 3); assert(recovered_memory.size() == 3);
    std::filesystem::remove_all(root, ec); return 0;
}
