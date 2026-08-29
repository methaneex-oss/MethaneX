#include "jarvis/core/perception_pipeline.hpp"

#include <utility>

namespace jarvis::core {

void PerceptionPipeline::add_provider(std::shared_ptr<const PerceptionProvider> provider) {
    if (provider) providers_.push_back(std::move(provider));
}

PerceptualRepresentation PerceptionPipeline::process(
    const PerceptionInput& input, const PerceptionContext& context) const {
    for (const auto& provider : providers_) {
        if (!provider->supports(input)) continue;
        auto representation = provider->perceive(input, context);
        if (validate(representation)) return representation;
    }

    Event event{context.sequence, input.timestamp_ns, input.source, input.kind, input.payload};
    return representation_.normalize(event);
}

bool PerceptionPipeline::validate(const PerceptualRepresentation& representation) const noexcept {
    return representation_.validate(representation);
}

std::size_t PerceptionPipeline::provider_count() const noexcept {
    return providers_.size();
}

} // namespace jarvis::core
