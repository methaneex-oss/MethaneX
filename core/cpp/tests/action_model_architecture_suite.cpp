#include "jarvis/core/action_model.hpp"

#include <cassert>
#include <cmath>
#include <vector>

using namespace jarvis::core;

int main() {
    ActionModel model;
    const std::vector<Decision> decisions{
        {{"safe", 0.9, 0.8, 0.1, 1.0}, 2.0},
        {{"risky", 0.9, 0.8, 0.9, 0.2}, 2.0},
        {{"negative", -0.1, 0.0, 0.1, 1.0}, -0.1}
    };

    const auto assessments = model.assess(decisions, ActionConstraints{0.5, false});
    assert(assessments.size() == 3);
    assert(assessments[0].disposition == ActionDisposition::execute);
    assert(assessments[0].permitted);
    assert(assessments[1].disposition == ActionDisposition::reject);
    assert(!assessments[1].permitted);
    assert(assessments[2].disposition == ActionDisposition::recommend);
    assert(!assessments[2].permitted);

    const auto reversible = model.assess({decisions.front()}, ActionConstraints{1.0, true});
    assert(reversible.front().disposition == ActionDisposition::execute);

    const auto non_reversible = model.assess({decisions[1]}, ActionConstraints{1.0, true});
    assert(non_reversible.front().disposition == ActionDisposition::clarify);

    const auto bounded = model.assess({{{"invalid", 0.0, 0.0, NAN, 1.0}, 0.0}},
                                      ActionConstraints{NAN, false});
    assert(bounded.size() == 1);
    assert(std::isfinite(bounded.front().confidence));

    return 0;
}
