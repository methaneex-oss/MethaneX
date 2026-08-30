#include "jarvis/core/reasoning.hpp"

#include <cassert>
#include <cstdint>
#include <vector>

using namespace jarvis::core;

int main() {
    ReasoningEngine engine;
    const Belief enabled{"system.enabled", true, 0.95, 3, 1};
    const Belief ready{"system.ready", true, 0.9, 2, 2};
    const Belief safe{"system.safe", true, 0.8, 1, 3};

    assert(engine.consistent({enabled, ready, safe}));
    assert(!engine.consistent({enabled, Belief{"system.enabled", false, 0.9, 1, 4}}));

    const std::vector<CausalLink> links{
        {"system.enabled=true", "system.ready=true", 0.9, 8},
        {"system.ready=true", "system.safe=true", 0.8, 5}
    };

    const auto inferred = engine.infer({enabled}, links, 8);
    assert(inferred.size() == 3);
    assert(inferred[1].key == "system.ready");
    assert(inferred[2].key == "system.safe");
    assert(inferred[1].confidence == 0.9);
    assert(inferred[2].confidence == 0.8);

    const auto solved = engine.solve(ReasoningProblem{{enabled}, links, 8});
    assert(solved.valid);
    assert(solved.kind == ReasoningKind::deduction);
    assert(solved.confidence == 0.8);
    assert(solved.conclusions.size() == 3);

    const auto contradiction = engine.solve(ReasoningProblem{
        {enabled, Belief{"system.enabled", false, 0.7, 1, 4}}, {}, 8});
    assert(!contradiction.valid);
    assert(contradiction.kind == ReasoningKind::contradiction);
    assert(contradiction.confidence == 1.0);

    const auto stable = engine.solve(ReasoningProblem{{ready}, {}, 8});
    assert(stable.valid);
    assert(stable.kind == ReasoningKind::consistency);
    assert(stable.conclusions.size() == 1);

    // max_steps bounds inference depth: the first causal edge is allowed,
    // but the second edge requires another step.
    const auto bounded = engine.infer({enabled}, links, 1);
    assert(bounded.size() == 2);
    assert(bounded[1].key == "system.ready");

    return 0;
}
