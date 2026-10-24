#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/developmental_world.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

namespace {
volatile std::sig_atomic_t stop_requested = 0;
void request_stop(int) { stop_requested = 1; }

CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        if (auto result = runtime.poll_result()) return *result;
        if (stop_requested) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    throw std::runtime_error("Timed out or interrupted while waiting for cognitive cycle");
}

CognitiveCycleInput make_input(const Goal& goal, const DevelopmentalWorld& world) {
    CognitiveCycleInput input;
    input.observation = world.observe().event;
    for (const auto& action : world.available_actions())
        input.candidate_actions.push_back(CandidateAction{action, 2.5, 0.5, 0.9, 0.1});
    input.goal_id = goal.id;
    input.developmental_context = world.config().context;
    input.planning_horizon = 1;
    input.memory_limit = 8;
    input.reasoning_steps = 4;
    input.resource_budget = 10.0;
    input.action_constraints = ActionConstraints{1.0, false};
    return input;
}

double strategy_value(const Brain& brain, const std::string& context, const std::string& action) {
    for (const auto& strategy : brain.developmental_strategies())
        if (strategy.context == context && strategy.action == action) return strategy.value;
    return 0.0;
}
} // namespace

int main(int argc, char** argv) {
    const auto duration_seconds = argc > 1 ? std::stoll(argv[1]) : 7200LL;
    const auto checkpoint_seconds = argc > 2 ? std::stoll(argv[2]) : 60LL;
    const std::filesystem::path output_dir = argc > 3 ? argv[3] : "dlt-001-results";
    if (duration_seconds <= 0 || checkpoint_seconds <= 0)
        throw std::invalid_argument("duration and checkpoint interval must be positive");

    std::filesystem::create_directories(output_dir);
    const auto journal = output_dir / "brain-journal.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    std::signal(SIGINT, request_stop);
    std::signal(SIGTERM, request_stop);

    std::ofstream episodes(output_dir / "episodes.csv", std::ios::out | std::ios::trunc);
    std::ofstream checkpoints(output_dir / "checkpoints.csv", std::ios::out | std::ios::trunc);
    std::ofstream report(output_dir / "trial.log", std::ios::out | std::ios::trunc);
    if (!episodes || !checkpoints || !report)
        throw std::runtime_error("Could not create DLT-001 output files");

    episodes << "episode,elapsed_seconds,phase,route_condition,selected_action,consequence,cycle_status,observation_count,outcome_count,prediction_count,prediction_outcome_count\n";
    checkpoints << "elapsed_seconds,phase,episodes,clear_good,clear_bad,flooded_good,flooded_bad,total_reward,good_route_value,bad_route_value,observations,outcomes,predictions,prediction_outcomes\n";
    episodes << std::unitbuf;
    checkpoints << std::unitbuf;
    report << std::unitbuf;

    DevelopmentalWorldConfig world_config;
    world_config.task = "reach_destination";
    world_config.context = "navigation/route-selection";
    world_config.initial_state = {
        {"route_condition", std::string("clear")},
        {"bridge_status", std::string("open")},
        {"visibility", std::string("clear")},
    };
    world_config.initial_resources = 100.0;
    world_config.random_seed = 20261024;
    world_config.max_steps = 4;
    DevelopmentalWorld world(world_config);

    for (const auto& action_name : {std::string("bad-route"), std::string("good-route")}) {
        if (!world.add_action(DevelopmentalWorldAction{
                action_name, 1.0, {},
                [action_name](const Attributes& state, std::mt19937_64&)
                    -> std::optional<DevelopmentalWorldTransition> {
                    const auto condition = std::get<std::string>(state.at("route_condition"));
                    const bool route_works = condition == "flooded"
                        ? action_name == "bad-route"
                        : action_name == "good-route";
                    return DevelopmentalWorldTransition{
                        route_works ? 1.0 : -1.0,
                        {{"last_route", action_name}},
                        {route_works ? "destination_progress" : "route_setback"},
                        false};
                }}))
            throw std::runtime_error("Could not register route action");
    }

    Goal goal;
    goal.id = "dlt-001-navigation-goal";
    goal.description = "Reach the destination using accumulated experience about route consequences";
    goal.priority = 1.0;

    std::int64_t episode = 0;
    std::uint64_t clear_good = 0, clear_bad = 0, flooded_good = 0, flooded_bad = 0;
    std::uint64_t observations = 0, outcomes = 0;
    double total_reward = 0.0;
    std::optional<DevelopmentalWorldStep> last_step;
    std::string active_phase = "clear";

    CognitiveRuntimeConfig runtime_config;
    runtime_config.input_capacity = 8;
    runtime_config.result_capacity = 8;
    runtime_config.feedback_capacity = 16;
    runtime_config.drain_on_stop = true;
    runtime_config.action_adapter.authorization.maximum_risk = 1.0;
    runtime_config.action_adapter.execute = [&](const CandidateAction& action) {
        const auto available = world.available_actions();
        return std::find(available.begin(), available.end(), action.name) != available.end();
    };
    runtime_config.action_adapter.verify = [](const CandidateAction&) { return true; };
    runtime_config.action_adapter.observe_consequence = [&](const CandidateAction& action) {
        last_step = world.step(action.name);
        if (last_step->consequence) {
            ++outcomes;
            total_reward += *last_step->consequence;
        }
        return last_step->consequence;
    };

    const auto started = std::chrono::steady_clock::now();
    const auto finish = started + std::chrono::seconds(duration_seconds);
    auto next_checkpoint = started + std::chrono::seconds(checkpoint_seconds);
    std::uint64_t previous_observations = 0, previous_outcomes = 0;
    report << "[DLT-001] status=STARTED duration_seconds=" << duration_seconds
           << " checkpoint_seconds=" << checkpoint_seconds
           << " seed=20261024 context=navigation/route-selection\n"
           << "[DLT-001] protocol=clear-environment-first-half then flooded-environment-second-half; same context; no action prescribed to brain\n";

    int exit_code = 0;
    try {
        Brain brain(journal);
        if (!brain.create_goal(goal) || !brain.activate_goal(goal.id))
            throw std::runtime_error("Could not initialize DLT-001 goal");

        CognitiveRuntime runtime(brain, runtime_config);
        if (!runtime.start()) throw std::runtime_error("Could not start cognitive runtime");

        while (!stop_requested && std::chrono::steady_clock::now() < finish) {
            const auto elapsed = std::chrono::steady_clock::now() - started;
            const auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
            const bool flooded = elapsed_seconds >= duration_seconds / 2;
            active_phase = flooded ? "flooded" : "clear";

            world.set_context("navigation/route-selection");
            world.reset_episode(Attributes{
                {"route_condition", std::string(flooded ? "flooded" : "clear")},
                {"bridge_status", std::string(flooded ? "closed" : "open")},
                {"visibility", std::string(flooded ? "poor" : "clear")},
            }, 100.0);
            last_step.reset();

            const auto input = make_input(goal, world);
            const auto result_submitted = runtime.submit(input, 1.0);
            if (!result_submitted) throw std::runtime_error("Cognitive runtime rejected an episode");
            const auto result = await_result(runtime);
            if (result.status != CognitiveCycleStatus::completed)
                throw std::runtime_error("Cognitive cycle did not complete");

            if (result.context.plan.steps.empty() || result.context.action_execution_results.size() != 1)
                throw std::runtime_error("Cycle did not produce exactly one selected action execution");

            const auto& selected = result.context.plan.steps.front().action.name;
            const auto& execution = result.context.action_execution_results.front();
            if (execution.action.name != selected)
                throw std::runtime_error("Executed action differs from selected plan action");
            if (!execution.outcome.observed || !last_step || !last_step->observed ||
                !last_step->consequence)
                throw std::runtime_error("Action consequence was not observed");

            if (flooded) {
                if (selected == "good-route") ++flooded_good;
                else if (selected == "bad-route") ++flooded_bad;
            } else {
                if (selected == "good-route") ++clear_good;
                else if (selected == "bad-route") ++clear_bad;
            }
            ++observations;
            const auto cycle_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - started).count();
            episodes << episode << ',' << cycle_elapsed << ',' << active_phase << ','
                     << (flooded ? "flooded" : "clear") << ',' << selected << ','
                     << *last_step->consequence << ",completed,"
                     << brain.memory().by_kind("observation").size() << ','
                     << brain.memory().by_kind("action_outcome").size() << ','
                     << brain.memory().by_kind("prediction").size() << ','
                     << brain.memory().by_kind("prediction_outcome").size() << '\n';
            std::cout << "[DLT-001] episode=" << episode << " elapsed_seconds=" << cycle_elapsed
                      << " phase=" << active_phase << " action=" << selected
                      << " consequence=" << *last_step->consequence << std::endl;
            ++episode;

            const auto now = std::chrono::steady_clock::now();
            if (now >= next_checkpoint || now >= finish || stop_requested) {
                const auto checkpoint_elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - started).count();
                const auto observation_count = brain.memory().by_kind("observation").size();
                const auto outcome_count = brain.memory().by_kind("action_outcome").size();
                const auto prediction_count = brain.memory().by_kind("prediction").size();
                const auto prediction_outcome_count = brain.memory().by_kind("prediction_outcome").size();
                const auto good_value = strategy_value(brain, "navigation/route-selection", "good-route");
                const auto bad_value = strategy_value(brain, "navigation/route-selection", "bad-route");
                checkpoints << checkpoint_elapsed << ',' << active_phase << ',' << episode << ','
                            << clear_good << ',' << clear_bad << ',' << flooded_good << ','
                            << flooded_bad << ',' << total_reward << ',' << good_value << ','
                            << bad_value << ',' << observation_count << ',' << outcome_count << ','
                            << prediction_count << ',' << prediction_outcome_count << '\n';
                report << "[DLT-001] checkpoint elapsed_seconds=" << checkpoint_elapsed
                       << " phase=" << active_phase << " episodes=" << episode
                       << " clear_good=" << clear_good << " clear_bad=" << clear_bad
                       << " flooded_good=" << flooded_good << " flooded_bad=" << flooded_bad
                       << " total_reward=" << total_reward << " good_route_value=" << good_value
                       << " bad_route_value=" << bad_value << " observations=" << observation_count
                       << " outcomes=" << outcome_count
                       << " predictions=" << prediction_count
                       << " prediction_outcomes=" << prediction_outcome_count << '\n';
                std::cout << "[DLT-001] checkpoint elapsed_seconds=" << checkpoint_elapsed
                          << " phase=" << active_phase << " episodes=" << episode
                          << " total_reward=" << total_reward
                          << " good_route_value=" << good_value
                          << " bad_route_value=" << bad_value << std::endl;
                previous_observations = observation_count;
                previous_outcomes = outcome_count;
                next_checkpoint = now + std::chrono::seconds(checkpoint_seconds);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        runtime.stop();
        const auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - started).count();
        const bool completed = !stop_requested && std::chrono::steady_clock::now() >= finish;
        report << "[DLT-001] status=" << (completed ? "COMPLETED" : "INTERRUPTED")
               << " elapsed_seconds=" << elapsed_seconds << " episodes=" << episode
               << " observations=" << previous_observations << " outcomes=" << previous_outcomes
               << " total_reward=" << total_reward << '\n';
        report << "[DLT-001] final clear_good=" << clear_good << " clear_bad=" << clear_bad
               << " flooded_good=" << flooded_good << " flooded_bad=" << flooded_bad
               << " good_route_value=" << strategy_value(brain, "navigation/route-selection", "good-route")
               << " bad_route_value=" << strategy_value(brain, "navigation/route-selection", "bad-route")
               << " observation_memories=" << brain.memory().by_kind("observation").size()
               << " outcome_memories=" << brain.memory().by_kind("action_outcome").size()
               << " prediction_memories=" << brain.memory().by_kind("prediction").size()
               << " prediction_outcome_memories=" << brain.memory().by_kind("prediction_outcome").size() << '\n';
        if (!completed) exit_code = 2;
    } catch (const std::exception& ex) {
        report << "[DLT-001] status=FAILED episode=" << episode << " error=" << ex.what() << '\n';
        std::cerr << "[DLT-001] status=FAILED episode=" << episode << " error=" << ex.what() << std::endl;
        exit_code = 1;
    }

    report.flush();
    episodes.flush();
    checkpoints.flush();
    std::cout << "[DLT-001] final_status=" << (exit_code == 0 ? "COMPLETED" : "NOT_COMPLETED")
              << " episodes=" << episode << " output_dir=" << output_dir.string() << std::endl;
    return exit_code;
}
