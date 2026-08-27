// Cognitive core: state, continuity, learning, evolution and recovery are replayable.
#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <chrono>
#include <mutex>
#include <utility>

namespace jarvis::core {
namespace {
std::uint64_t now_ns() noexcept { return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()); }
const std::string* string_value(const Attributes& data, const std::string& key) { const auto it = data.find(key); return it == data.end() ? nullptr : std::get_if<std::string>(&it->second); }
double double_value(const Attributes& data, const std::string& key, double fallback = 0.0) { const auto it = data.find(key); if (it == data.end()) return fallback; if (const auto p = std::get_if<double>(&it->second)) return *p; if (const auto p = std::get_if<std::int64_t>(&it->second)) return static_cast<double>(*p); return fallback; }
}

Brain::Brain(std::filesystem::path journal_path) : memory_(256, std::move(journal_path)) { const auto history = memory_.all(); for (const auto& event : history) replay(event); state_.events_seen = static_cast<std::uint64_t>(history.size()); if (!history.empty()) state_.cycle = history.back().sequence; }

void Brain::replay(const Event& event) {
    state_.cycle = std::max(state_.cycle, event.sequence);
    if (event.kind == "prediction") { const auto* key = string_value(event.data, "key"); const auto value_it = event.data.find("value"); if (key == nullptr || value_it == event.data.end()) return; predictions_[*key] = Prediction{*key, value_it->second, std::clamp(double_value(event.data, "confidence"), 0.0, 1.0), event.sequence, false, 0.0}; return; }
    if (event.kind == "prediction_outcome") { const auto* key = string_value(event.data, "key"); if (key == nullptr) return; const auto it = predictions_.find(*key); if (it == predictions_.end()) return; it->second.resolved = true; it->second.error = std::clamp(double_value(event.data, "error", 1.0), 0.0, 1.0); const auto actual_it = event.data.find("actual"); if (actual_it != event.data.end()) if (const auto predicted = std::get_if<double>(&it->second.predicted)) if (const auto actual = std::get_if<double>(&actual_it->second)) adaptation_.observe(*key, *predicted, *actual); return; }
    if (event.kind == "evolution_register") { const auto* key = string_value(event.data, "key"); if (key != nullptr) evolution_.register_parameter(*key, double_value(event.data, "initial")); return; }
    if (event.kind == "evolution_fitness") { const auto* key = string_value(event.data, "key"); if (key != nullptr) evolution_.observe_fitness(*key, double_value(event.data, "fitness")); return; }
    if (event.kind == "evolution_adopt") { const auto* key = string_value(event.data, "key"); if (key != nullptr) evolution_.adopt(EvolutionProposal{*key, double_value(event.data, "current"), double_value(event.data, "proposed"), double_value(event.data, "expected_gain"), double_value(event.data, "confidence")}); return; }
    if (event.kind == "evolution_rollback") { const auto* key = string_value(event.data, "key"); if (key != nullptr) evolution_.rollback(*key); return; }
    if (event.kind == "resilience_isolate") { const auto* component = string_value(event.data, "component"); if (component != nullptr) resilience_.isolate(*component); return; }
    if (event.kind == "resilience_recover") { const auto* component = string_value(event.data, "component"); if (component != nullptr) resilience_.recover(*component, double_value(event.data, "health")); return; }
    if (event.kind == "capability_observe") { const auto* name = string_value(event.data, "name"); if (name != nullptr) self_model_.observe_capability(*name, double_value(event.data, "availability"), double_value(event.data, "performance")); return; }
    if (event.kind == "capability_isolate") { const auto* name = string_value(event.data, "name"); if (name != nullptr) self_model_.isolate(*name); return; }
    if (event.kind == "capability_restore") { const auto* name = string_value(event.data, "name"); if (name != nullptr) self_model_.restore(*name, double_value(event.data, "availability"), double_value(event.data, "performance")); return; }
    if (event.kind != "observation" && event.kind != "learning") return;
    double reliability = event.kind == "learning" ? std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0) : 0.7;
    if (event.kind == "learning") for (const auto& [key, value] : event.data) if (key != "reliability") { knowledge_.assimilate(Evidence{event.source, key, value, reliability}); break; }
    std::vector<Belief> before; before.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) before.push_back(belief);
    for (const auto& [key, value] : event.data) { if (event.kind == "learning" && key == "reliability") continue; auto it = beliefs_.find(key); if (it == beliefs_.end()) beliefs_.emplace(key, Belief{key, value, reliability, 1, event.sequence}); else { const bool same = it->second.value == value; it->second.value = value; it->second.confidence = same ? std::min(0.999, it->second.confidence + (1.0 - it->second.confidence) * reliability) : std::max(0.05, it->second.confidence * (1.0 - reliability)); ++it->second.observations; it->second.updated_sequence = event.sequence; } world_.observe(Fact{event.source, key, value, reliability, 1}); }
    std::vector<Belief> after; after.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) after.push_back(belief); causal_.observe_transition(before, after);
    if (event.kind == "observation") { const auto history = memory_.recent(2); const double novelty = history.size() > 1 ? compute_novelty(event, {history.front()}) : 1.0; double strongest = 0.0; for (const auto& [_, belief] : beliefs_) strongest = std::max(strongest, belief.confidence); attention_state_ = attention_model_.score(event, novelty, strongest); threat_state_ = threat_model_.assess(event); state_.novelty = novelty; state_.attention = attention_state_.salience; state_.threat = threat_state_.score; if (const auto it = event.data.find("health"); it != event.data.end()) { double health = 1.0; if (const auto p = std::get_if<double>(&it->second)) health = *p; else if (const auto p = std::get_if<std::int64_t>(&it->second)) health = static_cast<double>(*p); resilience_.observe(event.source, std::clamp(health, 0.0, 1.0)); } }
}

