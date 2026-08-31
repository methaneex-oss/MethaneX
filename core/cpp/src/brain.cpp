// Cognitive core: persistent state, reasoning, adaptation, recovery and evolution.
#include "jarvis/core/brain.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <mutex>
#include <sstream>
#include <utility>

namespace jarvis::core {
namespace {

std::uint64_t now_ns() noexcept {
    return static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
}

const std::string* string_value(const Attributes& data, const std::string& key) {
    const auto it = data.find(key);
    return it == data.end() ? nullptr : std::get_if<std::string>(&it->second);
}

double double_value(const Attributes& data, const std::string& key, double fallback = 0.0) {
    const auto it = data.find(key);
    if (it == data.end()) return fallback;
    if (const auto value = std::get_if<double>(&it->second)) return *value;
    if (const auto value = std::get_if<std::int64_t>(&it->second)) return static_cast<double>(*value);
    return fallback;
}

std::uint64_t integer_value(const Attributes& data, const std::string& key, std::uint64_t fallback = 0) {
    const auto it = data.find(key);
    if (it == data.end()) return fallback;
    if (const auto value = std::get_if<std::int64_t>(&it->second)) return *value < 0 ? fallback : static_cast<std::uint64_t>(*value);
    if (const auto value = std::get_if<double>(&it->second)) return *value < 0.0 ? fallback : static_cast<std::uint64_t>(*value);
    return fallback;
}

std::string join_ids(const std::vector<std::string>& ids) {
    std::ostringstream out;
    for (std::size_t i = 0; i < ids.size(); ++i) {
        if (i != 0) out << '\x1f';
        out << ids[i];
    }
    return out.str();
}

std::vector<std::string> split_ids(const std::string& value) {
    std::vector<std::string> result;
    std::size_t start = 0;
    while (start <= value.size()) {
        const auto end = value.find('\x1f', start);
        const auto token = value.substr(start, end == std::string::npos ? std::string::npos : end - start);
        if (!token.empty()) result.push_back(token);
        if (end == std::string::npos) break;
        start = end + 1;
    }
    return result;
}

GoalStatus goal_status_value(std::int64_t value) {
    switch (value) {
        case 0: return GoalStatus::pending;
        case 1: return GoalStatus::active;
        case 2: return GoalStatus::completed;
        case 3: return GoalStatus::abandoned;
        default: return GoalStatus::pending;
    }
}

} // namespace

Brain::Brain(std::filesystem::path journal_path)
    : memory_(256, std::move(journal_path)) {
    const auto history = memory_.all();
    for (const auto& event : history) replay(event);
    state_.events_seen = static_cast<std::uint64_t>(history.size());
    if (!history.empty()) state_.cycle = history.back().sequence;
    sync_self_state();
}

void Brain::sync_self_state() {
    self_state_model_.set_activity(state_.events_seen == 0 ? "idle" : "cognitive_processing");
    self_state_model_.set_workload(std::clamp(
        std::min(1.0, static_cast<double>(state_.events_seen % 1000) / 1000.0), 0.0, 1.0));
    self_state_model_.set_uncertainty(std::clamp(1.0 - state_.attention, 0.0, 1.0));
    self_state_model_.set_health(CognitiveHealth{
        std::clamp(1.0 - state_.threat * 0.5, 0.0, 1.0),
        1.0,
        std::clamp(1.0 - state_.novelty * 0.1, 0.0, 1.0),
        1.0});
    self_state_model_.advance_cycle(state_.events_seen);
}

void Brain::replay(const Event& event) {
    state_.cycle = std::max(state_.cycle, event.sequence);

    if (event.kind == "goal_create") {
        const auto* id = string_value(event.data, "id");
        const auto* description = string_value(event.data, "description");
        if (id == nullptr || description == nullptr) return;
        Goal goal{*id, *description,
                  double_value(event.data, "priority"),
                  double_value(event.data, "progress"),
                  integer_value(event.data, "created_cycle"),
                  integer_value(event.data, "deadline_cycle"),
                  goal_status_value(static_cast<std::int64_t>(integer_value(event.data, "status"))),
                  string_value(event.data, "prerequisites") ? split_ids(*string_value(event.data, "prerequisites")) : std::vector<std::string>{},
                  string_value(event.data, "subgoals") ? split_ids(*string_value(event.data, "subgoals")) : std::vector<std::string>{}};
        goals_model_.create(std::move(goal));
        return;
    }
    if (event.kind == "goal_activate") {
        if (const auto* id = string_value(event.data, "id")) goals_model_.activate(*id);
        return;
    }
    if (event.kind == "goal_progress") {
        if (const auto* id = string_value(event.data, "id")) goals_model_.update_progress(*id, double_value(event.data, "progress"));
        return;
    }
    if (event.kind == "goal_abandon") {
        if (const auto* id = string_value(event.data, "id")) goals_model_.abandon(*id);
        return;
    }
    if (event.kind == "goal_priority") {
        if (const auto* id = string_value(event.data, "id")) goals_model_.set_priority(*id, double_value(event.data, "priority"));
        return;
    }

    if (event.kind == "prediction") {
        const auto* key = string_value(event.data, "key");
        const auto value = event.data.find("value");
        if (key == nullptr || value == event.data.end()) return;
        predictions_[*key] = Prediction{*key, value->second,
            std::clamp(double_value(event.data, "confidence"), 0.0, 1.0),
            event.sequence, false, 0.0};
        return;
    }

    if (event.kind == "prediction_outcome") {
        const auto* key = string_value(event.data, "key");
        if (key == nullptr) return;
        const auto prediction = predictions_.find(*key);
        if (prediction == predictions_.end()) return;
        prediction->second.resolved = true;
        prediction->second.error = std::clamp(double_value(event.data, "error", 1.0), 0.0, 1.0);
        const auto actual = event.data.find("actual");
        if (actual != event.data.end()) {
            if (const auto predicted = std::get_if<double>(&prediction->second.predicted)) {
                if (const auto observed = std::get_if<double>(&actual->second))
                    adaptation_.observe(*key, *predicted, *observed);
            }
        }
        return;
    }

    if (event.kind == "evolution_register") {
        if (const auto* key = string_value(event.data, "key"))
            evolution_.register_parameter(*key, double_value(event.data, "initial"));
        return;
    }
    if (event.kind == "evolution_fitness") {
        if (const auto* key = string_value(event.data, "key"))
            evolution_.observe_fitness(*key, double_value(event.data, "fitness"));
        return;
    }
    if (event.kind == "evolution_adopt") {
        if (const auto* key = string_value(event.data, "key")) {
            evolution_.adopt(EvolutionProposal{*key, double_value(event.data, "current"),
                double_value(event.data, "proposed"), double_value(event.data, "expected_gain"),
                double_value(event.data, "confidence")});
        }
        return;
    }
    if (event.kind == "evolution_rollback") {
        if (const auto* key = string_value(event.data, "key")) evolution_.rollback(*key);
        return;
    }
    if (event.kind == "resilience_isolate") {
        if (const auto* component = string_value(event.data, "component")) resilience_.isolate(*component);
        return;
    }
    if (event.kind == "resilience_recover") {
        if (const auto* component = string_value(event.data, "component"))
            resilience_.recover(*component, double_value(event.data, "health"));
        return;
    }
    if (event.kind == "capability_observe") {
        if (const auto* name = string_value(event.data, "name"))
            self_model_.observe_capability(*name, double_value(event.data, "availability"),
                                           double_value(event.data, "performance"));
        return;
    }
    if (event.kind == "capability_isolate") {
        if (const auto* name = string_value(event.data, "name")) self_model_.isolate(*name);
        return;
    }
    if (event.kind == "capability_restore") {
        if (const auto* name = string_value(event.data, "name"))
            self_model_.restore(*name, double_value(event.data, "availability"),
                                double_value(event.data, "performance"));
        return;
    }

    if (event.kind != "observation" && event.kind != "learning") return;
    const double reliability = event.kind == "learning"
        ? std::clamp(double_value(event.data, "reliability", 0.5), 0.0, 1.0) : 0.7;

    if (event.kind == "learning") {
        for (const auto& [key, value] : event.data) {
            if (key != "reliability") {
                knowledge_.assimilate(Evidence{event.source, key, value, reliability});
                break;
            }
        }
    }

    std::vector<Belief> before;
    before.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) before.push_back(belief);

