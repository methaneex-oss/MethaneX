#pragma once

#include "model_provider.hpp"

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace jarvis::engineering {

struct HttpRequest {
    std::string method;
    std::string url;
    std::vector<std::pair<std::string, std::string>> headers;
    std::string body;
};

struct HttpResponse {
    int status_code{0};
    std::string body;
    std::string error;
};

using HttpTransport = std::function<HttpResponse(const HttpRequest&)>;

struct HuggingFaceModelConfig {
    std::string model{"openai/gpt-oss-120b:fastest"};
    std::string token;
    std::string endpoint{"https://router.huggingface.co/v1/chat/completions"};
    double estimated_cost{0.0};
    double reliability{0.0};
};

class HuggingFaceModelProvider final : public EngineeringModelProvider {
public:
    HuggingFaceModelProvider(
        HuggingFaceModelConfig config,
        HttpTransport transport) noexcept;

    ModelDescriptor descriptor() const override;
    ModelResponse generate(const ModelRequest& request) override;

private:
    static std::string escape_json(std::string_view value);
    static std::string build_request_body(
        const HuggingFaceModelConfig& config,
        const ModelRequest& request);
    static std::string extract_json_string(
        std::string_view json,
        std::string_view key,
        std::size_t from = 0);
    static bool valid_config(const HuggingFaceModelConfig& config) noexcept;

    HuggingFaceModelConfig config_;
    HttpTransport transport_;
};

} // namespace jarvis::engineering
