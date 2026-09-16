#include "jarvis/core/evolution_experiment_runner.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace jarvis::core;

int main() {
    EvolutionProposal proposal{"strategy.weight", 0.4, 0.5, 0.1, 0.8};
    EvolutionExperiment experiment{"paired-run", proposal, 0.0, 0.0, 0.05, 0.0};

    std::size_t baseline_calls = 0;
    std::size_t candidate_calls = 0;
    const auto improved = EvolutionExperimentRunner::run(
        experiment,
        [&baseline_calls](double parameter) {
            ++baseline_calls;
            return 0.70 + parameter * 0.0;
        },
        [&candidate_calls](double parameter) {
            ++candidate_calls;
            return 0.90 + parameter * 0.0;
        },
        4);

    assert(baseline_calls == 4);
    assert(candidate_calls == 4);
    assert(improved.baseline.trials == 4);
    assert(improved.candidate.trials == 4);
    assert(std::abs(improved.improvement - 0.20) < 1e-12);
    assert(improved.confidence > 0.99);
    assert(improved.outcome == ExperimentOutcome::Improved);

    const auto noisy = EvolutionExperimentRunner::run(
        experiment,
        [](double) { return 0.70; },
        [](double) { return 0.70; },
        4);
    assert(noisy.outcome == ExperimentOutcome::Neutral);
    assert(noisy.confidence == 0.0);

    const auto degraded = EvolutionExperimentRunner::run(
        experiment,
        [](double) { return 0.90; },
        [](double) { return 0.70; },
        3);
    assert(degraded.outcome == ExperimentOutcome::Degraded);

    const auto invalid = EvolutionExperimentRunner::run(
        experiment,
        [](double) { return std::numeric_limits<double>::quiet_NaN(); },
        [](double) { return 0.90; },
        3);
    assert(invalid.outcome == ExperimentOutcome::Invalid);
    assert(invalid.baseline.trials == 0);

    const auto throws = EvolutionExperimentRunner::run(
        experiment,
        [](double) -> double { throw std::runtime_error("failed trial"); },
        [](double) { return 0.90; },
        3);
    assert(throws.outcome == ExperimentOutcome::Invalid);

    const auto zero_trials = EvolutionExperimentRunner::run(
        experiment, [](double) { return 1.0; }, [](double) { return 1.0; }, 0);
    assert(zero_trials.outcome == ExperimentOutcome::Invalid);

    return 0;
}
