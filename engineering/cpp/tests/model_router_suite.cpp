#include "jarvis/engineering/model_router.hpp"

#include <cassert>

using namespace jarvis::engineering;

namespace {

class FakeProvider final : public EngineeringModelProvider {
public:
    FakeProvider(std::string id, double cost, double reliability, ModelProviderStatus status)
        : descriptor_{std::move(id), "test", "coder", {"source"}, cost, reliability},
          status_(status) {}

    ModelDescriptor descriptor() const override { return descriptor_; }

    ModelResponse generate(const ModelRequest&) override {
        ++calls;
        return {status_, descriptor_.provider, descriptor_.model, "output", {}, {}, {}};
    }

    int calls{0};

private:
    ModelDescriptor descriptor_;
    ModelProviderStatus status_;
};

} // namespace

int main() {
    FakeProvider exhausted("astra", 0.1, 0.95, ModelProviderStatus::unavailable);
    FakeProvider fallback("hugging-face", 0.5, 0.8, ModelProviderStatus::succeeded);

    EngineeringModelRouter router;
    assert(router.register_provider(exhausted));
    assert(router.register_provider(fallback));
    assert(!router.register_provider(fallback));

    const auto response = router.generate({"implement", "context", {"source"}, 4096});
    assert(response.status == ModelProviderStatus::succeeded);
    assert(exhausted.calls == 1);
    assert(fallback.calls == 1);

    assert(router.unregister_provider("astra"));
    assert(!router.unregister_provider("astra"));
    return 0;
}
