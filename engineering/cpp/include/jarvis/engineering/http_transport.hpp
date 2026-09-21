#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace jarvis::engineering {

struct HttpRequest {
    std::string method;
    std::string url;
    std::vector<std::pair<std::string, std::string>> headers;
    std::string body;
};

struct HttpResponse {
    int status_code{0};
    std::string body;
    std::string error;
};

using HttpTransport = std::function<HttpResponse(const HttpRequest&)>;

} // namespace jarvis::engineering