    for (const auto& [key, value] : event.data) {
        if (event.kind == "learning" && key == "reliability") continue;
        const auto it = beliefs_.find(key);
        if (it == beliefs_.end()) {
            beliefs_.emplace(key, Belief{key, value, reliability, 1, event.sequence});
        } else {
            const bool same = it->second.value == value;
            it->second.value = value;
            it->second.confidence = same
                ? std::min(0.999, it->second.confidence + (1.0 - it->second.confidence) * reliability)
                : std::max(0.05, it->second.confidence * (1.0 - reliability));
            ++it->second.observations;
            it->second.updated_sequence = event.sequence;
        }
        world_.observe(Fact{event.source, key, value, reliability, 1});
    }

    std::vector<Belief> after;
    after.reserve(beliefs_.size());
    for (const auto& [_, belief] : beliefs_) after.push_back(belief);
    causal_.observe_transition(before, after);

    if (event.kind == "observation") {
        const auto history = memory_.recent(2);
        const double novelty = history.size() > 1 ? compute_novelty(event, {history.front()}) : 1.0;
        double strongest = 0.0;
        for (const auto& [_, belief] : beliefs_) strongest = std::max(strongest, belief.confidence);
        attention_state_ = attention_model_.score(event, novelty, strongest);
        threat_state_ = threat_model_.assess(event);
        state_.novelty = novelty;
        state_.attention = attention_state_.salience;
        state_.threat = threat_state_.score;
        const auto health = event.data.find("health");
        if (health != event.data.end())
            resilience_.observe(event.source, std::clamp(double_value(event.data, "health", 1.0), 0.0, 1.0));
    }
}

