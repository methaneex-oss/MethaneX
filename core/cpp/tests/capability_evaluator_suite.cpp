#include "jarvis/core/capability_evaluator.hpp"

#include <cassert>
#include <vector>

using namespace jarvis::core;

int main() {
    CapabilityDescriptor reliable{"github.inspect", "GitHub inspection", "Inspect repository state", {}, {}, {"repo:read"}, 0.1, CapabilityRisk::low, 0.95, CapabilityAvailability::available, true};
    CapabilityDescriptor risky{"system.modify", "System modification", "Modify system state", {}, {}, {"system:write"}, 0.2, CapabilityRisk::critical, 0.99, CapabilityAvailability::available, false};
    CapabilityDescriptor degraded{"remote.inspect", "Remote inspection", "Inspect remote state", {}, {}, {"remote:read"}, 0.1, CapabilityRisk::low, 0.9, CapabilityAvailability::degraded, true};

    CapabilityEvaluator evaluator;
    const auto result = evaluator.evaluate({reliable, risky, degraded}, CapabilityConstraints{CapabilityRisk::high, 0.5, 0.8, true});

    assert(result.size() == 3);
    assert(result[0].eligible);
    assert(result[0].capability.id == "github.inspect");
    assert(!result[1].eligible || result[1].capability.id != "system.modify");

    const auto strict = evaluator.evaluate({reliable}, CapabilityConstraints{CapabilityRisk::low, 0.05, 0.8, true});
    assert(strict.size() == 1);
    assert(!strict[0].eligible);
    return 0;
}
