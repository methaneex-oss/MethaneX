#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
constexpr const char* goal_id = "dlt-002-persistence-goal";
constexpr const char* clear_context = "navigation/clear";
constexpr const char* flooded_context = "navigation/flooded";
constexpr const char* tunnel_context = "navigation/tunnel";

void record_experience(Brain& brain, const std::string& context,
                       const std::string& action, double consequence) {
    ActionAssessment assessment;
    assessment.action.name = action;
    assessment.action.expected_consequence = 0.0;
    assessment.disposition = ActionDisposition::execute;
    assessment.permitted = true;
    assessment.confidence = 0.9;
    assessment.developmental_context = context;

    const auto result = brain.execute_action(
        assessment,
        [](const CandidateAction&) { return true; },
        [](const CandidateAction&) { return true; },
        {},
        [consequence](const CandidateAction&) { return consequence; });

    assert(result.authorized);
    assert(result.executed);
    assert(result.verified);
    assert(result.outcome.observed);
    assert(std::abs(result.outcome.actual_consequence - consequence) < 1e-12);
}

CognitiveCycleInput make_input(const std::string& context) {
    CognitiveCycleInput input;
    input.goal_id = goal_id;
    input.developmental_context = context;
    input.planning_horizon = 1;
    input.resource_budget = 10.0;
    input.observation = Event{0, 1, "dlt-002", "observation",
                              {{"environment", context}}};

    CandidateAction good;
    good.name = "good-route";
    good.utility = 0.5;
    good.expected_value = 0.5;
    good.confidence = 0.5;
    good.risk = 0.1;

    CandidateAction bad = good;
    bad.name = "bad-route";
    input.candidate_actions = {good, bad};
    return input;
}

double strategy_value(const Brain& brain, const std::string& context,
                      const std::string& action, std::uint64_t* uses = nullptr) {
    for (const auto& strategy : brain.developmental_strategies()) {
        if (strategy.context == context && strategy.action == action) {
            if (uses) *uses = strategy.uses;
            return strategy.value;
        }
    }
    if (uses) *uses = 0;
    return 0.0;
}

void assert_strategy_signs(const Brain& brain) {
    // Clear originally favored good-route, but that relationship was later
    // reversed. Flooded remains bad-route-favoring, while tunnel retains the
    // original clear-world mapping. These differences must remain context-local.
    assert(strategy_value(brain, clear_context, "good-route") < 0.0);
    assert(strategy_value(brain, clear_context, "bad-route") > 0.0);
    assert(strategy_value(brain, flooded_context, "good-route") < 0.0);
    assert(strategy_value(brain, flooded_context, "bad-route") > 0.0);
    assert(strategy_value(brain, tunnel_context, "good-route") > 0.0);
    assert(strategy_value(brain, tunnel_context, "bad-route") < 0.0);
}

std::string selected_action(Brain& brain, const std::string& context) {
    const auto result = CognitiveCycle(brain).run(make_input(context));
    assert(result.status == CognitiveCycleStatus::completed);
    assert(!result.context.plan.steps.empty());
    return result.context.plan.steps.front().action.name;
}

void assert_affective_learning(const Brain& brain) {
    const auto state = brain.affective_state();
    assert(state.updates > 0);
    assert(std::isfinite(state.valence) && state.valence >= -1.0 && state.valence <= 1.0);
    assert(std::isfinite(state.arousal) && state.arousal >= 0.0 && state.arousal <= 1.0);
    assert(std::isfinite(state.uncertainty) && state.uncertainty >= 0.0 && state.uncertainty <= 1.0);
    assert(std::isfinite(state.tension) && state.tension >= 0.0 && state.tension <= 1.0);
    assert(std::isfinite(state.stability) && state.stability >= 0.0 && state.stability <= 1.0);

    // The task deliberately supplies repeated consequences that contradict
    // the initial zero-valued forecasts. The affective appraisal model should
    // calibrate from that evidence, and replay after process restart must
    // reconstruct the learned calibration rather than only restoring outcomes.
    const auto calibration = brain.affective_calibration();
    assert(calibration.observations > 0);
    assert(calibration.observations == brain.affective_learning_updates());
    assert(std::isfinite(calibration.mean_absolute_error));
    assert(calibration.mean_absolute_error > 0.0 && calibration.mean_absolute_error <= 1.0);
    assert(std::isfinite(calibration.learning_rate_scale));
    assert(calibration.learning_rate_scale > 1.0 && calibration.learning_rate_scale <= 1.5);

    const auto appraisal = brain.affective_appraisal();
    assert(std::isfinite(appraisal.outcome_weight));
    assert(std::isfinite(appraisal.error_weight));
    assert(std::isfinite(appraisal.novelty_weight));
    assert(std::isfinite(appraisal.salience_weight));
    assert(std::isfinite(appraisal.uncertainty_weight));
    assert(std::isfinite(appraisal.tension_error_weight));
}

