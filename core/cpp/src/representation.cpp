#include "jarvis/core/representation.hpp"

#include <algorithm>
#include <functional>

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
    return "n:" + std::to_string(sequence) + ":" + std::to_string(std::hash<std::string>{}(key));
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

    const double base_confidence = result.modality == Modality::unknown ? 0.35 : 0.7;
    result.nodes.reserve(event.data.size());
    for (const auto& [key, value] : event.data) {
        SemanticNode node;
        node.id = node_id(event.sequence, key);
        node.kind = RepresentationKind::attribute;
        node.label = key;
        node.attributes.emplace("value", value);
        node.confidence = base_confidence;
        node.evidence.push_back(EvidenceSpan{event.source, event.sequence, base_confidence});
        result.nodes.push_back(std::move(node));
    }
    result.confidence = base_confidence;
    return result;
}

bool RepresentationEngine::validate(const PerceptualRepresentation& representation) const noexcept {
    if (representation.confidence < 0.0 || representation.confidence > 1.0) return false;
    for (const auto& node : representation.nodes) {
        if (node.id.empty() || node.label.empty()) return false;
        if (node.confidence < 0.0 || node.confidence > 1.0) return false;
        for (const auto& evidence : node.evidence)
            if (evidence.confidence < 0.0 || evidence.confidence > 1.0) return false;
    }
    for (const auto& relation : representation.relations) {
        if (relation.id.empty() || relation.subject_id.empty() || relation.predicate.empty() || relation.object_id.empty()) return false;
        if (relation.confidence < 0.0 || relation.confidence > 1.0) return false;
    }
    return true;
}

} // namespace jarvis::core
