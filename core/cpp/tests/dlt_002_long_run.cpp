#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/developmental_world.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <thread>

using namespace jarvis::core;

namespace {
volatile std::sig_atomic_t stop_requested = 0;
void request_stop(int) { stop_requested = 1; }

struct Phase {
    const char* name;
    const char* context;
    const char* latent_condition;
    const char* bridge_status;
    const char* visibility;
};

// The final phase deliberately reverses the first phase while retaining its
// context and visible cues. route_condition is withheld from the brain.
Phase phase_for(std::int64_t elapsed, std::int64_t duration) {
    const auto phase_length = std::max<std::int64_t>(1, duration / 4);
    switch (std::min<std::int64_t>(3, elapsed / phase_length)) {
    case 0: return {"clear-baseline", "navigation/clear", "alpha", "open", "clear"};
    case 1: return {"flooded", "navigation/flooded", "beta", "closed", "poor"};
    case 2: return {"tunnel", "navigation/tunnel", "alpha", "closed", "clear"};
    default: return {"clear-reversal", "navigation/clear", "beta", "open", "clear"};
    }
}

CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        if (auto result = runtime.poll_result()) return *result;
        if (stop_requested) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    throw std::runtime_error("Timed out or interrupted waiting for cognitive cycle");
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

double strategy_value(const Brain& brain, const std::string& context,
                      const std::string& action) {
    for (const auto& strategy : brain.developmental_strategies())
        if (strategy.context == context && strategy.action == action) return strategy.value;
    return 0.0;
}
} // namespace

