#pragma once

#include "message_bus.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace jarvis::engineering {

enum class AgentRisk : std::uint8_t { low, medium, high, critical };
enum class AgentAvailability : std::uint8_t { unavailable, degraded, available };

struct AgentDescriptor {
    std::string id;
    std::string name;
    std::string provider;
    std::string description;
    std::vector<std::string> capabilities;
    std::vector<std::string> permissions;
    std::vector<std::string> input_artifacts;
    std::vector<std::string> output_artifacts;
    double estimated_cost{0.0};
    double reliability{0.0};
    AgentRisk risk{AgentRisk::low};
    AgentAvailability availability{AgentAvailability::unavailable};
    bool supports_concurrency{false};
};

struct AgentArtifact {
    std::string type;
    std::string location;
    std::string digest;
};

struct AgentEvidence {
    std::string kind;
    std::string value;
};

struct EngineeringTask {
    std::string id;
    std::string objective;
    std::vector<std::string> required_capabilities;
    std::vector<std::string> required_permissions;
    std::vector<std::string> input_artifacts;
    std::vector<std::string> expected_artifacts;
    AgentRisk maximum_risk{AgentRisk::high};
    double maximum_cost{0.0};
    std::string workspace_id;
    bool manage_workspace{true};
    std::vector<std::string> workspace_files;
    std::vector<AgentArtifact> prior_stage_artifacts;
    std::vector<AgentEvidence> prior_stage_evidence;
    std::vector<AgentMessage> incoming_messages;
    AgentCommunicationEndpoint* communication{nullptr};
    std::vector<std::string> communication_targets;
};

struct AgentResult {
    bool accepted{false};
    std::string agent_id;
    std::string task_id;
    std::string reason;
    std::vector<AgentArtifact> artifacts;
    std::vector<AgentEvidence> evidence;
};

class EngineeringAgent {
public:
    virtual ~EngineeringAgent() = default;
    virtual AgentDescriptor descriptor() const = 0;
    virtual AgentResult execute(const EngineeringTask& task) = 0;
};

bool valid_descriptor(const AgentDescriptor& descriptor) noexcept;
bool valid_task(const EngineeringTask& task) noexcept;

} // namespace jarvis::engineering
