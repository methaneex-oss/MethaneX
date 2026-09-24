#include "jarvis/core/evolution_trials.hpp"

#include <cassert>
#include <cmath>
#include <limits>

using namespace jarvis::core;

int main() {
    const auto baseline = EvolutionTrials::summarize({0.70, 0.71, 0.69, 0.70});
    const auto candidate = EvolutionTrials::summarize({0.80, 0.81, 0.79, 0.80});

    assert(baseline.count == 4);
    assert(candidate.count == 4);
    assert(std::abs(candidate.mean - 0.80) < 1e-12);
    assert(candidate.standard_error >= 0.0);

    const auto comparison = EvolutionTrials::compare(baseline, candidate, 0.95);
    assert(comparison.valid);
    assert(comparison.mean_difference > 0.0);
    assert(comparison.effect_size > 0.0);
    assert(comparison.confidence_interval_low > 0.05);
    assert(EvolutionTrials::supports_adoption(baseline, candidate, 0.05, 0.95));
    assert(!EvolutionTrials::supports_adoption(baseline, candidate, 0.20, 0.95));

    const auto single = EvolutionTrials::summarize({1.0});
    assert(single.count == 1);
    assert(single.confidence == 0.0);
    assert(!EvolutionTrials::supports_adoption(single, candidate, 0.01, 0.95));

    const auto invalid = EvolutionTrials::summarize({0.7, std::numeric_limits<double>::quiet_NaN()});
    assert(invalid.count == 0);
    assert(!EvolutionTrials::supports_adoption(baseline, invalid, 0.01, 0.95));
    return 0;
}
