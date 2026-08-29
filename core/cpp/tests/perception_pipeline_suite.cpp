#include "jarvis/core/perception_pipeline.hpp"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>

using namespace jarvis::core;

namespace {
class TestProvider final : public PerceptionProvider {
public:
    explicit TestProvider(double confidence) : confidence_(confidence) {}

    bool supports(const PerceptionInput& input) const noexcept override {
        return input.source == "test-provider";
    }

    PerceptualRepresentation perceive(const PerceptionInput& input,
                                      const PerceptionContext& context) const override {
        PerceptualRepresentation result;
        result.sequence = context.sequence;
        result.modality = Modality::text;
        SemanticNode node;
        node.id = "provider-node-" + std::to_string(static_cast<int>(confidence_ * 100));
        node.kind = RepresentationKind::concept_node;
        node.label = "provider-result";
        node.confidence = confidence_;
        node.evidence.push_back(EvidenceSpan{input.source, context.sequence, confidence_});
        result.nodes.push_back(std::move(node));
        result.confidence = confidence_;
        return result;
    }

private:
    double confidence_;
};

class ThrowingProvider final : public PerceptionProvider {
public:
    bool supports(const PerceptionInput&) const noexcept override { return true; }
    PerceptualRepresentation perceive(const PerceptionInput&, const PerceptionContext&) const override {
        throw std::runtime_error("provider failure");
    }
};
}

int main() {
    PerceptionPipeline pipeline;
    assert(pipeline.provider_count() == 0);
    pipeline.add_provider(nullptr);
    assert(pipeline.provider_count() == 0);
    pipeline.add_provider(std::make_shared<TestProvider>(0.9));
    pipeline.add_provider(std::make_shared<TestProvider>(0.6));
    assert(pipeline.provider_count() == 2);

    PerceptionInput provider_input{1, "test-provider", "message", {{"text", std::string("hello")}}};
    auto provider_result = pipeline.process(provider_input, PerceptionContext{42, "session", {}});
    assert(provider_result.sequence == 42);
    assert(provider_result.nodes.size() == 1);
    assert(provider_result.nodes.front().kind == RepresentationKind::concept_node);
    assert(provider_result.confidence == 0.9);
    assert(pipeline.validate(provider_result));

    PerceptionInput fallback_input{2, "voice", "message", {{"text", std::string("hello")}}};
    auto fallback_result = pipeline.process(fallback_input, PerceptionContext{43, "session", {}});
    assert(fallback_result.sequence == 43);
    assert(fallback_result.modality == Modality::speech);
    assert(!fallback_result.nodes.empty());
    assert(pipeline.validate(fallback_result));

    PerceptionPipeline failure_pipeline;
    failure_pipeline.add_provider(std::make_shared<ThrowingProvider>());
    auto recovered = failure_pipeline.process(provider_input, PerceptionContext{45, "session", {}});
    assert(recovered.sequence == 45);
    assert(!recovered.nodes.empty());
    assert(failure_pipeline.validate(recovered));

    PerceptionInput empty_input{3, "unknown-source", "unknown", {}};
    auto empty_result = pipeline.process(empty_input, PerceptionContext{44, "session", {}});
    assert(empty_result.nodes.empty());
    assert(empty_result.confidence == 0.0);
    assert(pipeline.validate(empty_result));

    return 0;
}
