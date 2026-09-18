#include "jarvis/core/evolution_opportunity.hpp"

#include <algorithm>
#include <cmath>
#include <map>

namespace jarvis::core {
namespace {

double clamp_unit(double value) noexcept {
    return std::clamp(value, 0.0, 1.0);
}

} // namespace

EvolutionOpportunityDetector::EvolutionOpportunityDetector(EvolutionOpportunityPolicy policy)
    : policy_(policy) {
    if (!std::isfinite(policy_.severity_weight) || policy_.severity_weight < 0.0) policy_.severity_weight = 0.40;
    if (!std::isfinite(policy_.recurrence_weight) || policy_.recurrence_weight < 0.0) policy_.recurrence_weight = 0.25;
    if (!std::isfinite(policy_.confidence_weight) || policy_.confidence_weight < 0.0) policy_.confidence_weight = 0.20;
    if (!std::isfinite(policy_.magnitude_weight) || policy_.magnitude_weight < 0.0) policy_.magnitude_weight = 0.15;
    if (!std::isfinite(policy_.minimum_score)) policy_.minimum_score = 0.50;
    policy_.minimum_score = clamp_unit(policy_.minimum_score);
}

std::vector<EvolutionOpportunity> EvolutionOpportunityDetector::detect(
    const std::vector<EvolutionSignal>& signals, std::uint64_t sequence) const {
    struct Aggregate {
        EvolutionOpportunity opportunity;
        double weighted_score{0.0};
        double weight{0.0};
    };

    std::map<std::string, Aggregate> aggregates;
    for (const auto& signal : signals) {
        if (signal.source.empty() || !std::isfinite(signal.severity) ||
            !std::isfinite(signal.recurrence) || !std::isfinite(signal.confidence) ||
            !std::isfinite(signal.baseline) || !std::isfinite(signal.current)) {
            continue;
        }

        const double severity = clamp_unit(signal.severity);
        const double recurrence = clamp_unit(signal.recurrence);
        const double confidence = clamp_unit(signal.confidence);
        const double magnitude = clamp_unit(std::abs(signal.current - signal.baseline));

        const double weight = std::max(0.001, confidence);
        const double score = clamp_unit(
            policy_.severity_weight * severity +
            policy_.recurrence_weight * recurrence +
            policy_.confidence_weight * confidence +
            policy_.magnitude_weight * magnitude);

        auto& aggregate = aggregates[signal.source];
        if (aggregate.opportunity.source.empty()) {
            aggregate.opportunity.source = signal.source;
            aggregate.opportunity.id = "opportunity:" + signal.source;
            aggregate.opportunity.baseline = signal.baseline;
            aggregate.opportunity.current = signal.current;
            aggregate.opportunity.first_sequence = sequence;
        }
        aggregate.opportunity.current = signal.current;
        aggregate.opportunity.baseline = signal.baseline;
        ++aggregate.opportunity.evidence_count;
        aggregate.opportunity.last_sequence = sequence;
        aggregate.weighted_score += score * weight;
        aggregate.weight += weight;
    }

    std::vector<EvolutionOpportunity> result;
    for (auto& [_, aggregate] : aggregates) {
        if (aggregate.weight <= 0.0) continue;
        aggregate.opportunity.score = clamp_unit(aggregate.weighted_score / aggregate.weight);
        aggregate.opportunity.confidence = clamp_unit(
            static_cast<double>(aggregate.opportunity.evidence_count) /
            static_cast<double>(aggregate.opportunity.evidence_count + 1));
        if (aggregate.opportunity.score >= policy_.minimum_score) result.push_back(aggregate.opportunity);
    }

    std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
        if (left.score != right.score) return left.score > right.score;
        return left.id < right.id;
    });
    return result;
}

} // namespace jarvis::core
