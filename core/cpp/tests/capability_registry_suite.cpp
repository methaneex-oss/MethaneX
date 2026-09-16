#include "jarvis/core/capability_registry.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    CapabilityRegistry registry;

    CapabilityDescriptor inspect{
        .id = "repo.inspect",
        .name = "Repository inspection",
        .description = "Inspect repository state through an external provider.",
        .input_schema = {"repository", "ref"},
        .output_schema = {"repository_state"},
        .permissions = {"repository.read"},
        .estimated_cost = 1.0,
        .risk = CapabilityRisk::low,
        .reliability = 0.98,
        .availability = CapabilityAvailability::available,
        .reversible = true,
    };

    assert(registry.register_capability(inspect));
    assert(!registry.register_capability(inspect));
    assert(registry.size() == 1);

    const auto found = registry.find("repo.inspect");
    assert(found.has_value());
    assert(found->permissions.size() == 1);
    assert(found->reliability == 0.98);

    CapabilityDescriptor degraded = inspect;
    degraded.id = "repo.write";
    degraded.name = "Repository mutation";
    degraded.availability = CapabilityAvailability::degraded;
    degraded.reliability = 0.7;
    degraded.risk = CapabilityRisk::high;
    degraded.reversible = false;
    assert(registry.register_capability(degraded));

    assert(registry.discover(CapabilityAvailability::available).size() == 1);
    assert(registry.discover(CapabilityAvailability::degraded).size() == 2);

    assert(!registry.register_capability(CapabilityDescriptor{}));
    assert(!registry.unregister_capability("missing"));
    assert(registry.unregister_capability("repo.write"));
    assert(registry.size() == 1);

    registry.clear();
    assert(registry.size() == 0);
    return 0;
}
