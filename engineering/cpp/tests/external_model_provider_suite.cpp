#include "jarvis/engineering/external_model_provider.hpp"

#include <cassert>

using namespace jarvis::engineering;

namespace {

class FakeTransport final : public EngineeringModelTransport {
public:
    ModelResponse request(const ModelDescriptor& descriptor, const ModelRequest& request) override {
        ++calls;
        assert(descriptor.id == "hf-coder");
        assert(request.objective == "build feature");
        return {ModelProviderStatus::succeeded, {}, {}, "generated", {},
                {{"transport", "completed"}}, {}};
    }

    int calls{0};
};

} // namespace

int main() {
    FakeTransport transport;
    ExternalEngineeringModelProvider provider(
        {"hf-coder", "huggingface", "coder-model", {"code-generation"}, 0.2, 0.9},
        transport);

    const ModelRequest request{"build feature", "shared workspace evidence", {"source"}, 4096};
    const auto response = provider.generate(request);

    assert(response.status == ModelProviderStatus::succeeded);
    assert(response.provider == "huggingface");
    assert(response.model == "coder-model");
    assert(transport.calls == 1);
    return 0;
}