int main(int argc, char** argv) {
    const auto duration_seconds = argc > 1 ? std::stoll(argv[1]) : 14400LL;
    const auto checkpoint_seconds = argc > 2 ? std::stoll(argv[2]) : 60LL;
    const std::filesystem::path output_dir = argc > 3 ? argv[3] : "dlt-002-results";
    if (duration_seconds <= 0 || checkpoint_seconds <= 0)
        throw std::invalid_argument("duration and checkpoint interval must be positive");

    std::filesystem::create_directories(output_dir);
    const auto journal = output_dir / "brain-journal.bin";
    std::error_code ec;
    std::filesystem::remove(journal, ec);
    std::filesystem::remove(journal.string() + ".meta", ec);

    std::signal(SIGINT, request_stop);
    std::signal(SIGTERM, request_stop);

    std::ofstream episodes(output_dir / "episodes.csv", std::ios::trunc);
    std::ofstream checkpoints(output_dir / "checkpoints.csv", std::ios::trunc);
    std::ofstream report(output_dir / "trial.log", std::ios::trunc);
    if (!episodes || !checkpoints || !report)
        throw std::runtime_error("Could not create DLT-002 output files");
    episodes << "episode,elapsed_seconds,phase,context,latent_condition_evaluation_only,selected_action,consequence,observation_count,outcome_count,prediction_count,prediction_outcome_count\n";
    checkpoints << "elapsed_seconds,phase,episodes,total_reward,route_alpha_selected,route_beta_selected,positive_outcomes,negative_outcomes,observations,outcomes,predictions,prediction_outcomes,clear_alpha_value,clear_beta_value,flooded_alpha_value,flooded_beta_value,tunnel_alpha_value,tunnel_beta_value\n";
    episodes << std::unitbuf;
    checkpoints << std::unitbuf;
    report << std::unitbuf;

    DevelopmentalWorldConfig world_config;
    world_config.task = "navigation-under-changing-conditions";
    world_config.context = "navigation/clear";
    world_config.initial_state = {
        {"route_condition", std::string("alpha")},
        {"bridge_status", std::string("open")},
        {"visibility", std::string("clear")},
    };
    world_config.initial_resources = 100.0;
    world_config.random_seed = 20261025;
    world_config.max_steps = 4;
    world_config.observation_filter = [](const Attributes& state) {
        Attributes visible = state;
        visible.erase("route_condition");
        return visible;
    };
    DevelopmentalWorld world(world_config);

    for (const auto& action_name : {std::string("route-alpha"), std::string("route-beta")}) {
        if (!world.add_action(DevelopmentalWorldAction{
                action_name, 1.0, {},
                [action_name](const Attributes& state, std::mt19937_64& random)
                    -> std::optional<DevelopmentalWorldTransition> {
                    const auto condition = std::get<std::string>(state.at("route_condition"));
                    const bool matches =
                        (condition == "alpha" && action_name == "route-alpha") ||
                        (condition == "beta" && action_name == "route-beta");
                    // Consequences are noisy: 15% of outcomes contradict the
                    // underlying action/condition relationship.
                    const bool flip = std::generate_canonical<double, 10>(random) < 0.15;
                    const bool succeeds = matches != flip;
                    return DevelopmentalWorldTransition{
                        succeeds ? 1.0 : -1.0,
                        {{"last_route", action_name}},
                        {succeeds ? "destination_progress" : "route_setback"},
                        false};
                }}))
            throw std::runtime_error("Could not register DLT-002 route action");
    }

    Goal goal;
    goal.id = "dlt-002-contextual-reversal-goal";
    goal.description = "Reach a destination by learning from partial, noisy and changing route outcomes";
    goal.priority = 1.0;

    CognitiveRuntimeConfig runtime_config;
    runtime_config.input_capacity = 8;
    runtime_config.result_capacity = 8;
    runtime_config.feedback_capacity = 16;
    runtime_config.drain_on_stop = true;
    runtime_config.action_adapter.authorization.maximum_risk = 1.0;
    std::optional<DevelopmentalWorldStep> last_step;
    runtime_config.action_adapter.execute = [&](const CandidateAction& action) {
        const auto available = world.available_actions();
        return std::find(available.begin(), available.end(), action.name) != available.end();
    };
    runtime_config.action_adapter.verify = [](const CandidateAction&) { return true; };
    runtime_config.action_adapter.observe_consequence = [&](const CandidateAction& action) {
        last_step = world.step(action.name);
        return last_step->consequence;
    };

    const auto started = std::chrono::steady_clock::now();
    const auto finish = started + std::chrono::seconds(duration_seconds);
    auto next_checkpoint = started + std::chrono::seconds(checkpoint_seconds);
    std::array<std::array<std::uint64_t, 2>, 4> action_counts{};
    std::uint64_t positive = 0, negative = 0;
    std::uint64_t episode = 0;
    double total_reward = 0.0;
    std::string active_phase = "clear-baseline";
    report << "[DLT-002] status=STARTED duration_seconds=" << duration_seconds
           << " checkpoint_seconds=" << checkpoint_seconds
           << " seed=20261025 noise_rate=0.15 phases=4\n"
           << "[DLT-002] protocol=partial observation; noisy outcomes; clear mapping; flooded mapping; tunnel mapping; clear context then reverses while visible cues stay the same\n";

    int exit_code = 0;
    try {
        Brain brain(journal);
        if (!brain.create_goal(goal) || !brain.activate_goal(goal.id))
            throw std::runtime_error("Could not initialize DLT-002 goal");
        CognitiveRuntime runtime(brain, runtime_config);
        if (!runtime.start()) throw std::runtime_error("Could not start cognitive runtime");

        while (!stop_requested && std::chrono::steady_clock::now() < finish) {
            const auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - started).count();
            const auto phase = phase_for(elapsed, duration_seconds);
            active_phase = phase.name;
            world.set_context(phase.context);
            world.reset_episode(Attributes{
                {"route_condition", std::string(phase.latent_condition)},
                {"bridge_status", std::string(phase.bridge_status)},
                {"visibility", std::string(phase.visibility)},
            }, 100.0);
            last_step.reset();

            const auto input = make_input(goal, world);
            if (!runtime.submit(input, 1.0))
                throw std::runtime_error("Cognitive runtime rejected an episode");
            const auto result = await_result(runtime);
            if (result.status != CognitiveCycleStatus::completed ||
                result.context.plan.steps.empty() ||
                result.context.action_execution_results.size() != 1)
                throw std::runtime_error("Cognitive cycle did not complete exactly one action");
            const auto& selected = result.context.plan.steps.front().action.name;
            const auto& execution = result.context.action_execution_results.front();
            if (execution.action.name != selected || !execution.outcome.observed ||
                !last_step || !last_step->observed || !last_step->consequence)
                throw std::runtime_error("Selected action or observed consequence evidence is inconsistent");

            const auto phase_index = static_cast<std::size_t>(
                std::min<std::int64_t>(3, elapsed / std::max<std::int64_t>(1, duration_seconds / 4)));
            const auto action_index = selected == "route-alpha" ? 0U : 1U;
            ++action_counts[phase_index][action_index];
            total_reward += *last_step->consequence;
            if (*last_step->consequence > 0.0) ++positive;
            else if (*last_step->consequence < 0.0) ++negative;

            const auto cycle_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - started).count();
            const auto observations = brain.memory().by_kind("observation").size();
            const auto outcomes = brain.memory().by_kind("action_outcome").size();
            const auto predictions = brain.memory().by_kind("prediction").size();
            const auto prediction_outcomes = brain.memory().by_kind("prediction_outcome").size();
            episodes << episode << ',' << cycle_elapsed << ',' << phase.name << ','
                     << phase.context << ',' << phase.latent_condition << ',' << selected << ','
                     << *last_step->consequence << ',' << observations << ',' << outcomes << ','
                     << predictions << ',' << prediction_outcomes << '\n';
            ++episode;

            const auto now = std::chrono::steady_clock::now();
            if (now >= next_checkpoint || now >= finish || stop_requested) {
                checkpoints << std::chrono::duration_cast<std::chrono::seconds>(now - started).count()
                    << ',' << phase.name << ',' << episode << ',' << total_reward << ','
                    << action_counts[phase_index][0] << ',' << action_counts[phase_index][1] << ','
                    << positive << ',' << negative << ',' << observations << ',' << outcomes << ','
                    << predictions << ',' << prediction_outcomes << ','
                    << strategy_value(brain, "navigation/clear", "route-alpha") << ','
                    << strategy_value(brain, "navigation/clear", "route-beta") << ','
                    << strategy_value(brain, "navigation/flooded", "route-alpha") << ','
                    << strategy_value(brain, "navigation/flooded", "route-beta") << ','
                    << strategy_value(brain, "navigation/tunnel", "route-alpha") << ','
                    << strategy_value(brain, "navigation/tunnel", "route-beta") << '\n';
                report << "[DLT-002] checkpoint elapsed_seconds="
                    << std::chrono::duration_cast<std::chrono::seconds>(now - started).count()
                    << " phase=" << phase.name << " episodes=" << episode
                    << " total_reward=" << total_reward << " positive=" << positive
                    << " negative=" << negative << " observations=" << observations
                    << " outcomes=" << outcomes << " predictions=" << predictions
                    << " prediction_outcomes=" << prediction_outcomes
                    << " clear_alpha_value=" << strategy_value(brain, "navigation/clear", "route-alpha")
                    << " clear_beta_value=" << strategy_value(brain, "navigation/clear", "route-beta")
                    << " flooded_alpha_value=" << strategy_value(brain, "navigation/flooded", "route-alpha")
                    << " flooded_beta_value=" << strategy_value(brain, "navigation/flooded", "route-beta")
                    << " tunnel_alpha_value=" << strategy_value(brain, "navigation/tunnel", "route-alpha")
                    << " tunnel_beta_value=" << strategy_value(brain, "navigation/tunnel", "route-beta") << '\n';
                next_checkpoint = now + std::chrono::seconds(checkpoint_seconds);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        runtime.stop();
        const auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - started).count();
        const bool completed = !stop_requested && std::chrono::steady_clock::now() >= finish;
        report << "[DLT-002] status=" << (completed ? "COMPLETED" : "INTERRUPTED")
            << " elapsed_seconds=" << elapsed_seconds << " episodes=" << episode
            << " total_reward=" << total_reward << " positive=" << positive
            << " negative=" << negative << " observation_memories="
            << brain.memory().by_kind("observation").size()
            << " outcome_memories=" << brain.memory().by_kind("action_outcome").size()
            << " prediction_memories=" << brain.memory().by_kind("prediction").size()
            << " prediction_outcome_memories=" << brain.memory().by_kind("prediction_outcome").size()
            << " clear_alpha_value=" << strategy_value(brain, "navigation/clear", "route-alpha")
            << " clear_beta_value=" << strategy_value(brain, "navigation/clear", "route-beta")
            << " flooded_alpha_value=" << strategy_value(brain, "navigation/flooded", "route-alpha")
            << " flooded_beta_value=" << strategy_value(brain, "navigation/flooded", "route-beta")
            << " tunnel_alpha_value=" << strategy_value(brain, "navigation/tunnel", "route-alpha")
            << " tunnel_beta_value=" << strategy_value(brain, "navigation/tunnel", "route-beta") << '\n';
        if (!completed) exit_code = 2;
    } catch (const std::exception& ex) {
        report << "[DLT-002] status=FAILED episode=" << episode << " error=" << ex.what() << '\n';
        std::cerr << "[DLT-002] status=FAILED episode=" << episode << " error=" << ex.what() << std::endl;
        exit_code = 1;
    }

    report.flush();
    episodes.flush();
    checkpoints.flush();
    std::cout << "[DLT-002] final_status=" << (exit_code == 0 ? "COMPLETED" : "NOT_COMPLETED")
              << " episodes=" << episode << " output_dir=" << output_dir.string() << std::endl;
    return exit_code;
}
