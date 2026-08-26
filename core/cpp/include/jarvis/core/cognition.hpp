#pragma once

#include "event.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace jarvis::core {

struct Belief {
    std::string key;
    Scalar value;
    double confidence{0.5};
    std::uint64_t observations{0};
    std::uint64_t updated_sequence{0};
};

struct Prediction {
    std::string key;
    Scalar predicted;
    double confidence{0.0};
    std::uint64_t created_sequence{0};
    bool resolved{false};
    double error{0.0};
};

struct CausalLink {
    std::string cause;
    std::string effect;
    double strength{0.5};
    std::uint64_t observations{0};
};

struct CandidateAction {
    std::string name;
    double utility{0.0};
    double expected_value{0.0};
    double risk{0.0};
    double reversibility{1.0};
};

struct Decision {
    CandidateAction action;
    double score{0.0};
};

} // namespace jarvis::core
