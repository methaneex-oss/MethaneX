#include "jarvis/engineering/model_provider.hpp"

#include <cmath>

namespace jarvis::engineering {

bool valid_model_descriptor(const ModelDescriptor& descriptor) noexcept {
    if (descriptor.id.empty() || descriptor.provider.empty() || descriptor.model.empty()) {
        return false;
    }
    if (!std::isfinite(descriptor.estimated_cost) || descriptor.estimated_cost < 0.0) {
        return false;
    }
    if (!std::isfinite(descriptor.reliability) ||
        descriptor.reliability < 0.0 || descriptor.reliability > 1.0) {
        return false;
    }
    return true;
}

bool valid_model_request(const ModelRequest& request) noexcept {
    if (request.objective.empty() || request.maximum_output_bytes == 0) {
        return false;
    }
    return true;
}

} // namespace jarvis::engineering
