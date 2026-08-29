#include "jarvis/core/reasoning.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <unordered_map>

namespace jarvis::core {
namespace {

bool same_value(const Scalar& a, const Scalar& b) noexcept { return a == b; }

struct ParsedLink {
    std::string key;
    Scalar value;
};

std::optional<ParsedLink> parse_link_side(const std::string& side) {
    const auto separator = side.find('=');
    if (separator == std::string::npos || separator == 0) return std::nullopt;
    const auto key = side.substr(0, separator);
    const auto encoded = side.substr(separator + 1);
    if (encoded == "null") return ParsedLink{key, std::monostate{}};
    if (encoded == "true") return ParsedLink{key, true};
    if (encoded == "false") return ParsedLink{key, false};
    try {
        std::size_t used = 0;
        const auto integer = std::stoll(encoded, &used);
        if (used == encoded.size()) return ParsedLink{key, static_cast<std::int64_t>(integer)};
    } catch (...) {}
    try {
        std::size_t used = 0;
        const auto number = std::stod(encoded, &used);
        if (used == encoded.size()) return ParsedLink{key, number};
    } catch (...) {}
    return ParsedLink{key, encoded};
}

} // namespace

bool ReasoningEngine::consistent(const std::vector<Belief>& beliefs) const noexcept {
    std::unordered_map<std::string, Scalar> values;
    for (const auto& belief : beliefs) {
        const auto it = values.find(belief.key);
        if (it == values.end()) values.emplace(belief.key, belief.value);
        else if (!same_value(it->second, belief.value)) return false;
    }
    return true;
}

std::vector<Belief> ReasoningEngine::infer(const std::vector<Belief>& premises,
                                           const std::vector<CausalLink>& causal_links,
                                           std::size_t max_steps) const {
    std::vector<Belief> result = premises;
    if (max_steps == 0) return result;

    std::unordered_map<std::string, Scalar> known;
    for (const auto& belief : premises) known[belief.key] = belief.value;

    for (std::size_t step = 0; step < max_steps; ++step) {
        bool changed = false;
        for (const auto& link : causal_links) {
            const auto cause = parse_link_side(link.cause);
            const auto effect = parse_link_side(link.effect);
            if (!cause || !effect || link.strength <= 0.0) continue;
            const auto known_cause = known.find(cause->key);
            if (known_cause == known.end() || !same_value(known_cause->second, cause->value)) continue;
            const auto known_effect = known.find(effect->key);
            if (known_effect != known.end()) {
                if (!same_value(known_effect->second, effect->value)) continue;
                continue;
            }
            known.emplace(effect->key, effect->value);
            result.push_back(Belief{effect->key, effect->value, std::clamp(link.strength, 0.0, 1.0), link.observations, 0});
            changed = true;
        }
        if (!changed) break;
    }
    return result;
}

ReasoningResult ReasoningEngine::solve(const ReasoningProblem& problem) const {
    ReasoningResult result{};
    if (problem.premises.empty()) {
        result.kind = ReasoningKind::consistency;
        result.valid = true;
        result.confidence = 0.0;
        result.explanation = "No premises were supplied.";
        return result;
    }

    if (!consistent(problem.premises)) {
        result.kind = ReasoningKind::contradiction;
        result.valid = false;
        result.confidence = 1.0;
        result.explanation = "Premises contain incompatible values for the same belief key.";
        return result;
    }

    const auto conclusions = infer(problem.premises, problem.causal_links, problem.max_steps);
    result.conclusions = conclusions;
    result.valid = true;
    result.kind = conclusions.size() > problem.premises.size()
        ? ReasoningKind::deduction : ReasoningKind::consistency;
    if (result.kind == ReasoningKind::deduction) {
        double confidence = 1.0;
        for (std::size_t i = problem.premises.size(); i < conclusions.size(); ++i)
            confidence = std::min(confidence, conclusions[i].confidence);
        result.confidence = std::clamp(confidence, 0.0, 1.0);
        result.explanation = "Conclusions were derived from supplied premises and observed causal links.";
    } else {
        result.confidence = 1.0;
        result.explanation = "Premises are internally consistent; no supported new conclusion was derivable.";
    }
    return result;
}

} // namespace jarvis::core
