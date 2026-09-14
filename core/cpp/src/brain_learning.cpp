#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <mutex>

namespace jarvis::core {
namespace {
std::uint64_t learning_now_ns() noexcept {
    return static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
}

const double* numeric_value(const Scalar& value) noexcept {
    return std::get_if<double>(&value);
}
}

LearningCycle Brain::learn_from_prediction(const std::string& key,
                                           const Scalar& actual,
                                           double fitness) {
    std::unique_lock lock(mutex_);
    LearningCycle cycle{};
    if (key.empty() || !std::isfinite(fitness)) return cycle;

    const auto prediction_it = predictions_.find(key);
    if (prediction_it == predictions_.end() || prediction_it->second.resolved) return cycle;
    const auto predicted = numeric_value(prediction_it->second.predicted);
    const auto observed = numeric_value(actual);
    if (predicted == nullptr || observed == nullptr || !std::isfinite(*predicted) ||
        !std::isfinite(*observed)) return cycle;

    const double error = prediction_it->second.predicted == actual ? 0.0 : 1.0;
    Event outcome{0, learning_now_ns(), "brain", "prediction_outcome",
                  {{"key", key}, {"actual", actual}, {"error", error}}};
    outcome.sequence = memory_.append(outcome);
    if (outcome.sequence == 0) return cycle;

    prediction_it->second.resolved = true;
    prediction_it->second.error = error;
    ++state_.events_seen;
    state_.cycle = outcome.sequence;
    sync_self_state();

    const double bounded_fitness = std::clamp(fitness, -1.0, 1.0);
    Event fitness_event{0, learning_now_ns(), "learning_loop", "evolution_fitness",
                        {{"key", key}, {"fitness", bounded_fitness}}};
    fitness_event.sequence = memory_.append(fitness_event);
    if (fitness_event.sequence == 0) return cycle;
    ++state_.events_seen;
    state_.cycle = fitness_event.sequence;

    cycle = learning_loop_.process(
        LearningFeedback{key, std::clamp(*predicted, 0.0, 1.0),
                          std::clamp(*observed, 0.0, 1.0), bounded_fitness},
        adaptation_, evolution_);

    for (const auto& proposal : cycle.proposals) {
        if (proposal.key != key || proposal.current == proposal.proposed) continue;
        if (const auto* parameter = evolution_.parameter(key);
            parameter != nullptr && parameter->value == proposal.proposed) {
            Event adoption{0, learning_now_ns(), "learning_loop", "evolution_adopt",
                            {{"key", key},
                             {"current", proposal.current},
                             {"proposed", proposal.proposed},
                             {"expected_gain", proposal.expected_gain},
                             {"confidence", proposal.confidence}}};
            adoption.sequence = memory_.append(adoption);
            if (adoption.sequence != 0) {
                ++state_.events_seen;
                state_.cycle = adoption.sequence;
            }
            break;
        }
    }
    sync_self_state();
    return cycle;
}

} // namespace jarvis::core
