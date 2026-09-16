#include "jarvis/core/capability_evaluator.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

int CapabilityEvaluator::risk_rank(CapabilityRisk risk) noexcept {
    return static_cast<int>(risk);
}

double CapabilityEvaluator::bounded(double value) noexcept {
    return std::isfinite(value) ? std::clamp(value, 0.0, 1.0) : 0.0;
}

std::vector<CapabilityCandidate> CapabilityEvaluator::evaluate(
    const std::vector<CapabilityDescriptor>& capabilities,
    const CapabilityConstraints& constraints) const {
    const double minimum_reliability = bounded(constraints.minimum_reliability);
    std::vector<CapabilityCandidate> result;
    result.reserve(capabilities.size());

    for (const auto& capability : capabilities) {
        const double reliability = bounded(capability.reliability);
        const double cost = std::max(0.0, std::isfinite(capability.estimated_cost)
            ? capability.estimated_cost : 0.0);
        const bool eligible = capability.availability == CapabilityAvailability::available &&
                              risk_rank(capability.risk) <= risk_rank(constraints.maximum_risk) &&
                              (constraints.maximum_cost <= 0.0 || cost <= constraints.maximum_cost) &&
                              reliability >= minimum_reliability &&
                              (!constraints.require_reversible || capability.reversible);

        // The evaluator scores only observable operational properties. It does not
        // infer meaning from names/descriptions or map user phrases to capabilities.
        const double score = eligible
            ? reliability + (capability.reversible ? 0.1 : 0.0) -
              (constraints.maximum_cost > 0.0 ? 0.1 * cost / constraints.maximum_cost : 0.0)
            : 0.0;
        result.push_back(CapabilityCandidate{capability, score, eligible});
    }

    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        if (a.eligible != b.eligible) return a.eligible > b.eligible;
        if (a.score != b.score) return a.score > b.score;
        return a.capability.id < b.capability.id;
    });
    return result;
}

} // namespace jarvis::core
