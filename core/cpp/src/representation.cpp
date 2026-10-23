#include "jarvis/core/representation.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace jarvis::core {
namespace {

Modality modality_for(const std::string& source, const std::string& kind) {
    if (source == "voice" || source == "speech") return Modality::speech;
    if (source == "vision" || source == "camera") return Modality::vision;
    if (source == "audio" || source == "microphone") return Modality::audio;
    if (source == "sensor") return Modality::sensor;
    if (source == "system") return Modality::system;
    if (kind == "text" || kind == "command" || kind == "message") return Modality::text;
    return Modality::unknown;
}

std::string node_id(std::uint64_t sequence, const std::string& key) {
    // Semantic identifiers are used by downstream experience links. Avoid
    // std::hash: it is not a cross-process identity contract and can collide.
    // A length-prefixed key is deterministic and unambiguous.
    return "n:" + std::to_string(sequence) + ":" +
           std::to_string(key.size()) + ":" + key;
}

double confidence_for(const Event& event, double fallback) {
    const auto it = event.data.find("confidence");
    if (it == event.data.end()) return fallback;
    if (const auto* value = std::get_if<double>(&it->second))
        return std::isfinite(*value) ? std::clamp(*value, 0.0, 1.0) : 0.0;
    if (const auto* value = std::get_if<std::int64_t>(&it->second))
        return std::clamp(static_cast<double>(*value), 0.0, 1.0);
    return fallback;
}

bool is_appraisal_metadata(const std::string& key) {
    // These fields describe evidence quality or the learner's appraisal of an
    // experience. They should remain available for audit/replay, but must not
    // become semantic features that distort recall or developmental context.
    return key == "_external_observation" || key == "confidence" ||
           key == "reliability" || key == "evidence_reliability" ||
           key == "novelty" || key == "salience" || key == "urgency" ||
           key == "prediction_error" || key == "outcome" ||
           key == "world_step";
}

} // namespace

PerceptualRepresentation RepresentationEngine::normalize(const Event& event) const {
    PerceptualRepresentation result;
    result.sequence = event.sequence;
    result.modality = modality_for(event.source, event.kind);
    result.metadata.emplace("source", event.source);
    result.metadata.emplace("kind", event.kind);

    if (event.data.empty()) {
        result.confidence = 0.0;
        return result;
    }

    const double default_confidence = result.modality == Modality::unknown ? 0.35 : 0.7;
    const double base_confidence = confidence_for(event, default_confidence);
    result.nodes.reserve(event.data.size());
    for (const auto& [key, value] : event.data) {
        if (is_appraisal_metadata(key)) {
            result.metadata.insert_or_assign(key, value);
            continue;
        }
        SemanticNode node;
        node.id = node_id(event.sequence, key);
        node.kind = RepresentationKind::attribute;
        node.label = key;
        node.attributes.emplace("value", value);
        node.confidence = base_confidence;
        node.evidence.push_back(EvidenceSpan{event.source, event.sequence, base_confidence});
        result.nodes.push_back(std::move(node));
    }
    // A metadata-only event is auditable, but it has supplied no semantic
    // feature for downstream reasoning or action selection.
    result.confidence = result.nodes.empty() ? 0.0 : base_confidence;
    return result;
}

bool RepresentationEngine::validate(const PerceptualRepresentation& representation) const noexcept {
    if (!std::isfinite(representation.confidence) ||
        representation.confidence < 0.0 || representation.confidence > 1.0) return false;
    for (const auto& node : representation.nodes) {
        if (node.id.empty() || node.label.empty()) return false;
        if (!std::isfinite(node.confidence) ||
            node.confidence < 0.0 || node.confidence > 1.0) return false;
        for (const auto& evidence : node.evidence)
            if (!std::isfinite(evidence.confidence) ||
                evidence.confidence < 0.0 || evidence.confidence > 1.0) return false;
    }
    for (const auto& relation : representation.relations) {
        if (relation.id.empty() || relation.subject_id.empty() || relation.predicate.empty() || relation.object_id.empty()) return false;
        if (!std::isfinite(relation.confidence) ||
            relation.confidence < 0.0 || relation.confidence > 1.0) return false;
    }
    return true;
}

} // namespace jarvis::core
