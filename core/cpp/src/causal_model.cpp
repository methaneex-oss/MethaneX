#include "jarvis/core/causal_model.hpp"

#include <algorithm>
#include <cmath>
#include <string>
#include <type_traits>
#include <unordered_map>

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

std::pair<std::string, Scalar> decode_effect(const std::string& encoded) {
    const auto separator = encoded.find('=');
    if (separator == std::string::npos) return {encoded, std::monostate{}};
    return {encoded.substr(0, separator), decode(encoded.substr(separator + 1))};
}

}

void CausalModel::observe_transition(const std::vector<Belief>& before,
                                     const std::vector<Belief>& after) {
    for (const auto& current : after) {
        const auto prior = std::find_if(before.begin(), before.end(), [&](const Belief& belief) {
            return belief.key == current.key;
        });
        if (prior == before.end() || prior->value == current.value) continue;

        for (const auto& effect : after) {
            if (effect.key == current.key) continue;
            const auto cause = encode(current.key, current.value);
            const auto consequence = encode(effect.key, effect.value);
            auto it = std::find_if(links_.begin(), links_.end(), [&](const CausalLink& link) {
                return link.cause == cause && link.effect == consequence;
            });
            if (it == links_.end()) {
                links_.push_back(CausalLink{cause, consequence, 0.55, 1});
            } else {
                it->strength = std::clamp(it->strength + (1.0 - it->strength) * 0.08, 0.0, 1.0);
                ++it->observations;
            }
        }
    }
}

std::vector<CausalLink> CausalModel::links() const {
    return links_;
}

SimulationResult CausalModel::simulate(const std::vector<Belief>& assumptions,
                                       std::size_t horizon) const {
    SimulationResult result;
    result.depth = std::min<std::size_t>(std::max<std::size_t>(horizon, 1), 8);
    if (assumptions.empty()) return result;

    std::vector<std::string> frontier;
    frontier.reserve(assumptions.size());
    for (const auto& assumption : assumptions) frontier.push_back(encode(assumption.key, assumption.value));

    std::unordered_map<std::string, CausalPrediction> predicted;
    for (std::size_t depth = 1; depth <= result.depth && !frontier.empty(); ++depth) {
        std::vector<std::string> next;
        for (const auto& cause : frontier) {
            for (const auto& link : links_) {
                if (link.cause != cause || link.strength < 0.5) continue;
                const auto [key, value] = decode_effect(link.effect);
                const double confidence = std::clamp(link.strength * std::pow(0.92, static_cast<double>(depth - 1)), 0.0, 1.0);
                auto it = predicted.find(key);
                if (it == predicted.end() || confidence > it->second.confidence) {
                    predicted[key] = CausalPrediction{key, value, confidence, depth};
                    next.push_back(link.effect);
                }
            }
        }
        frontier = std::move(next);
    }

    result.predictions.reserve(predicted.size());
    double total_confidence = 0.0;
    for (const auto& [_, prediction] : predicted) {
        total_confidence += prediction.confidence;
        result.predictions.push_back(prediction);
    }
    std::sort(result.predictions.begin(), result.predictions.end(), [](const CausalPrediction& lhs, const CausalPrediction& rhs) {
        if (lhs.confidence != rhs.confidence) return lhs.confidence > rhs.confidence;
        if (lhs.depth != rhs.depth) return lhs.depth < rhs.depth;
        return lhs.key < rhs.key;
    });
    result.confidence = result.predictions.empty() ? 0.0 : total_confidence / static_cast<double>(result.predictions.size());
    return result;
}

std::vector<std::pair<std::string, Scalar>> CausalModel::predict(const std::vector<Belief>& assumptions) const {
    const auto simulation = simulate(assumptions, 1);
    std::vector<std::pair<std::string, Scalar>> result;
    result.reserve(simulation.predictions.size());
    for (const auto& prediction : simulation.predictions) result.emplace_back(prediction.key, prediction.value);
    return result;
}

} // namespace jarvis::core