Observation Brain::observe(Event event) { std::unique_lock lock(mutex_); event.timestamp_ns = event.timestamp_ns == 0 ? now_ns() : event.timestamp_ns; const auto previous = memory_.recent(1); const double novelty = compute_novelty(event, previous); event.sequence = memory_.append(event); ++state_.events_seen; state_.cycle = event.sequence; state_.novelty = novelty; replay(event); state_.novelty = novelty; return Observation{std::move(event), novelty}; }

double Brain::learn(const Evidence& evidence) { std::unique_lock lock(mutex_); const double fused = knowledge_.assimilate(evidence); Event event{0, now_ns(), evidence.source, "learning", {{evidence.key, evidence.value}, {"reliability", fused}}}; event.sequence = memory_.append(event); ++state_.events_seen; state_.cycle = event.sequence; replay(event); return fused; }

std::vector<Belief> Brain::beliefs() const { std::shared_lock lock(mutex_); std::vector<Belief> result; result.reserve(beliefs_.size()); for (const auto& [_, belief] : beliefs_) result.push_back(belief); return result; }

Prediction Brain::predict(std::string key, Scalar value, double confidence) { std::unique_lock lock(mutex_); Prediction prediction{std::move(key), std::move(value), std::clamp(confidence, 0.0, 1.0), state_.cycle, false, 0.0}; Event event{0, now_ns(), "brain", "prediction", {{"key", prediction.key}, {"value", prediction.predicted}, {"confidence", prediction.confidence}}}; event.sequence = memory_.append(std::move(event)); prediction.created_sequence = event.sequence; predictions_[prediction.key] = prediction; ++state_.events_seen; state_.cycle = event.sequence; return prediction; }

bool Brain::resolve_prediction(const std::string& key, const Scalar& actual) { std::unique_lock lock(mutex_); const auto it = predictions_.find(key); if (it == predictions_.end() || it->second.resolved) return false; it->second.resolved = true; it->second.error = it->second.predicted == actual ? 0.0 : 1.0; if (const auto predicted = std::get_if<double>(&it->second.predicted)) if (const auto observed = std::get_if<double>(&actual)) adaptation_.observe(key, *predicted, *observed); Event event{0, now_ns(), "brain", "prediction_outcome", {{"key", key}, {"actual", actual}, {"error", it->second.error}}}; event.sequence = memory_.append(std::move(event)); ++state_.events_seen; state_.cycle = event.sequence; return it->second.error == 0.0; }

