#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/developmental_world.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <csignal>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
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

// Phase four reverses the original clear context; phase five probes transfer in
// an unseen context. The final phase reverses the flooded context a second time
// while preserving its context and visible cues. This tests repeated revision
// and interference, not just one successful reversal. route_condition is
// withheld from the brain throughout.
Phase phase_for(std::int64_t elapsed, std::int64_t duration) {
    const auto phase_length = std::max<std::int64_t>(1, duration / 6);
    switch (std::min<std::int64_t>(5, elapsed / phase_length)) {
    case 0: return {"clear-baseline", "navigation/clear", "alpha", "open", "clear"};
    case 1: return {"flooded", "navigation/flooded", "beta", "closed", "poor"};
    case 2: return {"tunnel", "navigation/tunnel", "alpha", "closed", "clear"};
    case 3: return {"clear-reversal", "navigation/clear", "beta", "open", "clear"};
    case 4: return {"generalization-probe", "navigation/canyon", "beta", "open", "poor"};
    default: return {"flooded-reversal", "navigation/flooded", "alpha", "closed", "poor"};
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

struct PredictionMetrics {
    std::uint64_t total{0};
    std::uint64_t resolved{0};
    std::uint64_t unresolved_action_consequence{0};
    std::uint64_t unresolved_other{0};
    double mean_absolute_error{0.0};
};

PredictionMetrics prediction_metrics(const Brain& brain) {
    const auto predictions = brain.snapshot().predictions;
    PredictionMetrics metrics;
    double absolute_error_sum = 0.0;
    for (const auto& prediction : predictions) {
        ++metrics.total;
        if (!prediction.resolved) {
            if (prediction.key.rfind("action_consequence|", 0) == 0)
                ++metrics.unresolved_action_consequence;
            else
                ++metrics.unresolved_other;
            continue;
        }
        if (!std::isfinite(prediction.error)) continue;
        ++metrics.resolved;
        absolute_error_sum += std::abs(prediction.error);
    }
    if (metrics.resolved > 0)
        metrics.mean_absolute_error = absolute_error_sum / static_cast<double>(metrics.resolved);
    return metrics;
}
} // namespace

int main(int argc, char** argv) {
    const auto duration_seconds = argc > 1 ? std::stoll(argv[1]) : 14400LL;
    const auto checkpoint_seconds = argc > 2 ? std::stoll(argv[2]) : 60LL;
    const std::filesystem::path output_dir = argc > 3 ? argv[3] : "dlt-002-results";
    const auto seed = argc > 4 ? std::stoull(argv[4]) : 20261026ULL;
    const std::string feedback_mode = argc > 5 ? argv[5] : "enabled";
    if (feedback_mode != "enabled" && feedback_mode != "no-feedback")
        throw std::invalid_argument("feedback mode must be enabled or no-feedback");
    const bool feedback_enabled = feedback_mode == "enabled";
    if (duration_seconds <= 0 || checkpoint_seconds <= 0)
        throw std::invalid_argument("duration and checkpoint interval must be positive");

    std::filesystem::create_directories(output_dir);
    const auto journal = output_dir / "brain-journal.bin";
    const auto journal_meta = std::filesystem::path(journal.string() + ".meta");
    const auto episodes_path = output_dir / "episodes.csv";
    const auto checkpoints_path = output_dir / "checkpoints.csv";
    const auto report_path = output_dir / "trial.log";

    // DLT-002 is intentionally a single uninterrupted trial. This executable
    // does not restore phase clocks, RNG streams, world state, or aggregate
    // metrics, so it must never silently delete a journal or truncate evidence
    // from an earlier/partial run. An interrupted trial is incomplete; preserve
    // its files and start a separately identified experiment instead.
    for (const auto& protected_path : {
             journal, journal_meta, episodes_path, checkpoints_path, report_path}) {
        if (std::filesystem::exists(protected_path)) {
            std::cerr << "[DLT-002] status=REFUSED_OVERWRITE protected_path="
                      << protected_path.string()
                      << " reason=unsafe_resume_not_supported" << std::endl;
            return 64;
        }
    }

    std::signal(SIGINT, request_stop);
    std::signal(SIGTERM, request_stop);

    std::ofstream episodes(episodes_path, std::ios::out);
    std::ofstream checkpoints(checkpoints_path, std::ios::out);
    std::ofstream report(report_path, std::ios::out);
    if (!episodes || !checkpoints || !report)
        throw std::runtime_error("Could not create DLT-002 output files");
    episodes << "episode,elapsed_seconds,phase,context,latent_condition_evaluation_only,expected_action_evaluation_only,selected_action,optimal_action_selected,consequence,observation_count,outcome_count,prediction_count,prediction_outcome_count,generalization_probe_episode_index,generalization_transfer_source_context,generalization_transfer_source_action,generalization_transfer_source_similarity,generalization_initial_window_episode,generalization_initial_window_optimal,predicted_consequence_evaluation_only,actual_consequence_evaluation_only,brain_received_consequence_feedback\n";
    checkpoints << "elapsed_seconds,phase,episodes,total_reward,current_phase_route_one_selected,current_phase_route_two_selected,positive_outcomes,negative_outcomes,optimal_action_selections,nonoptimal_action_selections,current_phase_decision_accuracy,observations,outcomes,predictions,prediction_outcomes,resolved_predictions,mean_absolute_prediction_error,clear_route_one_value,clear_route_two_value,flooded_route_one_value,flooded_route_two_value,tunnel_route_one_value,tunnel_route_two_value,canyon_route_one_value,canyon_route_two_value,unresolved_action_consequence_predictions,unresolved_other_predictions\n";
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
    world_config.random_seed = seed;
    // Randomize the latent-state/action relationship per seed. This mapping belongs
    // to the environment and evaluation only; it is never supplied to the brain.
    std::mt19937_64 mapping_random(seed ^ 0x9E3779B97F4A7C15ULL);
    std::bernoulli_distribution choose_first_action_for_alpha(0.5);
    const std::string alpha_action = choose_first_action_for_alpha(mapping_random)
        ? "route-one" : "route-two";
    const std::string beta_action = alpha_action == "route-one" ? "route-two" : "route-one";
    world_config.max_steps = 4;
    world_config.observation_filter = [](const Attributes& state) {
        Attributes visible = state;
        visible.erase("route_condition");
        return visible;
    };
    DevelopmentalWorld world(world_config);

    for (const auto& action_name : {std::string("route-one"), std::string("route-two")}) {
        if (!world.add_action(DevelopmentalWorldAction{
                action_name, 1.0, {},
                [action_name, alpha_action, beta_action](const Attributes& state, std::mt19937_64& random)
                    -> std::optional<DevelopmentalWorldTransition> {
                    const auto condition = std::get<std::string>(state.at("route_condition"));
                    const bool matches =
                        (condition == "alpha" && action_name == alpha_action) ||
                        (condition == "beta" && action_name == beta_action);
                    // Consequences are noisy: 20% of outcomes contradict the
                    // underlying action/condition relationship.
                    const bool flip = std::generate_canonical<double, 10>(random) < 0.20;
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
        // In the control mode the world still executes and records the true
        // consequence for evaluation, but deliberately withholds it from Brain.
        if (!feedback_enabled) return std::optional<double>{};
        return last_step->consequence;
    };

    const auto started = std::chrono::steady_clock::now();
    const auto finish = started + std::chrono::seconds(duration_seconds);
    auto next_checkpoint = started + std::chrono::seconds(checkpoint_seconds);
    std::array<std::array<std::uint64_t, 2>, 6> action_counts{};
    std::uint64_t positive = 0, negative = 0;
    std::uint64_t optimal_action_selections = 0, nonoptimal_action_selections = 0;
    std::uint64_t episode = 0;
    std::uint64_t generalization_probe_episodes = 0;
    std::uint64_t generalization_initial_window_optimal = 0;
    constexpr std::uint64_t generalization_initial_window_size = 10;
    std::string generalization_transfer_source_context;
    std::string generalization_transfer_source_action;
    double generalization_transfer_source_similarity = 0.0;
    bool generalization_transfer_source_checked = false;
    double total_reward = 0.0;
    std::string active_phase = "clear-baseline";
    report << "[DLT-002] status=STARTED duration_seconds=" << duration_seconds
           << " checkpoint_seconds=" << checkpoint_seconds
           << " seed=" << seed << " feedback_mode=" << feedback_mode
           << " noise_rate=0.20 phases=6\n"
           << "[DLT-002] protocol=partial observation; 20% noisy outcomes; context-local mapping; clear-context reversal; unseen-context transfer; second reversal in flooded context with unchanged visible cues\n";

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

            // Record related experience before the first action in the held-out
            // context. This is diagnostic only: evaluation labels never enter
            // the brain and the retrieval threshold/learning rule is unchanged.
            if (std::string(phase.name) == "generalization-probe" &&
                !generalization_transfer_source_checked) {
                const auto related = brain.developmental_related_strategies(phase.context);
                if (!related.empty()) {
                    generalization_transfer_source_context = related.front().strategy.context;
                    generalization_transfer_source_action = related.front().strategy.action;
                    generalization_transfer_source_similarity = related.front().similarity;
                }
                generalization_transfer_source_checked = true;
            }

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
            if (execution.action.name != selected ||
                execution.outcome.observed != feedback_enabled ||
                !last_step || !last_step->observed || !last_step->consequence)
                throw std::runtime_error("Selected action or observed consequence evidence is inconsistent");

            // Record the prediction value actually calibrated and issued by
            // Brain, not merely the planner's uncalibrated action prior.
            if (!execution.consequence_prediction_sequence ||
                !execution.consequence_prediction_value)
                throw std::runtime_error("Calibrated action consequence prediction is missing");
            const double predicted_consequence_evaluation_only =
                *execution.consequence_prediction_value;
            if (!std::isfinite(predicted_consequence_evaluation_only))
                throw std::runtime_error("Action consequence prediction is non-finite");

            const auto phase_index = static_cast<std::size_t>(
                std::min<std::int64_t>(5, elapsed / std::max<std::int64_t>(1, duration_seconds / 6)));
            const auto action_index = selected == "route-one" ? 0U : 1U;
            ++action_counts[phase_index][action_index];
            const std::string expected_action = std::string(phase.latent_condition) == "alpha"
                ? alpha_action : beta_action;
            const bool optimal_action_selected = selected == expected_action;
            if (optimal_action_selected) ++optimal_action_selections;
            else ++nonoptimal_action_selections;
            const auto phase_selections = action_counts[phase_index][0] + action_counts[phase_index][1];
            const auto phase_optimal_selections = action_counts[phase_index][
                expected_action == "route-one" ? 0U : 1U];
            const double phase_decision_accuracy = phase_selections == 0 ? 0.0 :
                static_cast<double>(phase_optimal_selections) / static_cast<double>(phase_selections);
            total_reward += *last_step->consequence;
            if (*last_step->consequence > 0.0) ++positive;
            else if (*last_step->consequence < 0.0) ++negative;

            const auto cycle_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - started).count();
            const auto observations = brain.memory().by_kind("observation").size();
            const auto outcomes = brain.memory().by_kind("action_outcome").size();
            const auto predictions = brain.memory().by_kind("prediction").size();
            const auto prediction_outcomes = brain.memory().by_kind("prediction_outcome").size();
            const bool in_generalization_probe =
                std::string(phase.name) == "generalization-probe";
            std::uint64_t probe_episode_index = 0;
            std::string transfer_source_context;
            std::string transfer_source_action;
            double transfer_source_similarity = 0.0;
            std::string initial_window_episode;
            std::string initial_window_optimal;
            if (in_generalization_probe) {
                probe_episode_index = ++generalization_probe_episodes;
                if (probe_episode_index <= generalization_initial_window_size) {
                    if (optimal_action_selected) ++generalization_initial_window_optimal;
                    initial_window_episode = std::to_string(probe_episode_index);
                    initial_window_optimal = optimal_action_selected ? "1" : "0";
                }
                if (probe_episode_index == 1 && !generalization_transfer_source_context.empty()) {
                    transfer_source_context = generalization_transfer_source_context;
                    transfer_source_action = generalization_transfer_source_action;
                    transfer_source_similarity = generalization_transfer_source_similarity;
                }
            }
            episodes << episode << ',' << cycle_elapsed << ',' << phase.name << ','
                     << phase.context << ',' << phase.latent_condition << ',' << expected_action << ','
                     << selected << ',' << (optimal_action_selected ? 1 : 0) << ','
                     << *last_step->consequence << ',' << observations << ',' << outcomes << ','
                     << predictions << ',' << prediction_outcomes << ','
                     << (in_generalization_probe ? std::to_string(probe_episode_index) : "") << ','
                     << transfer_source_context << ',' << transfer_source_action << ','
                     << (transfer_source_context.empty() ? "" : std::to_string(transfer_source_similarity)) << ','
                     << initial_window_episode << ',' << initial_window_optimal << ','
                     << predicted_consequence_evaluation_only << ','
                     << *last_step->consequence << ','
                     << (execution.outcome.observed ? 1 : 0) << '\n';
            ++episode;

            const auto now = std::chrono::steady_clock::now();
            if (now >= next_checkpoint || now >= finish || stop_requested) {
                const auto prediction_quality = prediction_metrics(brain);
                checkpoints << std::chrono::duration_cast<std::chrono::seconds>(now - started).count()
                    << ',' << phase.name << ',' << episode << ',' << total_reward << ','
                    << action_counts[phase_index][0] << ',' << action_counts[phase_index][1] << ','
                    << positive << ',' << negative << ',' << optimal_action_selections << ','
                    << nonoptimal_action_selections << ',' << phase_decision_accuracy << ','
                    << observations << ',' << outcomes << ','
                    << predictions << ',' << prediction_outcomes << ',' << prediction_quality.resolved
                    << ',' << prediction_quality.mean_absolute_error << ','
                    << strategy_value(brain, "navigation/clear", "route-one") << ','
                    << strategy_value(brain, "navigation/clear", "route-two") << ','
                    << strategy_value(brain, "navigation/flooded", "route-one") << ','
                    << strategy_value(brain, "navigation/flooded", "route-two") << ','
                    << strategy_value(brain, "navigation/tunnel", "route-one") << ','
                    << strategy_value(brain, "navigation/tunnel", "route-two") << ','
                    << strategy_value(brain, "navigation/canyon", "route-one") << ','
                    << strategy_value(brain, "navigation/canyon", "route-two") << ','
                    << prediction_quality.unresolved_action_consequence << ','
                    << prediction_quality.unresolved_other << '\n';
                report << "[DLT-002] checkpoint elapsed_seconds="
                    << std::chrono::duration_cast<std::chrono::seconds>(now - started).count()
                    << " phase=" << phase.name << " episodes=" << episode
                    << " total_reward=" << total_reward << " positive=" << positive
                    << " negative=" << negative << " optimal_action_selections=" << optimal_action_selections
                    << " nonoptimal_action_selections=" << nonoptimal_action_selections
                    << " current_phase_decision_accuracy=" << phase_decision_accuracy
                    << " observations=" << observations
                    << " outcomes=" << outcomes << " predictions=" << predictions
                    << " prediction_outcomes=" << prediction_outcomes
                    << " resolved_predictions=" << prediction_quality.resolved
                    << " unresolved_action_consequence_predictions=" << prediction_quality.unresolved_action_consequence
                    << " unresolved_other_predictions=" << prediction_quality.unresolved_other
                    << " mean_absolute_prediction_error=" << prediction_quality.mean_absolute_error
                    << " clear_route_one_value=" << strategy_value(brain, "navigation/clear", "route-one")
                    << " clear_route_two_value=" << strategy_value(brain, "navigation/clear", "route-two")
                    << " flooded_route_one_value=" << strategy_value(brain, "navigation/flooded", "route-one")
                    << " flooded_route_two_value=" << strategy_value(brain, "navigation/flooded", "route-two")
                    << " tunnel_route_one_value=" << strategy_value(brain, "navigation/tunnel", "route-one")
                    << " tunnel_route_two_value=" << strategy_value(brain, "navigation/tunnel", "route-two")
                    << " canyon_route_one_value=" << strategy_value(brain, "navigation/canyon", "route-one")
                    << " canyon_route_two_value=" << strategy_value(brain, "navigation/canyon", "route-two") << '\n';
                next_checkpoint = now + std::chrono::seconds(checkpoint_seconds);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        runtime.stop();
        const auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - started).count();
        const bool completed = !stop_requested && std::chrono::steady_clock::now() >= finish;
        const auto final_prediction_quality = prediction_metrics(brain);
        report << "[DLT-002] status=" << (completed ? "COMPLETED" : "INTERRUPTED")
            << " feedback_mode=" << feedback_mode
            << " elapsed_seconds=" << elapsed_seconds << " episodes=" << episode
            << " total_reward=" << total_reward << " positive=" << positive
            << " negative=" << negative << " optimal_action_selections=" << optimal_action_selections
            << " nonoptimal_action_selections=" << nonoptimal_action_selections
            << " observation_memories="
            << brain.memory().by_kind("observation").size()
            << " outcome_memories=" << brain.memory().by_kind("action_outcome").size()
            << " prediction_memories=" << brain.memory().by_kind("prediction").size()
            << " prediction_outcome_memories=" << brain.memory().by_kind("prediction_outcome").size()
            << " generalization_probe_episodes=" << generalization_probe_episodes
            << " generalization_transfer_source_found=" << (!generalization_transfer_source_context.empty())
            << " generalization_transfer_source_context=" << (generalization_transfer_source_context.empty() ? "NONE" : generalization_transfer_source_context)
            << " generalization_transfer_source_action=" << (generalization_transfer_source_action.empty() ? "NONE" : generalization_transfer_source_action)
            << " generalization_transfer_source_similarity=" << generalization_transfer_source_similarity
            << " generalization_initial_window_size=" << std::min(generalization_probe_episodes, generalization_initial_window_size)
            << " generalization_initial_window_optimal=" << generalization_initial_window_optimal
            << " resolved_predictions=" << final_prediction_quality.resolved
            << " unresolved_action_consequence_predictions=" << final_prediction_quality.unresolved_action_consequence
            << " unresolved_other_predictions=" << final_prediction_quality.unresolved_other
            << " mean_absolute_prediction_error=" << final_prediction_quality.mean_absolute_error
            << " clear_route_one_value=" << strategy_value(brain, "navigation/clear", "route-one")
            << " clear_route_two_value=" << strategy_value(brain, "navigation/clear", "route-two")
            << " flooded_route_one_value=" << strategy_value(brain, "navigation/flooded", "route-one")
            << " flooded_route_two_value=" << strategy_value(brain, "navigation/flooded", "route-two")
            << " tunnel_route_one_value=" << strategy_value(brain, "navigation/tunnel", "route-one")
            << " tunnel_route_two_value=" << strategy_value(brain, "navigation/tunnel", "route-two") << '\n';
        if (!completed) exit_code = 2;
        // In feedback-enabled mode, every executed action's consequence is
        // returned to Brain, so unresolved action-consequence forecasts indicate
        // a broken feedback path. In no-feedback control mode, unresolved action
        // forecasts are expected because the outcome is deliberately withheld.
        // Other causal projections may lack a directly observed matching
        // outcome in either mode and are reported separately.
        if (completed && feedback_enabled &&
            final_prediction_quality.unresolved_action_consequence != 0) {
            report << "[DLT-002] status=FAILED unresolved_action_consequence_predictions="
                   << final_prediction_quality.unresolved_action_consequence << '\n';
            exit_code = 3;
        }
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
