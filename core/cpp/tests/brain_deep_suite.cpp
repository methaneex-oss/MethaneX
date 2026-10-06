#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

using namespace jarvis::core;

static Event event(std::uint64_t seq, std::string source, std::string kind,
                   std::string topic, double value) {
    return Event{seq, seq, std::move(source), std::move(kind),
                 {{"topic", Scalar{std::move(topic)}}, {"value", Scalar{value}}}};
}

static Event strategy_outcome(std::string context, std::string action,
                              double consequence, double error, double salience,
                              double novelty) {
    return Event{0, 0, "developmental-test", "action_outcome",
                 {{"action", Scalar{std::move(action)}},
                  {"context", Scalar{std::move(context)}},
                  {"status", Scalar{static_cast<std::int64_t>(ActionExecutionStatus::verified)}},
                  {"observed", Scalar{true}},
                  {"actual_consequence", Scalar{consequence}},
                  {"consequence_error", Scalar{error}},
                  {"reliability", Scalar{0.95}},
                  {"salience", Scalar{salience}},
                  {"novelty", Scalar{novelty}}}};
}

int main() {
    const auto root = std::filesystem::temp_directory_path() / "jarvis_brain_deep_suite";
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);

    Brain brain(root / "continuity.bin");
    const auto observed = brain.observe(event(0, "test", "observation", "persistent", 42.0));
    assert(observed.event.sequence == 1);
    assert(observed.novelty == 1.0);
    assert(brain.memory().size() == 1);

    assert(brain.learn(Evidence{"trusted", "temperature", Scalar{25.0}, 0.9}) >= 0.0);
    assert(brain.knowledge_source("trusted") != nullptr);

    const std::vector<CandidateAction> actions{{"safe", 0.9, 0.9, 0.05, 0.9}, {"risky", 0.95, 0.2, 0.9, 0.8}};
    const auto decisions = brain.choose(actions);
    assert(!decisions.empty());
    assert(!brain.plan(actions, 4).steps.empty());

    const auto assessments = brain.assess_actions(decisions, ActionConstraints{0.5, false});
    assert(!assessments.empty());
    const auto& executable = assessments.front();
    const auto affect_before_action = brain.affective_state();
    const auto action_result = brain.execute_action(
        executable,
        [](const CandidateAction& action) { return action.name == "safe"; },
        [](const CandidateAction& action) { return action.name == "safe"; },
        {},
        [](const CandidateAction& action) { return action.name == "safe" ? 0.8 : 0.0; });
    assert(action_result.authorized);
    assert(action_result.executed);
    assert(action_result.verified);
    assert(brain.memory().by_kind("action_outcome", 1).size() == 1);
    assert(brain.memory().by_kind("affective_learning", 1).size() == 1);
    assert(brain.memory().by_kind("learning", 1).size() == 1);
    // The derived learning event must not re-appraise the same experience.
    assert(brain.affective_state().updates == affect_before_action.updates + 1);

    // Derived affective-learning evidence is keyed to its source action and must not train twice.
    const auto affective_records = brain.memory().by_kind("affective_learning", 1);
    assert(affective_records.size() == 1);
    const duplicate_source = affective_records.front().data.find("source_action_sequence");
    assert(duplicate_source != affective_records.front().data.end());
    const auto affect_before_duplicate = brain.affective_state();
    const auto calibration_before_duplicate = brain.affective_calibration();
    brain.observe(affective_records.front());
    const auto affect_after_duplicate = brain.affective_state();
    const auto calibration_after_duplicate = brain.affective_calibration();
    assert(affect_after_duplicate.updates == affect_before_duplicate.updates);
    assert(calibration_after_duplicate.observations == calibration_before_duplicate.observations);
    assert(std::abs(calibration_after_duplicate.mean_absolute_error - calibration_before_duplicate.mean_absolute_error) < 1e-12);

    // Replay must reconstruct the same learned state produced by live processing.
    {
        Brain replayed_action(root / "continuity.bin");
        const auto live_affect = brain.affective_state();
        const auto replay_affect = replayed_action.affective_state();
        const auto live_calibration = brain.affective_calibration();
        const auto replay_calibration = replayed_action.affective_calibration();
        const auto live_attention = brain.attention();
        const auto replay_attention = replayed_action.attention();
        assert(std::abs(live_affect.valence - replay_affect.valence) < 1e-12);
        assert(std::abs(live_affect.arousal - replay_affect.arousal) < 1e-12);
        assert(std::abs(live_affect.uncertainty - replay_affect.uncertainty) < 1e-12);
        assert(std::abs(live_affect.tension - replay_affect.tension) < 1e-12);
        assert(std::abs(live_affect.stability - replay_affect.stability) < 1e-12);
        assert(live_affect.updates == replay_affect.updates);
        assert(std::abs(live_calibration.mean_absolute_error - replay_calibration.mean_absolute_error) < 1e-12);
        assert(std::abs(live_calibration.learning_rate_scale - replay_calibration.learning_rate_scale) < 1e-12);
        assert(live_calibration.observations == replay_calibration.observations);
        assert(std::abs(live_attention.salience - replay_attention.salience) < 1e-12);
        assert(std::abs(live_attention.novelty - replay_attention.novelty) < 1e-12);
        assert(std::abs(live_attention.uncertainty - replay_attention.uncertainty) < 1e-12);
    }

    const auto affect_before_failure = brain.affective_state();
    const auto learning_before_failure = brain.affective_learning_updates();
    const auto failed_action = brain.execute_action(
        executable,
        [](const CandidateAction&) { return false; },
        [](const CandidateAction&) { return false; });
    assert(failed_action.authorized);
    assert(!failed_action.executed);
    assert(brain.memory().by_kind("action_outcome", 2).size() == 2);
    assert(brain.memory().by_kind("affective_learning", 2).size() == 1);
    // No consequence observer means the action result must not train the
    // consequence-sensitive affective calibration model.
    assert(learning_before_failure > 0);
    assert(brain.affective_learning_updates() == learning_before_failure);

    const auto affect_after_failure = brain.affective_state();
    assert(std::isfinite(affect_after_failure.valence));
    assert(std::isfinite(affect_after_failure.tension));
    assert(brain.affective_learning_updates() == learning_before_failure);
    assert(affect_after_failure.valence != affect_before_failure.valence ||
           affect_after_failure.tension != affect_before_failure.tension ||
           affect_after_failure.arousal != affect_before_failure.arousal ||
           affect_after_failure.uncertainty != affect_before_failure.uncertainty);

    const CandidateAction probe{"probe", 0.0, 1.0, 0.2, 1.0};
    const auto before_decision = brain.choose_with_affect({probe}).front().score;
    brain.observe(event(0, "feedback", "observation", "consequence", -1.0));
    const auto after_decision = brain.choose_with_affect({probe}).front().score;
    assert(std::isfinite(before_decision));
    assert(std::isfinite(after_decision));
    assert(before_decision != after_decision);

    // Developmental learning must be reconstructable from the journal.
    const auto developmental_journal = root / "developmental.bin";
    {
        Brain learner(developmental_journal);
        for (int i = 0; i < 8; ++i) {
            learner.observe(strategy_outcome("navigation", "route_a", 0.9, 0.1, 0.8, 0.2));
            learner.observe(strategy_outcome("navigation", "route_b", -0.8, 0.9, 0.8, 0.2));
        }
        const auto* best = learner.developmental_best_strategy("navigation");
        assert(best != nullptr);
        assert(best->action == "route_a");
        assert(best->uses == 8);
        assert(learner.developmental_strategies().size() == 2);
    }
    {
        Brain replayed(developmental_journal);
        const auto strategies = replayed.developmental_strategies();
        assert(strategies.size() == 2);
        const auto* best = replayed.developmental_best_strategy("navigation");
        assert(best != nullptr);
        assert(best->action == "route_a");
        assert(best->uses == 8);
        const auto affect = replayed.affective_state();
        assert(std::isfinite(affect.valence));
        assert(std::isfinite(affect.arousal));
    }

    // Learned strategy must affect actual action selection, not merely remain
    // queryable as metadata. The learned route starts with a lower base utility
    // and only wins because prior consequences changed developmental value.
    const auto selection_journal = root / "selection.bin";
    Brain selector(selection_journal);
    assert(selector.create_goal(Goal{"navigation", "navigate", 1.0, 0.0, 0, 0,
                                     GoalStatus::pending, {}, {}}));
    assert(selector.activate_goal("navigation"));
    CandidateAction learned_route{"route_a", 0.0, 0.0, 0.1, 1.0};
    CandidateAction unlearned_route{"route_b", 0.15, 0.15, 0.1, 1.0};
    const auto before_learning = selector.choose({learned_route, unlearned_route});
    assert(!before_learning.empty());
    assert(before_learning.front().action.name == "route_b");

    for (int i = 0; i < 8; ++i) {
        selector.observe(strategy_outcome("navigation", "route_a", 0.9, 0.1, 0.8, 0.2));
        selector.observe(strategy_outcome("navigation", "route_b", -0.8, 0.9, 0.8, 0.2));
    }

    // The ordinary decision path now consumes the learned developmental
    // strategy. No separate "developmental decision" API is required.
    const auto learned_selection = selector.choose({learned_route, unlearned_route});
    assert(!learned_selection.empty());
    assert(learned_selection.front().action.name == "route_a");

    // The learned action preference must survive restart and journal replay.
    Brain replayed_selector(selection_journal);
    const auto replayed_selection = replayed_selector.choose({learned_route, unlearned_route});
    assert(!replayed_selection.empty());
    assert(replayed_selection.front().action.name == "route_a");

    // Goal, capability, and resilience mutations are journal-first and must
    // reconstruct the same durable state after restart.
    const auto state_journal = root / "state_transactions.bin";
    {
        Brain stateful(state_journal);
        assert(stateful.create_goal(Goal{"transaction-goal", "test durable goal", 0.5, 0.0, 0, 0,
                                         GoalStatus::pending, {}, {}}));
        assert(stateful.activate_goal("transaction-goal"));
        assert(stateful.update_goal_progress("transaction-goal", 0.4));
        const auto* live_goal = stateful.goal("transaction-goal");
        assert(live_goal != nullptr);
        assert(live_goal->progress == 0.4);
        assert(live_goal->outcome_momentum > 0.0);
        assert(stateful.set_goal_priority("transaction-goal", 0.8));

        stateful.observe_capability("planner", 0.9, 0.8);
        assert(stateful.isolate_capability("planner"));
        assert(stateful.restore_capability("planner", 0.7, 0.6));

        assert(stateful.observe(Event{0, 0, "health", "observation",
                                      {{"health", Scalar{0.8}}}}).event.sequence != 0);
        assert(stateful.isolate("health"));
        assert(stateful.recover("health", 0.95));
        assert(stateful.recovery_options().empty());
    }
    {
        Brain replayed(state_journal);
        const auto* replayed_goal = replayed.goal("transaction-goal");
        assert(replayed_goal != nullptr);
        assert(replayed_goal->progress == 0.4);
        assert(replayed_goal->priority == 0.8);
        assert(replayed_goal->outcome_momentum > 0.0);

        const auto replayed_self = replayed.snapshot().self_state;
        const auto pressure = replayed_self.resource_pressure.find("planner");
        assert(pressure != replayed_self.resource_pressure.end());
        assert(pressure->second > 0.0);
        assert(replayed.recovery_options().empty());
    }

    std::filesystem::remove_all(root, ec);
    return 0;
}