const KnowledgeMetric* Brain::knowledge_source(const std::string& source) const noexcept { std::shared_lock lock(mutex_); return knowledge_.source_metric(source); }
const AdaptiveMetric* Brain::learning_metric(const std::string& key) const noexcept { std::shared_lock lock(mutex_); return adaptation_.metric(key); }
double Brain::learning_confidence(const std::string& key) const noexcept { std::shared_lock lock(mutex_); return adaptation_.confidence(key); }
std::vector<std::pair<std::string, Scalar>> Brain::simulate(const std::vector<Belief>& assumptions) const { std::shared_lock lock(mutex_); return causal_.predict(assumptions); }
std::vector<CausalLink> Brain::causal_links() const { std::shared_lock lock(mutex_); return causal_.links(); }
std::vector<Decision> Brain::choose(const std::vector<CandidateAction>& actions) const { std::shared_lock lock(mutex_); double strongest = 0.0; for (const auto& [_, b] : beliefs_) strongest = std::max(strongest, b.confidence); return decision_.rank(actions, 1.0 - strongest, threat_state_.score); }
Plan Brain::plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const { std::shared_lock lock(mutex_); return planner_.build(actions, horizon); }
Reflection Brain::reflect() const { std::shared_lock lock(mutex_); std::vector<Belief> bs; std::vector<Prediction> ps; for (const auto& [_, b] : beliefs_) bs.push_back(b); for (const auto& [_, p] : predictions_) ps.push_back(p); return reflection_model_.evaluate(bs, ps); }
AttentionSignal Brain::attention() const { std::shared_lock lock(mutex_); return attention_state_; }
ThreatAssessment Brain::threat() const { std::shared_lock lock(mutex_); return threat_state_; }
std::vector<RecoveryPlan> Brain::recovery_options() const { std::shared_lock lock(mutex_); return resilience_.required_recovery(); }
bool Brain::isolate(const std::string& component) { std::unique_lock lock(mutex_); if (!resilience_.isolate(component)) return false; Event event{0, now_ns(), "brain", "resilience_isolate", {{"component", component}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; return true; }
bool Brain::recover(const std::string& component, double restored_health) { std::unique_lock lock(mutex_); const double health = std::clamp(restored_health, 0.0, 1.0); if (!resilience_.recover(component, health)) return false; Event event{0, now_ns(), "brain", "resilience_recover", {{"component", component}, {"health", health}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; return true; }
void Brain::register_evolution_parameter(std::string key, double initial) { std::unique_lock lock(mutex_); evolution_.register_parameter(key, initial); Event event{0, now_ns(), "brain", "evolution_register", {{"key", key}, {"initial", initial}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; }
void Brain::observe_evolution_fitness(const std::string& key, double fitness) { std::unique_lock lock(mutex_); const double bounded = std::clamp(fitness, -1.0, 1.0); evolution_.observe_fitness(key, bounded); Event event{0, now_ns(), "brain", "evolution_fitness", {{"key", key}, {"fitness", bounded}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; }
std::vector<EvolutionProposal> Brain::evolution_options() const { std::shared_lock lock(mutex_); return evolution_.propose(); }
bool Brain::adopt_evolution(const EvolutionProposal& proposal) { std::unique_lock lock(mutex_); if (!evolution_.adopt(proposal)) return false; Event event{0, now_ns(), "brain", "evolution_adopt", {{"key", proposal.key}, {"current", proposal.current}, {"proposed", proposal.proposed}, {"expected_gain", proposal.expected_gain}, {"confidence", proposal.confidence}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; return true; }
bool Brain::rollback_evolution(const std::string& key) { std::unique_lock lock(mutex_); if (!evolution_.rollback(key)) return false; Event event{0, now_ns(), "brain", "evolution_rollback", {{"key", key}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; return true; }
void Brain::observe_capability(const std::string& name, double availability, double performance) { std::unique_lock lock(mutex_); const double a = std::clamp(availability, 0.0, 1.0); const double p = std::clamp(performance, 0.0, 1.0); self_model_.observe_capability(name, a, p); Event event{0, now_ns(), "brain", "capability_observe", {{"name", name}, {"availability", a}, {"performance", p}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; }
bool Brain::isolate_capability(const std::string& name) { std::unique_lock lock(mutex_); if (!self_model_.isolate(name)) return false; Event event{0, now_ns(), "brain", "capability_isolate", {{"name", name}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; return true; }
bool Brain::restore_capability(const std::string& name, double availability, double performance) { std::unique_lock lock(mutex_); const double a = std::clamp(availability, 0.0, 1.0); const double p = std::clamp(performance, 0.0, 1.0); if (!self_model_.restore(name, a, p)) return false; Event event{0, now_ns(), "brain", "capability_restore", {{"name", name}, {"availability", a}, {"performance", p}}}; memory_.append(std::move(event)); ++state_.events_seen; ++state_.cycle; return true; }
BrainSnapshot Brain::snapshot() const { std::shared_lock lock(mutex_); BrainSnapshot result; result.state = state_; for (const auto& [_, b] : beliefs_) result.beliefs.push_back(b); for (const auto& [_, p] : predictions_) result.predictions.push_back(p); result.causal_links = causal_.links(); return result; }
BrainState Brain::state() const { std::shared_lock lock(mutex_); return state_; }

double Brain::compute_novelty(const Event& event, const std::vector<Event>& history) { if (history.empty() || event.data.empty()) return history.empty() ? 1.0 : 0.0; const auto& previous = history.back(); std::size_t differences = event.data.size(); for (const auto& [key, value] : event.data) { const auto it = previous.data.find(key); if (it != previous.data.end() && it->second == value && differences > 0) --differences; } return std::clamp(static_cast<double>(differences) / static_cast<double>(event.data.size()), 0.0, 1.0); }

} // namespace jarvis::core
