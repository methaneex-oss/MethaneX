#pragma once

#include "cognition.hpp"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace jarvis::core {

struct CausalPrediction {
    std::string key;
    Scalar value;
    double confidence{0.0};
    std::size_t depth{0};
};

struct SimulationResult {
    std::vector<CausalPrediction> predictions;
    double confidence{0.0};
    std::size_t depth{0};
};

class CausalModel {
public:
    void observe_transition(const std::vector<Belief>& before, const std::vector<Belief>& after);
    std::vector<CausalLink> links() const;
    std::vector<std::pair<std::string, Scalar>> predict(const std::vector<Belief>& assumptions) const;
    SimulationResult simulate(const std::vector<Belief>& assumptions, std::size_t horizon = 2) const;

private:
    std::vector<CausalLink> links_;
};

} // namespace jarvis::core
