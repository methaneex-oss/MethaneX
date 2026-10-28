#pragma once

#include "cognition.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <sstream>
#include <iomanip>
#include <limits>

namespace jarvis::core::detail {

// Version 2 is length-prefixed and type-tagged. Keys and string values may
// contain '=', ':', '|', or the version marker without changing boundaries.
inline std::string encode_causal_side(const std::string& key, const Scalar& value) {
    char tag = 'n';
    std::string payload;
    std::visit([&](const auto& item) {
        using T = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            tag = 'n';
        } else if constexpr (std::is_same_v<T, bool>) {
            tag = 'b';
            payload = item ? "1" : "0";
        } else if constexpr (std::is_same_v<T, std::string>) {
            tag = 's';
            payload = item;
        } else if constexpr (std::is_same_v<T, std::int64_t>) {
            tag = 'i';
            payload = std::to_string(item);
        } else if constexpr (std::is_same_v<T, double>) {
            tag = 'd';
            std::ostringstream out;
            out << std::setprecision(std::numeric_limits<double>::max_digits10) << item;
            payload = out.str();
        }
    }, value);

    return "@2|" + std::to_string(key.size()) + "|" + key + "|" + tag + "|" +
           std::to_string(payload.size()) + "|" + payload;
}

inline std::optional<std::pair<std::string, Scalar>>
decode_causal_side(const std::string& encoded) {
    if (encoded.rfind("@2|", 0) == 0) {
        std::size_t pos = 3;
        const auto read_size = [&](std::size_t& cursor, std::size_t& value) {
            const auto end = encoded.find('|', cursor);
            if (end == std::string::npos || end == cursor) return false;
            try {
                std::size_t used = 0;
                const auto parsed = std::stoull(encoded.substr(cursor, end - cursor), &used);
                if (used != end - cursor || parsed > encoded.size()) return false;
                value = static_cast<std::size_t>(parsed);
            } catch (...) {
                return false;
            }
            cursor = end + 1;
            return true;
        };

        std::size_t key_size = 0;
        if (!read_size(pos, key_size) || key_size > encoded.size() - pos)
            return std::nullopt;
        std::string key = encoded.substr(pos, key_size);
        pos += key_size;
        if (pos >= encoded.size() || encoded[pos++] != '|') return std::nullopt;
        if (pos + 1 >= encoded.size() || encoded[pos + 1] != '|')
            return std::nullopt;
        const char tag = encoded[pos];
        pos += 2;

        std::size_t payload_size = 0;
        if (!read_size(pos, payload_size) || payload_size != encoded.size() - pos)
            return std::nullopt;
        const std::string payload = encoded.substr(pos, payload_size);
        switch (tag) {
            case 'n':
                if (!payload.empty()) return std::nullopt;
                return std::make_pair(std::move(key), Scalar{std::monostate{}});
            case 'b':
                if (payload == "1") return std::make_pair(std::move(key), Scalar{true});
                if (payload == "0") return std::make_pair(std::move(key), Scalar{false});
                return std::nullopt;
            case 's':
                return std::make_pair(std::move(key), Scalar{payload});
            case 'i':
                try {
                    std::size_t used = 0;
                    const auto value = std::stoll(payload, &used);
                    if (used == payload.size())
                        return std::make_pair(std::move(key), Scalar{static_cast<std::int64_t>(value)});
                } catch (...) {}
                return std::nullopt;
            case 'd':
                try {
                    std::size_t used = 0;
                    const auto value = std::stod(payload, &used);
                    if (used == payload.size())
                        return std::make_pair(std::move(key), Scalar{value});
                } catch (...) {}
                return std::nullopt;
            default:
                return std::nullopt;
        }
    }

    // Backward compatibility for links persisted before the typed codec.
    const auto separator = encoded.find('=');
    if (separator == std::string::npos)
        return std::make_pair(encoded, Scalar{std::monostate{}});
    const std::string key = encoded.substr(0, separator);
    const std::string text = encoded.substr(separator + 1);
    if (text == "null") return std::make_pair(key, Scalar{std::monostate{}});
    if (text == "true") return std::make_pair(key, Scalar{true});
    if (text == "false") return std::make_pair(key, Scalar{false});
    try {
        std::size_t used = 0;
        const auto integer = std::stoll(text, &used);
        if (used == text.size())
            return std::make_pair(key, Scalar{static_cast<std::int64_t>(integer)});
    } catch (...) {}
    try {
        std::size_t used = 0;
        const auto number = std::stod(text, &used);
        if (used == text.size()) return std::make_pair(key, Scalar{number});
    } catch (...) {}
    return std::make_pair(key, Scalar{text});
}

} // namespace jarvis::core::detail
