#include "jarvis/core/reflection.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

Reflection ReflectionModel::evaluate(const std::vector<Belief>& beliefs,
                                     const std::vector<Prediction>& predictions,
                                     double affective_calibration_error,
                                     double affective_learning_pressure,
                                     std::uint64_t affective_observations) const {
    Reflection result{};
    if (!beliefs.empty()) {
        double confidence = 0.0;
        for (const auto& belief : beliefs) confidence += belief.confidence;
        confidence /= static_cast<double>(beliefs.size());
        result.uncertainty = 1.0 - confidence;
    }

    std::size_t resolved = 0;
    double accuracy = 0.0;
    for (const auto& prediction : predictions) {
        if (!prediction.resolved) continue;
        ++resolved;
        accuracy += 1.0 - std::clamp(prediction.error, 0.0, 1.0);
    }
    result.prediction_accuracy = resolved == 0 ? 0.0 : accuracy / static_cast<double>(resolved);

    result.affective_calibration_error = std::clamp(
        std::isfinite(affective_calibration_error) ? affective_calibration_error : 0.0,
        0.0, 1.0);
    result.affective_learning_pressure = std::clamp(
        std::isfinite(affective_learning_pressure) ? affective_learning_pressure : 1.0,
        0.5, 1.5);
    result.affective_observations = affective_observations;

    // Reflection treats appraisal calibration as another source of uncertainty.
    // It does not prescribe a response. A poorly calibrated appraisal model
    // simply lowers the current coherence estimate and records an observation
    // that higher-level cognition can use when allocating further processing.
    const double affective_reliability = 1.0 - result.affective_calibration_error;
    result.coherence = std::clamp(
        (1.0 - result.uncertainty + result.prediction_accuracy + affective_reliability) / 3.0,
        0.0, 1.0);

    if (result.uncertainty > result.coherence)
        result.observations.emplace_back("uncertainty dominates current cognitive state");
    if (resolved > 0 && result.prediction_accuracy < 0.5)
        result.observations.emplace_back("prediction performance requires adaptation");
    if (result.affective_observations > 0 && result.affective_calibration_error > 0.5)
        result.observations.emplace_back("affective appraisal calibration is currently unreliable");
    if (result.affective_observations > 0 && result.affective_learning_pressure > 1.0)
        result.observations.emplace_back("affective appraisal is adapting under elevated calibration error");
    return result;
}

} // namespace jarvis::core
