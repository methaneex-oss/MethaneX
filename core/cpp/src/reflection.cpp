#include "jarvis/core/reflection.hpp"

#include <algorithm>
#include <cstddef>
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
        std::size_t disputed_count = 0;
        for (const auto& belief : beliefs) {
            confidence += std::clamp(
                std::isfinite(belief.confidence) ? belief.confidence : 0.0,
                0.0, 1.0);
            if (belief.disputed) ++disputed_count;
        }
        confidence /= static_cast<double>(beliefs.size());
        // A disputed belief can retain high confidence in its latest value,
        // but that confidence must not hide unresolved counter-evidence from
        // reflection. Keep confidence and contradiction as separate signals.
        const double contradiction_pressure =
            static_cast<double>(disputed_count) / static_cast<double>(beliefs.size());
        result.uncertainty = std::max(1.0 - confidence, contradiction_pressure);
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

    // Coherence is evidence-weighted, not a default claim of competence.
    // A newborn or newly restarted brain may have no resolved predictions or
    // calibrated appraisals yet; treating those missing measurements as perfect
    // would inflate confidence, while treating them as failed measurements
    // would unfairly penalize learning that has not happened. Average only
    // dimensions for which experience exists.
    double coherence_sum = 0.0;
    std::size_t coherence_evidence = 0;
    if (!beliefs.empty()) {
        coherence_sum += 1.0 - result.uncertainty;
        ++coherence_evidence;
    }
    if (resolved > 0) {
        coherence_sum += result.prediction_accuracy;
        ++coherence_evidence;
    }
    if (result.affective_observations > 0) {
        coherence_sum += 1.0 - result.affective_calibration_error;
        ++coherence_evidence;
    }
    result.coherence = coherence_evidence == 0
        ? 0.0
        : std::clamp(coherence_sum / static_cast<double>(coherence_evidence),
                     0.0, 1.0);
    if (coherence_evidence == 0)
        result.observations.emplace_back("insufficient experience to assess cognitive coherence");

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
