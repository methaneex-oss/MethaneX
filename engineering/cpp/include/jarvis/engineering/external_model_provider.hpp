#pragma once

#include "model_provider.hpp"

namespace jarvis::engineering {

class EngineeringModelTransport {
public:
    virtual ~EngineeringModelTransport() = default;
    virtual ModelResponse request(
        const ModelDescriptor& descriptor,
        const ModelRequest& request) = 0;
};

class ExternalEngineeringModelProvider final : public EngineeringModelProvider {
public:
    ExternalEngineeringModelProvider(
        ModelDescriptor descriptor,
        EngineeringModelTransport& transport) noexcept;

    ModelDescriptor descriptor() const override;
    ModelResponse generate(const ModelRequest& request) override;

private:
    ModelDescriptor descriptor_;
    EngineeringModelTransport& transport_;
};

} // namespace jarvis::engineering
