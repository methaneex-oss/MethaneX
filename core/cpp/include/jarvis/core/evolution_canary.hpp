#pragma once

#include <cstddef>
#include <string>

namespace jarvis::core {

struct CanaryPolicy {
    std::size_t minimum_observations{3};
    double maximum_regression{0.0};
};

struct CanaryObservation {
    double baseline_fitness{0.0};
    double candidate_fitness{0.0};
};

struct CanaryDecision {
    bool rollback{false};
    bool sufficient_evidence{false};
    double mean_delta{0.0};
    std::string reason;
};

class EvolutionCanary {
public:
    explicit EvolutionCanary(CanaryPolicy policy = {});
    CanaryDecision observe(CanaryObservation observation) noexcept;
    CanaryDecision evaluate() const noexcept;
    void reset() noexcept;
private:
    CanaryPolicy policy_;
    std::size_t observations_{0};
    double delta_sum_{0.0};
};

} // namespace jarvis::core
