#include "jarvis/core/cognitive_cycle.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <string>

using namespace jarvis::core;

int main() {
    const auto journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_cycle_suite.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    Brain brain(journal);
    CognitiveCycle cycle(brain);

    Goal goal;
    goal.id = "stabilize";
    goal.description = "Stabilize the observed system";
    goal.priority = 1.0;
    goal.created_cycle = 0;
    assert(brain.create_goal(goal));
    assert(brain.activate_goal(goal.id));

    CognitiveCycleInput input;
    input.observation = Event{0, 0, "sensor", "observation", {{"temperature", 42.0}, {"status", std::string("unstable")}}};
    input.candidate_actions = {
        CandidateAction{"stabilize", 0.9, 0.8, 0.2, 0.1, 1.0, 0.0, 0.8},
        CandidateAction{"inspect", 0.6, 0.5, 0.1, 0.2, 0.5, 0.0, 0.4, DecisionOutcome::recommend},
    };
    input.goal_id = goal.id;
    input.planning_horizon = 2;
    input.memory_limit = 4;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.deadline_pressure = 0.5;
    input.action_constraints = ActionConstraints{0.5, false};

    const auto initial = cycle.run(input);
    assert(initial.status == CognitiveCycleStatus::completed);
    assert(initial.context.plan.steps.front().action.name == "stabilize");
    assert(initial.context.action_assessments.front().developmental_context.find("unstable") != std::string::npos);
    assert(initial.context.action_assessments.front().developmental_context != goal.id);
    assert(brain.knowledge_source("action_executor.stabilize") == nullptr);



    assert(brain.learn(Evidence{"action_executor.stabilize", "action.stabilize", std::string("failed"), 0.0}) >= 0.0);
    const auto learned_metric = brain.knowledge_source("action_executor.stabilize");
    assert(learned_metric != nullptr);
    assert(learned_metric->observations == 1);
    assert(learned_metric->reliability == 0.0);

    const auto adapted = cycle.run(input);
    assert(adapted.status == CognitiveCycleStatus::completed);
    assert(adapted.context.plan.steps.front().action.name == "inspect");
    assert(adapted.context.plan.steps.front().action.risk > input.candidate_actions.front().risk);
    assert(adapted.context.plan.steps.front().action.expected_value < input.candidate_actions.front().expected_value);

    brain.observe_capability("inspect", 0.0, 0.0);
    const auto capability_adapted = cycle.run(input);
    assert(capability_adapted.status == CognitiveCycleStatus::completed);
    assert(capability_adapted.context.plan.steps.front().action.name == "stabilize");
    assert(capability_adapted.context.plan.steps.front().action.expected_value > 0.0);
    assert(capability_adapted.context.plan.steps.front().action.risk < 1.0);
    assert(brain.restore_capability("inspect", 1.0, 1.0));

    brain.observe_capability("stabilize", 1.0, 1.0);
    assert(brain.isolate_capability("stabilize"));
    const auto isolated = cycle.run(input);
    assert(isolated.status == CognitiveCycleStatus::completed);
    assert(isolated.context.plan.steps.front().action.name == "inspect");
    assert(brain.restore_capability("stabilize", 1.0, 1.0));

    assert(adapted.context.observation.event.sequence != 0);
    assert(!adapted.context.beliefs.empty());
    assert(!adapted.context.eligible_goals.empty());
    assert(adapted.context.selected_goal.id == goal.id);
    assert(!adapted.context.plan.steps.empty());
    assert(!adapted.context.decisions.empty());
    assert(adapted.context.decisions.front().action.name == adapted.context.plan.steps.front().action.name);
    assert(adapted.context.decision_context.goal_priority == goal.priority);
    assert(adapted.context.decision_context.plan_expected_value == adapted.context.plan.expected_value);
    assert(adapted.context.decision_context.resource_budget == input.resource_budget);
    assert(adapted.context.decision_context.deadline_pressure >= input.deadline_pressure);
    assert(adapted.context.decision_context.deadline_pressure <= 1.0);
    assert(std::isfinite(adapted.context.decision_context.valence));
    assert(std::isfinite(adapted.context.decision_context.arousal));
    assert(std::isfinite(adapted.context.decision_context.affective_uncertainty));
    assert(std::isfinite(adapted.context.decision_context.tension));
    assert(std::isfinite(adapted.context.decision_context.stability));
    assert(adapted.context.action_assessments.size() == adapted.context.decisions.size());
    assert(adapted.context.action_assessments.front().action.name == adapted.context.decisions.front().action.name);
    assert(adapted.context.action_assessments.front().permitted);

    CognitiveCycleInput constrained = input;
    constrained.action_constraints = ActionConstraints{0.05, false};
    const auto constrained_result = cycle.run(constrained);
    assert(constrained_result.status == CognitiveCycleStatus::completed);
    assert(!constrained_result.context.action_assessments.empty());
    for (const auto& assessment : constrained_result.context.action_assessments) { assert(assessment.disposition == ActionDisposition::reject); assert(!assessment.permitted); }

    const auto prediction = brain.predict("temperature_next", 43.0, 0.8);
    assert(!prediction.key.empty());
    const auto before_reflection = brain.reflect();
    const auto feedback = cycle.process_outcome(prediction, Scalar{45.0}, Evidence{"sensor", "temperature", Scalar{45.0}, 0.9});
    // An inaccurate forecast can still be successfully resolved; only rejected
    // or duplicate feedback should report prediction_resolved=false.
    assert(feedback.prediction_resolved);
    assert(feedback.learned_reliability >= 0.0 && feedback.learned_reliability <= 1.0);
    assert(feedback.reflection.prediction_accuracy >= 0.0 && feedback.reflection.prediction_accuracy <= 1.0);
    const auto metric = brain.learning_metric("temperature_next");
    assert(metric != nullptr);
    assert(metric->observations > 0);
    assert(brain.knowledge_source("sensor") != nullptr);
    const auto duplicate_feedback = cycle.process_outcome(prediction.key, Scalar{45.0});
    assert(!duplicate_feedback.prediction_resolved);
    const auto learned = cycle.learn_from_outcome(Evidence{"sensor", "temperature", 43.0, 0.9});
    assert(learned >= 0.0 && learned <= 1.0);

    CognitiveCycleInput invalid = input;
    invalid.goal_id = "missing-goal";
    const auto invalid_result = cycle.run(invalid);
    assert(invalid_result.status == CognitiveCycleStatus::invalid_goal);

    Brain restored(journal);
    const auto restored_metric = restored.knowledge_source("action_executor.stabilize");
    assert(restored_metric != nullptr);
    assert(restored_metric->reliability == 0.0);

    const auto dispute_journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_dispute_suite.bin";
    // Self-model performance must affect future action selection even when
    // no action_executor knowledge metric exists yet. Reversing the observed
    // competence estimates should reverse the preferred action.
    const auto competence_journal = std::filesystem::temp_directory_path() / "jarvis_cognitive_competence_suite.bin";
    std::filesystem::remove(competence_journal, ec);
    std::filesystem::remove(competence_journal.string() + ".meta", ec);
    {
        Brain competence_brain(competence_journal);
        CognitiveCycle competence_cycle(competence_brain);
        Goal competence_goal;
        competence_goal.id = "competence-goal";
        competence_goal.description = "Choose the more reliable capability";
        competence_goal.priority = 1.0;
        assert(competence_brain.create_goal(competence_goal));
        assert(competence_brain.activate_goal(competence_goal.id));

        CognitiveCycleInput competence_input;
        competence_input.observation = Event{0, 0, "sensor", "observation",
            {{"condition", std::string("stable")}}};
        competence_input.candidate_actions = {
            CandidateAction{"weak", 0.9, 0.9, 0.9, 0.1, 1.0, 0.0, 0.8},
            CandidateAction{"competent", 0.55, 0.6, 0.9, 0.1, 1.0, 0.0, 0.6},
        };
        competence_input.goal_id = competence_goal.id;
        competence_input.planning_horizon = 1;
        competence_input.resource_budget = 1.0;

        competence_brain.observe_capability("weak", 1.0, 0.0);
        competence_brain.observe_capability("competent", 1.0, 1.0);
        auto competence_result = competence_cycle.run(competence_input);
        assert(competence_result.status == CognitiveCycleStatus::completed);
        assert(competence_result.context.plan.steps.front().action.name == "competent");
        assert(competence_brain.knowledge_source("action_executor.weak") == nullptr);

        competence_brain.observe_capability("weak", 1.0, 1.0);
        competence_brain.observe_capability("competent", 1.0, 0.0);
        competence_input.observation = Event{0, 0, "sensor", "observation",
            {{"condition", std::string("changed")}}};
        competence_result = competence_cycle.run(competence_input);
        assert(competence_result.status == CognitiveCycleStatus::completed);
        assert(competence_result.context.plan.steps.front().action.name == "weak");
    }
    std::filesystem::remove(competence_journal, ec);
    std::filesystem::remove(competence_journal.string() + ".meta", ec);
    // Intent selection is part of the integrated cognitive cycle, not only a
    // workspace display. With no caller-selected goal, intent appraisal may
    // choose a lower-progress objective instead of the goal-list fallback.
    const auto intent_journal =
        std::filesystem::temp_directory_path() / "jarvis_cognitive_intent_strategy_suite.bin";
    std::filesystem::remove(intent_journal, ec);
    std::filesystem::remove(intent_journal.string() + ".meta", ec);
    {
        Brain intent_brain(intent_journal);
        Goal nearly_complete;
        nearly_complete.id = "nearly-complete";
        nearly_complete.description = "Maintain a nearly complete objective";
        nearly_complete.priority = 0.8;
        nearly_complete.progress = 0.8;
        nearly_complete.created_cycle = 0;
        assert(intent_brain.create_goal(nearly_complete));
        assert(intent_brain.activate_goal(nearly_complete.id));

        Goal developing;
        developing.id = "developing-objective";
        developing.description = "Advance an objective with more progress remaining";
        developing.priority = 0.8;
        developing.progress = 0.0;
        developing.created_cycle = 1;
        assert(intent_brain.create_goal(developing));
        assert(intent_brain.activate_goal(developing.id));

        CognitiveCycleInput intent_input;
        intent_input.observation =
            Event{0, 0, "sensor", "observation", {{"state", std::string("stable")}}};
        intent_input.candidate_actions = {
            CandidateAction{"continue", 0.8, 0.8, 0.1, 0.1},
        };
        intent_input.planning_horizon = 1;
        intent_input.resource_budget = 10.0;
        const auto intent_result = CognitiveCycle(intent_brain).run(intent_input);
        assert(intent_result.status == CognitiveCycleStatus::completed);
        assert(intent_result.context.selected_goal.id == developing.id);
        assert(intent_result.context.decision_context.goal_priority == developing.priority);
        assert(intent_result.context.decision_context.goal_progress == 0.0);
    }
    std::filesystem::remove(intent_journal, ec);
    std::filesystem::remove(intent_journal.string() + ".meta", ec);

    // Strategy appraisal must carry experience-derived goal momentum into the
    // main planning path, rather than existing only as a standalone model.
    const auto strategy_journal =
        std::filesystem::temp_directory_path() / "jarvis_cognitive_strategy_feedback_suite.bin";
    std::filesystem::remove(strategy_journal, ec);
    std::filesystem::remove(strategy_journal.string() + ".meta", ec);
    {
        Brain strategy_brain(strategy_journal);
        Goal progressing;
        progressing.id = "experience-shaped-goal";
        progressing.description = "Learn from changing progress";
        progressing.priority = 0.5;
        assert(strategy_brain.create_goal(progressing));
        assert(strategy_brain.activate_goal(progressing.id));
        assert(strategy_brain.assimilate_goal_outcome(
            GoalOutcomeEvidence{progressing.id, 0.0, 0.5, 0.0, false, 0.9, 1}));
        assert(strategy_brain.assimilate_goal_outcome(
            GoalOutcomeEvidence{progressing.id, 0.5, 0.75, 0.0, false, 0.9, 2}));
        const auto* experienced_goal = strategy_brain.goal(progressing.id);
        assert(experienced_goal != nullptr);
        const double unappraised_priority = experienced_goal->priority;
        assert(experienced_goal->outcome_momentum > 0.0);

        CognitiveCycleInput strategy_input;
        strategy_input.observation =
            Event{0, 0, "sensor", "observation", {{"state", std::string("stable")}}};
        strategy_input.candidate_actions = {
            CandidateAction{"continue", 0.8, 0.8, 0.1, 0.1},
        };
        strategy_input.planning_horizon = 1;
        strategy_input.resource_budget = 10.0;
        const auto strategy_result = CognitiveCycle(strategy_brain).run(strategy_input);
        assert(strategy_result.status == CognitiveCycleStatus::completed);
        assert(strategy_result.context.selected_goal.id == progressing.id);
        assert(strategy_result.context.decision_context.goal_priority >
               unappraised_priority);
    }
    std::filesystem::remove(strategy_journal, ec);
    std::filesystem::remove(strategy_journal.string() + ".meta", ec);

    // Consequence expectations start from caller input when no matching
    // experience exists, then become grounded in observed local outcomes.
    const auto expectation_journal =
        std::filesystem::temp_directory_path() / "jarvis_cognitive_expectation_suite.bin";
    std::filesystem::remove(expectation_journal, ec);
    std::filesystem::remove(expectation_journal.string() + ".meta", ec);
    {
        Brain expectation_brain(expectation_journal);
        Goal expectation_goal;
        expectation_goal.id = "learn-consequence";
        expectation_goal.description = "Learn action consequences from experience";
        expectation_goal.priority = 1.0;
        assert(expectation_brain.create_goal(expectation_goal));
        assert(expectation_brain.activate_goal(expectation_goal.id));

        CognitiveCycleInput expectation_input;
        expectation_input.observation = Event{0, 0, "sensor", "observation",
            {{"status", std::string("stable")}, {"location", std::string("test-area")}}};
        expectation_input.candidate_actions = {
            CandidateAction{"probe-route", 0.8, 0.7, 0.8, 0.1, 1.0, 0.0, 0.25},
        };
        expectation_input.goal_id = expectation_goal.id;
        expectation_input.planning_horizon = 1;
        expectation_input.memory_limit = 16;

        CognitiveCycle expectation_cycle(expectation_brain);
        const auto without_history = expectation_cycle.run(expectation_input);
        assert(without_history.status == CognitiveCycleStatus::completed);
        assert(std::abs(without_history.context.plan.steps.front().action.expected_consequence - 0.25) < 1e-12);
        const auto context = without_history.context.action_assessments.front().developmental_context;

        assert(expectation_brain.observe(Event{0, 0, "executor", "action_outcome",
            {{"action", std::string("probe-route")},
             {"context", context},
             {"observed", true},
             {"expected_consequence", 0.25},
             {"actual_consequence", 0.8},
             {"consequence_error", 0.55},
             {"evidence_reliability", 1.0},
             {"reliability", 1.0}}}).event.sequence != 0);

        const auto with_history = expectation_cycle.run(expectation_input);
        assert(with_history.status == CognitiveCycleStatus::completed);
        assert(std::abs(with_history.context.plan.steps.front().action.expected_consequence - 0.8) < 1e-12);
    }
    std::filesystem::remove(expectation_journal, ec);
    std::filesystem::remove(expectation_journal.string() + ".meta", ec);

    std::filesystem::remove(dispute_journal, ec);
    std::filesystem::remove(dispute_journal.string() + ".meta", ec);
    Brain dispute_brain(dispute_journal);
    CognitiveCycle dispute_cycle(dispute_brain);
    Goal dispute_goal;
    dispute_goal.id = "respond";
    dispute_goal.description = "Respond to uncertain sensor state";
    dispute_goal.priority = 1.0;
    assert(dispute_brain.create_goal(dispute_goal));
    assert(dispute_brain.activate_goal(dispute_goal.id));
    CognitiveCycleInput dispute_input;
    dispute_input.observation = Event{0, 0, "sensor", "observation", {{"temperature", 20.0}}};
    dispute_input.candidate_actions = {
        CandidateAction{"commit", 0.0, 0.50, 0.0, 0.0, 0.0, 0.0, 0.0},
        CandidateAction{"inspect", 0.0, 0.47, 0.0, 0.1, 1.0, 0.0, 0.0},
    };
    dispute_input.goal_id = dispute_goal.id;
    dispute_input.planning_horizon = 1;
    dispute_input.reasoning_steps = 2;
    dispute_input.resource_budget = 1.0;
    dispute_input.action_constraints = ActionConstraints{1.0, false};
    const auto clear_result = dispute_cycle.run(dispute_input);
    assert(clear_result.status == CognitiveCycleStatus::completed);
    assert(clear_result.context.plan.steps.front().action.name == "commit");
    const double clear_uncertainty = clear_result.context.decision_context.uncertainty;
    dispute_input.observation = Event{0, 0, "sensor", "observation", {{"temperature", 80.0}}};
    const auto disputed_result = dispute_cycle.run(dispute_input);
    assert(disputed_result.status == CognitiveCycleStatus::completed);
    assert(disputed_result.context.plan.steps.front().action.name == "inspect");
    assert(disputed_result.context.decision_context.uncertainty > clear_uncertainty);
    bool found_disputed_temperature = false;
    for (const auto& belief : disputed_result.context.beliefs) if (belief.key == "temperature") { found_disputed_temperature = belief.disputed; assert(belief.confidence < 0.5); }
    assert(found_disputed_temperature);

    // Partial direct experience must not suppress transfer for an action
    // that has not yet been tried in the current context. The exact context
    // knows one route is harmful; a related context knows the alternative works.
    const auto generalization_gap_journal =
        std::filesystem::temp_directory_path() / "jarvis_cognitive_generalization_gap_suite.bin";
    std::filesystem::remove(generalization_gap_journal, ec);
    std::filesystem::remove(generalization_gap_journal.string() + ".meta", ec);
    {
        Brain generalization_brain(generalization_gap_journal);
        constexpr int evidence_count = 6;
        for (int i = 0; i < evidence_count; ++i) {
            assert(generalization_brain.observe(Event{0, 0, "generalization-gap", "action_outcome",
                {{"action", std::string("good-route")},
                 {"context", std::string("navigation route")},
                 {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
                 {"observed", true},
                 {"expected_consequence", 1.0},
                 {"actual_consequence", 1.0},
                 {"consequence_error", 0.0},
                 {"reliability", 1.0},
                 {"salience", 0.8},
                 {"novelty", 0.2}}}).event.sequence != 0);
            assert(generalization_brain.observe(Event{0, 0, "generalization-gap", "action_outcome",
                {{"action", std::string("bad-route")},
                 {"context", std::string("navigation route variant")},
                 {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
                 {"observed", true},
                 {"expected_consequence", 1.0},
                 {"actual_consequence", -1.0},
                 {"consequence_error", 2.0},
                 {"reliability", 1.0},
                 {"salience", 0.8},
                 {"novelty", 0.2}}}).event.sequence != 0);
        }

        Goal generalization_goal;
        generalization_goal.id = "generalization-gap-goal";
        generalization_goal.description = "Choose the better route using direct and transferred experience";
        generalization_goal.priority = 1.0;
        assert(generalization_brain.create_goal(generalization_goal));
        assert(generalization_brain.activate_goal(generalization_goal.id));

        CognitiveCycleInput generalization_input;
        generalization_input.observation = Event{0, 0, "sensor", "observation",
            {{"condition", std::string("new navigation condition")}}};
        generalization_input.candidate_actions = {
            CandidateAction{"bad-route", 1.0, 1.0, 0.9, 0.1},
            CandidateAction{"good-route", 0.0, 0.0, 0.9, 0.1},
        };
        generalization_input.goal_id = generalization_goal.id;
        generalization_input.developmental_context = "navigation route variant";
        generalization_input.planning_horizon = 1;
        generalization_input.resource_budget = 10.0;

        const auto generalized_decision = CognitiveCycle(generalization_brain).run(generalization_input);
        assert(generalized_decision.status == CognitiveCycleStatus::completed);
        assert(!generalized_decision.context.plan.steps.empty());
        // Without fallback transfer, the untried good route has no local bias
        // and loses to the initially preferred bad route.
        assert(generalized_decision.context.plan.steps.front().action.name == "good-route");
    }
    std::filesystem::remove(generalization_gap_journal, ec);
    std::filesystem::remove(generalization_gap_journal.string() + ".meta", ec);

    // Isolate context inference checks from the preceding action-learning
    // scenario so sensor observations cannot perturb its decision assertions.
    const auto context_journal =
        std::filesystem::temp_directory_path() / "jarvis_cognitive_context_suite.bin";
    std::filesystem::remove(context_journal, ec);
    std::filesystem::remove(context_journal.string() + ".meta", ec);
    {
        Brain context_brain(context_journal);
        Goal context_goal;
        context_goal.id = "numeric-context-goal";
        context_goal.description = "Classify numeric observations for learning";
        context_goal.priority = 1.0;
        assert(context_brain.create_goal(context_goal));
        assert(context_brain.activate_goal(context_goal.id));
        CognitiveCycleInput numeric_context_input;
        numeric_context_input.observation =
            Event{0, 0, "sensor", "observation", {{"temperature", 42.0}}};
        numeric_context_input.candidate_actions = {
            CandidateAction{"inspect", 0.6, 0.5, 0.1, 0.2, 0.5, 0.0, 0.4},
        };
        numeric_context_input.goal_id = context_goal.id;
        numeric_context_input.planning_horizon = 1;
        const auto numeric_context_result =
            CognitiveCycle(context_brain).run(numeric_context_input);
        assert(numeric_context_result.status == CognitiveCycleStatus::completed);
        const auto numeric_context =
            numeric_context_result.context.action_assessments.front().developmental_context;
        assert(numeric_context != context_goal.id);
        assert(numeric_context.find("temperature") != std::string::npos);
        assert(numeric_context.find("scale") != std::string::npos);

        numeric_context_input.observation =
            Event{0, 0, "sensor", "observation", {{"temperature", 80.0}}};
        const auto higher_numeric_context_result =
            CognitiveCycle(context_brain).run(numeric_context_input);
        assert(higher_numeric_context_result.status == CognitiveCycleStatus::completed);
        const auto higher_numeric_context =
            higher_numeric_context_result.context.action_assessments.front().developmental_context;
        assert(higher_numeric_context != numeric_context);

        numeric_context_input.developmental_context = "caller-defined-context";
        const auto explicit_context_result =
            CognitiveCycle(context_brain).run(numeric_context_input);
        assert(explicit_context_result.status == CognitiveCycleStatus::completed);
        assert(explicit_context_result.context.action_assessments.front().developmental_context ==
               "caller-defined-context");
    }
    std::filesystem::remove(context_journal, ec);
    std::filesystem::remove(context_journal.string() + ".meta", ec);

    // Perceptual confidence is part of the evidence used by planning.
    // A low-confidence interpretation must raise decision uncertainty rather
    // than remain a display-only property of the representation.
    const auto perception_confidence_journal =
        std::filesystem::temp_directory_path() / "jarvis_cognitive_perception_confidence_suite.bin";
    std::filesystem::remove(perception_confidence_journal, ec);
    std::filesystem::remove(perception_confidence_journal.string() + ".meta", ec);
    {
        Brain perception_brain(perception_confidence_journal);
        Goal perception_goal;
        perception_goal.id = "interpret-observation";
        perception_goal.description = "Interpret uncertain sensory evidence";
        perception_goal.priority = 1.0;
        assert(perception_brain.create_goal(perception_goal));
        assert(perception_brain.activate_goal(perception_goal.id));

        CognitiveCycleInput perception_input;
        perception_input.observation = Event{0, 0, "sensor", "observation",
            {{"reading", 17.0}, {"confidence", 0.1}}};
        perception_input.candidate_actions = {
            CandidateAction{"inspect", 0.6, 0.5, 0.1, 0.2},
        };
        perception_input.goal_id = perception_goal.id;
        perception_input.planning_horizon = 1;
        const auto perception_result = CognitiveCycle(perception_brain).run(perception_input);
        assert(perception_result.status == CognitiveCycleStatus::completed);
        assert(std::abs(perception_result.context.representation.confidence - 0.1) < 1e-12);
        assert(perception_result.context.decision_context.uncertainty >= 0.9);
    }
    std::filesystem::remove(perception_confidence_journal, ec);
    std::filesystem::remove(perception_confidence_journal.string() + ".meta", ec);

    std::filesystem::remove(dispute_journal, ec);
    std::filesystem::remove(dispute_journal.string() + ".meta", ec);
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
