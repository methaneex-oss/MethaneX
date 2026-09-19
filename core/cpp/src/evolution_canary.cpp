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
        return {false, observations_ >= policy_.minimum_observations, 0.0, worst_delta_, "invalid_observation"};
    }
    ++observations_;
    const double delta = observation.candidate_fitness - observation.baseline_fitness;
    delta_sum_ += delta;
    if (observations_ == 1 || delta < worst_delta_) worst_delta_ = delta;
    return evaluate();
}

CanaryDecision EvolutionCanary::evaluate() const noexcept {
    if (observations_ == 0) return {false, false, 0.0, 0.0, "no_observations"};
    const double mean_delta = delta_sum_ / static_cast<double>(observations_);
    const bool sufficient = observations_ >= policy_.minimum_observations;
    if (!sufficient) return {false, false, mean_delta, worst_delta_, "insufficient_evidence"};
    if (!std::isfinite(mean_delta) || !std::isfinite(worst_delta_))
        return {true, true, 0.0, worst_delta_, "non_finite_delta"};
    if (worst_delta_ < -std::abs(policy_.maximum_regression))
        return {true, true, mean_delta, worst_delta_, "regression_detected"};
    return {false, true, mean_delta, worst_delta_, "within_policy"};
}

void EvolutionCanary::reset() noexcept {
    observations_ = 0;
    delta_sum_ = 0.0;
    worst_delta_ = 0.0;
}

} // namespace jarvis::core
