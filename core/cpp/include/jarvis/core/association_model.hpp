#pragma once

#include "cognition.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

struct Association {
    std::string left;
    std::string right;
    double strength{0.0};
    double confidence{0.0};
    std::uint64_t observations{0};
    std::uint64_t last_sequence{0};
    std::uint64_t contradictory_observations{0};
};

struct AssociationInference {
    std::string key;
    double strength{0.0};
    std::size_t hops{0};
};

struct ConceptCandidate {
    std::vector<std::string> members;
    double coherence{0.0};
    std::uint64_t supporting_observations{0};
    std::uint64_t contradictory_observations{0};
};

// A structural match applies a learned relational pattern to a previously unseen key.
// It is evidence for analogy, not a semantic assertion that the key belongs to the concept.
struct ConceptMatch {
    std::vector<std::string> concept_members;
    std::vector<std::string> matched_contexts;
    double similarity{0.0};
    double evidence_strength{0.0};
};

class AssociationModel {
public:
    void observe(const std::vector<Belief>& before, const std::vector<Belief>& after,
                 std::uint64_t sequence, double observation_reliability = 1.0);
    std::vector<Association> all() const;
    std::vector<Association> related(const std::string& key, double minimum_strength = 0.5) const;
    std::vector<AssociationInference> contextual(const std::string& key,
                                                  std::size_t max_hops = 2,
                                                  double minimum_strength = 0.25) const;
    std::vector<ConceptCandidate> concept_candidates(
        double minimum_strength = 0.5,
        std::size_t minimum_shared_contexts = 2) const;
    std::vector<ConceptMatch> generalized_concepts(
        const std::string& key,
        double minimum_strength = 0.5,
        std::size_t minimum_shared_contexts = 2,
        double minimum_similarity = 0.5) const;
    void apply_prediction_feedback(const std::vector<std::string>& concept_members,
                                   bool successful,
                                   double evidence_strength,
                                   std::uint64_t sequence);

private:
    std::vector<Association> associations_;
};

} // namespace jarvis::core
