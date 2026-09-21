#pragma once

#include "huggingface_provider.hpp"

#include <cstddef>

namespace jarvis::engineering {

struct CurlTransportConfig {
    long timeout_ms{30000};
    std::size_t maximum_response_bytes{4 * 1024 * 1024};
};

class CurlHttpTransport final {
public:
    explicit CurlHttpTransport(CurlTransportConfig config = {}) noexcept;
    HttpResponse operator()(const HttpRequest& request) const;

private:
    CurlTransportConfig config_;
};

} // namespace jarvis::engineering
