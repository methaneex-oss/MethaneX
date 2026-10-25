#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/developmental_environment.hpp"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

namespace {
CognitiveCycleInput training_input(const std::string& goal_id,
                                   const DevelopmentalEnvironment& world) {
    CognitiveCycleInput input;
    input.observation = world.observe();
    // The environment offers both actions. It does not choose for the brain.
    // Keep the actions executable even after a negative strategy update.
    // Otherwise the action model can switch to "recommend" for every option,
    // preventing the brain from collecting the next outcome needed to learn.
    input.candidate_actions = {
        CandidateAction{"bad-route", 2.5, 0.5, 0.9, 0.1},
        CandidateAction{"good-route", 2.5, 0.5, 0.9, 0.1},
    };
    input.goal_id = goal_id;
    input.developmental_context = world.context();
    input.planning_horizon = 1;
    input.memory_limit = 8;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.action_constraints = ActionConstraints{1.0, false};
    return input;
}

CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int attempt = 0; attempt < 500; ++attempt) {
        if (auto result = runtime.poll_result()) return *result;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    assert(false && "timed out waiting for a developmental training episode");
    return {};
}
} // namespace

int main() {
    const auto journal = std::filesystem::temp_directory_path() /
                        "jarvis_developmental_training_environment.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    std::vector<std::string> executed_actions;
    DevelopmentalEnvironment world(
        "reach_destination", "navigation/route-selection",
        {{"route_condition", std::string("clear")},
         {"bridge_status", std::string("open")},
         {"visibility", std::string("clear")}},
        [](const std::string& action, const Attributes& state)
            -> std::optional<DevelopmentalTransition> {
            if (action != "good-route" && action != "bad-route") return std::nullopt;
            const auto condition = std::get<std::string>(state.at("route_condition"));
            const bool original_route_works = action == "good-route";
            const bool route_works = condition == "flooded"
                ? !original_route_works : original_route_works;
            return DevelopmentalTransition{route_works ? 1.0 : -1.0, std::nullopt};
        });
    auto set_world_condition = [&](const std::string& condition) {
        world.set_state({{"route_condition", condition},
                         {"bridge_status", std::string(condition == "flooded" ? "closed" : "open")},
                         {"visibility", std::string(condition == "flooded" ? "poor" : "clear")}});
    };
    CognitiveRuntimeConfig config;
    config.input_capacity = 32;
    config.result_capacity = 32;
    config.feedback_capacity = 32;
    config.drain_on_stop = true;
    config.action_adapter.authorization.maximum_risk = 1.0;
    // Episode zero simulates a total executor outage. Even if the plan contains
    // multiple actions, none can produce a real-world consequence in that episode.
    std::int64_t current_episode = -1;
    std::string current_context = "navigation/route-selection";
    std::string current_route_condition = "clear";
    config.action_adapter.execute = [&](const CandidateAction& action) {
        executed_actions.push_back(action.name);
        if (current_episode == 0) {
            (void)world.step(action.name, false);
            return false;
        }
        return true;
    };
    config.action_adapter.verify = [](const CandidateAction&) { return true; };
    config.action_adapter.observe_consequence = [&](const CandidateAction& action) {
        // The environment owns the transition rules. The brain receives
        // only the observation and the consequence of the action it selected.
        const auto outcome = world.step(action.name);
        return outcome.consequence;
    };

    std::vector<std::string> episode_actions;
    std::vector<std::string> reversal_actions;
    {
        Brain brain(journal);
        Goal goal;
        goal.id = "training-navigation-goal";
        goal.description = "Reach the destination with positive consequences";
        goal.priority = 1.0;
        assert(brain.create_goal(goal));
        assert(brain.activate_goal(goal.id));

        CognitiveRuntime runtime(brain, config);
        assert(runtime.start());

        constexpr std::int64_t episode_count = 8;
        for (std::int64_t episode = 0; episode < episode_count; ++episode) {
            current_episode = episode;
            current_route_condition = "clear";
            set_world_condition(current_route_condition);
            // Keep an executor outage separate from route selection: failed
            // execution produces no observed world consequence.
            world.set_context(episode == 0 ? "infrastructure/executor-outage"
                                           : "navigation/route-selection");
            auto input = training_input(goal.id, world);
            current_context = input.developmental_context;
            assert(runtime.submit(input, 1.0));
            const auto result = await_result(runtime);
            assert(result.status == CognitiveCycleStatus::completed);
            assert(!result.context.plan.steps.empty());
            // One-step plans must execute only the selected action, not every
            // candidate assessment. Otherwise the learner receives outcomes for
            // actions it did not choose.
            assert(result.context.action_execution_results.size() == 1);
            assert(result.context.action_execution_results.front().action.name ==
                   result.context.plan.steps.front().action.name);
            // The selected observation must expose the environment state that
            // the action/outcome loop is testing, not just an episode counter.
            assert(std::get<std::string>(result.context.observation.event.data.at("route_condition")) == current_route_condition);
            assert(result.context.observation.event.data.contains("bridge_status"));
            assert(result.context.observation.event.data.contains("visibility"));
            episode_actions.push_back(result.context.plan.steps.front().action.name);
            std::cout << "[experience] episode=" << episode
                      << " condition=" << current_route_condition
                      << " context=" << input.developmental_context
                      << " selected=" << episode_actions.back();
            if (result.context.action_execution_results.empty()) {
                std::cout << " outcome=none";
            } else {
                for (const auto& execution : result.context.action_execution_results) {
                    std::cout << " | " << execution.action.name
                              << " status=" << static_cast<int>(execution.status)
                              << " observed=" << std::boolalpha << execution.outcome.observed;
                    if (execution.outcome.observed) {
                        std::cout << " consequence=" << execution.outcome.actual_consequence;
                    }
                }
            }
            std::cout << '\n';

            if (episode == 0) {
                assert(runtime.running());
                bool observed_executor_failure = false;
                for (const auto& execution : result.context.action_execution_results) {
                    if (execution.status == ActionExecutionStatus::failed) {
                        observed_executor_failure = true;
                        break;
                    }
                }
                assert(observed_executor_failure);
                // Every execution failed before a consequence could be observed.
                // The failure may inform the outage context, but must not create
                // a route preference in the navigation context.
                assert(!result.context.action_execution_results.empty());
                for (const auto& execution : result.context.action_execution_results) {
                    assert(execution.status == ActionExecutionStatus::failed);
                    assert(!execution.outcome.observed);
                }
                const auto* outage_strategy =
                    brain.developmental_best_strategy("infrastructure/executor-outage");
                assert(outage_strategy != nullptr);
                assert(outage_strategy->value < 0.0);
                for (const auto& strategy : brain.developmental_strategies()) {
                    assert(strategy.context != "navigation/route-selection");
                }
            }
        }

        // Contradictory-evidence milestone: a strategy learned in the original
        // context initially transfers to a related context. There, environmental
        // conditions reverse. The first choice should reflect prior experience,
        // but subsequent real consequences must revise the local strategy rather
        // than making the transferred belief permanent.
        constexpr std::int64_t reversal_episode_count = 24;
        for (std::int64_t offset = 0; offset < reversal_episode_count; ++offset) {
            current_episode = episode_count + offset;
            current_context = "navigation/route-variant";
            current_route_condition = "flooded";
            set_world_condition(current_route_condition);
            world.set_context(current_context);
            auto input = training_input(goal.id, world);
            assert(runtime.submit(input, 1.0));
            const auto result = await_result(runtime);
            assert(result.status == CognitiveCycleStatus::completed);
            assert(!result.context.plan.steps.empty());
            // The environment should return one consequence for the action
            // actually selected by this one-step plan.
            assert(result.context.action_execution_results.size() == 1);
            assert(result.context.action_execution_results.front().action.name ==
                   result.context.plan.steps.front().action.name);
            assert(std::get<std::string>(result.context.observation.event.data.at("route_condition")) == current_route_condition);
            assert(result.context.observation.event.data.contains("bridge_status"));
            assert(result.context.observation.event.data.contains("visibility"));
            reversal_actions.push_back(result.context.plan.steps.front().action.name);
            std::cout << "[contradiction] episode=" << current_episode
                      << " condition=" << current_route_condition
                      << " context=" << current_context
                      << " selected=" << reversal_actions.back();
            for (const auto& execution : result.context.action_execution_results) {
                std::cout << " | " << execution.action.name
                          << " observed=" << std::boolalpha << execution.outcome.observed;
                if (execution.outcome.observed) {
                    std::cout << " consequence=" << execution.outcome.actual_consequence;
                }
            }
            std::cout << '\n';
            assert(!result.context.action_execution_results.empty());
            bool consequence_observed = false;
            for (const auto& execution : result.context.action_execution_results) {
                consequence_observed = consequence_observed || execution.outcome.observed;
            }
            assert(consequence_observed);
        }
        runtime.stop();

        // These are behavioral acceptance criteria, not just checks that
        // events were stored: the same brain must change its later choice.
        assert(episode_actions.front() == "bad-route");
        assert(episode_actions.back() == "good-route");
        assert(runtime.metrics().processed == episode_count + reversal_episode_count);
        assert(runtime.metrics().action_succeeded > 0);
        assert(reversal_actions.front() == "good-route");
        assert(reversal_actions.back() == "bad-route");

        // Environment task/context/step labels remain available in the
        // episodic journal, but are not treated as changing world facts.
        const auto learned_beliefs = brain.beliefs();
        for (const auto& belief : learned_beliefs) {
            assert(belief.key != "task");
            assert(belief.key != "context");
            assert(belief.key != "world_step");
        }
        assert(!brain.memory().by_kind("observation").empty());
        assert(!learned_beliefs.empty());

        const auto strategies = brain.developmental_strategies();
        bool learned_good_route = false;
        bool revised_variant_good_route = false;
        bool learned_variant_bad_route = false;
        for (const auto& strategy : strategies) {
            if (strategy.context == "navigation/route-selection" &&
                strategy.action == "good-route" && strategy.value > 0.0 &&
                strategy.uses > 0) {
                learned_good_route = true;
            }
            if (strategy.context == "navigation/route-variant" &&
                strategy.action == "good-route" && strategy.value < 0.0 &&
                strategy.uses > 0) {
                revised_variant_good_route = true;
            }
            if (strategy.context == "navigation/route-variant" &&
                strategy.action == "bad-route" && strategy.value > 0.0 &&
                strategy.uses > 0) {
                learned_variant_bad_route = true;
            }
        }
        // The original context keeps its useful knowledge while the related
        // context learns the exception from its own contradictory outcomes.
        assert(learned_good_route);
        assert(revised_variant_good_route);
        assert(learned_variant_bad_route);
        assert(!brain.memory().by_kind("action_outcome").empty());
        std::cout << "[learned-state] route-selection good-route="
                  << brain.developmental_best_strategy("navigation/route-selection")->value
                  << " route-variant bad-route="
                  << brain.developmental_best_strategy("navigation/route-variant")->value
                  << " action_outcomes=" << brain.memory().by_kind("action_outcome").size()
                  << " processed_episodes=" << runtime.metrics().processed << '\n';
    }

    // The second phase starts a fresh Brain from the same persistent journal.
    // It must retain the strategy and select the useful route without relearning.
    {
        Brain restored(journal);
        Goal goal;
        goal.id = "training-navigation-goal";
        goal.description = "Reach the destination with positive consequences";
        goal.priority = 1.0;
        assert(restored.goal(goal.id) != nullptr);

        world.set_context("navigation/route-selection");
        set_world_condition("clear");
        CognitiveCycleInput probe = training_input(goal.id, world);
        const auto decision = CognitiveCycle(restored).run(probe);
        assert(decision.status == CognitiveCycleStatus::completed);
        assert(!decision.context.plan.steps.empty());
        assert(decision.context.plan.steps.front().action.name == "good-route");
        assert(restored.developmental_best_strategy("navigation/route-selection") != nullptr);

        // The exception learned from contradictory outcomes is context-specific
        // and survives replay: the route variant now prefers bad-route.
        world.set_context("navigation/route-variant");
        set_world_condition("flooded");
        CognitiveCycleInput revised_probe = training_input(goal.id, world);
        const auto revised = CognitiveCycle(restored).run(revised_probe);
        assert(revised.status == CognitiveCycleStatus::completed);
        assert(!revised.context.plan.steps.empty());
        assert(revised.context.plan.steps.front().action.name == "bad-route");

        // The original useful strategy still generalizes to a different related
        // context that has no direct experience of its own.
        world.set_context("navigation/route-selection alternate");
        set_world_condition("clear");
        CognitiveCycleInput related_probe = training_input(goal.id, world);
        related_probe.developmental_context = "navigation/route-selection alternate";
        const auto generalized = CognitiveCycle(restored).run(related_probe);
        assert(generalized.status == CognitiveCycleStatus::completed);
        assert(!generalized.context.plan.steps.empty());
        assert(generalized.context.plan.steps.front().action.name == "good-route");
        std::cout << "[restart-probe] original=good-route revised=bad-route generalized=good-route"
                  << " restored_events=" << restored.memory().all().size() << '\n';

        // Transfer must remain bounded: navigation experience must not dictate
        // a choice in an unrelated task where the candidates are otherwise tied.
        world.set_context("orbital/cooking");
        set_world_condition("clear");
        CognitiveCycleInput unrelated_probe = training_input(goal.id, world);
        unrelated_probe.developmental_context = "orbital/cooking";
        // Use unseen action names so global capability reliability learned for
        // the route actions cannot confound this context-transfer check.
        unrelated_probe.candidate_actions = {
            CandidateAction{"unrelated-first", 0.5, 0.5, 0.9, 0.1},
            CandidateAction{"unrelated-second", 0.5, 0.5, 0.9, 0.1},
        };
        const auto unrelated = CognitiveCycle(restored).run(unrelated_probe);
        assert(unrelated.status == CognitiveCycleStatus::completed);
        assert(!unrelated.context.plan.steps.empty());
        assert(unrelated.context.plan.steps.front().action.name == "unrelated-first");
    }

    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);
    return 0;
}
