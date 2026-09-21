#include "jarvis/engineering/huggingface_provider.hpp"

#include <cassert>
#include <string>

using namespace jarvis::engineering;

int main() {
    HttpRequest captured;
    HuggingFaceModelProvider provider(
        HuggingFaceModelConfig{"openai/gpt-oss-120b:fastest", "secret", "https://router.huggingface.co/v1/chat/completions", 0.1, 0.9},
        [&](const HttpRequest& request) {
            captured = request;
            return HttpResponse{200,
                R"({"choices":[{"message":{"role":"assistant","content":"implemented"}}]})", {}};
        });

    const ModelRequest request{"build feature", "prior evidence", {"source"}, 100};
    const auto result = provider.generate(request);

    assert(result.status == ModelProviderStatus::succeeded);
    assert(result.output == "implemented");
    assert(captured.method == "POST");
    assert(captured.url == "https://router.huggingface.co/v1/chat/completions");
    assert(captured.headers.size() == 2);
    assert(captured.headers[0].first == "Authorization");
    assert(captured.headers[0].second == "Bearer secret");
    assert(captured.body.find(""model":"openai/gpt-oss-120b:fastest"") != std::string::npos);
    assert(captured.body.find("prior evidence") != std::string::npos);

    const auto denied = HuggingFaceModelProvider(
        HuggingFaceModelConfig{"model", "", "https://router.huggingface.co/v1/chat/completions", 0.0, 0.0},
        [](const HttpRequest&) { return HttpResponse{200, "{}", {}}; }).generate(request);
    assert(denied.status == ModelProviderStatus::rejected);

    return 0;
}
