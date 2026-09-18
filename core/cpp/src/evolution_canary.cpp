#include "jarvis/core/evolution_canary.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

EvolutionCanary::EvolutionCanary(CanaryPolicy policy) : policy_(policy) {
    if (policy_.minimum_observations == 0) policy_.minimum_observations = 1;
    if (!std::isfinite(policy_.maximum_regression) || policy_.maximum_regression < 0.0)
        policy_.maximum_regression = 0.02;
}

CanaryDecision EvolutionCanary::observe(CanaryObservation observation) noexcept {
    if (!std::isfinite(observation.baseline_fitness) ||
        !std::isfinite(observation.candidate_fitness)) {
        return {false, observations_ >= policy_.minimum_observations, 0.0, "invalid_observation"};
    }
    ++observations_;
    delta_sum_ += observation.candidate_fitness - observation.baseline_fitness;
    return evaluate();
}

CanaryDecision EvolutionCanary::evaluate() const noexcept {
    if (observations_ == 0) return {false, false, 0.0, "no_observations"};
    const double mean_delta = delta_sum_ / static_cast<double>(observations_);
    const bool sufficient = observations_ >= policy_.minimum_observations;
    if (!sufficient) return {false, false, mean_delta, "insufficient_evidence"};
    if (!std::isfinite(mean_delta)) return {true, true, 0.0, "non_finite_delta"};
    if (mean_delta < -std::abs(policy_.maximum_regression))
        return {true, true, mean_delta, "regression_detected"};
    return {false, true, mean_delta, "within_policy"};
}

void EvolutionCanary::reset() noexcept {
    observations_ = 0;
    delta_sum_ = 0.0;
}

} // namespace jarvis::core
