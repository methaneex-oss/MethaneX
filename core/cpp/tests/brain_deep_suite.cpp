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
    const auto assessments = brain.assess_actions(decisions, ActionConstraints{0.5, false});
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

    std::filesystem::remove_all(root, ec);
    return 0;
}
