#include "jarvis/core/brain.hpp"

#include <cassert>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <system_error>

using namespace jarvis::core;

namespace {
double numeric_prediction(const Prediction& prediction) {
    if (const auto* value = std::get_if<double>(&prediction.predicted)) return *value;
    if (const auto* value = std::get_if<std::int64_t>(&prediction.predicted))
        return static_cast<double>(*value);
    assert(false && "expected numeric prediction");
    return 0.0;
}

void remove_journal(const std::filesystem::path& path) {
    std::error_code error;
    std::filesystem::remove(path, error);
    std::filesystem::remove(path.string() + ".meta", error);
}
}

int main() {
    const auto path = std::filesystem::temp_directory_path() /
                      "jarvis_prediction_developmental_validation.bin";
    remove_journal(path);

    double first_forecast_error = 0.0;
    double trained_forecast_error = 0.0;
    double forecast_before_regime_change = 0.0;
    double forecast_after_regime_change = 0.0;

    {
        Brain brain(path);

        // The environment has a stable but initially unknown offset:
        // the supplied prior is 20 while repeated observed values are 30.
        // Each subsequent forecast is generated only after the previous
        // outcome has been recorded, so the next forecast is a genuine
        // sequential holdout rather than a replay of its own target.
        for (int i = 0; i < 8; ++i) {
            const auto prediction = brain.predict("stable.sensor", Scalar{20.0}, 0.8);
            assert(prediction.created_sequence != 0);
            const double error = std::abs(30.0 - numeric_prediction(prediction));
            if (i == 0) first_forecast_error = error;
            assert(brain.resolve_prediction_feedback(
                       prediction.created_sequence, Scalar{30.0}) ==
                   PredictionFeedbackStatus::resolved_with_error);
        }

        const auto held_out = brain.predict("stable.sensor", Scalar{20.0}, 0.8);
        assert(held_out.created_sequence != 0);
        trained_forecast_error = std::abs(30.0 - numeric_prediction(held_out));
        assert(trained_forecast_error < first_forecast_error);
        assert(brain.resolve_prediction_feedback(
                   held_out.created_sequence, Scalar{30.0}) ==
               PredictionFeedbackStatus::resolved_with_error);

        const auto* learned = brain.learning_metric("stable.sensor");
        assert(learned != nullptr);
        assert(learned->observations == 9);
        assert(std::isfinite(learned->mean_error));
        assert(std::isfinite(learned->recent_error));
        assert(learned->mean_error < 1.0 / 3.0);

        // Negative control: merely generating predictions without observing
        // their consequences must not create an adaptation metric or change
        // the untouched key's forecast. This also checks that learning under
        // stable.sensor does not leak into an unrelated prediction key.
        for (int i = 0; i < 4; ++i) {
            const auto unobserved =
                brain.predict("unobserved.sensor", Scalar{20.0}, 0.8);
            assert(unobserved.created_sequence != 0);
            assert(std::abs(numeric_prediction(unobserved) - 20.0) < 1e-12);
            assert(brain.learning_metric("unobserved.sensor") == nullptr);
        }
        assert(brain.learning_metric("stable.sensor")->observations == 9);

        // Change the generating process. Repeated surprising outcomes should
        // move the estimate rather than permanently preserving the old regime.
        const auto before_shift = brain.predict("stable.sensor", Scalar{20.0}, 0.8);
        forecast_before_regime_change = numeric_prediction(before_shift);
        assert(brain.resolve_prediction_feedback(
                   before_shift.created_sequence, Scalar{45.0}) ==
               PredictionFeedbackStatus::resolved_with_error);
        for (int i = 0; i < 3; ++i) {
            const auto prediction = brain.predict("stable.sensor", Scalar{20.0}, 0.8);
            assert(prediction.created_sequence != 0);
            assert(brain.resolve_prediction_feedback(
                       prediction.created_sequence, Scalar{45.0}) ==
                   PredictionFeedbackStatus::resolved_with_error);
        }
        const auto after_shift = brain.predict("stable.sensor", Scalar{20.0}, 0.8);
        const double pre_final_feedback = numeric_prediction(after_shift);
        assert(std::abs(45.0 - pre_final_feedback) <
               std::abs(45.0 - forecast_before_regime_change));
        assert(brain.resolve_prediction_feedback(
                   after_shift.created_sequence, Scalar{45.0}) ==
               PredictionFeedbackStatus::resolved_with_error);
        // Compare restart against a forecast generated from the fully updated
        // metric, not the forecast that preceded the final update.
        const auto post_shift = brain.predict("stable.sensor", Scalar{20.0}, 0.8);
        forecast_after_regime_change = numeric_prediction(post_shift);
    }

    // Reconstruct a new Brain from the journal and require its next forecast
    // and adaptive statistics to match the live learner's persisted state.
    {
        Brain restored(path);
        const auto* metric = restored.learning_metric("stable.sensor");
        assert(metric != nullptr);
        assert(metric->observations == 14);
        const auto restored_forecast =
            restored.predict("stable.sensor", Scalar{20.0}, 0.8);
        assert(restored_forecast.created_sequence != 0);
        const double restored_value = numeric_prediction(restored_forecast);
        assert(std::isfinite(restored_value));
        assert(std::abs(restored_value - forecast_after_regime_change) < 1e-12);
        assert(std::abs(first_forecast_error - 10.0) < 1e-12);
        assert(trained_forecast_error < first_forecast_error);
        assert(forecast_after_regime_change > forecast_before_regime_change);

        // The negative control is durable too: an unobserved prediction key
        // must not acquire learned state merely because its events were stored.
        assert(restored.learning_metric("unobserved.sensor") == nullptr);
        const auto unobserved_after_restart =
            restored.predict("unobserved.sensor", Scalar{20.0}, 0.8);
        assert(unobserved_after_restart.created_sequence != 0);
        assert(std::abs(numeric_prediction(unobserved_after_restart) - 20.0) < 1e-12);
    }

    remove_journal(path);
    std::cout << "prediction_developmental_validation_suite: PASS\n";
    return 0;
}
