#pragma once

#include "cognition.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace jarvis::core {

struct Reflection {
    double coherence{1.0};
    double uncertainty{0.0};
    double prediction_accuracy{0.0};
    std::vector<std::string> observations;
};

class ReflectionModel {
public:
    Reflection evaluate(const std::vector<Belief>& beliefs,
                         const std::vector<Prediction>& predictions) const;
};

} // namespace jarvis::core