Observation Brain::observe(Event event) {
    std::unique_lock lock(mutex_);
    event.timestamp_ns = event.timestamp_ns == 0 ? now_ns() : event.timestamp_ns;
    const auto previous = memory_.recent(1);
    const double novelty = compute_novelty(event, previous);
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return Observation{};
    ++state_.events_seen;
    state_.cycle = event.sequence;
    replay(event);
    state_.novelty = novelty;
    sync_self_state();
    return Observation{std::move(event), novelty};
}

double Brain::learn(const Evidence& evidence) {
    std::unique_lock lock(mutex_);
    if (evidence.key.empty()) return 0.0;
    const double reliability = std::clamp(evidence.reliability, 0.0, 1.0);
    Event event{0, now_ns(), evidence.source, "learning",
        {{evidence.key, evidence.value}, {"reliability", reliability}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return 0.0;
    ++state_.events_seen;
    state_.cycle = event.sequence;
    replay(event);
    sync_self_state();
    if (const auto* metric = knowledge_.source_metric(evidence.source)) return metric->reliability;
    return reliability;
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
    if (key.empty()) return Prediction{};
    Prediction prediction{std::move(key), std::move(value), std::clamp(confidence, 0.0, 1.0),
                          state_.cycle, false, 0.0};
    Event event{0, now_ns(), "brain", "prediction",
        {{"key", prediction.key}, {"value", prediction.predicted}, {"confidence", prediction.confidence}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return Prediction{};
    prediction.created_sequence = event.sequence;
    predictions_[prediction.key] = prediction;
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return prediction;
}

bool Brain::resolve_prediction(const std::string& key, const Scalar& actual) {
    std::unique_lock lock(mutex_);
    const auto it = predictions_.find(key);
    if (it == predictions_.end() || it->second.resolved) return false;
    const double error = it->second.predicted == actual ? 0.0 : 1.0;
    Event event{0, now_ns(), "brain", "prediction_outcome",
        {{"key", key}, {"actual", actual}, {"error", error}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return false;
    it->second.resolved = true;
    it->second.error = error;
    if (const auto predicted = std::get_if<double>(&it->second.predicted))
        if (const auto observed = std::get_if<double>(&actual)) adaptation_.observe(key, *predicted, *observed);
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return error == 0.0;
}

const KnowledgeMetric* Brain::knowledge_source(const std::string& source) const noexcept {
    std::shared_lock lock(mutex_);
    return knowledge_.source_metric(source);
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

std::vector<CausalLink> Brain::causal_links() const {
    std::shared_lock lock(mutex_);
    return causal_.links();
}

std::vector<Decision> Brain::choose(const std::vector<CandidateAction>& actions) const {
    std::shared_lock lock(mutex_);
    double strongest = 0.0;
    for (const auto& [_, belief] : beliefs_) strongest = std::max(strongest, belief.confidence);
    return decision_.rank(actions, 1.0 - strongest, threat_state_.score);
}

Plan Brain::plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const {
    std::shared_lock lock(mutex_);
    return planner_.build(actions, horizon);
}

Reflection Brain::reflect() const {
    std::shared_lock lock(mutex_);
    std::vector<Belief> current_beliefs;
    std::vector<Prediction> current_predictions;
    current_beliefs.reserve(beliefs_.size());
    current_predictions.reserve(predictions_.size());
    for (const auto& [_, belief] : beliefs_) current_beliefs.push_back(belief);
    for (const auto& [_, prediction] : predictions_) current_predictions.push_back(prediction);
    return reflection_model_.evaluate(current_beliefs, current_predictions);
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
    if (component.empty() || !resilience_.isolate(component)) return false;
    Event event{0, now_ns(), "brain", "resilience_isolate", {{"component", component}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) {
        resilience_.recover(component, 1.0);
        return false;
    }
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}

bool Brain::recover(const std::string& component, double restored_health) {
    std::unique_lock lock(mutex_);
    const double health = std::clamp(restored_health, 0.0, 1.0);
    if (component.empty() || !resilience_.recover(component, health)) return false;
    Event event{0, now_ns(), "brain", "resilience_recover", {{"component", component}, {"health", health}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) {
        resilience_.isolate(component);
        return false;
    }
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}

void Brain::register_evolution_parameter(std::string key, double initial) {
    std::unique_lock lock(mutex_);
    if (key.empty()) return;
    evolution_.register_parameter(key, initial);
    Event event{0, now_ns(), "brain", "evolution_register", {{"key", key}, {"initial", initial}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return;
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
}

void Brain::observe_evolution_fitness(const std::string& key, double fitness) {
    std::unique_lock lock(mutex_);
    if (key.empty()) return;
    const double bounded = std::clamp(fitness, -1.0, 1.0);
    evolution_.observe_fitness(key, bounded);
    Event event{0, now_ns(), "brain", "evolution_fitness", {{"key", key}, {"fitness", bounded}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return;
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
}

std::vector<EvolutionProposal> Brain::evolution_options() const {
    std::shared_lock lock(mutex_);
    return evolution_.propose();
}

bool Brain::adopt_evolution(const EvolutionProposal& proposal) {
    std::unique_lock lock(mutex_);
    if (proposal.key.empty() || !evolution_.adopt(proposal)) return false;
    Event event{0, now_ns(), "brain", "evolution_adopt",
        {{"key", proposal.key}, {"current", proposal.current}, {"proposed", proposal.proposed},
         {"expected_gain", proposal.expected_gain}, {"confidence", proposal.confidence}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) {
        evolution_.rollback(proposal.key);
        return false;
    }
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}

bool Brain::rollback_evolution(const std::string& key) {
    std::unique_lock lock(mutex_);
    if (key.empty() || !evolution_.rollback(key)) return false;
    Event event{0, now_ns(), "brain", "evolution_rollback", {{"key", key}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) {
        evolution_.rollback(key);
        return false;
    }
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}

void Brain::observe_capability(std::string name, double availability, double performance) {
    std::unique_lock lock(mutex_);
    if (name.empty()) return;
    const double a = std::clamp(availability, 0.0, 1.0);
    const double p = std::clamp(performance, 0.0, 1.0);
    self_model_.observe_capability(name, a, p);
    Event event{0, now_ns(), "brain", "capability_observe",
        {{"name", name}, {"availability", a}, {"performance", p}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) return;
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
}

bool Brain::isolate_capability(const std::string& name) {
    std::unique_lock lock(mutex_);
    if (name.empty() || !self_model_.isolate(name)) return false;
    Event event{0, now_ns(), "brain", "capability_isolate", {{"name", name}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) {
        self_model_.restore(name, 1.0, 1.0);
        return false;
    }
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}

bool Brain::restore_capability(const std::string& name, double availability, double performance) {
    std::unique_lock lock(mutex_);
    const double a = std::clamp(availability, 0.0, 1.0);
    const double p = std::clamp(performance, 0.0, 1.0);
    if (name.empty() || !self_model_.restore(name, a, p)) return false;
    Event event{0, now_ns(), "brain", "capability_restore",
        {{"name", name}, {"availability", a}, {"performance", p}}};
    event.sequence = memory_.append(event);
    if (event.sequence == 0) {
        self_model_.isolate(name);
        return false;
    }
    ++state_.events_seen;
    state_.cycle = event.sequence;
    sync_self_state();
    return true;
}

bool Brain::append_goal_event(const Event& event) {
    Event persisted = event;
    persisted.timestamp_ns = persisted.timestamp_ns == 0 ? now_ns() : persisted.timestamp_ns;
    persisted.sequence = memory_.append(persisted);
    if (persisted.sequence == 0) return false;
    ++state_.events_seen;
    state_.cycle = persisted.sequence;
    sync_self_state();
    return true;
}

bool Brain::create_goal(Goal goal) {
    std::unique_lock lock(mutex_);
    if (!goals_model_.create(goal)) return false;
    Event event{0, now_ns(), "brain", "goal_create",
        {{"id", goal.id}, {"description", goal.description}, {"priority", goal.priority},
         {"progress", goal.progress}, {"created_cycle", static_cast<std::int64_t>(goal.created_cycle)},
         {"deadline_cycle", static_cast<std::int64_t>(goal.deadline_cycle)},
         {"status", static_cast<std::int64_t>(goal.status)},
         {"prerequisites", join_ids(goal.prerequisites)}, {"subgoals", join_ids(goal.subgoals)}}};
    if (!append_goal_event(event)) {
        goals_model_.abandon(goal.id);
        return false;
    }
    return true;
}

bool Brain::activate_goal(const std::string& id) {
    std::unique_lock lock(mutex_);
    const Goal* goal = goals_model_.get(id);
    if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false;
    for (const auto& prerequisite : goal->prerequisites) {
        const Goal* dependency = goals_model_.get(prerequisite);
        if (dependency == nullptr || dependency->status != GoalStatus::completed) return false;
    }
    Event event{0, now_ns(), "brain", "goal_activate", {{"id", id}}};
    if (!append_goal_event(event)) return false;
    return goals_model_.activate(id);
}

bool Brain::update_goal_progress(const std::string& id, double progress) {
    std::unique_lock lock(mutex_);
    const Goal* goal = goals_model_.get(id);
    if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned ||
        !std::isfinite(progress) || progress < 0.0 || progress > 1.0) return false;
    Event event{0, now_ns(), "brain", "goal_progress", {{"id", id}, {"progress", progress}}};
    if (!append_goal_event(event)) return false;
    return goals_model_.update_progress(id, progress);
}

bool Brain::complete_goal(const std::string& id) { return update_goal_progress(id, 1.0); }

bool Brain::abandon_goal(const std::string& id) {
    std::unique_lock lock(mutex_);
    const Goal* goal = goals_model_.get(id);
    if (goal == nullptr || goal->status == GoalStatus::completed || goal->status == GoalStatus::abandoned) return false;
    Event event{0, now_ns(), "brain", "goal_abandon", {{"id", id}}};
    if (!append_goal_event(event)) return false;
    return goals_model_.abandon(id);
}

bool Brain::set_goal_priority(const std::string& id, double priority) {
    std::unique_lock lock(mutex_);
    const Goal* goal = goals_model_.get(id);
    if (goal == nullptr || !std::isfinite(priority)) return false;
    Event event{0, now_ns(), "brain", "goal_priority", {{"id", id}, {"priority", std::clamp(priority, 0.0, 1.0)}}};
    if (!append_goal_event(event)) return false;
    return goals_model_.set_priority(id, priority);
}

const Goal* Brain::goal(const std::string& id) const noexcept {
    std::shared_lock lock(mutex_);
    return goals_model_.get(id);
}

std::vector<Goal> Brain::goals() const {
    std::shared_lock lock(mutex_);
    return goals_model_.all();
}

std::vector<Goal> Brain::eligible_goals() const {
    std::shared_lock lock(mutex_);
    return goals_model_.eligible(state_.cycle);
}

BrainSnapshot Brain::snapshot() const {
    std::shared_lock lock(mutex_);
    BrainSnapshot result;
    result.state = state_;
    result.self_state = self_state_model_.snapshot();
    result.beliefs.reserve(beliefs_.size());
    result.predictions.reserve(predictions_.size());
    for (const auto& [_, belief] : beliefs_) result.beliefs.push_back(belief);
    for (const auto& [_, prediction] : predictions_) result.predictions.push_back(prediction);
    result.causal_links = causal_.links();
    result.goals = goals_model_.all();
    return result;
}

BrainState Brain::state() const {
    std::shared_lock lock(mutex_);
    return state_;
}

double Brain::compute_novelty(const Event& event, const std::vector<Event>& history) {
    if (event.data.empty()) return 0.0;
    if (history.empty()) return 1.0;
    const auto& previous = history.back();
    std::size_t differences = event.data.size();
    for (const auto& [key, value] : event.data) {
        const auto it = previous.data.find(key);
        if (it != previous.data.end() && it->second == value && differences > 0) --differences;
    }
    return std::clamp(static_cast<double>(differences) / static_cast<double>(event.data.size()), 0.0, 1.0);
}

} // namespace jarvis::core
