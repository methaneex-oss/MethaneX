#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <mutex>
#include <utility>

namespace jarvis::core {

Observation Brain::observe(Event event) {
    std::unique_lock lock(mutex_);
    std::vector<Belief> before;
    before.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) before.push_back(belief);

    event.sequence = memory_.next_sequence();
    ++state_.events_seen;
    ++state_.cycle;

    const auto history = memory_.recent(1);
    const double novelty = compute_novelty(event, history);
    state_.novelty = novelty;

    memory_.append(event);
    for (const auto& [key, value] : event.data) {
        auto it = beliefs_.find(key);
        if (it == beliefs_.end()) {
            beliefs_.emplace(key, Belief{key, value, 0.7, 1, event.sequence});
        } else {
            const bool same = it->second.value == value;
            it->second.value = value;
            it->second.confidence = same
                ? std::min(0.999, it->second.confidence + (1.0 - it->second.confidence) * 0.12)
                : std::max(0.05, it->second.confidence * 0.82);
            ++it->second.observations;
            it->second.updated_sequence = event.sequence;
        }
        world_.observe(Fact{event.source, key, value, 0.7, 1});
    }

    std::vector<Belief> after;
    after.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) after.push_back(belief);
    causal_.observe_transition(before, after);
    return Observation{std::move(event), novelty};
}

std::vector<Belief> Brain::beliefs() const {
    std::shared_lock lock(mutex_);
    std::vector<Belief> result;
    result.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) result.push_back(belief);
    return result;
}

Prediction Brain::predict(std::string key, Scalar value, double confidence) {
    std::unique_lock lock(mutex_);
    Prediction prediction{std::move(key), std::move(value), std::clamp(confidence, 0.0, 1.0), state_.cycle, false, 0.0};
    predictions_[prediction.key] = prediction;
    return prediction;
}

bool Brain::resolve_prediction(const std::string& key, const Scalar& actual) {
    std::unique_lock lock(mutex_);
    const auto it = predictions_.find(key);
    if (it == predictions_.end() || it->second.resolved) return false;
    it->second.resolved = true;
    it->second.error = it->second.predicted == actual ? 0.0 : 1.0;

    if (const auto predicted = std::get_if<double>(&it->second.predicted);
        predicted != nullptr) {
        if (const auto observed = std::get_if<double>(&actual); observed != nullptr) {
            adaptation_.observe(key, *predicted, *observed);
        }
    }
    return it->second.error == 0.0;
}

const AdaptiveMetric* Brain::learning_metric(const std::string& key) const noexcept {
    std::shared_lock lock(mutex_);
    return adaptation_.metric(key);
}

double Brain::learning_confidence(const std::string& key) const noexcept {
    std::shared_lock lock(mutex_);
    return adaptation_.confidence(key);
}

std::vector<std::pair<std::string, Scalar>> Brain::simulate(const std::vector<Belief>& assumptions) const {
    std::shared_lock lock(mutex_);
    return causal_.predict(assumptions);
}

std::vector<Decision> Brain::choose(const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);
    double strongest = 0.0;
    for (const auto& [_, belief] : beliefs_) strongest = std::max(strongest, belief.confidence);
    return decision_.rank(actions, 1.0 - strongest);
}

BrainState Brain::state() const {
    std::shared_lock lock(mutex_);
    return state_;
}

double Brain::compute_novelty(const Event& event, const std::vector<Event>& history) {
    if (history.empty()) return 1.0;
    const auto& previous = history.back();
    std::size_t differences = event.data.size();
    for (const auto& [key, value] : event.data) {
        const auto it = previous.data.find(key);
        if (it != previous.data.end() && it->second == value) --differences;
    }
    const double denominator = std::max<std::size_t>(1, event.data.size());
    return std::clamp(static_cast<double>(differences) / denominator, 0.0, 1.0);
}

} // namespace jarvis::core
