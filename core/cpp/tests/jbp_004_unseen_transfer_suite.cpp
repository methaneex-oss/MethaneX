#include "jarvis/core/cognitive_runtime.hpp"
#include "jarvis/core/developmental_world.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace jarvis::core;

namespace {
CognitiveCycleResult await_result(CognitiveRuntime& runtime) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        if (auto result = runtime.poll_result()) return *result;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    std::cerr << "JBP-004 status=FAIL reason=runtime_timeout\n";
    std::exit(70);
}

CognitiveCycleInput make_input(const Goal& goal, const DevelopmentalWorld& world) {
    CognitiveCycleInput input;
    input.observation = world.observe().event;
    input.candidate_actions = {
        CandidateAction{"choice-amber", 2.0, 0.5, 0.9, 0.1},
        CandidateAction{"choice-violet", 2.0, 0.5, 0.9, 0.1},
    };
    input.goal_id = goal.id;
    input.developmental_context = world.config().context;
    input.planning_horizon = 1;
    input.memory_limit = 12;
    input.reasoning_steps = 6;
    input.resource_budget = 10.0;
    input.action_constraints = ActionConstraints{1.0, false};
    return input;
}

struct TrialResult {
    std::uint64_t correct{0};
    std::uint64_t total{0};
};

bool run_mode(const std::filesystem::path& journal, std::uint64_t seed,
              bool verify_only) {
    std::mt19937_64 generator(seed ^ 0xD1B54A32D192ED03ULL);
    std::bernoulli_distribution choose_amber(0.5);
    const bool base_prefers_amber = choose_amber(generator);

    // The environment's reward rule is generated per seed and stays evaluator-side.
    // The brain sees only the current observable context and action consequences.
    DevelopmentalWorldConfig world_config;
    world_config.task = "partially-observed-adaptive-world";
    world_config.context = "sim/clear";
    world_config.initial_state = {
        {"weather", std::string("clear")},
        {"terrain", std::string("flat")},
        {"latent_route_rule", std::string("withheld")},
        {"step", std::int64_t{0}},
    };
    world_config.initial_resources = 10000.0;
    world_config.random_seed = seed;
    world_config.max_steps = 10000;
    world_config.observation_filter = [](const Attributes& state) {
        Attributes visible = state;
        visible.erase("latent_route_rule");
        return visible;
    };
    DevelopmentalWorld world(world_config);

    for (const auto& action_name : {std::string("choice-amber"), std::string("choice-violet")}) {
        const bool amber = action_name == "choice-amber";
        if (!world.add_action(DevelopmentalWorldAction{
                action_name, 1.0, {},
                [&, amber, action_name](const Attributes& state, std::mt19937_64& random)
                    -> std::optional<DevelopmentalWorldTransition> {
                    const auto weather = std::get<std::string>(state.at("weather"));
                    const auto terrain = std::get<std::string>(state.at("terrain"));
                    // Hidden compositional rule: the preferred action depends on
                    // the parity of two observable factors. The held-out combination
                    // is never trained and its correct action is evaluator-only.
                    const bool factor_parity = (weather == "storm") != (terrain == "rugged");
                    const bool preferred_amber = base_prefers_amber != factor_parity;
                    const bool preferred = amber == preferred_amber;
                    // 15% stochastic outcomes prevent memorizing a perfectly reliable
                    // single observation. The true rule is not exposed to the learner.
                    const bool noisy_flip =
                        std::generate_canonical<double, 10>(random) < 0.15;
                    const bool success = preferred != noisy_flip;
                    return DevelopmentalWorldTransition{
                        success ? 1.0 : -1.0,
                        {{"last_choice", action_name},
                         {"step", std::get<std::int64_t>(state.at("step")) + 1}},
                        {success ? "progress" : "setback"}, false};
                }})) {
            std::cerr << "JBP-004 status=FAIL reason=world_action_registration\n";
            return false;
        }
    }

    std::optional<DevelopmentalWorldStep> last_step;
    CognitiveRuntimeConfig runtime_config;
    runtime_config.input_capacity = 16;
    runtime_config.result_capacity = 16;
    runtime_config.feedback_capacity = 32;
    runtime_config.drain_on_stop = true;
    runtime_config.action_adapter.authorization.maximum_risk = 1.0;
    runtime_config.action_adapter.execute = [&](const CandidateAction& action) {
        const auto available = world.available_actions();
        return std::find(available.begin(), available.end(), action.name) != available.end();
    };
    runtime_config.action_adapter.verify = [](const CandidateAction&) { return true; };
    runtime_config.action_adapter.observe_consequence = [&](const CandidateAction& action) {
        last_step = world.step(action.name);
        if (verify_only || !last_step) return std::optional<double>{};
        return last_step->consequence;
    };

    Brain brain(journal);
    Goal goal;
    goal.id = "jbp-004-adaptive-world-goal";
    goal.description = "Maximize progress in a partially observed changing world";
    goal.priority = 1.0;
    if (!brain.create_goal(goal) && brain.goal(goal.id) == nullptr) {
        std::cerr << "JBP-004 status=FAIL reason=goal_creation\n";
        return false;
    }
    if (!brain.activate_goal(goal.id)) {
        std::cerr << "JBP-004 status=FAIL reason=goal_activation\n";
        return false;
    }

    CognitiveRuntime runtime(brain, runtime_config);
    if (!runtime.start()) {
        std::cerr << "JBP-004 status=FAIL reason=runtime_start\n";
        return false;
    }

    auto episode = [&](const std::string& weather, const std::string& terrain,
                       std::uint64_t index, bool expected_amber) -> std::optional<bool> {
        world.set_context("sim/" + weather + "/" + terrain);
        world.reset_episode(Attributes{
            {"weather", weather},
            {"terrain", terrain},
            {"latent_route_rule", std::string("withheld")},
            {"step", static_cast<std::int64_t>(index)},
        });
        last_step.reset();
        const auto input = make_input(goal, world);
        if (!runtime.submit(input, 1.0)) return std::nullopt;
        const auto result = await_result(runtime);
        if (result.status != CognitiveCycleStatus::completed ||
            result.context.plan.steps.empty() ||
            result.context.action_execution_results.size() != 1 ||
            !last_step.has_value() || !last_step->executed) return std::nullopt;
        const auto& selected = result.context.plan.steps.front().action.name;
        if (selected != result.context.action_execution_results.front().action.name)
            return std::nullopt;
        const bool selected_amber = selected == "choice-amber";
        // The evaluator records correctness after the learner has committed to an action.
        return selected_amber == expected_amber;
    };

    const std::array<std::pair<std::string, std::string>, 3> trained_contexts{{
        {"clear", "flat"}, {"clear", "rugged"}, {"storm", "flat"}
    }};
    auto expected_for = [&](const std::string& weather, const std::string& terrain) {
        const bool factor_parity = (weather == "storm") != (terrain == "rugged");
        return base_prefers_amber != factor_parity;
    };

    if (!verify_only) {
        std::array<std::uint64_t, 3> correct{};
        for (std::uint64_t i = 0; i < 80; ++i) {
            for (std::size_t c = 0; c < trained_contexts.size(); ++c) {
                const auto& [weather, terrain] = trained_contexts[c];
                const auto result = episode(weather, terrain, i * 3 + c,
                                            expected_for(weather, terrain));
                if (!result) {
                    runtime.stop();
                    std::cerr << "JBP-004 status=FAIL stage=acquisition_execution episode="
                              << i << " context=" << weather << "/" << terrain << "\\n";
                    return false;
                }
                if (i >= 60) correct[c] += *result;
            }
        }
        std::cout << "JBP-004 stage=known_context_acquisition"
                  << " clear_flat=" << correct[0] << "/20"
                  << " clear_rugged=" << correct[1] << "/20"
                  << " storm_flat=" << correct[2] << "/20\\n";
        for (const auto value : correct) {
            if (value < 12) {
                runtime.stop();
                std::cerr << "JBP-004 status=FAIL stage=known_context_acquisition required_each=12/20\\n";
                return false;
            }
        }
        runtime.stop();
        std::cout << "JBP-004 stage=training status=PASS seed=" << seed
                  << " trained_combinations=3 held_out=storm/rugged"
                  << " hidden_rule=two_factor_parity noise_rate=0.15 episodes=240\\n";
        return true;
    }

    // Fresh process: evaluate all three trained combinations plus the never-trained
    // fourth combination. No outcome feedback is delivered during this phase.
    std::array<std::uint64_t, 4> correct{};
    const std::array<std::pair<std::string, std::string>, 4> eval_contexts{{
        {"clear", "flat"}, {"clear", "rugged"},
        {"storm", "flat"}, {"storm", "rugged"}
    }};
    for (std::uint64_t i = 0; i < 20; ++i) {
        for (std::size_t c = 0; c < eval_contexts.size(); ++c) {
            const auto& [weather, terrain] = eval_contexts[c];
            const auto result = episode(weather, terrain, 1000 + i * 4 + c,
                                        expected_for(weather, terrain));
            if (!result) {
                runtime.stop();
                std::cerr << "JBP-004 status=FAIL stage=transfer_execution episode="
                          << i << " context=" << weather << "/" << terrain << "\\n";
                return false;
            }
            correct[c] += *result;
        }
    }
    runtime.stop();
    std::cout << "JBP-004 stage=fresh_process_evaluation"
              << " clear_flat=" << correct[0] << "/20"
              << " clear_rugged=" << correct[1] << "/20"
              << " storm_flat=" << correct[2] << "/20"
              << " held_out_storm_rugged=" << correct[3] << "/20"
              << " feedback_during_evaluation=false\\n";
    const bool known_pass = correct[0] >= 12 && correct[1] >= 12 && correct[2] >= 12;
    const bool transfer_pass = correct[3] >= 12;
    std::cout << "JBP-004 stage=known_context_recall status="
              << (known_pass ? "PASS" : "FAIL") << "\\n";
    std::cout << "JBP-004 stage=unseen_transfer status="
              << (transfer_pass ? "PASS" : "FAIL") << " required=12/20\\n";
    return known_pass && transfer_pass;
}
} // namespace

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: jarvis_jbp_004_unseen_transfer_suite train|verify <journal> <seed>\n";
        return 64;
    }
    const std::string mode = argv[1];
    const std::filesystem::path journal = argv[2];
    const auto seed = static_cast<std::uint64_t>(std::stoull(argv[3]));
    if (mode != "train" && mode != "verify") {
        std::cerr << "mode must be train or verify\n";
        return 64;
    }
    if (mode == "train" && std::filesystem::exists(journal)) {
        std::cerr << "JBP-004 status=REFUSED_OVERWRITE path=" << journal.string() << "\\n";
        return 64;
    }
    if (mode == "verify" && !std::filesystem::exists(journal)) {
        std::cerr << "JBP-004 status=FAIL reason=training_journal_missing path="
                  << journal.string() << "\\n";
        return 66;
    }
    const bool ok = run_mode(journal, seed, mode == "verify");
    return ok ? 0 : 1;
}
