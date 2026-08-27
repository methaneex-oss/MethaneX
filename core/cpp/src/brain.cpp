#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <chrono>
#include <mutex>
#include <utility>

namespace jarvis::core {
namespace {
std::uint64_t now_ns() noexcept {
    return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}
}

Brain::Brain() {
    const auto history = memory_.all();
    for (const auto& event : history) replay(event);
    state_.events_seen = static_cast<std::uint64_t>(history.size());
    if (!history.empty()) state_.cycle = history.back().sequence;
}

void Brain::replay(const Event& event) {
    state_.cycle = std::max(state_.cycle, event.sequence);
    if (event.kind == "prediction") {
        const auto key_it = event.data.find("key");
        const auto value_it = event.data.find("value");
        const auto confidence_it = event.data.find("confidence");
        if (key_it == event.data.end() || value_it == event.data.end()) return;
        const auto key = std::get_if<std::string>(&key_it->second);
        if (!key) return;
        double confidence = 0.0;
        if (confidence_it != event.data.end()) if (const auto p = std::get_if<double>(&confidence_it->second)) confidence = *p;
        predictions_[*key] = Prediction{*key, value_it->second, std::clamp(confidence, 0.0, 1.0), event.sequence, false, 0.0};
        return;
    }
    if (event.kind != "observation" && event.kind != "learning") return;
    for (const auto& [key, value] : event.data) {
        if (event.kind == "learning" && key == "reliability") continue;
        auto it = beliefs_.find(key);
        if (it == beliefs_.end()) beliefs_.emplace(key, Belief{key, value, event.kind == "learning" ? 0.5 : 0.7, 1, event.sequence});
        else {
            const bool same = it->second.value == value;
            it->second.value = value;
            it->second.confidence = same ? std::min(0.999, it->second.confidence + (1.0 - it->second.confidence) * 0.12) : std::max(0.05, it->second.confidence * 0.82);
            ++it->second.observations;
            it->second.updated_sequence = event.sequence;
        }
        world_.observe(Fact{event.source, key, value, 0.7, 1});
    }
}

Observation Brain::observe(Event event) {
    std::unique_lock lock(mutex_);
    event.timestamp_ns = event.timestamp_ns == 0 ? now_ns() : event.timestamp_ns;
    const auto previous = memory_.recent(1);
    const double novelty = compute_novelty(event, previous);
    std::vector<Belief> before; before.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) before.push_back(belief);
    event.sequence = memory_.append(event);
    ++state_.cycle;
    state_.novelty = novelty;
    replay(event);
    std::vector<Belief> after; after.reserve(beliefs_.size());
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
        resilience_.observe(event.source, std::clamp(health, 0.0, 1.0));
    }
    return Observation{std::move(event), novelty};
}

double Brain::learn(const Evidence& evidence) {
    std::unique_lock lock(mutex_);
    const double fused = knowledge_.assimilate(evidence);
    Event event{0, now_ns(), evidence.source, "learning", {{evidence.key, evidence.value}, {"reliability", fused}}};
    event.sequence = memory_.append(event);
    ++state_.events_seen;
    ++state_.cycle;
    replay(event);
    return fused;
}

std::vector<Belief> Brain::beliefs() const { std::shared_lock lock(mutex_); std::vector<Belief> result; result.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) result.push_back(belief); return result; }
Prediction Brain::predict(std::string key, Scalar value, double confidence) { std::unique_lock lock(mutex_); Prediction prediction{std::move(key), std::move(value), std::clamp(confidence, 0.0, 1.0), state_.cycle, false, 0.0}; evolution_.register_parameter(prediction.key, prediction.confidence); predictions_[prediction.key] = prediction; Event event{0, now_ns(), "brain", "prediction", {{"key", prediction.key}, {"value", prediction.predicted}, {"confidence", prediction.confidence}}}; memory_.append(std::move(event)); ++state_.events_seen; return prediction; }

