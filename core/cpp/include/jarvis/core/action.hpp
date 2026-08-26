#pragma once

#include "event.hpp"

#include <string>
#include <vector>

namespace jarvis::core {

struct CandidateAction {
    std::string name;
    Attributes arguments;
    double utility{0.0};
    double expected_value{0.0};
    double risk{0.0};
    double reversibility{1.0};
    std::vector<std::string> evidence;
};

struct Decision {
    CandidateAction action;
    double score{0.0};
    std::vector<std::string> rationale;
};

} // namespace jarvis::core
