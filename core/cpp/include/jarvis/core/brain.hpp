#pragma once

#include "event.hpp"
#include "memory.hpp"
#include "world_model.hpp"
#include "cognition.hpp"
#include "causal_model.hpp"
#include "decision.hpp"
#include "adaptation.hpp"
#include "attention.hpp"
#include "threat.hpp"
#include "resilience.hpp"
#include "evolution.hpp"
#include "planning.hpp"
#include "reflection.hpp"
#include "knowledge.hpp"
#include "self_model.hpp"

#include <cstddef>
#include <cstdint>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace jarvis::core {

struct BrainState {
    std::uint64_t cycle{0};
    std::uint64_t events_seen{0};
    double novelty{0.0};
    double attention{0.0};
    double threat{0.0};
};

class Brain {
public:
    Brain();
    Observation observe(Event event);
    double learn(const Evidence& evidence);
    std::vector<Belief> beliefs() const;
    Prediction predict(std::string key, Scalar value, double confidence);
    bool resolve_prediction(const std::string& key, const Scalar& actual);
    std::vector<std::pair<std::string, Scalar>> simulate(const std::vector<Belief>& assumptions) const;
    std::vector<CausalLink> causal_links() const;
    std::vector<Decision> choose(const std::vector<CandidateAction>& actions) const;
    Plan plan(const std::vector<CandidateAction>& actions, std::size_t horizon) const;
    Reflection reflect() const;
    const KnowledgeMetric* knowledge_source(const std::string& source) const noexcept;
    const AdaptiveMetric* learning_metric(const std::string& key) const noexcept;
    double learning_confidence(const std::string& key) const noexcept;
    AttentionSignal attention() const;
    ThreatAssessment threat() const;
    std::vector<RecoveryPlan> recovery_options() const;
    bool isolate(const std::string& component);
    bool recover(const std::string& component, double restored_health);
    std::vector<EvolutionProposal> evolution_options() const;
    bool adopt_evolution(const EvolutionProposal& proposal);
    void observe_capability(const std::string& name, double availability, double performance);
    bool isolate_capability(const std::string& name);
    bool restore_capability(const std::string& name, double availability, double performance);
    const SelfModel& self_model() const noexcept { return self_model_; }
    const WorldModel& world() const noexcept { return world_; }
    const Memory& memory() const noexcept { return memory_; }
    BrainState state() const;

private:
    static double compute_novelty(const Event& event, const std::vector<Event>& history);
    void replay(const Event& event);

    mutable std::shared_mutex mutex_;
    BrainState state_{};
    WorldModel world_{};
    Memory memory_{};
    std::unordered_map<std::string, Belief> beliefs_;
    std::unordered_map<std::string, Prediction> predictions_;
    CausalModel causal_{};
    DecisionEngine decision_{};
    AdaptationModel adaptation_{};
    AttentionModel attention_model_{};
    ThreatModel threat_model_{};
    ResilienceModel resilience_{};
    EvolutionModel evolution_{};
    Planner planner_{};
    ReflectionModel reflection_model_{};
    KnowledgeModel knowledge_{};
    SelfModel self_model_{};
    AttentionSignal attention_state_{};
    ThreatAssessment threat_state_{};
};

} // namespace jarvis::core
