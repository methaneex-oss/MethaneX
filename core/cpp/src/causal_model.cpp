#include "jarvis/core/causal_model.hpp"

#include <algorithm>
#include <string>
#include <type_traits>

namespace jarvis::core {
namespace {

std::string encode(const std::string& key, const Scalar& value) {
    return key + "=" + std::visit([](const auto& item) -> std::string {
        using T = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<T, std::monostate>) return "null";
        else if constexpr (std::is_same_v<T, bool>) return item ? "true" : "false";
        else if constexpr (std::is_same_v<T, std::string>) return item;
        else return std::to_string(item);
    }, value);
}

Scalar decode(const std::string& text) {
    if (text == "null") return std::monostate{};
    if (text == "true") return true;
    if (text == "false") return false;
    try {
        std::size_t consumed = 0;
        const auto integer = std::stoll(text, &consumed);
        if (consumed == text.size()) return static_cast<std::int64_t>(integer);
    } catch (...) {}
    try {
        std::size_t consumed = 0;
        const auto number = std::stod(text, &consumed);
        if (consumed == text.size()) return number;
    } catch (...) {}
    return text;
}

}

void CausalModel::observe_transition(const std::vector<Belief>& before, const std::vector<Belief>& after) {
    for (const auto& current : after) {
        const auto prior = std::find_if(before.begin(), before.end(), [&](const Belief& belief) { return belief.key == current.key; });
        if (prior == before.end() || prior->value == current.value) continue;
        for (const auto& effect : after) {
            if (effect.key == current.key) continue;
            const auto id = encode(current.key, current.value) + "->" + encode(effect.key, effect.value);
            auto& link = links_[id];
            if (link.observations == 0) {
                link.cause = encode(current.key, current.value);
                link.effect = encode(effect.key, effect.value);
                link.strength = 0.55;
            } else {
                link.strength += (1.0 - link.strength) * 0.08;
            }
            ++link.observations;
        }
    }
}

std::vector<CausalLink> CausalModel::links() const {
    std::vector<CausalLink> result;
    result.reserve(links_.size());
    for (const auto& [_, link] : links_) result.push_back(link);
    return result;
}

std::vector<std::pair<std::string, Scalar>> CausalModel::predict(const std::vector<Belief>& assumptions) const {
    std::vector<std::pair<std::string, Scalar>> result;
    for (const auto& assumption : assumptions) {
        const auto prefix = encode(assumption.key, assumption.value) + "->";
        for (const auto& [_, link] : links_) {
            if (link.cause.rfind(prefix, 0) == 0 && link.strength >= 0.5) {
                const auto separator = link.effect.find('=');
                if (separator != std::string::npos) result.emplace_back(link.effect.substr(0, separator), decode(link.effect.substr(separator + 1)));
            }
        }
    }
    return result;
}

} // namespace jarvis::core
