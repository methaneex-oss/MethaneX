#pragma once

#include "cognition.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct Reflection {
    double coherence{1.0};
    double uncertainty{0.0};
    double prediction_accuracy{0.0};
    // These are metacognitive measurements of appraisal reliability, not
    // semantic emotions. They let reflection distinguish "my world model is
    // uncertain" from "my appraisal model is poorly calibrated".
    double affective_calibration_error{0.0};
    double affective_learning_pressure{1.0};
    std::uint64_t affective_observations{0};
    std::vector<std::string> observations;
};

class ReflectionModel {
public:
    Reflection evaluate(const std::vector<Belief>& beliefs,
                         const std::vector<Prediction>& predictions,
                         double affective_calibration_error = 0.0,
                         double affective_learning_pressure = 1.0,
                         std::uint64_t affective_observations = 0) const;
};

} // namespace jarvis::core
