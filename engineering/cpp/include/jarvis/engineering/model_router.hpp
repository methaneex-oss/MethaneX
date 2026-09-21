#pragma once

#include "model_coordinator.hpp"

#include <mutex>
#include <vector>

namespace jarvis::engineering {

class EngineeringModelRouter final : public EngineeringModelProvider {
public:
    bool register_provider(EngineeringModelProvider& provider);
    bool unregister_provider(std::string_view provider_id);

    ModelDescriptor descriptor() const override;
    ModelResponse generate(const ModelRequest& request) override;

private:
    mutable std::mutex mutex_;
    std::vector<EngineeringModelProvider*> providers_;
};

} // namespace jarvis::engineering
