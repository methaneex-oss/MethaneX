#include "jarvis/engineering/agent_charter.hpp"

namespace jarvis::engineering {

AgentCharter default_engineering_charter(const AgentDescriptor& descriptor) {
    AgentCharter charter;
    charter.mission =
        "Build and verify JARVIS as a persistent, adaptive, software-first cognitive system.";
    charter.ownership =
        descriptor.id.empty()
            ? "Explicit subsystem ownership must be assigned before mutation."
            : "Subsystem owned by agent " + descriptor.id + ".";
    charter.allowed_paths = {
        "Only task-declared paths and explicitly approved integration files."};
    charter.forbidden_operations = {
        "hard-coded intelligence",
        "bypassing authorization or execution boundaries",
        "unverified authoritative-state mutation",
        "silent public-contract changes",
        "unbounded or unisolated execution",
        "claiming completion without evidence",
        "duplicating an existing capability without justification"};
    charter.preserved_contracts = {
        "provider-neutral interfaces",
        "authorization and execution boundaries",
        "artifact provenance and evidence flow",
        "workspace isolation and conflict rules",
        "persistence and restart semantics",
        "security invariants",
        "existing tests and CI expectations"};
    charter.mandatory_tests = {
        "relevant unit tests",
        "relevant integration/regression tests",
        "build and CI checks",
        "sanitizer or failure-path tests when the touched subsystem requires them"};
    charter.completion_requirements = {
        "requested behavior implemented",
        "relevant state/artifact transition verified",
        "failure paths handled",
        "mandatory tests passing",
        "evidence and known limitations submitted"};
    return charter;
}

} // namespace jarvis::engineering
