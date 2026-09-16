#pragma once

#include "capability_registry.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct CapabilityConstraints {
    CapabilityRisk maximum_risk{CapabilityRisk::high};
    double maximum_cost{0.0};
    double minimum_reliability{0.0};
    bool require_reversible{false};
};

struct CapabilityCandidate {
    CapabilityDescriptor capability;
    double score{0.0};
    bool eligible{false};
};

class CapabilityEvaluator {
public:
    std::vector<CapabilityCandidate> evaluate(
        const std::vector<CapabilityDescriptor>& capabilities,
        const CapabilityConstraints& constraints = {}) const;

private:
    static int risk_rank(CapabilityRisk risk) noexcept;
    static double bounded(double value) noexcept;
};

} // namespace jarvis::core
