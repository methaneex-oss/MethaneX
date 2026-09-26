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

// A derived contextual relationship is deliberately distinct from a learned
// direct association. It is evidence that two concepts are connected through
// a shared learned context, not proof that they are directly related.
struct AssociationInference {
    std::string key;
    double strength{0.0};
    std::size_t hops{0};
};

// A concept candidate is a derived cluster of experiences that repeatedly share
// the same contextual neighbors. It is not an asserted semantic category.
struct ConceptCandidate {
    std::vector<std::string> members;
    double coherence{0.0};
    std::uint64_t supporting_observations{0};
};

class AssociationModel {
public:
    // Observation reliability is supplied separately from belief confidence because
    // a newly observed value may temporarily lower belief confidence when it conflicts
    // with prior evidence. Associations should reflect the reliability of the
    // transition evidence rather than treating that contradiction penalty as evidence
    // that the observation itself was unreliable.
    void observe(const std::vector<Belief>& before, const std::vector<Belief>& after,
                 std::uint64_t sequence, double observation_reliability = 1.0);
    std::vector<Association> all() const;
    std::vector<Association> related(const std::string& key, double minimum_strength = 0.5) const;

    // Traverse the learned association graph without converting an indirect path
    // into a direct fact. Path strength is the product of edge strengths, so
    // unsupported long chains naturally decay toward zero.
    std::vector<AssociationInference> contextual(const std::string& key,
                                                  std::size_t max_hops = 2,
                                                  double minimum_strength = 0.25) const;
    std::vector<ConceptCandidate> concept_candidates(
        double minimum_strength = 0.5,
        std::size_t minimum_shared_contexts = 2) const;

private:
    std::vector<Association> associations_;
};

} // namespace jarvis::core