bool Brain::resolve_prediction(const std::string& key, const Scalar& actual) { std::unique_lock lock(mutex_); const auto it = predictions_.find(key); if (it == predictions_.end() || it->second.resolved) return false; it->second.resolved = true; it->second.error = it->second.predicted == actual ? 0.0 : 1.0; if (const auto predicted = std::get_if<double>(&it->second.predicted)) if (const auto observed = std::get_if<double>(&actual)) adaptation_.observe(key, *predicted, *observed); evolution_.observe_fitness(key, 1.0 - it->second.error); return it->second.error == 0.0; }
const KnowledgeMetric* Brain::knowledge_source(const std::string& source) const noexcept { std::shared_lock lock(mutex_); return knowledge_.source_metric(source); }
const AdaptiveMetric* Brain::learning_metric(const std::string& key) const noexcept { std::shared_lock lock(mutex_); return adaptation_.metric(key); }
double Brain::learning_confidence(const std::string& key) const noexcept { std::shared_lock lock(mutex_); return adaptation_.confidence(key); }
std::vector<std::pair<std::string, Scalar>> Brain::simulate(const std::vector<Belief>& assumptions) const { std::shared_lock lock(mutex_); return causal_.predict(assumptions); }
std::vector<CausalLink> Brain::causal_links() const { std::shared_lock lock(mutex_); return causal_.links(); }
std::vector<Decision> Brain::choose(const std::vector<CandidateAction>& actions) const { std::shared_lock lock(mutex_); double strongest = 0.0; for (const auto& [_, belief] : beliefs_) strongest = std::max(strongest, belief.confidence); return decision_.rank(actions, 1.0 - strongest); }
Plan Brain::plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const { std::shared_lock lock(mutex_); return planner_.build(actions, horizon); }
Reflection Brain::reflect() const { std::shared_lock lock(mutex_); std::vector<Belief> bs; std::vector<Prediction> ps; for (const auto& [_, b] : beliefs_) bs.push_back(b); for (const auto& [_, p] : predictions_) ps.push_back(p); return reflection_model_.evaluate(bs, ps); }
AttentionSignal Brain::attention() const { std::shared_lock lock(mutex_); return attention_state_; }
ThreatAssessment Brain::threat() const { std::shared_lock lock(mutex_); return threat_state_; }
std::vector<RecoveryPlan> Brain::recovery_options() const { std::shared_lock lock(mutex_); return resilience_.required_recovery(); }
bool Brain::isolate(const std::string& component) { std::unique_lock lock(mutex_); return resilience_.isolate(component); }
bool Brain::recover(const std::string& component, double restored_health) { std::unique_lock lock(mutex_); return resilience_.recover(component, std::clamp(restored_health, 0.0, 1.0)); }
std::vector<EvolutionProposal> Brain::evolution_options() const { std::shared_lock lock(mutex_); return evolution_.propose(); }
bool Brain::adopt_evolution(const EvolutionProposal& proposal) { std::unique_lock lock(mutex_); return evolution_.adopt(proposal); }
void Brain::observe_capability(const std::string& name, double availability, double performance) { std::unique_lock lock(mutex_); self_model_.observe_capability(name, std::clamp(availability, 0.0, 1.0), std::clamp(performance, 0.0, 1.0)); }
bool Brain::isolate_capability(const std::string& name) { std::unique_lock lock(mutex_); return self_model_.isolate(name); }
bool Brain::restore_capability(const std::string& name, double availability, double performance) { std::unique_lock lock(mutex_); return self_model_.restore(name, std::clamp(availability, 0.0, 1.0), std::clamp(performance, 0.0, 1.0)); }
BrainSnapshot Brain::snapshot() const { std::shared_lock lock(mutex_); BrainSnapshot result; result.state = state_; for (const auto& [_, belief] : beliefs_) result.beliefs.push_back(belief); for (const auto& [_, prediction] : predictions_) result.predictions.push_back(prediction); result.causal_links = causal_.links(); return result; }
BrainState Brain::state() const { std::shared_lock lock(mutex_); return state_; }

double Brain::compute_novelty(const Event& event, const std::vector<Event>& history) { if (history.empty() || event.data.empty()) return history.empty() ? 1.0 : 0.0; const auto& previous = history.back(); std::size_t differences = event.data.size(); for (const auto& [key, value] : event.data) { const auto it = previous.data.find(key); if (it != previous.data.end() && it->second == value && differences > 0) --differences; } return std::clamp(static_cast<double>(differences) / static_cast<double>(event.data.size()), 0.0, 1.0); }

} // namespace jarvis::core
