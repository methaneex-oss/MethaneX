#pragma once

#include "agent.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace jarvis::engineering {

enum class ModelProviderStatus : std::uint8_t {
    succeeded,
    rejected,
    unavailable,
    failed,
};

struct ModelDescriptor {
    std::string id;
    std::string provider;
    std::string model;
    std::vector<std::string> capabilities;
    double estimated_cost{0.0};
    double reliability{0.0};
};

struct ModelRequest {
    std::string objective;
    std::string context;
    std::vector<std::string> expected_artifacts;
    std::size_t maximum_output_bytes{1024 * 1024};
};

struct ModelFileChange {
    std::string path;
    std::string content;
};

struct ModelResponse {
    ModelProviderStatus status{ModelProviderStatus::failed};
    std::string provider;
    std::string model;
    std::string output;
    std::vector<ModelFileChange> file_changes;
    std::vector<AgentEvidence> evidence;
    std::string reason;
};

class EngineeringModelProvider {
public:
    virtual ~EngineeringModelProvider() = default;
    virtual ModelDescriptor descriptor() const = 0;
    virtual ModelResponse generate(const ModelRequest& request) = 0;
};

bool valid_model_descriptor(const ModelDescriptor& descriptor) noexcept;
bool valid_model_request(const ModelRequest& request) noexcept;

} // namespace jarvis::engineering
