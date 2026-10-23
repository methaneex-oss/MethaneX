#include "jarvis/core/cognitive_runtime.hpp"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

using namespace jarvis::core;

namespace {
CognitiveCycleInput make_input(const std::string& goal_id, int episode,
                               const std::string& condition) {
    CognitiveCycleInput input;
    input.observation = Event{0, 0, "developmental_world", "observation",
        {{"episode", static_cast<std::int64_t>(episode)},
         {"task", std::string("reach_destination")},
         {"route_condition", condition},
         {"bridge_status", std::string(condition == "flooded" ? "closed" : "open")},
         {"visibility", std::string(condition == "flooded" ? "poor" : "clear")}}};

    // The world offers choices but never tells JARVIS which one is correct.
    input.candidate_actions = {
        CandidateAction{"bad-route", 2.5, 0.5, 0.9, 0.1},
        CandidateAction{"good-route", 2.5, 0.5, 0.9, 0.1},
    };
    input.goal_id = goal_id;
    input.developmental_context = condition == "flooded"
        ? "navigation/route-variant" : "navigation/route-selection";
    input.planning_horizon = 1;
    input.memory_limit = 8;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.action_constraints = ActionConstraints{1.0, false};
    return input;
}

CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int i = 0; i < 1000; ++i) {
        if (auto result = runtime.poll_result()) return *result;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    throw std::runtime_error("Timed out waiting for JARVIS to finish an episode");
}
} // namespace

int main(int argc, char** argv) {
    const bool persistent_journal = argc > 1;
    const auto journal = persistent_journal
        ? std::filesystem::path(argv[1])
        : std::filesystem::temp_directory_path() / "jarvis_developmental_world_demo.bin";

    std::error_code ec;
    if (!persistent_journal) {
        std::filesystem::remove(journal, ec);
        std::filesystem::remove(journal.string() + ".meta", ec);
    }

    Brain brain(journal);
    const std::string goal_id = "developmental-world-goal";
    if (brain.goal(goal_id) == nullptr) {
        Goal goal;
        goal.id = goal_id;
        goal.description = "Reach the destination while learning from consequences";
        goal.priority = 1.0;
        if (!brain.create_goal(goal)) {
            std::cerr << "Could not create the developmental-world goal\n";
            return 1;
        }
    }
    brain.activate_goal(goal_id);

    std::string condition = "clear";
    CognitiveRuntimeConfig config;
    config.input_capacity = 8;
    config.result_capacity = 8;
    config.feedback_capacity = 8;
    config.drain_on_stop = true;
    config.action_adapter.authorization.maximum_risk = 1.0;
    config.action_adapter.execute = [](const CandidateAction&) { return true; };
    config.action_adapter.verify = [](const CandidateAction&) { return true; };
    config.action_adapter.observe_consequence = [&](const CandidateAction& action) {
        const bool good_route = action.name == "good-route";
        const bool succeeds = condition == "flooded" ? !good_route : good_route;
        return succeeds ? 1.0 : -1.0;
    };

    CognitiveRuntime runtime(brain, config);
    if (!runtime.start()) {
        std::cerr << "Could not start the cognitive runtime\n";
        return 1;
    }

    std::cout << "JARVIS DEVELOPMENTAL WORLD\n"
              << "Task: reach a destination; choose between two routes.\n"
              << "Feedback comes from the simulated world, not a route label.\n"
              << "Episodes 0-7: clear conditions. Episodes 8-23: conditions reverse.\n\n";

    constexpr int total_episodes = 24;
    for (int episode = 0; episode < total_episodes; ++episode) {
        condition = episode < 8 ? "clear" : "flooded";
        auto input = make_input(goal_id, episode, condition);
        if (episode == 0) {
            // Separate a simulated executor outage from route-quality evidence.
            config.action_adapter.execute = [](const CandidateAction&) { return true; };
        }
        if (!runtime.submit(input, 1.0)) {
            std::cerr << "Environment could not submit episode " << episode << '\n';
            runtime.stop();
            return 1;
        }

        const auto result = await_result(runtime);
        if (result.status != CognitiveCycleStatus::completed ||
            result.context.plan.steps.empty()) {
            std::cerr << "JARVIS could not complete episode " << episode
                      << ": " << result.error << '\n';
            runtime.stop();
            return 1;
        }

        std::cout << "episode=" << episode
                  << " condition=" << condition
                  << " chose=" << result.context.plan.steps.front().action.name;
        for (const auto& execution : result.context.action_execution_results) {
            if (execution.outcome.observed) {
                std::cout << " | outcome(" << execution.action.name << ")="
                          << execution.outcome.actual_consequence;
            } else {
                std::cout << " | outcome(" << execution.action.name << ")=unobserved";
            }
        }
        std::cout << '\n';
    }

    runtime.stop();
    std::cout << "\nLEARNED STRATEGIES\n";
    for (const auto& strategy : brain.developmental_strategies()) {
        if (strategy.context == "navigation/route-selection" ||
            strategy.context == "navigation/route-variant") {
            std::cout << "context=" << strategy.context
                      << " action=" << strategy.action
                      << " value=" << strategy.value
                      << " uses=" << strategy.uses << '\n';
        }
    }
    std::cout << "processed_episodes=" << runtime.metrics().processed
              << " journal_events=" << brain.memory().all().size()
              << "\njournal=" << journal.string() << '\n';
    return 0;
}
