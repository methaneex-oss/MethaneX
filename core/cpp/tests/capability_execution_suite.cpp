#include "jarvis/core/capability_execution.hpp"

#include <cassert>

using namespace jarvis::core;

int main() {
    CapabilityDescriptor capability{
        .id = "repo.inspect",
        .name = "Repository inspection",
        .description = "Inspect repository state.",
        .permissions = {"repository.read"},
        .estimated_cost = 1.0,
        .risk = CapabilityRisk::low,
        .reliability = 0.95,
        .availability = CapabilityAvailability::available,
        .reversible = true,
    };

    bool called = false;
    CapabilityProvider provider{
        capability.id,
        [&](const CapabilityExecutionRequest& request) {
            called = true;
            assert(request.capability.id == "repo.inspect");
            assert(request.input == "repository=MethaneX");
            return CapabilityExecutionResult::success(
                request.capability.id, "repository_state=available", "provider.test");
        }
    };

    CapabilityExecutionBoundary boundary;
    assert(boundary.register_provider(std::move(provider)));

    CapabilityExecutionRequest request{capability, "repository=MethaneX", {"repository.read"}, 0.5};
    const auto result = boundary.execute(request);

    assert(called);
    assert(result.status == CapabilityExecutionStatus::succeeded);
    assert(result.output == "repository_state=available");
    assert(result.provider == "provider.test");

    const auto denied = boundary.execute(
        CapabilityExecutionRequest{capability, "repository=MethaneX", {}, 0.5});
    assert(denied.status == CapabilityExecutionStatus::rejected);
    assert(denied.reason == "authorization_permission_denied");

    return 0;
}
