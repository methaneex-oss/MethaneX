#include "jarvis/core/evolution_learning.hpp"

#include <algorithm>
#include <cmath>

namespace jarvis::core {

EvolutionFailureInsight EvolutionLearning::analyze_failures(
    const std::string& parameter_key, const EvolutionHistory& history) {
    EvolutionFailureInsight insight;
    insight.parameter_key = parameter_key;
    if (parameter_key.empty()) return insight;

    const auto records = history.for_parameter(parameter_key);
    double total_gain = 0.0;
    for (const auto& record : records) {
        const bool failed = record.outcome == ExperimentOutcome::Degraded ||
                            record.action == EvolutionRecordAction::Rejected ||
                            record.action == EvolutionRecordAction::RolledBack;
        if (!failed) continue;
        ++insight.failures;
        if (record.action == EvolutionRecordAction::RolledBack) ++insight.rollbacks;
        total_gain += record.candidate_fitness - record.baseline_fitness;
    }

    if (insight.failures > 0) {
        insight.average_failed_gain = total_gain / static_cast<double>(insight.failures);
        const double failure_rate = static_cast<double>(insight.failures) /
                                    static_cast<double>(std::max<std::size_t>(records.size(), 1));
        const double rollback_rate = static_cast<double>(insight.rollbacks) /
                                     static_cast<double>(insight.failures);
        insight.caution = std::clamp(0.65 * failure_rate + 0.35 * rollback_rate, 0.0, 1.0);
    }
    return insight;
}

} // namespace jarvis::core
