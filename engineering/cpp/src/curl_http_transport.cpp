#include "jarvis/engineering/curl_http_transport.hpp"

#include <curl/curl.h>

#include <limits>
#include <string>

namespace jarvis::engineering {

namespace {

struct ResponseBuffer {
    std::string body;
    std::size_t maximum_bytes{0};
    bool exceeded{false};
};

size_t write_body(char* data, size_t size, size_t count, void* userdata) {
    auto& buffer = *static_cast<ResponseBuffer*>(userdata);
    if (size != 0 && count > std::numeric_limits<std::size_t>::max() / size) {
        buffer.exceeded = true;
        return 0;
    }
    const std::size_t bytes = size * count;
    if (bytes > buffer.maximum_bytes - std::min(buffer.body.size(), buffer.maximum_bytes)) {
        buffer.exceeded = true;
        return 0;
    }
    buffer.body.append(data, bytes);
    return bytes;
}

} // namespace

CurlHttpTransport::CurlHttpTransport(CurlTransportConfig config) noexcept
    : config_(config) {}

HttpResponse CurlHttpTransport::operator()(const HttpRequest& request) const {
    if (request.method != "POST" || request.url.empty() ||
        config_.timeout_ms <= 0 || config_.maximum_response_bytes == 0) {
        return {0, {}, "invalid HTTP request or transport configuration"};
    }

    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        return {0, {}, "curl initialization failed"};
    }

    struct Cleanup {
        CURL* handle;
        ~Cleanup() { curl_easy_cleanup(handle); }
    } cleanup{curl};

    struct curl_slist* headers = nullptr;
    for (const auto& [name, value] : request.headers) {
        headers = curl_slist_append(headers, (name + ": " + value).c_str());
    }
    struct HeaderCleanup {
        curl_slist* headers;
        ~HeaderCleanup() { curl_slist_free_all(headers); }
    } header_cleanup{headers};

    ResponseBuffer buffer{{}, config_.maximum_response_bytes, false};
    curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE,
                     static_cast<curl_off_t>(request.body.size()));
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, config_.timeout_ms);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_body);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    const CURLcode result = curl_easy_perform(curl);
    if (buffer.exceeded) {
        return {0, {}, "HTTP response size limit exceeded"};
    }
    if (result != CURLE_OK) {
        return {0, std::move(buffer.body), curl_easy_strerror(result)};
    }

    long status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
    return {static_cast<int>(status), std::move(buffer.body), {}};
}

} // namespace jarvis::engineering
