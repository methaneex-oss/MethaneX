#include "jarvis/engineering/model_router.hpp"

#include <algorithm>

namespace jarvis::engineering {

bool EngineeringModelRouter::register_provider(EngineeringModelProvider& provider) {
    const auto descriptor = provider.descriptor();
    if (!valid_model_descriptor(descriptor)) {
        return false;
    }

    std::lock_guard lock(mutex_);
    const auto duplicate = std::find_if(providers_.begin(), providers_.end(),
        [&](const auto* current) {
            return current == &provider || current->descriptor().id == descriptor.id;
        });
    if (duplicate != providers_.end()) {
        return false;
    }
    providers_.push_back(&provider);
    return true;
}

bool EngineeringModelRouter::unregister_provider(std::string_view provider_id) {
    std::lock_guard lock(mutex_);
    const auto old_size = providers_.size();
    providers_.erase(std::remove_if(providers_.begin(), providers_.end(),
        [&](const auto* provider) {
            return provider->descriptor().id == provider_id;
        }), providers_.end());
    return providers_.size() != old_size;
}

ModelDescriptor EngineeringModelRouter::descriptor() const {
    return {"engineering-router", "jarvis", "routing",
            {"source", "code-generation"}, 0.0, 0.0};
}

ModelResponse EngineeringModelRouter::generate(const ModelRequest& request) {
    if (!valid_model_request(request)) {
        return {ModelProviderStatus::rejected, "jarvis", "routing", {}, {}, {},
                "invalid model request"};
    }

    std::vector<EngineeringModelProvider*> providers;
    {
        std::lock_guard lock(mutex_);
        providers = providers_;
    }

    std::vector<ModelDescriptor> descriptors;
    descriptors.reserve(providers.size());
    for (auto* provider : providers) {
        descriptors.push_back(provider->descriptor());
    }

    EngineeringModelCoordinator coordinator;
    const auto ranked = coordinator.rank(request, descriptors);

    for (const auto& candidate : ranked) {
        if (!candidate.eligible) {
            continue;
        }

        auto it = std::find_if(providers.begin(), providers.end(),
            [&](auto* provider) {
                return provider->descriptor().id == candidate.model.id;
            });
        if (it == providers.end()) {
            continue;
        }

        const auto response = (*it)->generate(request);
        if (response.status == ModelProviderStatus::succeeded ||
            response.status == ModelProviderStatus::rejected) {
            return response;
        }
        if (response.status != ModelProviderStatus::unavailable &&
            response.status != ModelProviderStatus::failed) {
            return response;
        }
    }

    return {ModelProviderStatus::unavailable, "jarvis", "routing", {}, {}, {},
            "no eligible model provider available"};
}

} // namespace jarvis::engineering
