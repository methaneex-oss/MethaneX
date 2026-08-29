#pragma once

#include "causal_model.hpp"
#include "cognition.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

enum class ReasoningKind : std::uint8_t { deduction, prediction, contradiction, consistency };

struct ReasoningResult {
    ReasoningKind kind{ReasoningKind::consistency};
    bool valid{false};
    double confidence{0.0};
    std::string explanation;
    std::vector<Belief> conclusions;
};

struct ReasoningProblem {
    std::vector<Belief> premises;
    std::vector<CausalLink> causal_links;
    std::size_t max_steps{8};
};

class ReasoningEngine {
public:
    ReasoningResult solve(const ReasoningProblem& problem) const;
    std::vector<Belief> infer(const std::vector<Belief>& premises,
                              const std::vector<CausalLink>& causal_links,
                              std::size_t max_steps) const;
    bool consistent(const std::vector<Belief>& beliefs) const noexcept;
};

} // namespace jarvis::core
