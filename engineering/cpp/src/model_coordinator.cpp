#include "jarvis/engineering/model_coordinator.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::engineering {

namespace {

bool contains(const std::vector<std::string>& values, const std::string& required) noexcept {
    return std::find(values.begin(), values.end(), required) != values.end();
}

} // namespace

bool EngineeringModelCoordinator::satisfies_capabilities(
    const ModelDescriptor& model,
    const ModelRequest& request) noexcept {
    for (const auto& artifact : request.expected_artifacts) {
        if (!contains(model.capabilities, artifact)) {
            return false;
        }
    }
    return true;
}

std::vector<ModelCandidate> EngineeringModelCoordinator::discover(
    const ModelRequest& request,
    const std::vector<ModelDescriptor>& models) const {
    std::vector<ModelCandidate> candidates;
    for (const auto& model : models) {
        const bool eligible =
            valid_model_descriptor(model) &&
            valid_model_request(request) &&
            satisfies_capabilities(model, request);

        double score = 0.0;
        if (eligible) {
            score += model.reliability;
            score += 1.0 / (1.0 + std::max(0.0, model.estimated_cost));
        }
        candidates.push_back({model, score, eligible});
    }
    return candidates;
}

std::vector<ModelCandidate> EngineeringModelCoordinator::rank(
    const ModelRequest& request,
    const std::vector<ModelDescriptor>& models) const {
    auto candidates = discover(request, models);
    std::stable_sort(candidates.begin(), candidates.end(),
        [](const ModelCandidate& left, const ModelCandidate& right) {
            if (left.eligible != right.eligible) {
                return left.eligible > right.eligible;
            }
            if (left.score != right.score) {
                return left.score > right.score;
            }
            return left.model.id < right.model.id;
        });
    return candidates;
}

} // namespace jarvis::engineering
