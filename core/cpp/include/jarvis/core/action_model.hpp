#pragma once

#include "cognition.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

enum class ActionDisposition : std::uint8_t { execute, recommend, clarify, reject };

struct ActionConstraints {
    double maximum_risk{1.0};
    bool require_reversible{false};
};

struct ActionAssessment {
    CandidateAction action;
    ActionDisposition disposition{ActionDisposition::recommend};
    bool permitted{false};
    double confidence{0.0};
    std::string reason;
    // Context used by the decision that produced this assessment. Carry it
    // into outcome learning so consequences train the same representation.
    std::string developmental_context;
};

class ActionModel {
public:
    std::vector<ActionAssessment> assess(const std::vector<Decision>& decisions,
                                         ActionConstraints constraints = {}) const;
};

} // namespace jarvis::core
