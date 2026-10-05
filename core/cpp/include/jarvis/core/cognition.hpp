#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <variant>
#include <vector>
#include <unordered_map>

namespace jarvis::core {

using Scalar = std::variant<std::monostate, double, std::int64_t, bool, std::string>;
using Attributes = std::unordered_map<std::string, Scalar>;

struct Event { std::uint64_t sequence{0}; std::uint64_t timestamp{0}; std::string source; std::string kind; Attributes data; };
struct Observation { Event event; double novelty{0.0}; };
struct Evidence { std::string source; std::string key; Scalar value; double confidence{0.0}; };
struct Belief { std::string key; Scalar value; double confidence{0.0}; std::uint64_t observations{0}; std::uint64_t updated_sequence{0}; };
struct Prediction { std::string key; Scalar predicted; double confidence{0.0}; std::uint64_t created_sequence{0}; bool resolved{false}; double error{0.0}; };
struct Association { std::string left; std::string right; double strength{0.0}; std::uint64_t observations{0}; };
struct AssociationInference { std::string key; double strength{0.0}; std::size_t hops{0}; };
struct ConceptCandidate { std::string key; double strength{0.0}; std::size_t shared_contexts{0}; };
struct ConceptMatch { std::string key; double similarity{0.0}; double strength{0.0}; };
struct CausalLink { std::string cause; std::string effect; double strength{0.0}; std::uint64_t observations{0}; };

enum class DecisionOutcome : std::uint8_t {
    act,
    defer,
    observe,
    ask_clarify,
    recommend,
    reject,
    escalate,
};

struct CandidateAction {
    std::string name;
    double utility{0.0};
    double expected_value{0.0};
    double confidence{0.0};
    double risk{0.0};
    double reversibility{1.0};
    double resource_cost{0.0};
    double expected_consequence{0.0};
    double urgency{0.0};
    double novelty{0.0};
    double uncertainty{0.0};
    DecisionOutcome preferred_outcome{DecisionOutcome::act};
    std::vector<std::string> required_permissions;
};

struct DecisionContext {
    double goal_priority{0.0};
    double goal_progress{0.0};
    double plan_expected_value{0.0};
    double plan_risk{0.0};
    double resource_budget{0.0};
    double uncertainty{0.0};
    double threat{0.0};
    double deadline_pressure{0.0};
    double valence{0.0};
    double arousal{0.0};
    double affective_uncertainty{0.0};
    double tension{0.0};
    double stability{1.0};
};

struct Decision {
    CandidateAction action;
    double score{0.0};
    DecisionOutcome outcome{DecisionOutcome::defer};
    std::string rationale;
};

struct SimulationResult { std::vector<std::pair<std::string, Scalar>> states; double confidence{0.0}; };
struct PlanningContext {
    std::vector<Belief> assumptions;
    double risk_tolerance{1.0};
    double minimum_confidence{0.0};
    double valence{0.0};
    double arousal{0.0};
    double affective_uncertainty{0.0};
    double tension{0.0};
    double stability{1.0};
};
struct PlanStep { CandidateAction action; double expected_score{0.0}; };
struct Plan { std::vector<PlanStep> steps; double expected_value{0.0}; double confidence{0.0}; };

} // namespace jarvis::core
