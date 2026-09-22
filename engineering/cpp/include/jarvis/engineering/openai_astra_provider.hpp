#pragma once

#include "http_transport.hpp"
#include "model_provider.hpp"

#include <string>
#include <string_view>

namespace jarvis::engineering {

struct OpenAIAstraModelConfig {
    std::string model{"gpt-6-astra"};
    std::string token;
    std::string endpoint{"https://api.openai.com/v1/responses"};
    std::string reasoning_effort{"high"};
    double estimated_cost{0.0};
    double reliability{0.0};
};

class OpenAIAstraModelProvider final : public EngineeringModelProvider {
public:
    OpenAIAstraModelProvider(
        OpenAIAstraModelConfig config,
        HttpTransport transport) noexcept;

    ModelDescriptor descriptor() const override;
    ModelResponse generate(const ModelRequest& request) override;

private:
    static std::string escape_json(std::string_view value);
    static std::string build_request_body(
        const OpenAIAstraModelConfig& config,
        const ModelRequest& request);
    static std::string extract_json_string(
        std::string_view json,
        std::string_view key,
        std::size_t from = 0);
    static std::vector<ModelFileChange> extract_file_changes(
        std::string_view json);
    static bool valid_config(const OpenAIAstraModelConfig& config) noexcept;

    OpenAIAstraModelConfig config_;
    HttpTransport transport_;
};

} // namespace jarvis::engineering
