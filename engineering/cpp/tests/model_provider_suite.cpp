#include "jarvis/engineering/model_provider.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

namespace {

class FakeModel final : public EngineeringModelProvider {
public:
    ModelDescriptor descriptor() const override {
        return {"fake-model", "test", "coder-1", {"code-generation"}, 0.1, 0.9};
    }

    ModelResponse generate(const ModelRequest& request) override {
        return {ModelProviderStatus::succeeded, "test", "coder-1",
                "generated", {{ "src/example.cpp", "int answer() { return 42; }" }},
                {{"model.output", request.objective}}, {}};
    }
};

} // namespace

int main() {
    FakeModel model;
    assert(valid_model_descriptor(model.descriptor()));

    ModelRequest request{"implement feature", "existing architecture", {"source"}, 4096};
    assert(valid_model_request(request));

    const auto response = model.generate(request);
    assert(response.status == ModelProviderStatus::succeeded);
    assert(response.file_changes.size() == 1);
    assert(response.file_changes.front().path == "src/example.cpp");
    assert(response.provider == "test");

    assert(!valid_model_request(ModelRequest{"", "", {}, 4096}));
    assert(!valid_model_descriptor(ModelDescriptor{"", "test", "coder", {}, 0.0, 0.5}));
    return 0;
}
