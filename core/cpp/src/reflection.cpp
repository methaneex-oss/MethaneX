#include "jarvis/core/reflection.hpp"

#include <algorithm>

namespace jarvis::core {

Reflection ReflectionModel::evaluate(const std::vector<Belief>& beliefs,
                                     const std::vector<Prediction>& predictions) const {
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
    result.coherence = std::clamp((1.0 - result.uncertainty + result.prediction_accuracy) * 0.5, 0.0, 1.0);
    if (result.uncertainty > result.coherence) result.observations.emplace_back("uncertainty dominates current cognitive state");
    if (resolved > 0 && result.prediction_accuracy < 0.5) result.observations.emplace_back("prediction performance requires adaptation");
    return result;
}

} // namespace jarvis::core
