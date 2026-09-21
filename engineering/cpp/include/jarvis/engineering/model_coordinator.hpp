#pragma once

#include "model_provider.hpp"

#include <vector>

namespace jarvis::engineering {

struct ModelCandidate {
    ModelDescriptor model;
    double score{0.0};
    bool eligible{false};
};

class EngineeringModelCoordinator {
public:
    std::vector<ModelCandidate> discover(
        const ModelRequest& request,
        const std::vector<ModelDescriptor>& models) const;

    std::vector<ModelCandidate> rank(
        const ModelRequest& request,
        const std::vector<ModelDescriptor>& models) const;

private:
    static bool satisfies_capabilities(
        const ModelDescriptor& model,
        const ModelRequest& request) noexcept;
};

} // namespace jarvis::engineering
