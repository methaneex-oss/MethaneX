#include "jarvis/core/perception_pipeline.hpp"

#include <exception>
#include <utility>

namespace jarvis::core {

void PerceptionPipeline::add_provider(std::shared_ptr<const PerceptionProvider> provider) {
    if (provider) providers_.push_back(std::move(provider));
}

PerceptualRepresentation PerceptionPipeline::process(
    const PerceptionInput& input, const PerceptionContext& context) const {
    PerceptualRepresentation best;
    bool found = false;

    // Providers are capabilities, not hardcoded cognition. Each capable provider
    // gets an opportunity to produce a representation; the strongest valid result
    // is selected. A failing provider is isolated from the remaining pipeline.
    for (const auto& provider : providers_) {
        if (!provider) continue;
        bool supported = false;
        try {
            supported = provider->supports(input);
        } catch (const std::exception&) {
            continue;
        } catch (...) {
            continue;
        }
        if (!supported) continue;

        try {
            auto candidate = provider->perceive(input, context);
            if (!validate(candidate)) continue;
            if (!found || candidate.confidence > best.confidence) {
                best = std::move(candidate);
                found = true;
            }
        } catch (const std::exception&) {
            continue;
        } catch (...) {
            continue;
        }
    }

    if (found) return best;

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
