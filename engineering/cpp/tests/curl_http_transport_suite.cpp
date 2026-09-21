#include "jarvis/engineering/curl_http_transport.hpp"

#include <cassert>

using namespace jarvis::engineering;

int main() {
    CurlHttpTransport transport(CurlTransportConfig{1, 1024});
    const auto invalid = transport(HttpRequest{"GET", "", {}, {}});
    assert(invalid.status_code == 0);
    assert(!invalid.error.empty());
    return 0;
}
