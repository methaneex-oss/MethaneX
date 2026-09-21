#include "jarvis/engineering/huggingface_provider.hpp"

#include <cmath>
#include <utility>

namespace jarvis::engineering {

HuggingFaceModelProvider::HuggingFaceModelProvider(
    HuggingFaceModelConfig config,
    HttpTransport transport) noexcept
    : config_(std::move(config)), transport_(std::move(transport)) {}

ModelDescriptor HuggingFaceModelProvider::descriptor() const {
    return {
        "huggingface",
        "hugging-face",
        config_.model,
        {"code.implementation", "code.review", "code.verification", "report"},
        config_.estimated_cost,
        config_.reliability
    };
}

bool HuggingFaceModelProvider::valid_config(
    const HuggingFaceModelConfig& config) noexcept {
    return !config.model.empty() &&
           !config.token.empty() &&
           !config.endpoint.empty() &&
           std::isfinite(config.estimated_cost) &&
           config.estimated_cost >= 0.0 &&
           std::isfinite(config.reliability) &&
           config.reliability >= 0.0 && config.reliability <= 1.0;
}

std::string HuggingFaceModelProvider::escape_json(std::string_view value) {
    std::string escaped;
    escaped.reserve(value.size() + 16);
    for (const char ch : value) {
        switch (ch) {
        case '"': escaped += "\\""; break;
        case '\': escaped += "\\\\"; break;
        case '\b': escaped += "\\b"; break;
        case '\f': escaped += "\\f"; break;
        case '\n': escaped += "\\n"; break;
        case '\r': escaped += "\\r"; break;
        case '\t': escaped += "\\t"; break;
        default:
            if (static_cast<unsigned char>(ch) < 0x20) {
                escaped += ' ';
            } else {
                escaped += ch;
            }
        }
    }
    return escaped;
}

std::string HuggingFaceModelProvider::build_request_body(
    const HuggingFaceModelConfig& config,
    const ModelRequest& request) {
    return "{\"model\":\"" + escape_json(config.model) +
        "\",\"messages\":[{\"role\":\"user\",\"content\":\"" +
        escape_json(request.objective + "\n\n" + request.context) +
        "\"}],\"stream\":false}";
}

std::string HuggingFaceModelProvider::extract_json_string(
    std::string_view json,
    std::string_view key,
    std::size_t from) {
    const std::string marker = "\"" + std::string(key) + "\":\"";
    const std::size_t begin = json.find(marker, from);
    if (begin == std::string_view::npos) {
        return {};
    }

    const std::size_t value_begin = begin + marker.size();
    std::string value;
    bool escaped = false;
    for (std::size_t i = value_begin; i < json.size(); ++i) {
        const char ch = json[i];
        if (escaped) {
            switch (ch) {
            case 'n': value += '\n'; break;
            case 'r': value += '\r'; break;
            case 't': value += '\t'; break;
            case 'b': value += '\b'; break;
            case 'f': value += '\f'; break;
            case '"': value += '"'; break;
            case '\': value += '\\'; break;
            default: value += ch; break;
            }
            escaped = false;
        } else if (ch == '\\') {
            escaped = true;
        } else if (ch == '"') {
            return value;
        } else {
            value += ch;
        }
    }
    return {};
}

ModelResponse HuggingFaceModelProvider::generate(const ModelRequest& request) {
    if (!valid_config(config_) || !valid_model_request(request) || !transport_) {
        return {ModelProviderStatus::rejected, "hugging-face", config_.model,
                {}, {}, {}, "invalid configuration, request, or transport"};
    }

    const HttpRequest http{
        "POST",
        config_.endpoint,
        {{"Authorization", "Bearer " + config_.token},
         {"Content-Type", "application/json"}},
        build_request_body(config_, request)
    };
    const auto response = transport_(http);

    if (response.status_code == 401 || response.status_code == 403) {
        return {ModelProviderStatus::rejected, "hugging-face", config_.model,
                {}, {}, {}, "hugging-face authorization rejected"};
    }
    if (response.status_code == 429 || response.status_code == 408 ||
        response.status_code >= 500) {
        return {ModelProviderStatus::unavailable, "hugging-face", config_.model,
                {}, {}, {}, response.error.empty()
                    ? "hugging-face temporarily unavailable"
                    : response.error};
    }
    if (response.status_code < 200 || response.status_code >= 300) {
        return {ModelProviderStatus::failed, "hugging-face", config_.model,
                {}, {}, {}, response.error.empty()
                    ? "hugging-face request failed"
                    : response.error};
    }

    const std::string output = extract_json_string(response.body, "content");
    if (output.empty()) {
        return {ModelProviderStatus::failed, "hugging-face", config_.model,
                {}, {}, {}, "hugging-face response missing assistant content"};
    }
    if (output.size() > request.maximum_output_bytes) {
        return {ModelProviderStatus::failed, "hugging-face", config_.model,
                {}, {}, {}, "hugging-face output limit exceeded"};
    }

    return {ModelProviderStatus::succeeded, "hugging-face", config_.model,
            output, {}, {{"model.provider", "hugging-face"},
                         {"model.id", config_.model}}, {}};
}

} // namespace jarvis::engineering
