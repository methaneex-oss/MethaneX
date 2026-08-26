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

    double strongest = 0.0;
    for (const auto& [_, belief] : beliefs_) strongest = std::max(strongest, belief.confidence);
    attention_state_ = attention_model_.score(event, novelty, strongest);
    threat_state_ = threat_model_.assess(event);
    state_.attention = attention_state_.salience;
    state_.threat = threat_state_.score;

    if (const auto it = event.data.find("health"); it != event.data.end()) {
        double health = 1.0;
        if (const auto p = std::get_if<double>(&it->second)) health = *p;
        else if (const auto p = std::get_if<std::int64_t>(&it->second)) health = static_cast<double>(*p);
        resilience_.observe(event.source, health);
    }

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
    evolution_.register_parameter(prediction.key, prediction.confidence);
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
    evolution_.observe_fitness(key, 1.0 - it->second.error);
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

Plan Brain::plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const {
    std::shared_lock lock(mutex_);
    return planner_.build(actions, horizon);
}

Reflection Brain::reflect() const {
    std::shared_lock lock(mutex_);
    std::vector<Belief> beliefs;
    beliefs.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) beliefs.push_back(belief);
    std::vector<Prediction> predictions;
    predictions.reserve(predictions_.size());
    for (const auto& [_, prediction] : predictions_) predictions.push_back(prediction);
    return reflection_model_.evaluate(beliefs, predictions);
}

AttentionSignal Brain::attention() const {
    std::shared_lock lock(mutex_);
    return attention_state_;
}

ThreatAssessment Brain::threat() const {
    std::shared_lock lock(mutex_);
    return threat_state_;
}

std::vector<RecoveryPlan> Brain::recovery_options() const {
    std::shared_lock lock(mutex_);
    return resilience_.required_recovery();
}

bool Brain::isolate(const std::string& component) {
    std::unique_lock lock(mutex_);
    return resilience_.isolate(component);
}

bool Brain::recover(const std::string& component, double restored_health) {
    std::unique_lock lock(mutex_);
    return resilience_.recover(component, restored_health);
}

std::vector<EvolutionProposal> Brain::evolution_options() const {
    std::shared_lock lock(mutex_);
    return evolution_.propose();
}

bool Brain::adopt_evolution(const EvolutionProposal& proposal) {
    std::unique_lock lock(mutex_);
    return evolution_.adopt(proposal);
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
