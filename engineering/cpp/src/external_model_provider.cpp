#include "jarvis/engineering/external_model_provider.hpp"

#include <utility>

namespace jarvis::engineering {

ExternalEngineeringModelProvider::ExternalEngineeringModelProvider(
    ModelDescriptor descriptor,
    EngineeringModelTransport& transport) noexcept
    : descriptor_(std::move(descriptor)), transport_(transport) {}

ModelDescriptor ExternalEngineeringModelProvider::descriptor() const {
    return descriptor_;
}

ModelResponse ExternalEngineeringModelProvider::generate(const ModelRequest& request) {
    if (!valid_model_descriptor(descriptor_)) {
        return {ModelProviderStatus::rejected, descriptor_.provider, descriptor_.model,
                {}, {}, {}, "invalid external model descriptor"};
    }
    if (!valid_model_request(request)) {
        return {ModelProviderStatus::rejected, descriptor_.provider, descriptor_.model,
                {}, {}, {}, "invalid model request"};
    }

    auto response = transport_.request(descriptor_, request);
    if (response.provider.empty()) response.provider = descriptor_.provider;
    if (response.model.empty()) response.model = descriptor_.model;
    return response;
}

} // namespace jarvis::engineering
