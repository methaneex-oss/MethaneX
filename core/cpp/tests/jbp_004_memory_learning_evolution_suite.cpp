#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace jarvis::core;

namespace {
struct Level {
    std::string name;
    int contexts;
    int actions;
    int episodes;
    double noise;
    int reversals;
};

const std::array<Level, 3> levels{{
    {"simple", 2, 2, 240, 0.0, 1},
    {"hard", 2, 2, 480, 0.12, 1},
    {"very-hard", 3, 3, 840, 0.20, 2},
}};

const std::array<std::string, 3> context_names{{"clear", "storm", "fog"}};
const std::array<std::string, 3> action_names{{"route-a", "route-b", "route-c"}};

std::vector<CandidateAction> candidates(int count) {
    std::vector<CandidateAction> result;
    for (int i = 0; i < count; ++i) {
        result.push_back(CandidateAction{
            action_names[static_cast<std::size_t>(i)],
            0.5, 0.5, 0.9, 0.2, 1.0, 0.0, 0.5,
            DecisionOutcome::act, 0.0});
    }
    return result;
}

int selected_action(Brain& brain, const std::vector<CandidateAction>& actions,
                    const std::string& context, std::mt19937& random,
                    double exploration) {
    std::uniform_real_distribution<double> unit(0.0, 1.0);
    if (unit(random) < exploration) {
        std::uniform_int_distribution<int> choose(0, static_cast<int>(actions.size()) - 1);
        return choose(random);
    }
    const auto decisions = brain.choose_with_developmental_learning(actions, context);
    if (decisions.empty()) return 0;
    const auto best = std::max_element(decisions.begin(), decisions.end(),
        [](const Decision& left, const Decision& right) {
            return left.score < right.score;
        });
    const auto found = std::find_if(actions.begin(), actions.end(),
        [&](const CandidateAction& action) { return action.name == best->action.name; });
    return found == actions.end() ? 0 : static_cast<int>(found - actions.begin());
}

int evaluate(Brain& brain, const Level& level, int level_index, int seed,
             const std::vector<int>& best_action, int context_index,
             int trials, int action_count) {
    const auto actions = candidates(action_count);
    std::mt19937 random(static_cast<std::uint32_t>(
        seed * 7919 + level_index * 101 + context_index * 17 + 991));
    int correct = 0;
    const std::string context = "jbp-004/" + level.name + "/context/" +
        context_names[static_cast<std::size_t>(context_index)];
    for (int i = 0; i < trials; ++i) {
        const int chosen = selected_action(brain, actions, context, random, 0.0);
        if (chosen == best_action[static_cast<std::size_t>(context_index)]) ++correct;
    }
    return correct;
}

std::vector<int> initial_mapping(int seed, int level_index, int contexts, int actions) {
    std::mt19937 random(static_cast<std::uint32_t>(seed * 104729 + level_index * 997));
    std::uniform_int_distribution<int> choose(0, actions - 1);
    std::vector<int> mapping(static_cast<std::size_t>(contexts));
    for (auto& action : mapping) action = choose(random);
    return mapping;
}

void record_outcome(Brain& brain, const std::string& context,
                    const std::string& action, double actual,
                    double reliability, int episode) {
    const auto observed = brain.observe(Event{
        0, 0, "jbp-004-generated-environment", "action_outcome",
        {{"action", action},
         {"context", context},
         {"status", static_cast<std::int64_t>(ActionExecutionStatus::verified)},
         {"observed", true},
         {"expected_consequence", 0.0},
         {"actual_consequence", actual},
         {"consequence_error", std::abs(actual)},
         {"reliability", reliability},
         {"evidence_reliability", reliability},
         {"salience", 0.65},
         {"novelty", episode % 11 == 0 ? 0.7 : 0.15}}});
    assert(observed.event.sequence != 0);
}

void assert_accuracy(Brain& brain, const Level& level, int level_index, int seed,
                     const std::vector<int>& mapping, int minimum_percent) {
    for (int context = 0; context < level.contexts; ++context) {
        const int correct = evaluate(brain, level, level_index, seed, mapping,
                                     context, 30, level.actions);
        const int percent = correct * 100 / 30;
        if (percent < minimum_percent) {
            std::cerr << "JBP-004 gate failed: level=" << level.name
                      << " context=" << context_names[static_cast<std::size_t>(context)]
                      << " correct=" << correct << "/30 required_percent="
                      << minimum_percent << "\n";
            std::abort();
        }
        std::cout << "JBP-004 level=" << level.name
                  << " context=" << context_names[static_cast<std::size_t>(context)]
                  << " correct=" << correct << "/30 required_percent="
                  << minimum_percent << "\n";
    }
}

void train(const std::filesystem::path& path, int seed) {
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::remove(path.string() + ".meta", ec);
    Brain brain(path);

    for (std::size_t level_index = 0; level_index < levels.size(); ++level_index) {
        const auto& level = levels[level_index];
        auto mapping = initial_mapping(seed, static_cast<int>(level_index),
                                       level.contexts, level.actions);
        const auto original_mapping = mapping;
        const auto actions = candidates(level.actions);
        std::mt19937 random(static_cast<std::uint32_t>(
            seed * 65537 + static_cast<int>(level_index) * 31337));
        std::uniform_real_distribution<double> unit(0.0, 1.0);
        std::uniform_int_distribution<int> choose_context(0, level.contexts - 1);

        const int first_reversal = level.episodes / 2;
        const int second_reversal = level.episodes * 3 / 4;
        for (int episode = 0; episode < level.episodes; ++episode) {
            if (episode == first_reversal) {
                // Measure pre-change acquisition before mutating the hidden world.
                assert_accuracy(brain, level, static_cast<int>(level_index), seed,
                                original_mapping, 60);
                const int target = level.contexts > 1 ? 1 : 0;
                mapping[static_cast<std::size_t>(target)] =
                    (mapping[static_cast<std::size_t>(target)] + 1) % level.actions;
            }
            if (level.reversals > 1 && episode == second_reversal) {
                const int target = level.contexts - 1;
                mapping[static_cast<std::size_t>(target)] =
                    (mapping[static_cast<std::size_t>(target)] + 1) % level.actions;
            }

            const int context_index = choose_context(random);
            const std::string context = "jbp-004/" + level.name + "/context/" +
                context_names[static_cast<std::size_t>(context_index)];
            const int action_index = selected_action(
                brain, actions, context, random, level_index == 0 ? 0.22 : 0.25);
            const double expected = action_index == mapping[static_cast<std::size_t>(context_index)]
                ? 1.0 : -1.0;
            const bool flipped = unit(random) < level.noise;
            const double actual = flipped ? -expected : expected;
            const double reliability = 0.9;
            record_outcome(brain, context,
                           action_names[static_cast<std::size_t>(action_index)],
                           actual, reliability, episode);
        }

        assert_accuracy(brain, level, static_cast<int>(level_index), seed,
                        mapping, level_index == 0 ? 70 : (level_index == 1 ? 65 : 60));
        // Every level records a stable context as a control when one exists.
        if (level.contexts > 1) {
            const int control = evaluate(brain, level, static_cast<int>(level_index),
                                         seed, mapping, 0, 30, level.actions);
            std::cout << "JBP-004 final-control level=" << level.name
                      << " context=clear correct=" << control << "/30\n";
        }
    }

    // Prediction error and observed fitness must reach the evolution subsystem
    // through the same durable experience journal.
    assert(brain.register_evolution_parameter("jbp004.integration.weight", 0.35));
    for (int i = 0; i < 5; ++i) {
        const double predicted = 0.35 + static_cast<double>(i) * 0.01;
        brain.predict("jbp004.integration.weight", Scalar{predicted}, 0.9);
        const auto cycle = brain.learn_from_prediction(
            "jbp004.integration.weight", Scalar{predicted + 0.04}, 0.85);
        assert(cycle.adaptation.observations > 0);
    }
    brain.observe_evolution_fitness("jbp004.integration.weight", 0.8);
    brain.observe_evolution_fitness("jbp004.integration.weight", 0.9);
    auto proposals = brain.evolution_options();
    const auto proposal = std::find_if(proposals.begin(), proposals.end(),
        [](const EvolutionProposal& item) {
            return item.key == "jbp004.integration.weight" &&
                   std::isfinite(item.proposed) && item.proposed != item.current;
        });
    assert(proposal != proposals.end());
    EvolutionExperiment experiment{
        "jbp004-integration-" + std::to_string(seed), *proposal,
        0.70, 0.85, 0.01, 0.90, ExperimentOutcome::Improved, true};
    assert(brain.record_evolution_evaluation(experiment));
    assert(brain.adopt_evolution_experiment(experiment));
    const auto* adopted = brain.evolution_parameter("jbp004.integration.weight");
    assert(adopted != nullptr && adopted->value == proposal->proposed);

    const auto journal = brain.memory().all();
    assert(journal.size() > 500);
    assert(brain.memory().latest_sequence_by_kind("action_outcome") != 0);
    assert(brain.memory().latest_sequence_by_kind("prediction_outcome") != 0);
    assert(brain.memory().latest_sequence_by_kind("evolution_adopt") != 0);
    std::cout << "JBP-004 train passed seed=" << seed
              << " journal_events=" << journal.size()
              << " evolution_value=" << adopted->value << "\n";
}

void verify(const std::filesystem::path& path, int seed) {
    Brain restored(path);
    for (std::size_t level_index = 0; level_index < levels.size(); ++level_index) {
        const auto& level = levels[level_index];
        auto mapping = initial_mapping(seed, static_cast<int>(level_index),
                                       level.contexts, level.actions);
        mapping[static_cast<std::size_t>(level.contexts > 1 ? 1 : 0)] =
            (mapping[static_cast<std::size_t>(level.contexts > 1 ? 1 : 0)] + 1) % level.actions;
        if (level.reversals > 1) {
            const int target = level.contexts - 1;
            mapping[static_cast<std::size_t>(target)] =
                (mapping[static_cast<std::size_t>(target)] + 1) % level.actions;
        }
        assert_accuracy(restored, level, static_cast<int>(level_index), seed,
                        mapping, level_index == 0 ? 70 : (level_index == 1 ? 65 : 60));
    }

    const auto outcomes = restored.memory().by_kind("action_outcome");
    assert(outcomes.size() > 500);
    const auto recalled = restored.memory().recall_ranked(
        {{"context", Scalar{std::string("jbp-004/hard/context/storm")}}}, 16,
        "action_outcome", true);
    assert(!recalled.empty());
    assert(std::any_of(recalled.begin(), recalled.end(), [](const MemoryRecord& record) {
        return record.event.data.contains("actual_consequence") &&
               record.event.data.contains("action");
    }));

    const auto* parameter = restored.evolution_parameter("jbp004.integration.weight");
    assert(parameter != nullptr);
    assert(parameter->observations >= 2);
    assert(parameter->value != parameter->baseline);
    const auto history = restored.evolution_history();
    assert(std::any_of(history.begin(), history.end(),
        [](const EvolutionHistoryRecord& record) {
            return record.parameter_key == "jbp004.integration.weight" &&
                   record.action == EvolutionRecordAction::Adopted;
        }));

    std::cout << "JBP-004 fresh-process verify passed seed=" << seed
              << " outcomes=" << outcomes.size()
              << " evolution_value=" << parameter->value << "\n";
}
} // namespace

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: jarvis_jbp_004_memory_learning_evolution_suite "
                     "<train|verify> <journal-path> <seed>\n";
        return 2;
    }
    const std::string mode = argv[1];
    const std::filesystem::path path = argv[2];
    const int seed = std::stoi(argv[3]);
    if (mode == "train") train(path, seed);
    else if (mode == "verify") verify(path, seed);
    else return 2;
    return 0;
}
