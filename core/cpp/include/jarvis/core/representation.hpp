#pragma once

#include "event.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace jarvis::core {

enum class Modality : std::uint8_t { unknown, text, speech, vision, audio, sensor, system };

enum class RepresentationKind : std::uint8_t { unknown, entity, event, concept_node, relation, attribute };

struct EvidenceSpan {
    std::string source;
    std::uint64_t sequence{0};
    double confidence{0.0};
};

struct SemanticNode {
    std::string id;
    RepresentationKind kind{RepresentationKind::unknown};
    std::string label;
    Attributes attributes;
    double confidence{0.0};
    std::vector<EvidenceSpan> evidence;
};

struct SemanticRelation {
    std::string id;
    std::string subject_id;
    std::string predicate;
    std::string object_id;
    double confidence{0.0};
    std::vector<EvidenceSpan> evidence;
};

struct PerceptualRepresentation {
    std::uint64_t sequence{0};
    Modality modality{Modality::unknown};
    std::vector<SemanticNode> nodes;
    std::vector<SemanticRelation> relations;
    Attributes metadata;
    double confidence{0.0};
};

class RepresentationEngine {
public:
    PerceptualRepresentation normalize(const Event& event) const;
    bool validate(const PerceptualRepresentation& representation) const noexcept;
};

} // namespace jarvis::core
