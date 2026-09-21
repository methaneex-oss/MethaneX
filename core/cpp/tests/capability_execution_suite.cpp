#include "jarvis/core/capability_execution.hpp"
#include "jarvis/core/brain.hpp"

#include <cassert>
#include <filesystem>

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

    const auto path = std::filesystem::temp_directory_path() / "jarvis_capability_execution_brain.bin";
    std::error_code ec;
    std::filesystem::remove(path, ec);
    Brain brain(path);
    bool brain_called = false;
    CapabilityProvider brain_provider{capability.id, [&](const CapabilityExecutionRequest& request) {
        brain_called = true;
        assert(request.input == "repository=MethaneX");
        return CapabilityExecutionResult::success(request.capability.id, "brain_provider_ok", "provider.test");
    }};
    const auto brain_result = brain.execute_capability(
        capability, "repository=MethaneX", {"repository.read"}, 0.5, std::move(brain_provider));
    assert(brain_called);
    assert(brain_result.status == CapabilityExecutionStatus::succeeded);
    assert(brain_result.output == "brain_provider_ok");
    assert(brain_result.provider == "provider.test");
    assert(brain.memory().size() == 1);
    const auto events = brain.memory().by_kind("capability_execution");
    assert(events.size() == 1);
    assert(std::get<std::string>(events.front().data.at("capability_id")) == "repo.inspect");
    assert(std::get<std::string>(events.front().data.at("provider")) == "provider.test");
    assert(std::get<std::int64_t>(events.front().data.at("status")) == static_cast<std::int64_t>(CapabilityExecutionStatus::succeeded));
    std::filesystem::remove(path, ec);
    return 0;
}