void assert_prediction_feedback(const Brain& brain) {
    const auto predictions = brain.memory().by_kind("prediction");
    const auto outcomes = brain.memory().by_kind("prediction_outcome");

    // Causal world projections and action-consequence forecasts are different
    // prediction classes. This fixture guarantees feedback for each observed
    // action consequence; it does not claim every causal projection has an
    // observed matching outcome in this controlled test.
    const auto snapshot = brain.snapshot();
    std::size_t action_consequence_predictions = 0;
    for (const auto& prediction : snapshot.predictions) {
        if (prediction.key.rfind("action_consequence|", 0) != 0) continue;
        ++action_consequence_predictions;
        assert(prediction.resolved);
    }
    assert(action_consequence_predictions == 60);
    assert(outcomes.size() == action_consequence_predictions);
    assert(snapshot.predictions.size() == predictions.size());

    const auto* clear_good =
        brain.learning_metric("action_consequence|navigation/clear|good-route");
    const auto* clear_bad =
        brain.learning_metric("action_consequence|navigation/clear|bad-route");
    const auto* flooded_good =
        brain.learning_metric("action_consequence|navigation/flooded|good-route");
    const auto* flooded_bad =
        brain.learning_metric("action_consequence|navigation/flooded|bad-route");
    const auto* tunnel_good =
        brain.learning_metric("action_consequence|navigation/tunnel|good-route");
    const auto* tunnel_bad =
        brain.learning_metric("action_consequence|navigation/tunnel|bad-route");

    assert(clear_good && clear_good->observations >= 18 && clear_good->estimate < 0.0);
    assert(clear_bad && clear_bad->observations >= 18 && clear_bad->estimate > 0.0);
    assert(flooded_good && flooded_good->observations >= 6 && flooded_good->estimate < 0.0);
    assert(flooded_bad && flooded_bad->observations >= 6 && flooded_bad->estimate > 0.0);
    assert(tunnel_good && tunnel_good->observations >= 6 && tunnel_good->estimate > 0.0);
    assert(tunnel_bad && tunnel_bad->observations >= 6 && tunnel_bad->estimate < 0.0);
}
} // namespace

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: jarvis_dlt_002_persistence <train|verify> <journal-path>\n";
        return 64;
    }
    const std::string mode = argv[1];
    const std::filesystem::path journal = argv[2];

    if (mode == "train") {
        std::error_code ec;
        std::filesystem::remove(journal, ec);
        std::filesystem::remove(journal.string() + ".meta", ec);

        Brain brain(journal);
        Goal goal;
        goal.id = goal_id;
        goal.description = "Learn context-sensitive action consequences, revise one context, and preserve the others";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        // Phase A: acquire three context-specific action/outcome mappings.
        // Clear and tunnel share a mapping; flooded has the opposite mapping.
        // No route choice is passed into the learner as a prescribed answer:
        // each update is based on an observed action consequence.
        for (int repetition = 0; repetition < 6; ++repetition) {
            record_experience(brain, clear_context, "good-route", 1.0);
            record_experience(brain, clear_context, "bad-route", -1.0);
            record_experience(brain, flooded_context, "good-route", -1.0);
            record_experience(brain, flooded_context, "bad-route", 1.0);
            record_experience(brain, tunnel_context, "good-route", 1.0);
            record_experience(brain, tunnel_context, "bad-route", -1.0);
        }

        // The learned preference must alter actual action selection, not only
        // internal strategy values. Check behavior after acquisition, before
        // introducing contradictory evidence.
        assert(selected_action(brain, clear_context) == "good-route");

        // Phase B: only the clear context changes. Repeat enough contradictory
        // evidence to require revising its learned preference without erasing
        // the flooded or tunnel mappings. This is harder than merely replaying
        // a fixed pair of context/action associations.
        for (int repetition = 0; repetition < 12; ++repetition) {
            record_experience(brain, clear_context, "good-route", -1.0);
            record_experience(brain, clear_context, "bad-route", 1.0);
        }

        // After reversal, behavior must change in clear without collapsing
        // the separate flooded and tunnel policies. Causal projections are not
        // conflated with the action-consequence forecasts checked below.
        assert(selected_action(brain, clear_context) == "bad-route");
        assert(selected_action(brain, flooded_context) == "bad-route");
        assert(selected_action(brain, tunnel_context) == "good-route");

        assert_strategy_signs(brain);
        assert_prediction_feedback(brain);
        assert_affective_learning(brain);
        assert(brain.memory().by_kind("action_outcome").size() == 60);

        std::cout << "[DLT-002] TRAINED outcomes="
                  << brain.memory().by_kind("action_outcome").size()
                  << " predictions=" << brain.memory().by_kind("prediction").size()
                  << " prediction_outcomes=" << brain.memory().by_kind("prediction_outcome").size()
                  << " clear_context_reversed=true untouched_contexts_preserved=true"
                  << " journal=" << journal.string() << '\n';
        return 0;
    }

    if (mode == "verify") {
        // This executable is invoked in a second OS process by the workflow.
        // The process that trained the brain has exited; all assertions below
        // therefore test journal restoration, not surviving in-memory objects.
        Brain restored(journal);
        assert(restored.goal(goal_id) != nullptr);
        assert(restored.memory().by_kind("action_outcome").size() == 60);
        assert_strategy_signs(restored);
        assert_prediction_feedback(restored);
        assert_affective_learning(restored);

        std::uint64_t clear_bad_uses = 0;
        std::uint64_t flooded_bad_uses = 0;
        std::uint64_t tunnel_good_uses = 0;
        assert(strategy_value(restored, clear_context, "bad-route", &clear_bad_uses) > 0.0);
        assert(strategy_value(restored, flooded_context, "bad-route", &flooded_bad_uses) > 0.0);
        assert(strategy_value(restored, tunnel_context, "good-route", &tunnel_good_uses) > 0.0);
        assert(clear_bad_uses > 0 && flooded_bad_uses > 0 && tunnel_good_uses > 0);

        const auto clear = CognitiveCycle(restored).run(make_input(clear_context));
        assert(clear.status == CognitiveCycleStatus::completed);
        assert(!clear.context.plan.steps.empty());
        assert(clear.context.plan.steps.front().action.name == "bad-route");

        const auto flooded = CognitiveCycle(restored).run(make_input(flooded_context));
        assert(flooded.status == CognitiveCycleStatus::completed);
        assert(!flooded.context.plan.steps.empty());
        assert(flooded.context.plan.steps.front().action.name == "bad-route");

        const auto tunnel = CognitiveCycle(restored).run(make_input(tunnel_context));
        assert(tunnel.status == CognitiveCycleStatus::completed);
        assert(!tunnel.context.plan.steps.empty());
        assert(tunnel.context.plan.steps.front().action.name == "good-route");

        std::cout << "[DLT-002] PASS process_restart=verified "
                  << "clear_choice=bad-route flooded_choice=bad-route tunnel_choice=good-route "
                  << "restored_outcomes=" << restored.memory().by_kind("action_outcome").size()
                  << " resolved_predictions=" << restored.memory().by_kind("prediction_outcome").size()
                  << " context_specific_revision=verified\n";

        std::error_code ec;
        std::filesystem::remove(journal, ec);
        std::filesystem::remove(journal.string() + ".meta", ec);
        return 0;
    }

    std::cerr << "unknown mode: " << mode << '\n';
    return 64;
}
